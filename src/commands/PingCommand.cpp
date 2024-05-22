/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 20:03:23 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PingCommand::PingCommand() : Command() {
}


PingCommand::PingCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


PingCommand::PingCommand(const PingCommand &command) : Command() {
	*this = command;
}


PingCommand &PingCommand::operator=(const PingCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


PingCommand::~PingCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PingCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) server;
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(ERR_NOORIGIN(client.getNick()));
		return false;
	}

	client.send("PONG " + client.getNick() + " :" + args[0]);
	return true;
}
