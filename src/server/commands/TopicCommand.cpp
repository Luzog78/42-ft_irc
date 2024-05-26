/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                    :+:      :+:    :+:   */
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


TopicCommand::TopicCommand() : Command() {
}


TopicCommand::TopicCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


TopicCommand::TopicCommand(const TopicCommand &command) : Command() {
	*this = command;
}


TopicCommand &TopicCommand::operator=(const TopicCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


TopicCommand::~TopicCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	TopicCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), "TOPIC"));
		return false;
	}

	try {
		Channel	&channel = server.getChannelByName(args[0]);

		if (argsCount == 1) {
			if (channel.getTopic().empty())
				client.send(server, RPL_NOTOPIC(client.getNick(), channel.getName()));
			else
				client.send(server, RPL_TOPIC(client.getNick(), channel.getName(), channel.getTopic()));
		} else {
			if (!channel.isMember(client.getSocket())) {
				client.send(server, ERR_NOTONCHANNEL(client.getNick(), channel.getName()));
				return false;
			}
			if (!channel.isOperator(client.getFullAddress())
				&& channel.isTopicRestricted()) {
				client.send(server, ERR_CHANOPRIVSNEEDED(client.getNick(), channel.getName()));
				return false;
			}
			if (args[1] != channel.getTopic()) {
				channel.setTopic(args[1]);
				channel.broadcast(server,
					name + " " + channel.getName() + " :" + args[1],
					client.getPrefix());
			}
		}
	} catch (std::exception &e) {
		client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), args[0]));
		return false;
	}

	return true;
}
