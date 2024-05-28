/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:36:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


PartExecutor::PartExecutor() : Executor() {
}


PartExecutor::PartExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


PartExecutor::PartExecutor(const PartExecutor &command) : Executor() {
	*this = command;
}


PartExecutor &PartExecutor::operator=(const PartExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


PartExecutor::~PartExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	PartExecutor::getDesc() {
	return "Part from a channel.";
}


std::string	PartExecutor::getUsage() {
	return name + " <channel> [<reason>]";
}


bool	PartExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) target;

	if (args.size() < 1) {
		bot->send(sender, "Usage: " + getUsage());
		return false;
	}

	bot->send("PART " + args[0] + (args.size() > 1 ? " :" + args[1] : ""));
	bot->send(sender, "Parted from " + args[0]
		+ (args.size() > 1 ? " (" + args[1] + ")" : "") + ".");
	return true;
}
