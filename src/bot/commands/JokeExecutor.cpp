/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JokeExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:56:46 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


JokeExecutor::JokeExecutor() : Executor() {
}


JokeExecutor::JokeExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


JokeExecutor::JokeExecutor(const JokeExecutor &command) : Executor() {
	*this = command;
}


JokeExecutor &JokeExecutor::operator=(const JokeExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


JokeExecutor::~JokeExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	JokeExecutor::getDesc() {
	return "Get a random joke from ICanHazDadJoke.com.";
}


std::string	JokeExecutor::getUsage() {
	return name;
}


bool	JokeExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) sender;

	// Other Jokes APIs:
	// - https://jokeapi.dev/
	// - https://official-joke-api.appspot.com/jokes/random
	// - https://v2.jokeapi.dev/joke/Any
	// - https://sv443.net/jokeapi/v2/joke/Any
	std::string	joke = curlRequest("https://icanhazdadjoke.com/");

	if (joke.empty())
		bot->send(target, "I'm sorry, I can't tell you a joke right now.");
	else
		bot->send(target, joke);
	return true;
}
