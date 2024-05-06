/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:57:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 20:22:38 by ysabik           ###   ########.fr       */
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
		pollfds = server.pollfds;
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
		throw ServerException("Bind failed");

	if (listen(sckt, maxClients) < 0)
		throw ServerException("Listen failed");

	log(INFO, "##############################");
	log(INFO, "## >>> Server started ! <<< ##");
	log(INFO, "##############################\n");
}


void	Server::accept() {
	pollfd	pollResult;

	pollResult.fd = sckt;
	pollResult.events = POLLIN;
	pollResult.revents = 0;

	int ret = ::poll(&pollResult, 1, 0);
	if (ret < 0)
		throw ServerException("Accepting poll failed");
		
	if (ret > 0 &&pollResult.revents & POLLIN) {
		struct sockaddr_in	clientAddr;
		socklen_t			clientAddrLen = sizeof(clientAddr);

		int	clientSocket = ::accept(sckt, (struct sockaddr*) &clientAddr, &clientAddrLen);
		if (clientSocket < 0)
			throw ServerException("Accept failed");

		if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
			throw ServerException("fcntl failed (new client, fd: " + itoa(clientSocket)
				+ ", ip: " + inet_ntoa(clientAddr.sin_addr) + ")");
		
		Client	newClient(clientSocket, clientAddr);
		clients[clientSocket] = newClient;

		log(INFO, "<" + newClient.getFullAddress() + "> : Connected");

		pollfd	newPollfd;
		newPollfd.fd = clientSocket;
		newPollfd.events = POLLIN | POLLOUT;
		pollfds.push_back(newPollfd);
	}
}


void	Server::poll() {
	int pollResult = ::poll(pollfds.data(), pollfds.size(), 0);
	if (pollResult < 0)
		throw ServerException("Poll failed");

	if (pollResult == 0)
		return;

	for (size_t i = 0; i < pollfds.size(); i++) {
		Client	client = clients[pollfds[i].fd];
		pollfd	pollfd = pollfds[i];
		
		if (pollfd.revents & POLLIN) {
			char	buffer[1025];
			int		ret = recv(pollfd.fd, buffer, 1024, 0);

			if (ret < 0)
				throw ServerException("Receive failed from " + client.getFullAddress());

			if (ret == 0) {
				log(INFO, "<" + client.getFullAddress() + "> : Disconnected");
				client.close();
				clients.erase(pollfd.fd);
				pollfds.erase(pollfds.begin() + i);
				continue;
			}

			buffer[ret] = 0;
			log(INFO, "<" + client.getFullAddress() + "> : Received: ");
			log(DATA, std::string(buffer));
		}

		// if (pollfd.revents & POLLOUT) {
		// 	// Send data
		// 	std::string message = "Hello from server!";
		// 	int ret = send(pollfd.fd, message.c_str(), message.size(), 0);
		// 	if (ret < 0)
		// 		throw ServerException("Send failed to " + client.getFullAddress());
		// 	log(INFO, "Sent: " + message + " to " + client.getFullAddress());
		// }
	}
}


void	Server::close() {
	if (sckt >= 0) {
		log(INFO, "Closing <" + getFullAddress() + ">...");
		::close(sckt);
	}
	sckt = -1;
	for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
		it->second.close();
}


std::string	Server::getFullAddress() {
	return std::string(inet_ntoa(addr.sin_addr)) + ":" + itoa(ntohs(addr.sin_port)) + "/" + itoa(sckt);
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


std::map<int, Client>	Server::getClients() {
	return clients;
}


void	Server::setClients(std::map<int, Client> clients) {
	this->clients = clients;
}


std::vector<pollfd>	Server::getPollfds() {
	return pollfds;
}


void	Server::setPollfds(std::vector<pollfd> pollfds) {
	this->pollfds = pollfds;
}
