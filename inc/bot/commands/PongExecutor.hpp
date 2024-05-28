/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:31:46 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:31:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONGEXECUTOR_HPP
# define PONGEXECUTOR_HPP

# include "bot.hpp"

class PongExecutor : public Executor {
	public:
		PongExecutor();
		PongExecutor(std::string name, std::vector<std::string> aliases);
		PongExecutor(const PongExecutor &pongExecutor);
		PongExecutor	&operator=(const PongExecutor &pongExecutor);
		~PongExecutor();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
