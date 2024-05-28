/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivBotCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:33:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:10:32 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PrivBotCommand::PrivBotCommand() : Executor() {
}


PrivBotCommand::PrivBotCommand(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PrivBotCommand::PrivBotCommand(const PrivBotCommand &command) : Executor() {
	*this = command;
}


PrivBotCommand &PrivBotCommand::operator=(const PrivBotCommand &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PrivBotCommand::~PrivBotCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PrivBotCommand::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	if (args.size() != 2)
		return false;
	if (args[1].empty() || args[1][0] != '!')
		return false;

	std::vector<std::string>	newArgs;

	if (!args[0].empty() && args[0][0] == '#')
		target = args[0];
	else {
		std::size_t	found = prefix.find("!");
		if (found != std::string::npos)
			target = prefix.substr(0, found);
		else
			target = prefix;
	}

	char		quote = 0;
	std::string	arg;

	for (size_t pos = 0; pos < args[1].size(); pos++) {
		if (isspace(args[1][pos]) && !quote) {
			if (!arg.empty())
				newArgs.push_back(arg);
			arg.clear();
		} else if (args[1][pos] == '"' || args[1][pos] == '\''
				|| args[1][pos] == '`') {
			if (!quote)
				quote = args[1][pos];
			else if (quote == args[1][pos])
				quote = 0;
			else
				arg += args[1][pos];
		} else
			arg += args[1][pos];
	}
	if (!arg.empty())
		newArgs.push_back(arg);
	
	label = newArgs[0];
	newArgs.erase(newArgs.begin());

	CommandResponse	response;
	response.setPrefix(prefix);
	response.setSender(sender);
	response.setTarget(target);
	response.setLabel(label);
	response.setArgs(newArgs);
	response.setRaw(":" + prefix + ":" + args[0] + " " + args[1]);

	return executorManager.exec(bot, &response);
}
