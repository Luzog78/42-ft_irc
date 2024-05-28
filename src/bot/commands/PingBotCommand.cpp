/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingBotCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:26:17 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:56:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PingBotCommand::PingBotCommand() : Executor() {
}


PingBotCommand::PingBotCommand(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PingBotCommand::PingBotCommand(const PingBotCommand &command) : Executor() {
	*this = command;
}


PingBotCommand &PingBotCommand::operator=(const PingBotCommand &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PingBotCommand::~PingBotCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PingBotCommand::isElementary() {
	return true;
}


bool	PingBotCommand::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) sender;
	(void) target;

	if (args.size() == 0)
		bot->send("PONG :" + bot->getIp());
	else
		bot->send("PONG :" + args[0]);
	return true;
}
