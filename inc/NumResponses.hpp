/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumResponses.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:01:27 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 16:16:18 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMRESPONSES_HPP
# define NUMRESPONSES_HPP

# define RPL_WELCOME(nick)				"001 " + nick + " :Welcome to the ft_irc Network " + nick + "!"
# define RPL_YOURHOST(nck, serv, ver)	"002 " + nck + " :Your host is " + serv + ", running version " + ver
# define RPL_CREATED(nick, date)		"003 " + nick + " :This server was created " + date
// # define RPL_MYINFO(server)				"004 " + server + " :ft_irc 1.0 o o"
// # define RPL_USERHOST(nick)				"302 :" + nick
// # define RPL_ISON(nick)					"303 :" + nick
// # define RPL_AWAY(nick, msg)				"301 " + nick + " :" + msg
// # define RPL_UNAWAY						"305 :You are no longer marked as being away"
// # define RPL_NOWAWAY						"306 :You have been marked as being away"
// # define RPL_WHOISUSER(nick, user, host, real)	"311 " + nick + " " + user + " " + host + " * :" + real
// # define RPL_WHOISSERVER(nick, server, serverInfo)	"312 " + nick + " " + server + " :" + serverInfo
// # define RPL_WHOISOPERATOR(nick)			"313 " + nick + " :is an IRC operator"
// # define RPL_WHOISIDLE(nick, idle)		"317 " + nick + " " + idle + " :seconds idle"
// # define RPL_ENDOFWHOIS(nick)			"318 " + nick + " :End of WHOIS list"

# define ERR_NOSUCHNICK(nick)			"401 " + nick + " :No such nick/channel"
# define ERR_NOSUCHSERVER(server)		"402 " + server + " :No such server"
# define ERR_NOSUCHCHANNEL(channel)		"403 " + channel + " :No such channel"
# define ERR_CANNOTSENDTOCHAN(channel)	"404 " + channel + " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS(channel)	"405 " + channel + " :You have joined too many channels"
# define ERR_WASNOSUCHNICK(nick)		"406 " + nick + " :There was no such nickname"
# define ERR_TOOMANYTARGETS(targets)	"407 " + targets + " :Duplicate recipients. No message delivered"
# define ERR_NOORIGIN					"409 :No origin specified"
# define ERR_UNKNOWNCOMMAND(cmd)		"421 " + cmd + " :Unknown command"
# define ERR_NOMOTD						"422 :MOTD File is missing"
# define ERR_NOADMININFO(server)		"423 " + server + " :No administrative info available"
# define ERR_NONICKNAMEGIVEN			"431 :No nickname given"
# define ERR_ERRONEUSNICKNAME(nick)		"432 " + nick + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(nick)		"433 " + nick + " :Nickname is already in use"
# define ERR_UNAVAILRESOURCE(ress)		"437 " + ress + " :Nick/channel is temporarily unavailable"
# define ERR_USERNOTINCHANNEL(nck, chl)	"441 " + nck + " " + chl + " :They aren't on that channel"
# define ERR_NOTONCHANNEL(channel)		"442 " + channel + " :You're not on that channel"
# define ERR_USERONCHANNEL(nick, chl)	"443 " + nick + " " + chl + " :is already on channel"
# define ERR_NOLOGIN(nick)				"444 " + nick + " :User not logged in"
# define ERR_NOTREGISTERED(nick)		"451 " + nick + " :You have not registered"
# define ERR_NEEDMOREPARAMS(cmd)		"461 " + cmd + " :Not enough parameters"
# define ERR_ALREADYREGISTRED			"462 :Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH				"464 :Password incorrect"
# define ERR_YOUREBANNEDCREEP			"465 :You are banned from this server"
# define ERR_UNKNOWNMODE(mode)			"472 " + mode + " :is unknown mode char to me"
# define ERR_NOPRIVILEGES				"481 :Permission Denied- You're not an IRC operator"
# define ERR_CHANOPRIVSNEEDED(channel)	"482 " + channel + " :You're not channel operator"
# define ERR_UMODEUNKNOWNFLAG			"501 :Unknown MODE flag"
# define ERR_USERSDONTMATCH				"502 :Cannot change mode for other users"

#endif
