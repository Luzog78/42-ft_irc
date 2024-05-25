/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumResponses.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:01:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 17:26:42 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMRESPONSES_HPP
# define NUMRESPONSES_HPP

# define RPL_WELCOME(n)						"001 " + n + " :Welcome to the ft_irc Network " + n + "!"
# define RPL_YOURHOST(n, serv, ver)			"002 " + n + " :Your host is " + serv + ", running version " + ver
# define RPL_CREATED(n, date)				"003 " + n + " :This server was created " + date
# define RPL_CHANNELMODEIS(n, chan, md)		"324 " + n + " " + chan + " " + md
# define RPL_NOTOPIC(n, chan)				"331 " + n + " " + chan + " :No topic is set"
# define RPL_TOPIC(n, chan, topic)			"332 " + n + " " + chan + " :" + topic
# define RPL_INVITING(n, nick, chan)		"341 " + n + " " + nick + " " + chan
# define RPL_NAMREPLY(n, chan, nicks)		"353 " + n + " = " + chan + " :" + nicks
# define RPL_ENDOFNAMES(n, chan)			"366 " + n + " " + chan + " :End of /NAMES list"

# define ERR_NOSUCHNICK(n, nick)			"401 " + n + " " + nick + " :No such nick/channel"
# define ERR_NOSUCHCHANNEL(n, chan)			"403 " + n + " " + chan + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(n, chan)		"404 " + n + " " + chan + " :Cannot send to channel"
# define ERR_NOORIGIN(n)					"409 " + n + " :No origin specified"
# define ERR_NORECIPIENT(n)					"411 " + n + " :No recipient given"
# define ERR_NOTEXTTOSEND(n)				"412 " + n + " :No text to send"
# define ERR_UNKNOWNCOMMAND(n, cmd)			"421 " + n + " " + cmd + " :Unknown command"
# define ERR_NONICKNAMEGIVEN(n)				"431 " + n + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(n, nick)		"432 " + n + " " + nick + " :Erroneous nickname"
# define ERR_NICKNAMEINUSE(n, nick)			"433 " + n + " " + nick + " :Nickname is already in use"
# define ERR_USERNOTINCHANNEL(n, nick, chn)	"441 " + n + " " + nick + " " + chn + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(n, chan)			"442 " + n + " " + chan + " :You're not on that channel"
# define ERR_USERONCHANNEL(n, nick, chan)	"443 " + n + " " + nick + " " + chan + " :is already on channel"
# define ERR_NEEDMOREPARAMS(n, cmd)			"461 " + n + " " + cmd + " :Not enough parameters"
# define ERR_ALREADYREGISTRED(n)			"462 " + n + " :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH(n)				"464 " + n + " :Password incorrect"
# define ERR_CHANNELISFULL(n, chan)			"471 " + n + " " + chan + " :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE(n, mode)			"472 " + n + " " + mode + " :is unknown mode char to me"
# define ERR_INVITEONLYCHAN(n, chan)		"473 " + n + " " + chan + " :Cannot join channel (+i)"
# define ERR_BADCHANNELKEY(n, chan)			"475 " + n + " " + chan + " :Cannot join channel (+k)"
# define ERR_CHANOPRIVSNEEDED(n, chan)		"482 " + n + " " + chan + " :You're not channel operator"

#endif
