/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 14:49:45 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


Server			server;
CommandManager	commandManager;


void	signalHandler(int signum) {
	std::cerr << std::endl;
	log(WARNING, "Interrupt signal received");

	server.close();

	exit(signum);
}


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


int main(int argc, char **argv) {
	signal(SIGINT, signalHandler);

	commandManager
		.addCommand(new InviteCommand("INVITE", List<std::string>("I")))
		.addCommand(new JoinCommand("JOIN", List<std::string>("J")))
		.addCommand(new KickCommand("KICK", List<std::string>("K")))
		.addCommand(new ListCommand("LIST", List<std::string>("L")))
		.addCommand(new ModeCommand("MODE", List<std::string>("MD")))
		.addCommand(new NamesCommand("NAMES", List<std::string>("NM")))
		.addCommand(new NickCommand("NICK", List<std::string>("N")))
		.addCommand(new PartCommand("PART", List<std::string>("P")))
		.addCommand(new PassCommand("PASS", List<std::string>("PA")("PS")("PSS")("W")))
		.addCommand(new PingCommand("PING", List<std::string>("PI")))
		.addCommand(new PongCommand("PONG", List<std::string>("PO")))
		.addCommand(new PrivCommand("PRIVMSG", List<std::string>("M")("MSG")))
		.addCommand(new UserCommand("USER", List<std::string>("U")))
		.addCommand(new UsersCommand("USERS", List<std::string>("US")))
		.addCommand(new TopicCommand("TOPIC", List<std::string>("T")))
		.addCommand(new QuitCommand("QUIT", List<std::string>("Q")))
		;

	std::string	usage = "Usage: " + std::string(argv[0]) + " [<params...>]\n"
		+ "\n"
		+ "Params:\n"
		+ "  -?, --help                     - display this help\n"
		+ "  -p, --port      =<port>        - port number (default: 8080)\n"
		+ "  -k, --key       =<password>    - password for server (default: '')\n"
		+ "  -h, --hostname  =<hostname>    - hostname (default: 'localhost')\n"
		+ "  -l, --limit     =<clientLimit> - maximum number of clients (default: 100)\n"
		+ "\n"
		+ "Example: \n"
		+ std::string(argv[0]) + " 8080\n"
		+ std::string(argv[0]) + " 8080 P4ssK3y\n"
		+ std::string(argv[0]) + " --password=P4ssK3y --limit=50 -h=42.irc.net\n";

	int			port = 8080;
	int			clientLimit = 100;
	std::string	hostname = "localhost";
	std::string	password;
	bool		plainArgs = true;

	try {
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
				log(ERROR, usage);
				return 0;
			} else if (i == 1 && argv[i][0] != '-')
				port = parseUnsigned(argv[i], "Port");
			else if (i == 2 && plainArgs)
				password = arg;
			else
				throw std::invalid_argument("Unknown argument: " + arg);
		}

		server.start(port, clientLimit, hostname, password);
	} catch (IRCException &e) {
		log(ERROR, std::string(e.what()));
		return 1;
	} catch (std::invalid_argument &e) {
		log(ERROR, std::string(e.what()));
		log(ERROR, "\n");
		log(ERROR, usage);
		return 1;
	}

	while (true) {
		try {
			server.poll();
			server.accept();
			server.receive();
		} catch (IRCException &e) {
			log(ERROR, std::string(e.what()));
			break;
		}
	}

	log(INFO, "STOP.");

	server.close();

	return 0;
}
