/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 19:54:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PartCommand::PartCommand() : Command() {
}


PartCommand::PartCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


PartCommand::PartCommand(const PartCommand &command) : Command() {
	*this = command;
}


PartCommand &PartCommand::operator=(const PartCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


PartCommand::~PartCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


static std::vector<std::string>		split(std::string raw) {
	std::vector<std::string>	list;
	std::string					sub;
	size_t						pos = 0;

	while ((pos = raw.find(",")) != std::string::npos) {
		sub = raw.substr(0, pos);
		list.push_back(sub);
		raw.erase(0, pos + 1);
	}
	list.push_back(raw);
	return list;
}


bool	PartCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}

	std::vector<std::string>	channelNames = split(args[0]);
	std::string					reason = argsCount > 1 ? " :" + args[1] : "";

	for (size_t i = 0; i < channelNames.size(); i++) {
		if (channelNames[i].empty())
			continue;
		try {
			Channel	&channel = server.getChannelByName(channelNames[i]);

			if (!channel.isMember(client.getSocket())) {
				client.send(server, ERR_NOTONCHANNEL(client.getNick(), channelNames[i]));
				continue;
			}
			channel.broadcast(server,
				name + " " + channel.getName() + reason, client.getPrefix());
			channel.removeMember(client.getSocket());
			if (channel.getMembers().empty())
				server.removeChannel(channel.getName());
			client.removeChannel(channel.getName());
		} catch (Server::ServerException &e) {
			client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), channelNames[i]));
		}
	}

	return true;
}
