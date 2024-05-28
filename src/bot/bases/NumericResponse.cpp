/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:10:28 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 11:12:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


NumericResponse::NumericResponse() : Response() {
	code = 0;
	numeric = true;
}


NumericResponse::NumericResponse(const NumericResponse &numericResponse) : Response() {
	*this = numericResponse;
}


NumericResponse &NumericResponse::operator=(const NumericResponse &numericResponse) {
	if (this != &numericResponse) {
		Response::operator=(numericResponse);
		code = numericResponse.code;
		args = numericResponse.args;
		message = numericResponse.message;
	}
	return *this;
}


NumericResponse::~NumericResponse() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


int	NumericResponse::getCode() {
	return code;
}


void	NumericResponse::setCode(int code) {
	this->code = code;
}


std::vector<std::string>	NumericResponse::getArgs() {
	return args;
}


void	NumericResponse::setArgs(std::vector<std::string> args) {
	this->args = args;
}


void	NumericResponse::addArg(std::string arg) {
	args.push_back(arg);
}


std::string	NumericResponse::getMessage() {
	return message;
}


void	NumericResponse::setMessage(std::string message) {
	this->message = message;
}
