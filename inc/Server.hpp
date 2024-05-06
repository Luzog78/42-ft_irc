/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:53:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 19:55:51 by ysabik           ###   ########.fr       */
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

		std::map<int, Client>	clients;
		std::vector<pollfd>		pollfds;

	public:
		Server();
		Server(const Server &server);
		Server	&operator=(const Server &server);
		~Server();

		void					start(int port, int maxClients);
		void					accept();
		void					poll();
		void					close();

		std::string				getFullAddress();
		
		int						getPort();
		int						getMaxClients();
		int						getSocket();
		void					setSocket(int sckt);
		struct sockaddr_in		getAddr();
		void					setAddr(struct sockaddr_in addr);
		struct sockaddr_in		*getAddrPtr();
		std::map<int, Client>	getClients();
		void					setClients(std::map<int, Client> clients);
		std::vector<pollfd>		getPollfds();
		void					setPollfds(std::vector<pollfd> pollfds);

		class ServerException : public IRCException {
			private:
				const char	*message;

			public:
				ServerException(std::string message) {
					this->message = message.c_str();
				}

				const char	*what() const throw() {
					return message;
				}
		};
};

#endif
