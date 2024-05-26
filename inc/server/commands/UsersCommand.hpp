/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsersCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 02:58:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UsersCommand_HPP
# define UsersCommand_HPP

# include "server.hpp"

class UsersCommand : public Command {
	public:
		UsersCommand();
		UsersCommand(std::string name, std::vector<std::string> aliases);
		UsersCommand(const UsersCommand &command);
		UsersCommand	&operator=(const UsersCommand &command);
		~UsersCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
