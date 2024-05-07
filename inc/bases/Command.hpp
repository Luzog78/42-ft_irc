/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 07:22:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/07 11:00:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "ft_irc.hpp"

class Command {
	protected:
		std::string					name;
		std::vector<std::string>	aliases;

	public:
		Command();
		Command(std::string name, std::vector<std::string> aliases);
		Command(const Command &command);
		Command	&operator=(const Command &command);
		virtual ~Command();

		std::string					getName();
		void						setName(std::string name);
		std::vector<std::string>	getAliases();
		void						setAliases(std::vector<std::string> aliases);

		virtual bool	exec(Server &server, Client &client, std::string label,
							std::string prefix, std::string args[], int argsCount) = 0;

		class CommandException : public IRCException {
			public:
				CommandException(std::string message) :
					IRCException("CommandException", message) {}
		};
};

#endif
