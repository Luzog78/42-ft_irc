/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuoteExecutor.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:57:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


QuoteExecutor::QuoteExecutor() : Executor() {
}


QuoteExecutor::QuoteExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


QuoteExecutor::QuoteExecutor(const QuoteExecutor &command) : Executor() {
	*this = command;
}


QuoteExecutor &QuoteExecutor::operator=(const QuoteExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


QuoteExecutor::~QuoteExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	QuoteExecutor::getDesc() {
	return "Get a random quote from Quotable.io.";
}


std::string	QuoteExecutor::getUsage() {
	return name;
}


bool	QuoteExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) sender;

	std::string	quote = curlRequest("https://api.quotable.io/random");

	if (quote.empty())
		bot->send(target, "I'm sorry, I can't tell you a quote right now.");
	else {
		std::string	author = quote.substr(quote.find("\"author\":\"") + 10);
		author = author.substr(0, author.find("\""));

		quote = quote.substr(quote.find("\"content\":\"") + 11);
		quote = quote.substr(0, quote.find("\""));

		bot->send(target, quote);
		bot->send(target, " - " + author);
	}
	return true;
}
