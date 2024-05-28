/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:09:47 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:18:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"


Bot				bot;
ExecutorManager	executorManager;


void	signalHandler(int signum) {
	(void) signum;

	std::cerr << std::endl;
	log(WARNING, "Interrupt signal received");

	bot.setRunning(false);
}


int main(int argc, char **argv) {
	signal(SIGINT, signalHandler);

	executorManager
		.addExecutor(new PingBotCommand("PING", List<std::string>()))
		.addExecutor(new PongBotCommand("PONG", List<std::string>()))
		.addExecutor(new PrivBotCommand("PRIVMSG", List<std::string>("M")("MSG")))
		.addExecutor(new HelpExecutor("!help", List<std::string>("!h")("!?")))
		.addExecutor(new JoinExecutor("!join", List<std::string>()))
		.addExecutor(new PingExecutor("!ping", List<std::string>("!p")))
		.addExecutor(new PongExecutor("!pong", List<std::string>("!pp")))
		.addExecutor(new QuoteExecutor("!quote", List<std::string>("!q")))
		.addExecutor(new JokeExecutor("!joke", List<std::string>("!j")))
		.addExecutor(new FactExecutor("!fact", List<std::string>("!f")))
		;

	std::string	usage = "Usage: " + std::string(argv[0]) + " <IPv4> <port> [<password>]";

	int			port;
	std::string	hostname;
	std::string	password;

	try {
		parse(argc, argv, port, hostname, password);
		bot.start(hostname, port, password);
	} catch (IRCException &e) {
		log(ERROR, std::string(e.what()));
		bot.close();
		return 1;
	} catch (std::invalid_argument &e) {
		log(ERROR, std::string(e.what()));
		log(ERROR, usage);
		bot.close();
		return 1;
	}

	while (bot.isRunning()) {
		try {
			bot.poll();
			bot.receive();
			bot.execute();
		} catch (IRCException &e) {
			log(ERROR, std::string(e.what()));
			break;
		}
	}

	bot.close();
	return 0;
}
