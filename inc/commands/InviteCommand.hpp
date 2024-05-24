/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 11:25:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "ft_irc.hpp"

class InviteCommand : public Command {
	public:
		InviteCommand();
		InviteCommand(std::string name, std::vector<std::string> aliases);
		InviteCommand(const InviteCommand &command);
		InviteCommand	&operator=(const InviteCommand &command);
		~InviteCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
