/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 21:30:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


NamesCommand::NamesCommand() : Command() {
}


NamesCommand::NamesCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


NamesCommand::NamesCommand(const NamesCommand &command) : Command() {
	*this = command;
}


NamesCommand &NamesCommand::operator=(const NamesCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


NamesCommand::~NamesCommand() {
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

bool	NamesCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) server;
	(void) label;
	(void) prefix;

	if (argsCount == 0) {
		std::vector<Channel> channels = server.getChannels();
		client.send(RPL_ENDOFNAMES(client.getNick(), ""));
		return true;
	}
	std::vector<std::string> channels = split(args[1]);

	for (size_t i = 0; i < channels.size(); i++) {
		try {
			Channel	&channel = server.getChannelByName(channels[i]);
			client.send(RPL_NAMREPLY(client.getNick(), channel.getName(), channel.getMemberNicks()));
			client.send(RPL_ENDOFNAMES(client.getNick(), channel.getName()));
		} catch (std::exception &e) {
			client.send(ERR_NOSUCHCHANNEL(client.getNick(), channels[i]));
			continue ;
		}

	}
	return true;
}
