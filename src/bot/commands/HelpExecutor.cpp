/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 11:01:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


HelpExecutor::HelpExecutor() : Executor() {
}


HelpExecutor::HelpExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


HelpExecutor::HelpExecutor(const HelpExecutor &command) : Executor() {
	*this = command;
}


HelpExecutor &HelpExecutor::operator=(const HelpExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


HelpExecutor::~HelpExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	HelpExecutor::getDesc() {
	return "List all available commands or get help for a specific one.";
}


std::string	HelpExecutor::getUsage() {
	return name + " [<command>]";
}


bool	HelpExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) sender;

	if (args.size() == 0) {
		std::vector<Executor *>	ex = executorManager.getExecutors();
		int						count = 0;

		for (size_t i = 0; i < ex.size(); i++)
			if (!ex[i]->isElementary())
				count++;
		bot->send(target, "Available commands (" + itoa(count) + "):");
		for (size_t i = 0; i < ex.size(); i++)
			if (!ex[i]->isElementary())
				bot->send(target, "  > " + ex[i]->getName()
					+ " - " + ex[i]->getDesc());
	} else {
		Executor	*ex;

		if (!args[0].empty() && args[0][0] != '!')
			args[0] = "!" + args[0];
		if ((ex = executorManager.getExecutor(args[0])) == NULL)
			bot->send(target, "Command '" + args[0] + "' not found.");
		else {
			std::string					aliasesMsg;
			std::vector<std::string>	aliases = ex->getAliases();

			for (size_t i = 0; i < aliases.size(); i++) {
				if (i != 0)
					aliasesMsg += ", ";
				aliasesMsg += aliases[i];
			}
			bot->send(target, "Command '" + ex->getName() + "':");
			bot->send(target, "  > Description: " + ex->getDesc());
			bot->send(target, "  > Aliases: [ " + aliasesMsg + " ]");
			bot->send(target, "  > Usage: " + ex->getUsage());
		}
	}
	return true;
}
