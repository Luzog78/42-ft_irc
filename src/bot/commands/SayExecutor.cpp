/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SayExecutor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:55:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


SayExecutor::SayExecutor() : Executor() {
}


SayExecutor::SayExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


SayExecutor::SayExecutor(const SayExecutor &command) : Executor() {
	*this = command;
}


SayExecutor &SayExecutor::operator=(const SayExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


SayExecutor::~SayExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	SayExecutor::getDesc() {
	return "Make the bot say something.";
}


std::string	SayExecutor::getUsage() {
	return name + " <receiver> <message>";
}


bool	SayExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;

	if (args.size() < 2) {
		bot->send(sender, "Usage: " + getUsage());
		return false;
	}

	std::string	msg = sender + " whispers to you : " + args[1];
	bool		ret = true;

	bot->send(args[0], msg, 1000);
	pthread_mutex_lock(bot->getResponsesMutex());
	std::vector<Response *>	responses = bot->getResponses();
	for (size_t i = 0; i < responses.size(); i++)
		if (responses[i]->isNumeric()
			&& IS_FATAL(responses[i]->asNumeric()->getCode())) {
			NumericResponse	*num = responses[i]->asNumeric();
			log(ERROR, "[" + itoa(num->getCode()) + "] " + num->getMessage());
			bot->send(target, "I'm sorry, I can't send the message... :(");
			ret = false;
			break;
		}
	pthread_mutex_unlock(bot->getResponsesMutex());
	if (ret)
		bot->send(target, "Message sent to " + args[0] + " ! :D");
	return true;
}
