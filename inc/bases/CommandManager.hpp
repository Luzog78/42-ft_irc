/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:40:31 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:18:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDMANAGER_HPP
# define COMMANDMANAGER_HPP

# include "ft_irc.hpp"
# include "UserCommand.hpp"
# include "NickCommand.hpp"
# include "PingCommand.hpp"
# include "PongCommand.hpp"
# include "QuitCommand.hpp"

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
