/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:41:06 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 17:28:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Channel {
	private:
		std::string					name;

		std::string					owner;
		std::vector<std::string>	operators;

		std::vector<int>			members;

		bool						inviteOnly;
		std::vector<std::string>	invited;
		bool						topicRestricted;
		std::string					topic;
		std::string					key;
		bool						limited;
		size_t						limit;


	public:
		Channel();
		Channel(std::string name, std::string ownerAddr);
		Channel(const Channel &channel);
		Channel	&operator=(const Channel &channel);
		~Channel();

		static bool					isLegalName(std::string name);
		static bool					isLegalKey(std::string key);

		std::vector<Client>			getOnlineClients(Server &server);
		bool						hasRight(std::string nick, std::string addr);
		bool						isMember(int socket);
		bool						isFull();
		std::string					getMemberNicks();
		bool						isOperator(std::string addr);
		bool						isInvited(std::string nick);

		void						broadcast(Server &server, std::string command);
		void						broadcast(Server &server, std::string command, std::string prefix);

		std::string					getName();
		void						setName(std::string name);
		std::string					getOwner();
		void						setOwner(std::string ownerAddr);
		std::vector<std::string>	getOperators();
		void						addOperator(std::string addr);
		void						removeOperator(std::string addr);
		void						setOperators(std::vector<std::string> operators);
		std::vector<int>			getMembers();
		void						addMember(int socket);
		void						removeMember(int socket);
		void						setMembers(std::vector<int> sockets);
		bool						isInviteOnly();
		void						setInviteOnly(bool inviteOnly);
		std::vector<std::string>	getInvited();
		void						addInvited(std::string invited);
		void						removeInvited(std::string invited);
		void						setInvited(std::vector<std::string> invited);
		bool						isTopicRestricted();
		void						setTopicRestricted(bool topicRestricted);
		std::string					getTopic();
		void						setTopic(std::string topic);
		std::string					getKey();
		void						setKey(std::string key);
		bool						isLimited();
		void						setLimited(bool limited);
		size_t						getLimit();
		void						setLimit(size_t limit);

		class ChannelException : public IRCException {
			public:
				ChannelException(std::string message) :
					IRCException("ChannelException", message) {}
		};
};

#endif
