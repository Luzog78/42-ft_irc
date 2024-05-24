/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 13:08:36 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


ModeCommand::ModeCommand() : Command() {
}


ModeCommand::ModeCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


ModeCommand::ModeCommand(const ModeCommand &command) : Command() {
	*this = command;
}


ModeCommand &ModeCommand::operator=(const ModeCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


ModeCommand::~ModeCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


static size_t	atou(const char *str) {
	const size_t	INT_MAX_10 = 2147483647 / 10;
	size_t			res = 0;

	while (*str >= '0' && *str <= '9') {
		if (res > INT_MAX_10)
			return 1;
		res = res * 10 + *str - '0';
		str++;
	}
	if (*str)
		return 1;
	return res;
}


bool	ModeCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) server;
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}
	try {
		Channel	&channel = server.getChannelByName(args[0]);
		bool	isMaster = channel.getOwner() == client.getFullAddress()
							|| channel.isOperator(client.getFullAddress());

		if (argsCount == 1) {
			std::string	mode = "+";

			if (channel.isInviteOnly())
				mode += "i";
			if (!channel.getKey().empty())
				mode += "k";
			if (channel.isLimited())
				mode += "l";
			if (channel.isTopicRestricted())
				mode += "t";
			if (!channel.getKey().empty() && channel.isMember(client.getSocket()))
				mode += " " + channel.getKey();
			if (channel.isLimited() && channel.isMember(client.getSocket()))
				mode += " " + itoa(channel.getLimit());
			client.send(RPL_CHANNELMODEIS(client.getNick(), channel.getName(), mode));
		} else if (!isMaster) {
			client.send(ERR_CHANOPRIVSNEEDED(client.getNick(), channel.getName()));
			return false;
		} else {
			bool	grant = args[1].empty() || args[1][0] != '-';
			char	grantChar = grant ? '+' : '-';

			for (size_t i = args[1][0] == '+' || args[1][0] == '-'; i < args[1].length(); i++)
				if (args[1][i] == 'i') {
					if (channel.isInviteOnly() == grant)
						continue;
					channel.setInviteOnly(grant);
					channel.broadcast(server,
						name + " " + channel.getName() + " " + grantChar + "i",
						client.getPrefix());
					if (!grant)
						channel.setInvited(std::vector<std::string>());
				} else if (args[1][i] == 't') {
					if (channel.isTopicRestricted() == grant)
						continue;
					channel.setTopicRestricted(grant);
					channel.broadcast(server,
						name + " " + channel.getName() + " " + grantChar + "t",
						client.getPrefix());
				} else if (args[1][i] == 'o') {
					if (argsCount == 2)
						continue;
					try {
						Client	&target = server.getClientByNickname(args[2]);

						std::vector<std::string>	tmpArgs = std::vector<std::string>(args, args + argsCount);
						tmpArgs.erase(tmpArgs.begin() + 2, tmpArgs.begin() + 3);
						args = tmpArgs.data();
						if (channel.isOperator(target.getFullAddress()) == grant)
							continue;
						if (grant)
							channel.addOperator(target.getFullAddress());
						else
							channel.removeOperator(target.getFullAddress());
						channel.broadcast(server,
							name + " " + channel.getName() + " " + grantChar + "o " + target.getNick(),
							client.getPrefix());
					} catch (Server::ServerException &e) {
						client.send(ERR_NOSUCHNICK(client.getNick(), args[2]));
						return false;
					}
				} else if (args[1][i] == 'l') {
					if (!grant) {
						if (!channel.isLimited())
							continue;
						channel.setLimited(false);
						channel.broadcast(server,
							name + " " + channel.getName() + " -l",
							client.getPrefix());
						continue;
					}
					if (argsCount == 2) 
						continue;

					size_t	limit = args[2][0] == '-' ? 1 : atou(args[2].c_str());

					std::vector<std::string>	tmpArgs = std::vector<std::string>(args, args + argsCount);
					tmpArgs.erase(tmpArgs.begin() + 2, tmpArgs.begin() + 3);
					args = tmpArgs.data();
					limit = limit < 1 ? 1 : limit;
					if (args[2].empty() || channel.getLimit() == limit)
						continue;
					channel.setLimited(true);
					channel.setLimit(limit);
					channel.broadcast(server,
						name + " " + channel.getName() + " +l " + itoa(limit),
						client.getPrefix());
				} else if (args[1][i] == 'k') {
					if (!grant) {
						if (channel.getKey().empty())
							continue;
						channel.setKey("");
						channel.broadcast(server,
							name + " " + channel.getName() + " -k",
							client.getPrefix());
						continue;
					}
					if (argsCount == 2)
						continue;

					std::string	key = args[2];

					std::vector<std::string>	tmpArgs = std::vector<std::string>(args, args + argsCount);
					tmpArgs.erase(tmpArgs.begin() + 2, tmpArgs.begin() + 3);
					args = tmpArgs.data();
					if (key.empty() || channel.getKey() == key)
						continue;
					channel.setKey(key);
					channel.broadcast(server,
						name + " " + channel.getName() + " +k " + key,
						client.getPrefix());
				} else {
					client.send(ERR_UNKNOWNMODE(client.getNick(), args[1][i]));
					return false;
				}
		}
	} catch (std::exception &e) {
		client.send(ERR_NOSUCHCHANNEL(client.getNick(), args[0]));
		return false;
	}

	return true;
}
