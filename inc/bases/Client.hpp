/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:53:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 06:53:00 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client {
	private:
		int							sckt;
		struct sockaddr_in			addr;

		std::string					ip;
		int							port;
		pollfd						pollFd;

		std::string					nickname;
		std::string					username;
		std::string					realname;
		std::vector<std::string>	channels;

	public:
		Client();
		Client(int sckt, struct sockaddr_in addr);
		Client(const Client &client);
		Client	&operator=(const Client &client);
		~Client();

		void				close();
		std::string			getFullAddress();

		void				sendCommand(std::string command);

		std::string			getIp();
		int					getPort();
		int					getSocket();
		void				setSocket(int sckt);
		struct sockaddr_in	getAddr();
		struct sockaddr_in	*getAddrPtr();
		void				setAddr(struct sockaddr_in addr);
		pollfd				getPollFd();
		pollfd				*getPollFdPtr();
		void				setPollFd(pollfd pollFd);

		std::string			getNickname();
		void				setNickname(std::string nickname);
		std::string			getUsername();
		void				setUsername(std::string username);
		std::string			getRealname();
		void				setRealname(std::string realname);

		class ClientException : public IRCException {
			public:
				ClientException(std::string message) :
					IRCException("ClientException", message) {}
		};
};

#endif
