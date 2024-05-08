/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:05:38 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


NickCommand::NickCommand() : Command() {
}


NickCommand::NickCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


NickCommand::NickCommand(const NickCommand &command) : Command() {
	*this = command;
}


NickCommand &NickCommand::operator=(const NickCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


NickCommand::~NickCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	NickCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (argsCount == 0) {
		client.sendCommand(ERR_NONICKNAMEGIVEN);
		return false;
	}

	std::vector<std::string>	nicknames = server.getNicknames();
	if (find(nicknames.begin(), nicknames.end(), args[0]) != nicknames.end()) {
		client.sendCommand(ERR_NICKNAMEINUSE(args[0]));
		return false;
	}

	client.setNickname(args[0]);

	if (!client.getUsername().empty() && !client.getRealname().empty()
		&& !client.isRegistered())
		server.welcome(client);
	return true;
}
