/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:36:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 02:52:42 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Command::Command() {
}


Command::Command(std::string name, std::vector<std::string> aliases) {
	this->name = name;
	setAliases(aliases);
}


Command::Command(const Command &command) {
	*this = command;
}


Command &Command::operator=(const Command &command) {
	if (this != &command) {
		name = command.name;
		setAliases(command.aliases);
	}
	return *this;
}


Command::~Command() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


std::string	Command::getName() {
	return name;
}


void	Command::setName(std::string name) {
	this->name = name;
}


std::vector<std::string>	Command::getAliases() {
	return aliases;
}


void	Command::setAliases(std::vector<std::string> aliases) {
	this->aliases = aliases;
	for (size_t i = 0; i < this->aliases.size(); i++) {
		if (this->aliases[i].empty()) {
			this->aliases.erase(this->aliases.begin() + i);
			i--;
		}
	}
}
