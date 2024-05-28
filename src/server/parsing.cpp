/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:32:02 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 12:38:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


static size_t	parseUnsigned(const char *str, std::string message) {
	size_t			res = 0;

	while (*str >= '0' && *str <= '9') {
		res = res * 10 + *str - '0';
		if (res > 65535)
			throw std::invalid_argument(message + " is too big (maximum: 65535)");
		str++;
	}
	if (*str)
		throw std::invalid_argument(message + " is not a positive number");
	if (res == 0)
		throw std::invalid_argument(message + " is too small (minimum: 1)");
	return res;
}


std::string	getUsage(char *name) {
	std::string	n = std::string(name);

	return "Usage: " + n + " [<params...>]\n"
		+ "\n"
		+ "Params:\n"
		+ "  -?, --help                     - display this help\n"
		+ "  -p, --port      =<port>        - port number (default: 8080)\n"
		+ "  -k, --key       =<password>    - password for server (default: '')\n"
		+ "  -h, --hostname  =<hostname>    - hostname (default: 'localhost')\n"
		+ "  -l, --limit     =<clientLimit> - maximum number of clients (default: 100)\n"
		+ "\n"
		+ "Example: \n"
		+ n + " 8080\n"
		+ n + " 8080 P4ssK3y\n"
		+ n + " --password=P4ssK3y --limit=50 -h=42.irc.net\n";
}


int	parse(int argc, char **argv, int &port, int &clientLimit,
				std::string &hostname, std::string &password) {
	bool	plainArgs = true;

	for (int i = 1; i < argc; i++) {
		std::string	arg = argv[i];

		if (startsWith(arg, "-p") || startsWith(arg, "--port")) {
			if (arg.find('=') == std::string::npos)
				throw std::invalid_argument("Port number is missing");
			port = parseUnsigned(arg.substr(arg.find('=') + 1).c_str(), "Port");
			plainArgs = false;
		} else if (startsWith(arg, "-k") || startsWith(arg, "--key")) {
			if (arg.find('=') == std::string::npos)
				throw std::invalid_argument("Password is missing");
			password = arg.substr(arg.find('=') + 1);
			plainArgs = false;
		} else if (startsWith(arg, "-h") || startsWith(arg, "--hostname")) {
			if (arg.find('=') == std::string::npos)
				throw std::invalid_argument("Hostname is missing");
			hostname = arg.substr(arg.find('=') + 1);
			plainArgs = false;
		} else if (startsWith(arg, "-l") || startsWith(arg, "--limit")) {
			if (arg.find('=') == std::string::npos)
				throw std::invalid_argument("Client limit is missing");
			clientLimit = parseUnsigned(arg.substr(arg.find('=') + 1).c_str(), "Client limit");
			plainArgs = false;
		} else if (startsWith(arg, "-?") || startsWith(arg, "--help")) {
			log(ERROR, getUsage(argv[0]));
			return 1;
		} else if (i == 1 && argv[i][0] != '-')
			port = parseUnsigned(argv[i], "Port");
		else if (i == 2 && plainArgs)
			password = arg;
		else
			throw std::invalid_argument("Unknown argument: " + arg);
	}
	return 0;
}
