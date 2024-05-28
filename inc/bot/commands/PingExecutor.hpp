/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:06:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGEXECUTOR_HPP
# define PINGEXECUTOR_HPP

# include "bot.hpp"

class PingExecutor : public Executor {
	public:
		PingExecutor();
		PingExecutor(std::string name, std::vector<std::string> aliases);
		PingExecutor(const PingExecutor &pingExecutor);
		PingExecutor	&operator=(const PingExecutor &pingExecutor);
		~PingExecutor();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
