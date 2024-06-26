/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 02:57:02 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PassCommand::PassCommand() : Command() {
}


PassCommand::PassCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


PassCommand::PassCommand(const PassCommand &command) : Command() {
	*this = command;
}


PassCommand &PassCommand::operator=(const PassCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


PassCommand::~PassCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PassCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) server;
	(void) label;
	(void) prefix;

	if (client.isRegistered()
		|| !client.getNick().empty() || !client.getUsername().empty()) {
		client.send(server, ERR_ALREADYREGISTRED(client.getNick()));
		return false;
	}
	if (argsCount < 1) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}

	client.setPass(args[0]);
	return true;
}
