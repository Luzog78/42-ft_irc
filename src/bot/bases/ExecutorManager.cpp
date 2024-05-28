/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecutorManagerManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:53:15 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 11:54:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


ExecutorManager::ExecutorManager() {
}


ExecutorManager::ExecutorManager(const ExecutorManager &executorManager) {
	*this = executorManager;
}


ExecutorManager &ExecutorManager::operator=(const ExecutorManager &executorManager) {
	if (this != &executorManager) {
		executors = executorManager.executors;
	}
	return *this;
}


ExecutorManager::~ExecutorManager() {
	for (std::vector<Executor *>::iterator it = executors.begin();
			it != executors.end(); it++) {
		delete *it;
	}
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


ExecutorManager	&ExecutorManager::addExecutor(Executor *executor) {
	executors.push_back(executor);
	return *this;
}


Executor	*ExecutorManager::getExecutor(std::string executor) {
	std::string	ex = executor;

	std::transform(ex.begin(), ex.end(), ex.begin(), ::tolower);
	for (size_t i = 0; i < executors.size(); i++) {
		Executor					*exec = executors[i];
		std::string					name = exec->getName();
		std::vector<std::string>	aliases = exec->getAliases();

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (name == ex)
			return exec;
		for (size_t j = 0; j < aliases.size(); j++) {
			std::string	alias = aliases[j];
			std::transform(alias.begin(), alias.end(), alias.begin(), ::tolower);
			if (alias == ex)
				return exec;
		}
	}
	return NULL;
}


bool	ExecutorManager::exec(Bot *bot, CommandResponse *commandResponse) {
	Executor	*executor = getExecutor(commandResponse->getLabel());
	if (executor == NULL)
		return false;
	return executor->exec(bot, commandResponse->getLabel(),
			commandResponse->getPrefix(), commandResponse->getArgs(),
			commandResponse->getSender(), commandResponse->getTarget());
}


/* ************************************************************************** */
/* ----------------------------- Getter/Setters ----------------------------- */
/* ************************************************************************** */


std::vector<Executor *>	ExecutorManager::getExecutors() {
	return executors;
}


void	ExecutorManager::setExecutors(std::vector<Executor *> executors) {
	this->executors = executors;
}
