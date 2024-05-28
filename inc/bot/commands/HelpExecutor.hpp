/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:36:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPEXECUTOR_HPP
# define HELPEXECUTOR_HPP

# include "bot.hpp"

class HelpExecutor : public Executor {
	public:
		HelpExecutor();
		HelpExecutor(std::string name, std::vector<std::string> aliases);
		HelpExecutor(const HelpExecutor &helpExecutor);
		HelpExecutor	&operator=(const HelpExecutor &helpExecutor);
		~HelpExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
