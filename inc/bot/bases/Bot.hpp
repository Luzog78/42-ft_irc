/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:45:18 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 05:26:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include "bot.hpp"

class Bot {
	private:
		std::string				ip;
		int						port;
		std::string				password;
		bool					connected;

		int						clientSckt;
		struct sockaddr_in		serverAddr;
		pollfd					pollFd;

		std::string				cmdBuffer;

	public:
		Bot();
		Bot(const Bot &bot);
		Bot	&operator=(const Bot &bot);
		~Bot();
		
		void		start(std::string ip, int port, std::string password);
		void		close();
		void		poll();
		void		receive();
		void		send(std::string command);

		std::string	getIp();
		int			getPort();
		std::string	getPassword();
		bool		isConnected();

		class BotException : public IRCException {
			public:
				BotException(std::string message) :
					IRCException("BotException", message) {}
		};
};

#endif
