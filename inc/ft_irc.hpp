/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:53:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 20:13:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP


// Standard
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


typedef enum e_error_level {
	INFO,
	DATA,
	WARNING,
	ERROR
}	ErrorLevel;


class IRCException : public std::exception {};
class Server;
class Client;

# include "Server.hpp"
# include "Client.hpp"


extern Server	server;


std::string	itoa(int n);
void		log(ErrorLevel errorLevel, std::string message);


#endif
