/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
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


UserCommand::UserCommand() : Command() {
}


UserCommand::UserCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


UserCommand::UserCommand(const UserCommand &command) : Command() {
	*this = command;
}


UserCommand &UserCommand::operator=(const UserCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


UserCommand::~UserCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	UserCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (client.isRegistered()) {
		client.send(ERR_ALREADYREGISTRED(client.getNick()));
		return false;
	}
	if (argsCount < 4) {
		client.send(ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}

	client.setUsername(args[0]);
	client.setRealname(args[3]);

	if (!client.getNick().empty())
		server.welcome(client);
	return true;
}
