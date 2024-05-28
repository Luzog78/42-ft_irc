/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:39:23 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


FactExecutor::FactExecutor() : Executor() {
}


FactExecutor::FactExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


FactExecutor::FactExecutor(const FactExecutor &command) : Executor() {
	*this = command;
}


FactExecutor &FactExecutor::operator=(const FactExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


FactExecutor::~FactExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	FactExecutor::getDesc() {
	return "Get a random fact about cats from CatFact.ninja.";
}


std::string	FactExecutor::getUsage() {
	return name;
}


bool	FactExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) sender;

	std::string	fact = curlRequest("https://catfact.ninja/fact");

	if (fact.empty())
		bot->send(target, "I'm sorry, I can't tell you a fact about cats right now.");
	else {
		fact = fact.substr(fact.find("\"fact\":\"") + 8);
		fact = fact.substr(0, fact.find("\""));

		bot->send(target, fact);
	}
	return true;
}
