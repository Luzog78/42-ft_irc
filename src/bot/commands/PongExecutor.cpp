/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:57:17 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PongExecutor::PongExecutor() : Executor() {
}


PongExecutor::PongExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PongExecutor::PongExecutor(const PongExecutor &command) : Executor() {
	*this = command;
}


PongExecutor &PongExecutor::operator=(const PongExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PongExecutor::~PongExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	PongExecutor::getDesc() {
	return "Pong. Sends a ping.";
}


std::string	PongExecutor::getUsage() {
	return name + " [<whatever>]";
}


bool	PongExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;

	if (args.size() == 0)
		bot->send(target, "Ping " + sender + "!");
	else
		bot->send(target, "Ping " + args[0] + "!");
	return true;
}
