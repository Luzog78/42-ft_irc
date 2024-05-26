/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 20:49:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NamesCommand_HPP
# define NamesCommand_HPP

# include "server.hpp"

class NamesCommand : public Command {
	public:
		NamesCommand();
		NamesCommand(std::string name, std::vector<std::string> aliases);
		NamesCommand(const NamesCommand &command);
		NamesCommand	&operator=(const NamesCommand &command);
		~NamesCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
