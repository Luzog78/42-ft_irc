/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 11:15:25 by ysabik           ###   ########.fr       */
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
	(void) server;
	(void) label;
	(void) prefix;
	(void) args;
	(void) argsCount;

	if (argsCount < 4) {
		log(WARNING, "UserCommand: not enough arguments");
		return false;
	}

	client.setUsername(args[0]);
	client.setRealname(args[3]);
	if (client.getNickname().empty())
		client.setNickname("user" + itoa(client.getPort()));

	client.sendCommand("CAP * LS :");
	client.sendCommand("001 " + client.getNickname() + " :Weeelcoooooooooome to ft_irc !");
	client.sendCommand("003 " + client.getNickname() + " :This server was created sometime");

	return true;
}
