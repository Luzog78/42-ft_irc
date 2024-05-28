/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:45:55 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:18:19 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Response::Response() {
	numeric = false;
}


Response::Response(const Response &response) {
	*this = response;
}


Response &Response::operator=(const Response &response) {
	if (this != &response) {
		raw = response.raw;
		prefix = response.prefix;
		sender = response.sender;
		numeric = response.numeric;
	}
	return *this;
}


Response::~Response() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


Response	*Response::parse(std::string raw) {
	std::vector<std::string>	args;
	std::string					prefix;
	std::string					sender;
	std::string					copy = raw;
	size_t						pos = 0;
	bool						trailing = false;
	std::string					arg;

	while (pos < copy.size()) {
		if (isspace(copy[pos]) && !trailing) {
			arg = copy.substr(0, pos);
			if (!arg.empty())
				args.push_back(arg);
			copy.erase(0, pos + 1);
			pos = 0;
			continue;
		}
		if (copy[pos] == ':' && !trailing && pos == 0 && copy != raw) {
			trailing = true;
			copy.erase(0, 1);
			continue;
		}
		pos++;
	}
	if (!copy.empty())
		args.push_back(copy);

	if (!args.empty() && !args[0].empty() && args[0][0] == ':') {
		prefix = args[0].substr(1);
		args.erase(args.begin());
		if (prefix.find("!") != std::string::npos)
			sender = prefix.substr(0, prefix.find("!"));
		else
			sender = prefix;
	}
	if (args.empty())
		return new Response();
	arg = args[0];
	args.erase(args.begin());
	if (arg.size() == 3 && isdigit(arg[0])
		&& isdigit(arg[1]) && isdigit(arg[2])) {
		NumericResponse	*response = new NumericResponse();
		response->setRaw(raw);
		response->setPrefix(prefix);
		response->setCode((arg[0] - '0') * 100 + (arg[1] - '0') * 10 + (arg[2] - '0'));
		if (!args.empty()) {
			response->setMessage(args[args.size() - 1]);
			args.pop_back();
		}
		response->setArgs(args);
		return response;
	} else {
		CommandResponse	*response = new CommandResponse();
		response->setRaw(raw);
		response->setPrefix(prefix);
		response->setSender(sender);
		response->setLabel(arg);
		response->setArgs(args);
		return response;
	}
}


NumericResponse	*Response::asNumeric() {
	return dynamic_cast<NumericResponse *>(this);
}


CommandResponse	*Response::asCommand() {
	return dynamic_cast<CommandResponse *>(this);
}


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


std::string	Response::getRaw() {
	return raw;
}


void	Response::setRaw(std::string raw) {
	this->raw = raw;
}


std::string	Response::getPrefix() {
	return prefix;
}


void	Response::setPrefix(std::string prefix) {
	this->prefix = prefix;
}


std::string	Response::getSender() {
	return sender;
}


void	Response::setSender(std::string sender) {
	this->sender = sender;
}

bool	Response::isNumeric() {
	return numeric;
}
