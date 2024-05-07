/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:41:06 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 09:12:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Channel {
	private:
		std::string			name;
		std::vector<int>	clients;

	public:
		Channel();
		Channel(std::string name);
		Channel(const Channel &channel);
		Channel	&operator=(const Channel &channel);
		~Channel();

		std::string			getName();
		void				setName(std::string name);
		std::vector<int>	getClients();
		void				setClients(std::vector<int> clients);

		class ChannelException : public IRCException {
			public:
				ChannelException(std::string message) :
					IRCException("ChannelException", message) {}
		};
};

#endif
