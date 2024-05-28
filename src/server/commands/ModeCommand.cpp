/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:48:19 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 13:48:36 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


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


static void	displayModes(Server &server, Client &client, Channel &channel) {
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
	client.send(server, RPL_CHANNELMODEIS(
			client.getNick(), channel.getName(), mode));
}


static bool	optionI(Server &server, Client &client, Channel &channel,
				bool &grant, char &grantChar, std::string &name) {
	if (channel.isInviteOnly() == grant)
		return true;
	channel.setInviteOnly(grant);
	channel.broadcast(server,
		name + " " + channel.getName() + " " + grantChar + "i",
		client.getPrefix());
	if (!grant)
		channel.setInvited(std::vector<std::string>());
	return true;
}


static bool	optionT(Server &server, Client &client, Channel &channel,
				bool &grant, char &grantChar, std::string &name) {
	if (channel.isTopicRestricted() == grant)
		return true;
	channel.setTopicRestricted(grant);
	channel.broadcast(server,
		name + " " + channel.getName() + " " + grantChar + "t",
		client.getPrefix());
	return true;
}


static bool	optionO(Server &server, Client &client, Channel &channel,
				bool &grant, char &grantChar, std::string &name,
				std::vector<std::string> &args, int &argsCount) {
	if (argsCount == 2)
		return true;
	try {
		Client	&target = server.getClientByNickname(args[2]);

		args.erase(args.begin() + 2, args.begin() + 3);
		if (channel.isOperator(target.getFullAddress()) == grant)
			return true;
		if (grant)
			channel.addOperator(target.getFullAddress());
		else
			channel.removeOperator(target.getFullAddress());
		channel.broadcast(server,
			name + " " + channel.getName() + " " + grantChar + "o " + target.getNick(),
			client.getPrefix());
	} catch (Server::ServerException &e) {
		client.send(server, ERR_NOSUCHNICK(
				client.getNick(), args[2]));
		return false;
	}
	return true;
}


static bool	optionL(Server &server, Client &client, Channel &channel,
				bool &grant, std::string &name, std::vector<std::string> &args,
				int &argsCount) {
	if (!grant) {
		if (!channel.isLimited())
			return true;
		channel.setLimited(false);
		channel.broadcast(server,
			name + " " + channel.getName() + " -l",
			client.getPrefix());
		return true;
	}
	if (argsCount == 2) 
		return true;

	size_t	limit = args[2][0] == '-' ? 1 : atou(args[2].c_str());

	args.erase(args.begin() + 2, args.begin() + 3);
	limit = limit < 1 ? 1 : limit;
	if (args[2].empty() || channel.getLimit() == limit)
		return true;
	channel.setLimited(true);
	channel.setLimit(limit);
	channel.broadcast(server,
		name + " " + channel.getName() + " +l " + itoa(limit),
		client.getPrefix());
	return true;
}


static bool	optionK(Server &server, Client &client, Channel &channel,
				bool &grant, std::string &name, std::vector<std::string> &args,
				int &argsCount) {
	if (!grant) {
		if (channel.getKey().empty())
			return true;
		channel.setKey("");
		channel.broadcast(server,
			name + " " + channel.getName() + " -k",
			client.getPrefix());
		return true;
	}
	if (argsCount == 2)
		return true;
	if (!Channel::isLegalKey(args[2])) {
		client.send(server, ERR_PASSWDMISMATCH(client.getNick()));
		return false;
	}

	std::string	key = args[2];

	args.erase(args.begin() + 2, args.begin() + 3);
	if (key.empty() || channel.getKey() == key)
		return true;
	channel.setKey(key);
	channel.broadcast(server,
		name + " " + channel.getName() + " +k " + key,
		client.getPrefix());
	return true;
}


static bool	options(Server &server, Client &client, Channel &channel,
				std::string &name, std::vector<std::string> &args,
				int &argsCount) {
	bool	grant = args[1].empty() || args[1][0] != '-';
	char	grantChar = grant ? '+' : '-';
	bool	result;

	for (size_t i = args[1][0] == '+' || args[1][0] == '-';
			i < args[1].length(); i++) {
		if (args[1][i] == 'i')
			result = optionI(server, client, channel, grant,
				grantChar, name);
		else if (args[1][i] == 't')
			result = optionT(server, client, channel, grant,
				grantChar, name);
		else if (args[1][i] == 'o')
			result = optionO(server, client, channel, grant,
				grantChar, name, args, argsCount);
		else if (args[1][i] == 'l')
			result = optionL(server, client, channel, grant,
				name, args, argsCount);
		else if (args[1][i] == 'k')
			result = optionK(server, client, channel, grant,
				name, args, argsCount);
		else {
			client.send(server, ERR_UNKNOWNMODE(
					client.getNick(), args[1][i]));
			result = false;
		}
		if (!result)
			return false;
	}
	return true;
}


bool	ModeCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) server;
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(server, ERR_NEEDMOREPARAMS(client.getNick(), name));
		return false;
	}
	std::vector<std::string>	newArgs =
		std::vector<std::string>(args, args + argsCount);
	try {
		Channel	&channel = server.getChannelByName(args[0]);
		bool	isOp = channel.isOperator(client.getFullAddress());

		if (argsCount == 1) {
			displayModes(server, client, channel);
		} else if (!isOp) {
			client.send(server, ERR_CHANOPRIVSNEEDED(
					client.getNick(), channel.getName()));
			return false;
		} else if (!options(server, client, channel, name, newArgs, argsCount))
			return false;
	} catch (std::exception &e) {
		client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), args[0]));
		return false;
	}
	return true;
}
