/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:45:18 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:14:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include "bot.hpp"

class Bot {
	private:
		bool					running;
		pthread_mutex_t			runningMutex;

		std::string				ip;
		int						port;
		std::string				password;
		bool					connected;

		int						clientSckt;
		struct sockaddr_in		serverAddr;
		pollfd					pollFd;

		std::string				cmdBuffer;
		std::vector<Response *>	queue;
		std::vector<Response *>	responses;
		pthread_mutex_t			responsesMutex;
		bool					waitingForResponse;
		pthread_mutex_t			waitingForResponseMutex;
		bool					executingCommand;
		pthread_mutex_t			executingCommandMutex;
		pthread_t				executingThread;

	public:
		Bot();
		Bot(const Bot &bot);
		Bot	&operator=(const Bot &bot);
		~Bot();

		static void		*executeCommand(void *_bot);
		static void		*welcome(void *_bot);
		
		void		start(std::string ip, int port, std::string password);
		void		close();
		void		poll();
		void		receive();
		void		execute();
		void		send(std::string target, std::string command);
		void		send(std::string target, std::string command, long long waiting);
		void		send(std::string command);
		void		send(std::string command, long long waiting);
		void		tryCommand(std::string command, long long waiting);
		void		emptyResponsesToQueue();

		bool		isRunning();
		void		setRunning(bool running);

		std::string	getIp();
		int			getPort();
		std::string	getPassword();
		bool		isConnected();

		std::vector<Response *>	getQueue();
		std::vector<Response *>	getResponses();

		bool		isWaitingForResponse();
		void		setWaitingForResponse(bool waitingForResponse);
		bool		isExecutingCommand();
		void		setExecutingCommand(bool executingCommand);
		
		pthread_mutex_t	*getRunningMutex();
		pthread_mutex_t	*getResponsesMutex();
		pthread_mutex_t	*getWaitingForResponseMutex();
		pthread_mutex_t	*getExecutingCommandMutex();

		class BotException : public IRCException {
			public:
				BotException(std::string message) :
					IRCException("BotException", message) {}
		};
};

#endif
