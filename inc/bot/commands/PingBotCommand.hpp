/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingBotCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:24:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:06:46 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGBOTCOMMAND_HPP
# define PINGBOTCOMMAND_HPP

# include "bot.hpp"

class PingBotCommand : public Executor {
	public:
		PingBotCommand();
		PingBotCommand(std::string name, std::vector<std::string> aliases);
		PingBotCommand(const PingBotCommand &pingBotCommand);
		PingBotCommand	&operator=(const PingBotCommand &pingBotCommand);
		~PingBotCommand();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
