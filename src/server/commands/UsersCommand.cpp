/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsersCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 20:03:23 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


UsersCommand::UsersCommand() : Command() {
}


UsersCommand::UsersCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


UsersCommand::UsersCommand(const UsersCommand &command) : Command() {
	*this = command;
}


UsersCommand &UsersCommand::operator=(const UsersCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


UsersCommand::~UsersCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	UsersCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) argsCount;
	
	if (!client.isRegistered())
		return false;
	try {
		std::vector<Client> clients = server.getClients();
		if (clients.size() != 0) {
			for (size_t i = 0; i < clients.size(); i++) {
				client.send(server, clients[i].getNick());
			}
			client.send(server, RPL_ENDOFUSERS(client.getNick()));
		}
	} catch (std::exception &e) {
		return false;
	}
	return true;
}
