/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 00:14:32 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


KickCommand::KickCommand() : Command() {
}


KickCommand::KickCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


KickCommand::KickCommand(const KickCommand &command) : Command() {
	*this = command;
}


KickCommand &KickCommand::operator=(const KickCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


KickCommand::~KickCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	KickCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount < 2) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}

	try {
		Channel	&channel = server.getChannelByName(args[0]);

		if (!channel.isMember(client.getSocket())) {
			client.send(server, ERR_NOTONCHANNEL(client.getNick(), channel.getName()));
			return false;
		}
		if (!channel.isOperator(client.getFullAddress())) {
			client.send(server, ERR_CHANOPRIVSNEEDED(client.getNick(), channel.getName()));
			return false;
		}
		try {
			Client		&target = server.getClientByNickname(args[1]);
			std::string	quitMessage = argsCount > 2 ? args[2]
				: "Got kicked by @" + client.getNick() + "... :/";

			if (!channel.isMember(target.getSocket())) {
				client.send(server, ERR_USERNOTINCHANNEL(client.getNick(),
					target.getNick(), channel.getName()));
				return false;
			}
			channel.broadcast(server,
				name + " " + channel.getName() + " " + target.getNick()
				+ " :" + quitMessage, client.getPrefix());
			channel.removeMember(client.getSocket());
			if (channel.getMembers().empty())
				server.removeChannel(channel.getName());
			client.removeChannel(channel.getName());
		} catch (std::exception &e) {
			client.send(server, ERR_NOSUCHNICK(client.getNick(), args[1]));
			return false;
		}
	} catch (std::exception &e) {
		client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), args[0]));
		return false;
	}
	return true;
}
