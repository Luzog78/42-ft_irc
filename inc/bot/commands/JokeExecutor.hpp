/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JokeExecutor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:58:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 06:30:17 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOKEEXECUTOR_HPP
# define JOKEEXECUTOR_HPP

# include "bot.hpp"

class JokeExecutor : public Executor {
	public:
		JokeExecutor();
		JokeExecutor(std::string name, std::vector<std::string> aliases);
		JokeExecutor(const JokeExecutor &jokeExecutor);
		JokeExecutor	&operator=(const JokeExecutor &jokeExecutor);
		~JokeExecutor();

		bool	exec(Bot *bot, std::string label, std::string prefix,
					std::vector<std::string> args, std::string sender,
					std::string target);
};

#endif
