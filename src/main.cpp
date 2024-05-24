/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 13:42:59 by ysabik           ###   ########.fr       */
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
		.addCommand(new ModeCommand("MODE", List<std::string>("MD")))
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
