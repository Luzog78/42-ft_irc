/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 20:18:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Server	server;

std::string	itoa(int n) {
	std::string str;
	std::stringstream ss;
	ss << n;
	ss >> str;
	return str;
}

void	log(ErrorLevel errorLevel, std::string message) {
	std::time_t			t = std::time(0);
	std::tm*			now = std::localtime(&t);
	std::istringstream	mess(message + "\n");
	std::string			prefix;

	switch (errorLevel)
	{
	case INFO:
		prefix = "[INFO]    :";
		break;
	case WARNING:
		prefix = "[WARNING] :";
		break;
	case ERROR:
		prefix = "[ERROR]   :";
		break;
	default:
		prefix = "          :";
		break;
	}

	for (std::string str; std::getline(mess, str);)
		std::cout	<< std::setfill('0') << "["
					<< std::setw(4) << now->tm_year + 1900 << "-"
					<< std::setw(2) << now->tm_mon + 1 << "-"
					<< std::setw(2) << now->tm_mday << " "
					<< std::setw(2) << now->tm_hour << ":"
					<< std::setw(2) << now->tm_min << ":"
					<< std::setw(2) << now->tm_sec << "] "
					<< prefix << " " << str << std::endl;
}

void	signalHandler(int signum) {
	log(WARNING, "Interrupt signal received");

	server.close();

	exit(signum);
}

int main() {
	signal(SIGINT, signalHandler);

	try {
		server.start(8080, 20);
	} catch (IRCException &e) {
		log(ERROR, e.what());
		return 1;
	}

	while (true) {
		try {
			server.accept();
			server.poll();
		} catch (IRCException &e) {
			log(ERROR, e.what());
			break;
		}
	}

	log(INFO, "STOP.");

	server.close();

	return 0;
}
