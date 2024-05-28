/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:36:36 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTEXECUTOR_HPP
# define FACTEXECUTOR_HPP

# include "bot.hpp"

class FactExecutor : public Executor {
	public:
		FactExecutor();
		FactExecutor(std::string name, std::vector<std::string> aliases);
		FactExecutor(const FactExecutor &factExecutor);
		FactExecutor	&operator=(const FactExecutor &factExecutor);
		~FactExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
