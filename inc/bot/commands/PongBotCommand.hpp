/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongBotCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:24:30 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:06:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONGBOTCOMMAND_HPP
# define PONGBOTCOMMAND_HPP

# include "bot.hpp"

class PongBotCommand : public Executor {
	public:
		PongBotCommand();
		PongBotCommand(std::string name, std::vector<std::string> aliases);
		PongBotCommand(const PongBotCommand &pingBotCommand);
		PongBotCommand	&operator=(const PongBotCommand &pingBotCommand);
		~PongBotCommand();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
