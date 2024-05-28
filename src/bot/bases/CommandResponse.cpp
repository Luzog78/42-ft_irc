/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:05:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


CommandResponse::CommandResponse() : Response() {
	numeric = false;
}


CommandResponse::CommandResponse(const CommandResponse &commandResponse) : Response() {
	*this = commandResponse;
}


CommandResponse &CommandResponse::operator=(const CommandResponse &commandResponse) {
	if (this != &commandResponse) {
		Response::operator=(commandResponse);
		label = commandResponse.label;
		target = commandResponse.target;
		args = commandResponse.args;
	}
	return *this;
}


CommandResponse::~CommandResponse() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


std::string	CommandResponse::getLabel() {
	return label;
}


void	CommandResponse::setLabel(std::string label) {
	this->label = label;
}


std::string	CommandResponse::getTarget() {
	return target;
}


void	CommandResponse::setTarget(std::string target) {
	this->target = target;
}


std::vector<std::string>	CommandResponse::getArgs() {
	return args;
}


void	CommandResponse::setArgs(std::vector<std::string> args) {
	this->args = args;
}
