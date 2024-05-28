/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:51:20 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 00:56:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP

# include "bot.hpp"

class Executor {
	protected:
		std::string					name;
		std::vector<std::string>	aliases;

	public:
		Executor();
		Executor(std::string name, std::vector<std::string> aliases);
		Executor(const Executor &command);
		Executor	&operator=(const Executor &command);
		virtual ~Executor();

		std::string					getName();
		void						setName(std::string name);
		std::vector<std::string>	getAliases();
		void						setAliases(std::vector<std::string> aliases);

		virtual bool				exec(Bot *bot,
										std::string label,
										std::string prefix,
										std::vector<std::string> args,
										std::string sender,
										std::string target) = 0;
};

#endif
