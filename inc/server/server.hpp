/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:48:52 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 02:58:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef server_HPP
# define server_HPP

# include "ft_irc.hpp"


class ITarget;
class Server;
class Client;
class Channel;
class Command;
class CommandManager;

# include "IRCException.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "CommandManager.hpp"


extern Server			server;
extern CommandManager	commandManager;

#endif
