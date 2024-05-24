/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:40:31 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 15:17:00 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include "ft_irc.hpp"
# include "InviteCommand.hpp"
# include "JoinCommand.hpp"
# include "KickCommand.hpp"
# include "ModeCommand.hpp"
# include "NamesCommand.hpp"
# include "NickCommand.hpp"
# include "PartCommand.hpp"
# include "PingCommand.hpp"
# include "PongCommand.hpp"
# include "PrivCommand.hpp"
# include "QuitCommand.hpp"
# include "TopicCommand.hpp"
# include "UserCommand.hpp"

class CommandManager {
	private:
		std::vector<Command *>	commands;

		int	getCommandIndex(std::string name);

	public:
		CommandManager();
		CommandManager(const CommandManager &commandManager);
		CommandManager	&operator=(const CommandManager &commandManager);
		~CommandManager();

		CommandManager			&addCommand(Command *command);
		CommandManager			&removeCommand(std::string name);
		Command					*getCommand(std::string name);
		std::vector<Command *>	getCommands();
		CommandManager			&setCommands(std::vector<Command *> commands);

		bool	exec(Server &server, Client &client, std::string raw);
		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
