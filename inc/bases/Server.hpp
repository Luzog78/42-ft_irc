/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:53:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:26:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class Server {
	private:
		int						port;
		int						maxClients;

		int						sckt;
		struct sockaddr_in		addr;

		std::vector<Client>		clients;
		std::vector<Channel>	channels;

		pollfd					acceptPoll;
		std::string				cmdBuffer;


		std::vector<pollfd>		_pollfds;

	public:
		Server();
		Server(const Server &server);
		Server	&operator=(const Server &server);
		~Server();

		void					start(int port, int maxClients);
		void					poll();
		void					accept();
		void					receive();
		void					close();

		void					welcome(Client &client);
		void					removeClient(Client &client);

		std::string					getFullAddress();
		std::vector<std::string>	getNicknames();
		
		int						getPort();
		int						getMaxClients();
		int						getSocket();
		void					setSocket(int sckt);
		struct sockaddr_in		getAddr();
		void					setAddr(struct sockaddr_in addr);
		struct sockaddr_in		*getAddrPtr();
		std::vector<Client>		getClients();
		void					setClients(std::vector<Client> clients);
		std::vector<Channel>	getChannels();
		void					setChannels(std::vector<Channel> channels);
		pollfd					getAcceptPoll();
		pollfd					*getAcceptPollPtr();
		void					setAcceptPoll(pollfd acceptPoll);
		std::string				getCmdBuffer();
		void					setCmdBuffer(std::string cmdBuffer);

		class ServerException : public IRCException {
			public:
				ServerException(std::string message) :
					IRCException("ServerException", message) {}
		};
};

#endif
