/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:53:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 05:33:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "server.hpp"

class Client {
	private:
		int							sckt;
		struct sockaddr_in			addr;

		std::string					ip;
		int							port;
		pollfd						pollFd;

		bool						registered;
		std::string					nickname;
		std::string					username;
		std::string					realname;
		std::string					password;
		std::vector<std::string>	channels;

		std::string					commandBuffer;

	public:
		Client();
		Client(int sckt, struct sockaddr_in addr);
		Client(const Client &client);
		Client	&operator=(const Client &client);
		~Client();

		static bool			isLegalNickname(std::string name);
		static bool			isLegalUsername(std::string name);

		void				close();
		std::string			getFullAddress();
		std::string			getPrefix();
		std::string			getLogPrefix();

		void				send(Server &server, std::string command);
		void				send(std::string command, std::string prefix);

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

		bool						isRegistered();
		void						setRegistered(bool registered);
		std::string					getNick();
		void						setNick(std::string nickname);
		std::string					getUsername();
		void						setUsername(std::string username);
		std::string					getRealname();
		void						setRealname(std::string realname);
		std::string					getPass();
		void						setPass(std::string password);
		std::vector<std::string>	getChannels();
		void						addChannel(std::string channel);
		void						removeChannel(std::string channel);
		void						setChannels(std::vector<std::string> channels);
		std::string					getCommandBuffer();
		void						setCommandBuffer(std::string commandBuffer);

		class ClientException : public IRCException {
			public:
				ClientException(std::string message) :
					IRCException("ClientException", message) {}
		};
};

#endif
