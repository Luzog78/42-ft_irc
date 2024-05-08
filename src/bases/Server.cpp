/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:57:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:27:02 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Server::Server() {
	port = 0;
	maxClients = 0;
	sckt = -1;
	addr = (struct sockaddr_in){};
	acceptPoll = (pollfd){};
}


Server::Server(const Server &server) {
	*this = server;
}


Server &Server::operator=(const Server &server) {
	if (this != &server) {
		port = server.port;
		maxClients = server.maxClients;
		sckt = server.sckt;
		addr = server.addr;
		clients = server.clients;
		channels = server.channels;
		cmdBuffer = server.cmdBuffer;
		acceptPoll = server.acceptPoll;
	}
	return *this;
}


Server::~Server() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


void	Server::start(int port, int maxClients) {
	this->port = port;
	this->maxClients = maxClients;
	
	sckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sckt < 0)
		throw ServerException("Socket creation failed");

	if (fcntl(sckt, F_SETFL, O_NONBLOCK) < 0)
		throw ServerException("fcntl failed");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sckt, (struct sockaddr*) &addr, sizeof(addr)) < 0)
		throw ServerException("Bind failed (port: " + itoa(port) + ")");

	if (listen(sckt, maxClients) < 0)
		throw ServerException("Listen failed");

	log(INFO, "##############################");
	log(INFO, "## >>> Server started ! <<< ##");
	log(INFO, "##############################\n\n");
}


void	Server::poll() {
	acceptPoll.fd = sckt;
	acceptPoll.events = POLLIN;
	acceptPoll.revents = 0;
	_pollfds.push_back(acceptPoll);

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		_pollfds.push_back(it->getPollFd());

	int	pollResult = ::poll(_pollfds.data(), _pollfds.size(), 0);
	if (pollResult < 0)
		throw ServerException("Poll failed");
	
	acceptPoll = _pollfds[0];
	for (size_t i = 1; i < _pollfds.size(); i++) {
		clients[i - 1].setPollFd(_pollfds[i]);
	}
	_pollfds.clear();
}


void	Server::accept() {
	if (acceptPoll.revents & POLLIN) {
		struct sockaddr_in	clientAddr;
		socklen_t			clientAddrLen = sizeof(clientAddr);

		int	clientSocket = ::accept(sckt, (struct sockaddr*) &clientAddr, &clientAddrLen);
		if (clientSocket < 0)
			throw ServerException("Accept failed");

		if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
			throw ServerException("fcntl failed (new client, fd: " + itoa(clientSocket)
				+ ", ip: " + inet_ntoa(clientAddr.sin_addr) + ")");
		
		Client	newClient(clientSocket, clientAddr);

		log(INFO, "<" + newClient.getFullAddress() + ">: Connected");

		pollfd	newPollfd;
		newPollfd.fd = clientSocket;
		newPollfd.events = POLLIN | POLLOUT;
		newPollfd.revents = 0;
		newClient.setPollFd(newPollfd);
		clients.push_back(newClient);
	}
}


void	Server::receive() {
	for (size_t i = 0; i < clients.size(); i++) {
		Client	&client = clients[i];
		
		if (client.getPollFd().revents & POLLIN) {
			char	buffer[1025];
			int		ret = recv(client.getSocket(), buffer, 1024, 0);

			if (ret < 0)
				throw ServerException("Receive failed from " + client.getFullAddress());

			if (ret == 0) {
				log(INFO, "<" + client.getFullAddress() + ">: Disconnected");
				client.close();
				clients.erase(clients.begin() + i);
				continue;
			}

			buffer[ret] = 0;
			cmdBuffer += std::string(buffer);
			if (cmdBuffer.find("\n") == std::string::npos)
				continue;

			std::istringstream	ss(cmdBuffer);
			cmdBuffer = "";
			for (std::string line; std::getline(ss, line, '\n');) {
				if (line.find("\n") != std::string::npos) {
					cmdBuffer = line;
					break;
				}
				log(INFO, "(R) <" + client.getFullAddress() + ">: " + line, C_CYAN);
				commandManager.exec(*this, client, line);
			}
		}
	}
}


void	Server::welcome(Client &client) {
	client.setRegistered(true);
	client.sendCommand("CAP * LS :");
	client.sendCommand(RPL_WELCOME(client.getNickname()));
	client.sendCommand(RPL_YOURHOST(client.getNickname(), std::string("localhost"), "1.0"));
	client.sendCommand(RPL_CREATED(client.getNickname(), std::string("once upon a time...")));
}


void	Server::removeClient(Client &client) {
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->getSocket() == client.getSocket()) {
			clients.erase(it);
			break;
		}
	}
}


void	Server::close() {
	if (sckt >= 0) {
		log(INFO, "Closing <" + getFullAddress() + ">...");
		::close(sckt);
	}
	sckt = -1;
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		it->close();
}


std::string	Server::getFullAddress() {
	return std::string(inet_ntoa(addr.sin_addr)) + ":" + itoa(ntohs(addr.sin_port)) + "/" + itoa(sckt);
}


std::vector<std::string>	Server::getNicknames() {
	std::vector<std::string>	nicknames;

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		nicknames.push_back(it->getNickname());
	return nicknames;
}


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


int	Server::getPort() {
	return port;
}


int	Server::getMaxClients() {
	return maxClients;
}


int	Server::getSocket() {
	return sckt;
}


void	Server::setSocket(int sckt) {
	this->sckt = sckt;
}


struct sockaddr_in	Server::getAddr() {
	return addr;
}


void	Server::setAddr(struct sockaddr_in addr) {
	this->addr = addr;
}


struct sockaddr_in	*Server::getAddrPtr() {
	return &addr;
}


std::vector<Client>	Server::getClients() {
	return clients;
}


void	Server::setClients(std::vector<Client> clients) {
	this->clients = clients;
}


std::vector<Channel>	Server::getChannels() {
	return channels;
}


void	Server::setChannels(std::vector<Channel> channels) {
	this->channels = channels;
}


pollfd	Server::getAcceptPoll() {
	return acceptPoll;
}


pollfd	*Server::getAcceptPollPtr() {
	return &acceptPoll;
}


void	Server::setAcceptPoll(pollfd acceptPoll) {
	this->acceptPoll = acceptPoll;
}


std::string	Server::getCmdBuffer() {
	return cmdBuffer;
}


void	Server::setCmdBuffer(std::string cmdBuffer) {
	this->cmdBuffer = cmdBuffer;
}
