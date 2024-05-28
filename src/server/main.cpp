/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 12:38:36 by ysabik           ###   ########.fr       */
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
		.addCommand(new TopicCommand("TOPIC", List<std::string>("T")))
		.addCommand(new QuitCommand("QUIT", List<std::string>("Q")))
		;

	int			port = 8080;
	int			clientLimit = 100;
	std::string	hostname = "localhost";
	std::string	password;

	try {
		if (parse(argc, argv, port, clientLimit, hostname, password))
			return 0;
		server.start(port, clientLimit, hostname, password);
	} catch (IRCException &e) {
		log(ERROR, std::string(e.what()));
		server.close();
		return 1;
	} catch (std::invalid_argument &e) {
		log(ERROR, std::string(e.what()));
		log(ERROR, "\n");
		log(ERROR, getUsage(argv[0]));
		server.close();
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
