/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:17 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:41:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITEXECUTOR_HPP
# define QUITEXECUTOR_HPP

# include "bot.hpp"

class QuitExecutor : public Executor {
	public:
		QuitExecutor();
		QuitExecutor(std::string name, std::vector<std::string> aliases);
		QuitExecutor(const QuitExecutor &quitExecutor);
		QuitExecutor	&operator=(const QuitExecutor &quitExecutor);
		~QuitExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
