/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:25:59 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


QuitCommand::QuitCommand() : Command() {
}


QuitCommand::QuitCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


QuitCommand::QuitCommand(const QuitCommand &command) : Command() {
	*this = command;
}


QuitCommand &QuitCommand::operator=(const QuitCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


QuitCommand::~QuitCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	QuitCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	std::string	quitMessage = argsCount > 0 ? args[0] : "Got bored... -_-";

	for (std::vector<Client>::iterator it = server.getClients().begin(); it != server.getClients().end(); it++) {
		if (it->getNickname() == client.getNickname())
			continue;
		it->sendCommand("QUIT :" + quitMessage, client.getPrefix());
	}

	server.removeClient(client);
	return true;
}
