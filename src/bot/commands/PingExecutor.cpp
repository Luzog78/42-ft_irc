/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:07:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PingExecutor::PingExecutor() : Executor() {
}


PingExecutor::PingExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PingExecutor::PingExecutor(const PingExecutor &command) : Executor() {
	*this = command;
}


PingExecutor &PingExecutor::operator=(const PingExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PingExecutor::~PingExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	PingExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;

	if (args.size() == 0)
		bot->send(target, "Pong " + sender + "!");
	else
		bot->send(target, "Pong " + args[0] + "!");
	return true;
}
