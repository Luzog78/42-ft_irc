/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 03:23:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


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


static std::vector<std::string>	splitTargets(std::string rawTargets) {
	std::vector<std::string>	targetNames;
	size_t						pos = 0;

	while ((pos = rawTargets.find(",")) != std::string::npos) {
		if (!rawTargets.substr(0, pos).empty())
			targetNames.push_back(rawTargets.substr(0, pos));
		rawTargets.erase(0, pos + 1);
	}
	if (!rawTargets.empty())
		targetNames.push_back(rawTargets);
	return targetNames;
}


bool	ListCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;

	std::vector<Channel>	channels;

	if (argsCount == 0) {
		channels = server.getChannels();
	} else {
		std::vector<std::string>	channelNames = splitTargets(args[0]);
		for (size_t i = 0; i < channelNames.size(); i++)
			try {
				channels.push_back(server.getChannelByName(channelNames[i]));
			} catch (IRCException &e) {
				client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), channelNames[i]));
			}
	}
	
	client.send(server, RPL_LISTSTART(client.getNick()));
	for (size_t i = 0; i < channels.size(); i++)
		client.send(server, RPL_LIST(client.getNick(), channels[i].getName(),
			itoa(channels[i].getOnlineClients(server).size()),
			channels[i].getTopic()));
	client.send(server, RPL_LISTEND(client.getNick()));
	return true;
}
