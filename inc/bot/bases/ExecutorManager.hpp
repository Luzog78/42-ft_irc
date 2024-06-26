/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecutorManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:48:10 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:51:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTORMANAGER_HPP
# define EXECUTORMANAGER_HPP

# include "bot.hpp"

# include "FactExecutor.hpp"
# include "HelpExecutor.hpp"
# include "JoinExecutor.hpp"
# include "JokeExecutor.hpp"
# include "PartExecutor.hpp"
# include "PingBotCommand.hpp"
# include "PingExecutor.hpp"
# include "PongBotCommand.hpp"
# include "PongExecutor.hpp"
# include "PrivBotCommand.hpp"
# include "QuitExecutor.hpp"
# include "QuoteExecutor.hpp"
# include "SayExecutor.hpp"

class ExecutorManager {
	private:
		std::vector<Executor *>	executors;

	public:
		ExecutorManager();
		ExecutorManager(const ExecutorManager &executorManager);
		ExecutorManager	&operator=(const ExecutorManager &executorManager);
		~ExecutorManager();

		ExecutorManager			&addExecutor(Executor *executor);
		Executor				*getExecutor(std::string executor);
		bool					exec(Bot *bot, CommandResponse *commandResponse);

		std::vector<Executor *>	getExecutors();
		void					setExecutors(std::vector<Executor *> executors);
};

#endif
