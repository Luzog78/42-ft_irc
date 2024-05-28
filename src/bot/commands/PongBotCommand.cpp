/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongBotCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:32:35 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:57:10 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PongBotCommand::PongBotCommand() : Executor() {
}


PongBotCommand::PongBotCommand(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PongBotCommand::PongBotCommand(const PongBotCommand &command) : Executor() {
	*this = command;
}


PongBotCommand &PongBotCommand::operator=(const PongBotCommand &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PongBotCommand::~PongBotCommand() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PongBotCommand::isElementary() {
	return true;
}


bool	PongBotCommand::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) sender;
	(void) target;

	if (args.size() == 0)
		bot->send("PING :" + bot->getIp());
	else
		bot->send("PING :" + args[0]);
	return true;
}
