/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:53:15 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 11:53:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Executor::Executor() {
}


Executor::Executor(std::string name, std::vector<std::string> aliases) {
	this->name = name;
	setAliases(aliases);
}


Executor::Executor(const Executor &command) {
	*this = command;
}


Executor &Executor::operator=(const Executor &command) {
	if (this != &command) {
		name = command.name;
		setAliases(command.aliases);
	}
	return *this;
}


Executor::~Executor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


std::string	Executor::getName() {
	return name;
}


void	Executor::setName(std::string name) {
	this->name = name;
}


std::vector<std::string>	Executor::getAliases() {
	return aliases;
}


void	Executor::setAliases(std::vector<std::string> aliases) {
	this->aliases = aliases;
	for (size_t i = 0; i < this->aliases.size(); i++) {
		if (this->aliases[i].empty()) {
			this->aliases.erase(this->aliases.begin() + i);
			i--;
		}
	}
}
