/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:52:50 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 15:12:40 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	char		quote = 0;
	for (size_t i = 0; i < raw.length(); i++) {
		if (isspace(raw[i]) && quote == 0) {
			if (tmp.length() > 0)
				args.push_back(tmp);
			tmp = "";
		} else if (raw[i] == '"' || raw[i] == '\'') {
			if (quote == 0) {
				quote = raw[i];
			} else if (quote == raw[i]) {
				quote = 0;
			} else {
				tmp += raw[i];
			}
		} else if (raw[i] == ':' && quote == 0 && tmp.length() == 0) {
			quote = ':';
		} else {
			tmp += raw[i];
		}
	}
	if (tmp.length() > 0)
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
			client.send(ERR_UNKNOWNCOMMAND(client.getNick(), label));
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
