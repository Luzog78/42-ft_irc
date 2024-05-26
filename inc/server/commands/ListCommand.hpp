/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand copy.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 17:27:01 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ListCommand_HPP
# define ListCommand_HPP

# include "server.hpp"

class ListCommand : public Command {
	public:
		ListCommand();
		ListCommand(std::string name, std::vector<std::string> aliases);
		ListCommand(const ListCommand &command);
		ListCommand	&operator=(const ListCommand &command);
		~ListCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
