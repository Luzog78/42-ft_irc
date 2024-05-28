/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:44:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


QuitExecutor::QuitExecutor() : Executor() {
}


QuitExecutor::QuitExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


QuitExecutor::QuitExecutor(const QuitExecutor &command) : Executor() {
	*this = command;
}


QuitExecutor &QuitExecutor::operator=(const QuitExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


QuitExecutor::~QuitExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	QuitExecutor::getDesc() {
	return "Quit the server.";
}


std::string	QuitExecutor::getUsage() {
	return name + " [<reason>]";
}


bool	QuitExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) sender;

	bot->send(target, "Bye." + (args.size() > 0 ? " Reason: " + args[0] : ""));
	bot->send("QUIT" + (args.size() > 0 ? " :" + args[0] : ""));
	return true;
}
