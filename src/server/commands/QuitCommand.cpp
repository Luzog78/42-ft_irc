/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
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

	if (!client.isRegistered()) {
		server.removeClient(client);
		return true;
	}

	std::string					quitMessage = argsCount > 0 ? args[0] : "Got bored... -_-";
	std::vector<std::string>	channels = client.getChannels();

	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
		Channel	&channel = server.getChannelByName(*it);

		channel.removeMember(client.getSocket());
		channel.broadcast(server, name + " :" + quitMessage, client.getPrefix());
	}
	server.removeClient(client);
	return true;
}
