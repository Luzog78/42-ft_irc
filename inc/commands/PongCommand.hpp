/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:10:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONGCOMMAND_HPP
# define PONGCOMMAND_HPP

# include "ft_irc.hpp"

class PongCommand : public Command {
	public:
		PongCommand();
		PongCommand(std::string name, std::vector<std::string> aliases);
		PongCommand(const PongCommand &command);
		PongCommand	&operator=(const PongCommand &command);
		~PongCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
