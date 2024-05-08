/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/08 17:18:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "ft_irc.hpp"

class QuitCommand : public Command {
	public:
		QuitCommand();
		QuitCommand(std::string name, std::vector<std::string> aliases);
		QuitCommand(const QuitCommand &command);
		QuitCommand	&operator=(const QuitCommand &command);
		~QuitCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
