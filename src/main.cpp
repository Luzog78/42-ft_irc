/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 13:07:13 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Server			server;
CommandManager	commandManager;

std::string	itoa(int n) {
	std::string str;
	std::stringstream ss;
	ss << n;
	ss >> str;
	return str;
}

void	log(ErrorLevel errorLevel, std::string message, std::string color) {
	std::time_t			t = std::time(0);
	std::tm*			now = std::localtime(&t);
	std::istringstream	mess(message);
	std::string			prefix;
	std::string			prefixColor = "", messageColor = "";

	switch (errorLevel)
	{
	case INFO:
		prefix = "[INFO]    ";
		messageColor = color;
		break;
	case WARNING:
		prefix = "[WARNING] ";
		prefixColor = C_YELLOW;
		messageColor = color.empty() ? C_YELLOW : color;
		break;
	case ERROR:
		prefix = "[ERROR]   ";
		prefixColor = C_RED;
		messageColor = color.empty() ? C_RED : color;
		break;
	default:
		prefix = "          ";
		messageColor = color;
		break;
	}

	for (std::string str; std::getline(mess, str);)
		std::cout	<< C_DIM << std::setfill('0') << "["
					<< std::setw(4) << now->tm_year + 1900 << "-"
					<< std::setw(2) << now->tm_mon + 1 << "-"
					<< std::setw(2) << now->tm_mday << " "
					<< std::setw(2) << now->tm_hour << ":"
					<< std::setw(2) << now->tm_min << ":"
					<< std::setw(2) << now->tm_sec << "] " << C_RESET
					<< prefixColor + C_BOLD + prefix + C_RESET
					<< prefixColor + ": " + C_RESET
					<< messageColor + str + C_RESET << std::endl;
}

void	signalHandler(int signum) {
	std::cerr << std::endl;
	log(WARNING, "Interrupt signal received");

	server.close();

	exit(signum);
}

template <typename T>
class List : public std::vector<T> {
	public:
		List() {
		}

		List(T item) {
			this->push_back(item);
		}

		List	operator()(T item) {
			this->push_back(item);
			return *this;
		}
};

int main() {
	signal(SIGINT, signalHandler);

	commandManager
		.addCommand(new InviteCommand("INVITE", List<std::string>("I")))
		.addCommand(new JoinCommand("JOIN", List<std::string>("J")))
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

	try {
		server.start(8082, 20);
	} catch (IRCException &e) {
		log(ERROR, std::string(e.what()));
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
