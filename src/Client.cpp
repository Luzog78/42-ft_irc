/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:59:23 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 20:22:52 by ysabik           ###   ########.fr       */
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


void	Client::setAddr(struct sockaddr_in addr) {
	this->addr = addr;
	this->ip = inet_ntoa(addr.sin_addr);
	this->port = ntohs(addr.sin_port);
}


struct sockaddr_in	*Client::getAddrPtr() {
	return &addr;
}
