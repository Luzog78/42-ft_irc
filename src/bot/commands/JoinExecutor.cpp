/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinExecutor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:59:56 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:17:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


JoinExecutor::JoinExecutor() : Executor() {
}


JoinExecutor::JoinExecutor(std::string name, std::vector<std::string> aliases)
	: Executor(name, aliases) {
}


JoinExecutor::JoinExecutor(const JoinExecutor &command) : Executor() {
	*this = command;
}


JoinExecutor &JoinExecutor::operator=(const JoinExecutor &command) {
	if (this != &command)
		Executor::operator=(command);
	return *this;
}


JoinExecutor::~JoinExecutor() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


std::string	JoinExecutor::getDesc() {
	return "Try to join a channel.";
}


std::string	JoinExecutor::getUsage() {
	return name + " <channel> [<key>]";
}


bool	JoinExecutor::exec(Bot *bot, std::string label, std::string prefix,
			std::vector<std::string> args, std::string sender, std::string target) {
	(void) label;
	(void) prefix;
	(void) args;
	(void) sender;

	if (args.size() < 1) {
		bot->send(target, "Usage: " + getUsage());
		return false;
	}

	std::string	cmd = "JOIN " + args[0] + (args.size() > 1 ? " " + args[1] : "");
	bool		ret = true;

	bot->send(cmd, 1000);
	pthread_mutex_lock(bot->getResponsesMutex());
	std::vector<Response *>	responses = bot->getResponses();
	for (size_t i = 0; i < responses.size(); i++)
		if (responses[i]->isNumeric()
			&& IS_FATAL(responses[i]->asNumeric()->getCode())) {
			NumericResponse	*num = responses[i]->asNumeric();
			log(ERROR, "[" + itoa(num->getCode()) + "] " + num->getMessage());
			bot->send(target, "I'm sorry, I can't join the channel. :(");
			ret = false;
			break;
		}
	pthread_mutex_unlock(bot->getResponsesMutex());
	if (ret)
		bot->send(target, "I'm in! :D");
	return true;
}
