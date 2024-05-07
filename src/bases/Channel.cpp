/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:50:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 09:29:46 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Channel::Channel() {
	name = "";
}


Channel::Channel(std::string name) {
	this->name = name;
}


Channel::Channel(const Channel &channel) {
	*this = channel;
}


Channel &Channel::operator=(const Channel &channel) {
	if (this != &channel) {
		name = channel.name;
		clients = channel.clients;
	}
	return *this;
}


Channel::~Channel() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


std::string	Channel::getName() {
	return name;
}


void	Channel::setName(std::string name) {
	this->name = name;
}


std::vector<int>	Channel::getClients() {
	return clients;
}


void	Channel::setClients(std::vector<int> clients) {
	this->clients = clients;
}
