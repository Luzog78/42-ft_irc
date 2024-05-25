/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 17:22:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


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
		.addCommand(new PingCommand("PING", List<std::string>("PI")))
		.addCommand(new PongCommand("PONG", List<std::string>("PO")))
		.addCommand(new PrivCommand("PRIVMSG", List<std::string>("M")("MSG")))
		.addCommand(new UserCommand("USER", List<std::string>("U")))
		.addCommand(new TopicCommand("TOPIC", List<std::string>("T")))
		.addCommand(new QuitCommand("QUIT", List<std::string>("Q")))
		;

	std::string	usage = "Usage: " + std::string(argv[0]) + " [<port> [<client_limit>]]";
	const char	*port = argc > 1 ? argv[1] : "8080";
	const char	*clientLimit = argc > 2 ? argv[2] : "100";

	if (argc > 3) {
		log(ERROR, "Too many arguments");
		log(ERROR, usage);
		return 1;
	}

	try {
		server.start(parseUnsigned(port, "Port"),
			parseUnsigned(clientLimit, "Client limit"));
	} catch (IRCException &e) {
		log(ERROR, std::string(e.what()));
		return 1;
	} catch (std::invalid_argument &e) {
		log(ERROR, std::string(e.what()));
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
