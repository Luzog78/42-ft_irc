/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
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


JoinCommand::JoinCommand() : Command() {
}


JoinCommand::JoinCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


JoinCommand::JoinCommand(const JoinCommand &command) : Command() {
	*this = command;
}


JoinCommand &JoinCommand::operator=(const JoinCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


JoinCommand::~JoinCommand() {
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


bool	JoinCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}

	std::vector<std::string>	channelNames = split(args[0]);
	std::vector<std::string>	keys = split(argsCount > 1 ? args[1] : "");

	for (size_t i = 0; i < channelNames.size(); i++) {
		if (channelNames[i].empty())
			continue;
		if (!Channel::isLegalName(channelNames[i])) {
			client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), channelNames[i]));
			continue;
		}
		try {
			std::string		channelName = channelNames[i];
			std::string		key = i < keys.size() ? keys[i] : "";
			Channel			&channel = server.getChannelByName(channelName);

			if (channel.isMember(client.getSocket())) {
				// ignore
			} else if (!channel.hasRight(client.getNick(), client.getFullAddress())) {
				client.send(server, ERR_INVITEONLYCHAN(client.getNick(), channel.getName()));
			} else if (channel.isFull()) {
				client.send(server, ERR_CHANNELISFULL(client.getNick(), channel.getName()));
			} else if (!channel.getKey().empty() && channel.getKey() != key) {
				client.send(server, ERR_BADCHANNELKEY(client.getNick(), channel.getName()));
			} else {
				channel.removeInvited(client.getNick());
				client.addChannel(channel.getName());
				channel.addMember(client.getSocket());
				channel.broadcast(server, name + " " + channel.getName(), client.getPrefix());
				if (channel.getTopic().empty())
					client.send(server, RPL_NOTOPIC(client.getNick(), channel.getName()));
				else
					client.send(server, RPL_TOPIC(client.getNick(), channel.getName(), channel.getTopic()));
				client.send(server, RPL_NAMREPLY(client.getNick(), channel.getName(), channel.getMemberNicks()));
				client.send(server, RPL_ENDOFNAMES(client.getNick(), channel.getName()));
			}
		} catch (Server::ServerException &e) {
			Channel		channel(channelNames[i]);
			std::string	newArgs[] = {channelNames[i]};

			channel.addOperator(client.getFullAddress());
			server.addChannel(channel);
			return exec(server, client, label, prefix, newArgs, 1);
		}
	}

	return true;
}
