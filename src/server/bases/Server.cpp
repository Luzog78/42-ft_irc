/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:57:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 12:41:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


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
		acceptPoll = server.acceptPoll;
	}
	return *this;
}


Server::~Server() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	Server::isLegalHostname(std::string hostname) {
	std::string	s = "." + hostname + ".";
	
	if (hostname.empty() || hostname.length() > 63
		|| s.find("..") != std::string::npos
		|| s.find(".-") != std::string::npos
		|| s.find("-.") != std::string::npos)
		return false;
	for (size_t i = 0; i < hostname.length(); i++) {
		if (!isalnum(hostname[i]) && hostname[i] != '-' && hostname[i] != '.')
			return false;
	}
	return true;
}


bool	Server::isLegalPassword(std::string password) {
	if (password.length() > 256)
		return false;
	for (size_t i = 0; i < password.length(); i++) {
		if (!isprint(password[i]) || isspace(password[i]))
			return false;
	}
	return true;
}


void	Server::start(int port, int maxClients,
			std::string hostname, std::string password) {
	this->port = port;
	this->maxClients = maxClients;
	this->hostname = hostname;
	this->password = password;

	if (port < 1024 || port > 65535)
		throw ServerException("Illegal port number (port: " + itoa(port) + ")");

	if (!isLegalHostname(hostname))
		throw ServerException("Illegal hostname (hostname: '" + hostname + "')");

	if (!isLegalPassword(password))
		throw ServerException("Illegal password (password: '" + password + "')");

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
	log(INFO, "##############################");
	log(INFO, "\n");
	log(INFO, "> Hostname:    " + std::string(C_YELLOW) + hostname);
	log(INFO, "> Port:        " + std::string(C_YELLOW) + ":" + itoa(port));
	log(INFO, "> Max clients: " + std::string(C_BLUE) + itoa(maxClients));
	if (password.empty())
		log(INFO, "> Password:    " + std::string(C_RED) + "none");
	else
		log(INFO, "> Password:    " + std::string(C_GREEN) + password);
	log(INFO, "\n");
}


void	Server::poll() {
	acceptPoll.fd = sckt;
	acceptPoll.events = POLLIN;
	acceptPoll.revents = 0;
	_pollfds.push_back(acceptPoll);

	for (std::vector<Client>::iterator it = clients.begin();
			it != clients.end(); it++)
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

		int	clientSocket = ::accept(
				sckt, (struct sockaddr*) &clientAddr, &clientAddrLen);
		if (clientSocket < 0)
			throw ServerException("Accept failed");

		if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
			throw ServerException(
				"fcntl failed (new client, fd: " + itoa(clientSocket)
				+ ", ip: " + inet_ntoa(clientAddr.sin_addr) + ")");

		Client	newClient(clientSocket, clientAddr);

		log(INFO, "<" + newClient.getLogPrefix() + ">: Connected");

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
		Client		&client = clients[i];
		std::string	cmdBuffer = client.getCommandBuffer();

		if (client.getPollFd().revents & POLLIN) {
			char	buffer[1025];
			int		ret = recv(client.getSocket(), buffer, 1024, 0);

			if (ret < 0)
				throw ServerException("Receive failed from " + client.getFullAddress());

			if (ret == 0) {
				log(INFO, "(X) <" + client.getLogPrefix()
					+ ">: QUIT :Client disconnected", C_MAGENTA);
				commandManager.exec(*this, client, "QUIT :Client disconnected");
				continue;
			}

			buffer[ret] = 0;
			cmdBuffer += std::string(buffer);
			while (cmdBuffer.find("\n") != std::string::npos) {
				std::string	line = cmdBuffer.substr(0, cmdBuffer.find("\n"));

				cmdBuffer.erase(0, cmdBuffer.find("\n") + 1);
				log(INFO, "(R) <" + client.getLogPrefix() + ">: " + line, C_CYAN);
				commandManager.exec(*this, client, line);
			}
			client.setCommandBuffer(cmdBuffer);
		}
		if (client.getPollFd().revents & (POLLERR | POLLHUP | POLLNVAL)) {
			log(INFO, "(X) <" + client.getLogPrefix()
				+ ">: QUIT :Client disconnected", C_MAGENTA);
			commandManager.exec(*this, client, "QUIT :Client disconnected");
		}
	}
}


void	Server::welcome(Client &client) {
	if (!password.empty() && client.getPass() != password) {
		client.send(server, ERR_PASSWDMISMATCH(client.getNick()));
		removeClient(client);
		return;
	}
	client.setRegistered(true);
	client.send(server, RPL_WELCOME(client.getNick()));
	client.send(server, RPL_YOURHOST(client.getNick(), hostname, "1.0"));
	client.send(server, RPL_CREATED(client.getNick(), std::string("once upon a time...")));
}


void	Server::removeClient(Client &client) {
	log(INFO, "<" + client.getLogPrefix() + ">: Disconnected");
	client.close();
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
	return std::string(inet_ntoa(addr.sin_addr))
		+ ":" + itoa(ntohs(addr.sin_port)) + "/" + itoa(sckt);
}


std::vector<std::string>	Server::getNicknames() {
	std::vector<std::string>	nicknames;

	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		nicknames.push_back(it->getNick());
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


std::string	Server::getHostname() {
	return hostname;
}


std::string	Server::getPassword() {
	return password;
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


Client	&Server::getClientBySocket(int sckt) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i].getSocket() == sckt)
			return clients[i];
	}
	throw ServerException("Client not found (socket: " + itoa(sckt) + ")");
}


Client	&Server::getClientByAddress(std::string addr) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i].getFullAddress() == addr)
			return clients[i];
	}
	throw ServerException("Client not found (address: " + addr + ")");
}


Client	&Server::getClientByNickname(std::string nickname) {
	std::transform(nickname.begin(), nickname.end(), nickname.begin(), ::tolower);
	for (size_t i = 0; i < clients.size(); i++)
		if (clients[i].getNick().length() == nickname.length()) {
			std::string	clientNickname = clients[i].getNick();
			std::transform(clientNickname.begin(), clientNickname.end(),
				clientNickname.begin(), ::tolower);
			if (clientNickname == nickname)
				return clients[i];
		}
	throw ServerException("Client not found (nickname: " + nickname + ")");
}


void	Server::setClients(std::vector<Client> clients) {
	this->clients = clients;
}


std::vector<Channel>	Server::getChannels() {
	return channels;
}


Channel	&Server::getChannelByName(std::string name) {
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (size_t i = 0; i < channels.size(); i++)
		if (channels[i].getName().length() == name.length()) {
			std::string	channelName = channels[i].getName();
			std::transform(channelName.begin(), channelName.end(),
				channelName.begin(), ::tolower);
			if (channelName == name)
				return channels[i];
		}
	throw ServerException("Channel not found (name: " + name + ")");
}


void	Server::addChannel(Channel channel) {
	channels.push_back(channel);
}


void	Server::removeChannel(std::string name) {
	for (std::vector<Channel>::iterator it = channels.begin();
			it != channels.end(); it++) {
		if (it->getName() == name) {
			channels.erase(it);
			return;
		}
	}
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
