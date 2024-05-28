/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivBotCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:25:32 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:06:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVBOTCOMMAND_HPP
# define PRIVBOTCOMMAND_HPP

# include "bot.hpp"

class PrivBotCommand : public Executor {
	public:
		PrivBotCommand();
		PrivBotCommand(std::string name, std::vector<std::string> aliases);
		PrivBotCommand(const PrivBotCommand &pingBotCommand);
		PrivBotCommand	&operator=(const PrivBotCommand &pingBotCommand);
		~PrivBotCommand();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
