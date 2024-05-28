/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:30:50 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 14:31:01 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTEXECUTOR_HPP
# define PARTEXECUTOR_HPP

# include "bot.hpp"

class PartExecutor : public Executor {
	public:
		PartExecutor();
		PartExecutor(std::string name, std::vector<std::string> aliases);
		PartExecutor(const PartExecutor &partExecutor);
		PartExecutor	&operator=(const PartExecutor &partExecutor);
		~PartExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
