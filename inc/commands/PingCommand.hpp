/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:10:09 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCOMMAND_HPP
# define PINGCOMMAND_HPP

# include "ft_irc.hpp"

class PingCommand : public Command {
	public:
		PingCommand();
		PingCommand(std::string name, std::vector<std::string> aliases);
		PingCommand(const PingCommand &command);
		PingCommand	&operator=(const PingCommand &command);
		~PingCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
