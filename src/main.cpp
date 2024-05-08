/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:27:32 by ysabik           ###   ########.fr       */
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
class List {
	private:
		std::vector<T>	list;
	
	public:
		List() {
		}

		List(T item) {
			add(item);
		}

		List	operator()(T item) {
			add(item);
			return *this;
		}

		List	add(T item) {
			list.push_back(item);
			return *this;
		}
		
		T	get(size_t index) {
			return list[index];
		}

		size_t	size() {
			return list.size();
		}

		List	clear() {
			list.clear();
			return *this;
		}

		List	remove(size_t index) {
			list.erase(list.begin() + index);
			return *this;
		}

		std::vector<T>	vec() {
			return list;
		}
};

int main() {
	signal(SIGINT, signalHandler);

	commandManager
		.addCommand(new UserCommand("USER", std::vector<std::string>()))
		.addCommand(new NickCommand("NICK", std::vector<std::string>()))
		.addCommand(new PingCommand("PING", std::vector<std::string>()))
		.addCommand(new PongCommand("PONG", std::vector<std::string>()))
		.addCommand(new QuitCommand("QUIT", std::vector<std::string>()))
		;

	try {
		server.start(8080, 20);
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
