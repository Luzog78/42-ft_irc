/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:52:50 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 19:49:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


CommandManager::CommandManager() {
}


CommandManager::CommandManager(const CommandManager &commandManager) {
	*this = commandManager;
}


CommandManager &CommandManager::operator=(const CommandManager &commandManager) {
	if (this != &commandManager) {
		commands = commandManager.commands;
	}
	return *this;
}


CommandManager::~CommandManager() {
	for (std::vector<Command *>::iterator it = commands.begin(); it != commands.end(); it++)
		delete *it;
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


int	CommandManager::getCommandIndex(std::string label) {
	for (size_t i = 0; i < commands.size(); i++) {
		Command						*cmd = commands[i];
		std::vector<std::string>	aliases = cmd->getAliases();

		if (cmd->getName() == label || std::find(aliases.begin(),
				aliases.end(), label) != aliases.end())
			return i;
	}
	return -1;
}


bool	CommandManager::exec(Server &server, Client &client, std::string raw) {
	std::string					prefix;
	std::string					label;
	std::vector<std::string>	args;

	std::string	tmp;
	bool		trailing = false;
	for (size_t i = 0; i < raw.length(); i++) {
		if (isspace(raw[i]) && !trailing) {
			if (!tmp.empty())
				args.push_back(tmp);
			tmp = "";
		} else if (raw[i] == ':' && !trailing && tmp.empty() && i > 0) {
			trailing = true;
		} else {
			tmp += raw[i];
		}
	}
	if (!tmp.empty() || trailing)
		args.push_back(tmp);

	if (args.size() > 0 && args[0][0] == ':') {
		prefix = args[0].substr(1);
		args.erase(args.begin());
	}
	if (args.size() > 0) {
		label = args[0];
		std::transform(label.begin(), label.end(), label.begin(), ::toupper);
		args.erase(args.begin());
	}
	return exec(server, client, label, prefix, args.data(), args.size());
}

bool	CommandManager::exec(Server &server, Client &client, std::string label,
			std::string prefix, std::string args[], int argsCount) {
	if (label.empty())
		return false;
	int	idx = getCommandIndex(label);
	if (idx == -1) {
		if (client.isRegistered())
			client.send(server, ERR_UNKNOWNCOMMAND(client.getNick(), label));
		return false;
	}
	return commands[idx]->exec(server, client, label, prefix, args, argsCount);
}


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


CommandManager	&CommandManager::addCommand(Command *command) {
	commands.push_back(command);
	return *this;
}


CommandManager	&CommandManager::removeCommand(std::string label) {
	int	idx = getCommandIndex(label);
	if (idx != -1)
		commands.erase(commands.begin() + idx);
	return *this;
}


Command	*CommandManager::getCommand(std::string label) {
	int	idx = getCommandIndex(label);
	if (idx != -1)
		return commands[idx];
	return 0;
}


std::vector<Command *>	CommandManager::getCommands() {
	return commands;
}


CommandManager	&CommandManager::setCommands(std::vector<Command *> commands) {
	this->commands = commands;
	return *this;
}
