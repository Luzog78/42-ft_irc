/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivCommand.cpp                                    :+:      :+:    :+:   */
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


PrivCommand::PrivCommand() : Command() {
}


PrivCommand::PrivCommand(std::string name, std::vector<std::string> aliases)
	: Command(name, aliases) {
}


PrivCommand::PrivCommand(const PrivCommand &command) : Command() {
	*this = command;
}


PrivCommand &PrivCommand::operator=(const PrivCommand &command) {
	if (this != &command)
		Command::operator=(command);
	return *this;
}


PrivCommand::~PrivCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


static std::vector<std::string>		splitTargets(std::string rawTargets) {
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


static std::map<std::string, std::vector<Client> >	getTargets(Server &server, Client &client,
														std::string rawTargets, bool *error) {
	std::map<std::string, std::vector<Client> >	targets;
	std::vector<std::string>					targetNames = splitTargets(rawTargets);

	for (std::vector<std::string>::iterator it = targetNames.begin();
			it != targetNames.end(); it++)
		try {
			if (targets.find(*it) != targets.end())
				continue;
			if (it->at(0) == '#') {
				Channel				channel = server.getChannelByName(*it);
				if (!channel.isMember(client.getSocket())) {
					client.send(server, ERR_CANNOTSENDTOCHAN(client.getNick(), *it));
					*error = true;
					continue;
				}
				std::vector<Client>	channelMembers = channel.getOnlineClients(server);
				targets[*it] = std::vector<Client>();
				for (size_t i = 0; i < channelMembers.size(); i++)
					if (channelMembers[i].getSocket() != client.getSocket())
						targets[*it].push_back(channelMembers[i]);
			} else {
				Client	target = server.getClientByNickname(*it);
				targets[*it] = std::vector<Client>();
				targets[*it].push_back(target);
			}
		} catch (Server::ServerException &e) {
			if (it->at(0) == '#')
				client.send(server, ERR_NOSUCHCHANNEL(client.getNick(), *it));
			else
				client.send(server, ERR_NOSUCHNICK(client.getNick(), *it));
			*error = true;
		}
	return targets;
}


static bool	isEmpty(std::map<std::string, std::vector<Client> > targets) {
	for (std::map<std::string, std::vector<Client> >::iterator it = targets.begin();
			it != targets.end(); it++)
		if (it->second.size() > 0)
			return false;
	return true;
}


bool	PrivCommand::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	(void) label;
	(void) prefix;

	if (!client.isRegistered())
		return false;
	if (argsCount == 0) {
		client.send(server, ERR_NORECIPIENT(client.getNick()));
		return false;
	}
	if (argsCount == 1) {
		client.send(server, ERR_NOTEXTTOSEND(client.getNick()));
		return false;
	}

	bool										error;
	std::map<std::string, std::vector<Client> >	targets;

	error = false;
	targets = getTargets(server, client, args[0], &error);
	if (error)
		return false;

	if (isEmpty(targets)) {
		client.send(server, ERR_NORECIPIENT(client.getNick()));
		return false;
	}

	for (std::map<std::string, std::vector<Client> >::iterator it = targets.begin();
			it != targets.end(); it++)
		for (size_t i = 0; i < it->second.size(); i++)
			it->second[i].send(name + " " + it->first + " :" + args[1], client.getPrefix());

	return true;
}
