/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:36:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 10:38:30 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Command::Command() {
}


Command::Command(std::string name, std::vector<std::string> aliases) {
	this->name = name;
	this->aliases = aliases;
}


Command::Command(const Command &command) {
	*this = command;
}


Command &Command::operator=(const Command &command) {
	if (this != &command) {
		name = command.name;
		aliases = command.aliases;
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
}
