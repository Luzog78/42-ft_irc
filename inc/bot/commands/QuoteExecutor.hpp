/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuoteExecutor.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 10:37:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTEEXECUTOR_HPP
# define QUOTEEXECUTOR_HPP

# include "bot.hpp"

class QuoteExecutor : public Executor {
	public:
		QuoteExecutor();
		QuoteExecutor(std::string name, std::vector<std::string> aliases);
		QuoteExecutor(const QuoteExecutor &quoteExecutor);
		QuoteExecutor	&operator=(const QuoteExecutor &quoteExecutor);
		~QuoteExecutor();

		bool		exec(Bot *bot, std::string label, std::string prefix,
						std::vector<std::string> args, std::string sender,
						std::string target);
		std::string	getDesc();
		std::string	getUsage();
};

#endif
