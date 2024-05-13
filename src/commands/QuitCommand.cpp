/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/13 15:02:44 by ysabik           ###   ########.fr       */
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

	if (!client.isRegistered())
		return false;

	std::string	quitMessage = argsCount > 0 ? args[0] : "Got bored... -_-";

	std::vector<Client> clients = server.getClients();
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if (it->getSocket() == client.getSocket())
			continue;
		it->sendCommand(name + " :" + quitMessage, client.getPrefix());
	}

	server.removeClient(client);
	return true;
}
