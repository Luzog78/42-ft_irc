/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 17:38:08 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


ListCommand::ListCommand() : Command() {
}


ListCommand::ListCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


ListCommand::ListCommand(const ListCommand &command) : Command() {
	*this = command;
}


ListCommand &ListCommand::operator=(const ListCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


ListCommand::~ListCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	ListCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;
	(void) server;
	(void) args;

	if (argsCount == 0) {
		std::vector<Channel> channels = server.getChannels();
		for (size_t i = 0; i < channels.size(); i++) {
			try {
				client.send(channels[i].getName() + " topic: " + channels[i].getTopic());
			} catch (std::exception &e) {
				client.send(ERR_NOSUCHCHANNEL(client.getNick(), channels[i].getName()));
			}
		}
		return true;
	}
	client.send("List command called");
	return true;
}
