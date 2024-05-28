/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:06:58 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:07:07 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINEXECUTOR_HPP
# define JOINEXECUTOR_HPP

# include "bot.hpp"

class JoinExecutor : public Executor {
	public:
		JoinExecutor();
		JoinExecutor(std::string name, std::vector<std::string> aliases);
		JoinExecutor(const JoinExecutor &joinExecutor);
		JoinExecutor	&operator=(const JoinExecutor &joinExecutor);
		~JoinExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
