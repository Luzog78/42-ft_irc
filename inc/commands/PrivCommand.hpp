/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:13:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/22 14:38:53 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVCOMMAND_HPP
# define PRIVCOMMAND_HPP

# include "ft_irc.hpp"

class PrivCommand : public Command {
	public:
		PrivCommand();
		PrivCommand(std::string name, std::vector<std::string> aliases);
		PrivCommand(const PrivCommand &command);
		PrivCommand	&operator=(const PrivCommand &command);
		~PrivCommand();

		bool	exec(Server &server, Client &client, std::string label,
					std::string prefix, std::string args[], int argsCount);
};

#endif
