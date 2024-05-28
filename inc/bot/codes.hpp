/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:40:24 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 09:57:08 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODES_HPP
# define CODES_HPP

# define CRPL_WELCOME			1
# define CRPL_YOURHOST			2
# define CRPL_CREATED			3
# define CRPL_CHANNELMODEIS		324
# define CRPL_NOTOPIC			331
# define CRPL_TOPIC				332
# define CRPL_INVITING			341
# define CRPL_NAMREPLY			353
# define CRPL_ENDOFNAMES		366

# define CERR_NOSUCHNICK		401
# define CERR_NOSUCHCHANNEL		403
# define CERR_CANNOTSENDTOCHAN	404
# define CERR_NOORIGIN			409
# define CERR_NORECIPIENT		411
# define CERR_NOTEXTTOSEND		412
# define CERR_UNKNOWNCOMMAND	421
# define CERR_NONICKNAMEGIVEN	431
# define CERR_ERRONEUSNICKNAME	432
# define CERR_NICKNAMEINUSE		433
# define CERR_USERNOTINCHANNEL	441
# define CERR_NOTONCHANNEL		442
# define CERR_USERONCHANNEL		443
# define CERR_NEEDMOREPARAMS	461
# define CERR_ALREADYREGISTRED	462
# define CERR_PASSWDMISMATCH	464
# define CERR_CHANNELISFULL		471
# define CERR_UNKNOWNMODE		472
# define CERR_INVITEONLYCHAN	473
# define CERR_BADCHANNELKEY		475
# define CERR_CHANOPRIVSNEEDED	482

# define IS_FATAL(code)			(code >= 400 && code < 600)

#endif
