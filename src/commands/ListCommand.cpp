/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 13:01:53 by kbutor-b         ###   ########.fr       */
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

// static std::vector<std::string>		splitTargets(std::string rawTargets) {
// 	std::vector<std::string>	targetNames;
// 	size_t						pos = 0;

// 	while ((pos = rawTargets.find(",")) != std::string::npos) {
// 		if (!rawTargets.substr(0, pos).empty())
// 			targetNames.push_back(rawTargets.substr(0, pos));
// 		rawTargets.erase(0, pos + 1);
// 	}
// 	if (!rawTargets.empty())
// 		targetNames.push_back(rawTargets);
// 	return targetNames;
// }

static std::vector<std::string>		split(const std::string raw) {
	std::vector<std::string>	list;
	std::string					sub;
	size_t						pos = 0;
	size_t						start = 0;

	while ((pos = raw.find(",", start)) != std::string::npos) {
		sub = raw.substr(start, pos - start);
		list.push_back(sub);
		start = pos + 1;
	}
	list.push_back(raw.substr(start));
	return list;
}

bool	ListCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (argsCount == 0) {
		std::vector<std::string> channelNames;
		std::vector<Channel> channels = server.getChannels();
		for (size_t i = 0; i < channels.size(); i++) {
			channelNames.push_back(channels[i].getName());
		}
		for (size_t i = 0; i < channelNames.size(); i++) {
			try {
				Channel &channel = server.getChannelByName(channelNames[i]);
				client.send(channel.getName() + ": " + channel.getTopic());
			} catch (std::exception &e) {
				client.send(ERR_NOSUCHCHANNEL(client.getNick(), channelNames[i]));
			}
		}
		return true;
	}
	// client.send(args[1]);
	std::vector<std::string> channels = split(args[1]);
	// for (size_t i = 0; i < channels.size(); i++) {
	// 	client.send("channels >" + channels[i]);
	// }
	for (size_t i = 0; i < channels.size(); i++) {
		try {
			Channel	&channel = server.getChannelByName(channels[i]);
			client.send(channel.getName() + ": " + channel.getTopic());
		} catch (std::exception &e) {
			client.send(ERR_NOSUCHCHANNEL(client.getNick(), channels[i]));
		}
	}
	return true;
}
