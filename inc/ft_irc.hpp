/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 10:51:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP


// Standard
# include <algorithm>
# include <unistd.h>
# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <sstream>
# include <string>
# include <vector>
# include <map>

// Time
# include <ctime>

// Sockets
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>

// Signal
# include <csignal>


# define	C_RESET		"\033[0m"
# define	C_RED		"\033[31m"
# define	C_GREEN		"\033[32m"
# define	C_YELLOW	"\033[33m"
# define	C_BLUE		"\033[34m"
# define	C_MAGENTA	"\033[35m"
# define	C_CYAN		"\033[36m"
# define	C_WHITE		"\033[37m"
# define	C_DIM		"\033[2m"
# define	C_BOLD		"\033[1m"


typedef enum e_error_level {
	INFO,
	WARNING,
	ERROR
}	ErrorLevel;


class IRCException : public std::exception {
	private:
		std::string	message;

	public:
		IRCException(std::string prefix = "IRCException", std::string message = "") {
			if (message.empty())
				this->message = prefix.empty() ? "Unknown exception" : prefix;
			else
				this->message = prefix + ": " + message;
		}
		~IRCException() throw() {}

		const char	*what() const throw() {
			return message.c_str();
		}
};

class ITarget;
class Server;
class Client;
class Channel;
class Command;
class CommandManager;

# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "CommandManager.hpp"

# include "NumResponses.hpp"


extern Server			server;
extern CommandManager	commandManager;


std::string	itoa(int n);
void		log(ErrorLevel errorLevel, std::string message, std::string color = "");


#endif
