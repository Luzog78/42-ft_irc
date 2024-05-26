/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:44:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 05:33:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Bot::Bot() {
	connected = false;
	serverAddr = (struct sockaddr_in){};
	pollFd = (struct pollfd){};
}


Bot::Bot(const Bot &bot) {
	*this = bot;
}


Bot &Bot::operator=(const Bot &bot) {
	if (this != &bot) {
		ip = bot.ip;
		port = bot.port;
		password = bot.password;
	}
	return *this;
}


Bot::~Bot() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


void	Bot::start(std::string ip, int port, std::string password) {
	this->ip = ip;
	this->port = port;
	this->password = password;

	if (port < 1024 || port > 65535)
		throw BotException("Illegal port number (port: " + itoa(port) + ")");

	clientSckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSckt < 0)
		throw BotException("Socket creation failed");

	if (fcntl(clientSckt, F_SETFL, O_NONBLOCK) < 0)
		throw BotException("fcntl failed");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0)
		throw BotException("IP address not supported (" + ip + ")");
	connect(clientSckt, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	// connect will return -1 and set errno to EINPROGRESS
	//  because the connection is in progress. We will check
	//  the connection status in poll() function.
}


void	Bot::close() {
	// TODO
	exit(0);
}


void	Bot::poll() {
	pollFd.fd = clientSckt;
	pollFd.events = connected ? POLLIN | POLLOUT : POLLOUT;

	if (::poll(&pollFd, 1, 0) < 0)
		throw BotException("Poll failed");

	if (connected)
		receive();
	else if (pollFd.revents & (POLLHUP | POLLNVAL) || pollFd.revents & POLLERR)
		throw BotException("Connection failed (" + ip + ":" + itoa(port) + ")");
	else if (pollFd.revents & POLLOUT) {
		connected = true;
		log(INFO, "Connected to " + ip + ":" + itoa(port));
		send("PASS :" + password);
		send("NICK :bot");
		send("USER bot 0 * :bot");
		send("JOIN #bot");
	}
}


void	Bot::receive() {
	if (pollFd.revents & POLLIN) {
		char	buffer[1025];
		int		ret = recv(clientSckt, buffer, 1024, 0);

		if (ret < 0)
			return;

		if (ret == 0) {
			log(INFO, "XXX | Server disconnected", C_MAGENTA);
			close(); // TODO
		}

		buffer[ret] = 0;
		cmdBuffer += std::string(buffer);
		if (cmdBuffer.find("\n") == std::string::npos)
			return;

		std::istringstream	ss(cmdBuffer);
		cmdBuffer = "";
		for (std::string line; std::getline(ss, line, '\n');) {
			if (line.find("\n") != std::string::npos) {
				cmdBuffer = line;
				break;
			}
			log(INFO, "<-- | " + line, C_CYAN);
			// commandManager.exec(*this, client, line);  // TODO
		}
	}
}


void	Bot::send(std::string command) {
	ssize_t		ret;
	std::string	finalCommand = command + "\n";

	ret = ::send(clientSckt, finalCommand.c_str(), finalCommand.length(), 0);
	if (ret < 0)
		throw BotException("Send failed");
	if (ret != (ssize_t) finalCommand.length())
		throw BotException("Only " + itoa(ret)
			+ " bytes sent out of " + itoa(finalCommand.length()));
	log(INFO, "--> | " + command, C_GREEN);
}


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


std::string	Bot::getIp() {
	return ip;
}


int	Bot::getPort() {
	return port;
}


std::string	Bot::getPassword() {
	return password;
}


bool	Bot::isConnected() {
	return connected;
}
