/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 20:03:23 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


InviteCommand::InviteCommand() : Command() {
}


InviteCommand::InviteCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


InviteCommand::InviteCommand(const InviteCommand &command) : Command() {
	*this = command;
}


InviteCommand &InviteCommand::operator=(const InviteCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


InviteCommand::~InviteCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	InviteCommand::exec(Server &server, Client &client, std::string label,
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
		Channel &channel = server.getChannelByName(args[1]);

		if (!channel.isMember(client.getSocket())) {
			client.send(server, ERR_NOTONCHANNEL(client.getNick(), channel.getName()));
			return false;
		}
		if (!channel.isOperator(client.getFullAddress())) {
			client.send(server, ERR_CHANOPRIVSNEEDED(client.getNick(), channel.getName()));
			return false;
		}
		try {
			Client &invitee = server.getClientByNickname(args[0]);

			if (channel.isMember(invitee.getSocket())) {
				client.send(server, ERR_USERONCHANNEL(client.getNick(), invitee.getNick(), channel.getName()));
				return false;
			}
			if (!channel.isInvited(invitee.getNick())) {
				client.send(server, RPL_INVITING(client.getNick(), invitee.getNick(), channel.getName()));
				channel.broadcast(server, "NOTICE @" + channel.getName() + " :" + client.getNick() + " invited " + invitee.getNick() + " into the channel.");
				channel.addInvited(invitee.getNick());
				invitee.send(name + " " + invitee.getNick() + " " + channel.getName(), client.getPrefix());
			}
		} catch (Server::ServerException &e) {
			client.send(server, ERR_NOSUCHNICK(client.getNick(), args[1]));
			return false;
		}
	} catch (Server::ServerException &e) {
		client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), args[0]));
		return false;
	}

	return true;
}
