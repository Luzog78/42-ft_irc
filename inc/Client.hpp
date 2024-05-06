/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:53:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/06 20:04:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client {
	private:
		int					sckt;
		struct sockaddr_in	addr;

		std::string			ip;
		int					port;

	public:
		Client();
		Client(int sckt, struct sockaddr_in addr);
		Client(const Client &client);
		Client	&operator=(const Client &client);
		~Client();

		void				close();
		std::string			getFullAddress();

		std::string			getIp();
		int					getPort();
		int					getSocket();
		void				setSocket(int sckt);
		struct sockaddr_in	getAddr();
		void				setAddr(struct sockaddr_in addr);
		struct sockaddr_in	*getAddrPtr();

		class ClientException : public IRCException {
			private:
				const char	*message;

			public:
				ClientException(std::string message) {
					this->message = message.c_str();
				}

				const char	*what() const throw() {
					return message;
				}
		};
};

#endif
