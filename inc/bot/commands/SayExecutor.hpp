/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SayExecutor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:51:00 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:51:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAYEXECUTOR_HPP
# define SAYEXECUTOR_HPP

# include "bot.hpp"

class SayExecutor : public Executor {
	public:
		SayExecutor();
		SayExecutor(std::string name, std::vector<std::string> aliases);
		SayExecutor(const SayExecutor &sayExecutor);
		SayExecutor	&operator=(const SayExecutor &sayExecutor);
		~SayExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
