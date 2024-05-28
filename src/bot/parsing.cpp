/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:58:37 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:00:26 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


static size_t	parseUnsigned(const char *str, std::string message, size_t min, size_t max) {
	size_t			res = 0;

	if (!*str)
		throw std::invalid_argument(message + " is empty");
	while (*str >= '0' && *str <= '9') {
		res = res * 10 + *str - '0';
		if (res > max)
			throw std::invalid_argument(message + " is too big (maximum: " + itoa((int) max) + ")");
		str++;
	}
	if (*str)
		throw std::invalid_argument(message + " is not a positive number");
	if (res < min)
		throw std::invalid_argument(message + " is too small (minimum: " + itoa((int) min) + ")");
	return res;
}


void	parse(int argc, char **argv, int &port,
			std::string &hostname, std::string &password) {
	if (argc < 3)
		throw std::invalid_argument("Not enough arguments");
	if (argc > 4)
		throw std::invalid_argument("Too many arguments");
	
	hostname = argv[1];
	try {
		if (hostname.find('.') == std::string::npos)
			throw std::exception();
		parseUnsigned(hostname.substr(0, hostname.find('.')).c_str(), "", 0, 255);
		hostname = hostname.substr(hostname.find('.') + 1);
		if (hostname.find('.') == std::string::npos)
			throw std::exception();
		parseUnsigned(hostname.substr(0, hostname.find('.')).c_str(), "", 0, 255);
		hostname = hostname.substr(hostname.find('.') + 1);
		if (hostname.find('.') == std::string::npos)
			throw std::exception();
		parseUnsigned(hostname.substr(0, hostname.find('.')).c_str(), "", 0, 255);
		parseUnsigned(hostname.substr(hostname.find('.') + 1).c_str(), "", 0, 255);
		hostname = argv[1];
	} catch (std::exception &e) {
		throw std::invalid_argument("Invalid IPv4 address");
	}
	port = parseUnsigned(argv[2], "Port", 1024, 65535);
	if (argc == 4)
		password = argv[3];
}
