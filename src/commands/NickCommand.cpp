/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 19:54:38 by ysabik           ###   ########.fr       */
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
		client.send(server, ERR_NONICKNAMEGIVEN(client.getNick()));
		return false;
	}
	if (!Client::isLegalNickname(args[0])) {
		client.send(server, ERR_ERRONEUSNICKNAME(client.getNick(), args[0]));
		return false;
	}

	try {
		server.getClientByNickname(args[0]);
		client.send(server, ERR_NICKNAMEINUSE(client.getNick(), args[0]));
		return false;
	} catch (Server::ServerException &ignored) {
	}

	if (client.isRegistered()) {
		std::vector<Client> clients = server.getClients();
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); it++)
			it->send(name + " " + args[0], client.getPrefix());
	}

	client.setNick(args[0]);

	if (!client.getUsername().empty() && !client.getRealname().empty()
		&& !client.isRegistered())
		server.welcome(client);
	return true;
}
