/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:59:23 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 11:02:09 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Client::Client() {
	sckt = -1;
	addr = (struct sockaddr_in){};
	ip = "";
	port = 0;
	pollFd = (pollfd){};
}


Client::Client(int sckt, struct sockaddr_in addr) {
	this->sckt = sckt;
	this->addr = addr;
	this->ip = inet_ntoa(addr.sin_addr);
	this->port = ntohs(addr.sin_port);
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
		nickname = client.nickname;
		username = client.username;
		realname = client.realname;
		channels = client.channels;
	}
	return *this;
}


Client::~Client() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


void	Client::close() {
	if (sckt >= 0) {
		log(INFO, "Closing <" + getFullAddress() + ">...");
		::close(sckt);
	}
	sckt = -1;
}


std::string	Client::getFullAddress() {
	return ip + ":" + itoa(port) + "/" + itoa(sckt);
}


void	Client::sendCommand(std::string command) {
	if (sckt < 0)
		throw ClientException("Socket is not connected");
	if (!(pollFd.revents & POLLOUT))
		throw ClientException("Socket is not ready to send data");

	log(INFO, "(S) <" + getFullAddress() + ">: " + command, C_GREEN);

	std::string	finalCmd = ":" + getIp() + " " + command + "\n";
	if (send(sckt, finalCmd.c_str(), finalCmd.length(), 0) < 0)
		throw ClientException("Send command '" + finalCmd + "' to <" + getFullAddress() + "> failed");
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


std::string	Client::getNickname() {
	return nickname;
}


void	Client::setNickname(std::string nickname) {
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
