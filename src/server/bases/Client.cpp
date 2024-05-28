/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:59:23 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 12:41:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Client::Client() {
	sckt = -1;
	addr = (struct sockaddr_in){};
	ip = "";
	port = 0;
	pollFd = (pollfd){};
	registered = false;
}


Client::Client(int sckt, struct sockaddr_in addr) {
	this->sckt = sckt;
	this->addr = addr;
	this->ip = inet_ntoa(addr.sin_addr);
	this->port = ntohs(addr.sin_port);
	this->registered = false;
}


Client::Client(const Client &client) {
	*this = client;
}


Client &Client::operator=(const Client &client) {
	if (this != &client) {
		sckt = client.sckt;
		addr = client.addr;
		ip = client.ip;
		port = client.port;
		pollFd = client.pollFd;
		registered = client.registered;
		nickname = client.nickname;
		username = client.username;
		realname = client.realname;
		channels = client.channels;
		password = client.password;
	}
	return *this;
}


Client::~Client() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	Client::isLegalNickname(std::string name) {
	if (name.length() < 1 || name.size() > 9
		|| std::isdigit(name[0]) || name[0] == '-')
		return false;
	for (size_t i = 0; i < name.size(); i++)
		if (!std::isprint(name[i]) || std::isspace(name[i])
			|| (!std::isalnum(name[i]) && name[i] != '-'
				&& name[i] != '[' && name[i] != ']' && name[i] != '\\'
				&& name[i] != '_' && name[i] != '^' && name[i] != '{'
				&& name[i] != '|' && name[i] != '}' && name[i] != '`'))
			return false;
	return true;
}


bool	Client::isLegalUsername(std::string name) {
	if (name.length() < 1 || name.size() > 50)
		return false;
	for (size_t i = 0; i < name.size(); i++)
		if (!std::isprint(name[i]) || std::isspace(name[i])
			|| name[i] == ',' || name[i] == ':' || name[i] == '!'
			|| name[i] == '@' || name[i] == '*')
			return false;
	return true;
}


void	Client::close() {
	if (sckt >= 0) {
		log(INFO, "Closing <" + getLogPrefix() + ">...");
		::close(sckt);
	}
	sckt = -1;
}


std::string	Client::getFullAddress() {
	return ip + ":" + itoa(port) + "/" + itoa(sckt);
}


std::string	Client::getPrefix() {
	if (nickname.empty() || username.empty())
		return ip;
	return nickname + "!" + username + "@" + ip;
}


std::string	Client::getLogPrefix() {
	if (nickname.empty() || username.empty())
		return getFullAddress();
	return nickname + "!" + username + "@" + ip
			+ ":" + itoa(port) + "/" + itoa(sckt);
}


void	Client::send(Server &server, std::string command) {
	send(command, server.getHostname());
}


void	Client::send(std::string command, std::string prefix) {
	if (sckt < 0)
		throw ClientException("Socket is not connected");
	if (!(pollFd.revents & POLLOUT))
		throw ClientException("Socket is not ready to send data");

	std::string	finalCmd = ":" + prefix + " " + command + "\n";

	log(INFO, "(S) <" + getLogPrefix() + ">: " + finalCmd, C_GREEN);
	if (::send(sckt, finalCmd.c_str(), finalCmd.length(), 0) < 0)
		throw ClientException("Send command '" + finalCmd
			+ "' to <" + getLogPrefix() + "> failed");
}


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


std::string	Client::getIp() {
	return ip;
}


int	Client::getPort() {
	return port;
}


int	Client::getSocket() {
	return sckt;
}


void	Client::setSocket(int sckt) {
	this->sckt = sckt;
}


struct sockaddr_in	Client::getAddr() {
	return addr;
}


struct sockaddr_in	*Client::getAddrPtr() {
	return &addr;
}


void	Client::setAddr(struct sockaddr_in addr) {
	this->addr = addr;
	this->ip = inet_ntoa(addr.sin_addr);
	this->port = ntohs(addr.sin_port);
}


pollfd	Client::getPollFd() {
	return pollFd;
}


pollfd	*Client::getPollFdPtr() {
	return &pollFd;
}


void	Client::setPollFd(pollfd pollFd) {
	this->pollFd = pollFd;
}


bool	Client::isRegistered() {
	return registered;
}


void	Client::setRegistered(bool registered) {
	this->registered = registered;
}


std::string	Client::getNick() {
	return nickname;
}


void	Client::setNick(std::string nickname) {
	this->nickname = nickname;
}


std::string	Client::getUsername() {
	return username;
}


void	Client::setUsername(std::string username) {
	this->username = username;
}


std::string	Client::getRealname() {
	return realname;
}


void	Client::setRealname(std::string realname) {
	this->realname = realname;
}


std::string	Client::getPass() {
	return password;
}


void	Client::setPass(std::string password) {
	this->password = password;
}


std::vector<std::string>	Client::getChannels() {
	return channels;
}


void	Client::addChannel(std::string channel) {
	channels.push_back(channel);
}


void	Client::removeChannel(std::string channel) {
	std::vector<std::string>::iterator it = std::find(
		channels.begin(), channels.end(), channel);
	if (it != channels.end())
		channels.erase(it);
}


void	Client::setChannels(std::vector<std::string> channels) {
	this->channels = channels;
}


std::string	Client::getCommandBuffer() {
	return commandBuffer;
}


void	Client::setCommandBuffer(std::string commandBuffer) {
	this->commandBuffer = commandBuffer;
}
