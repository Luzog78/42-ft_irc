/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:34:44 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:03:10 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDRESPONSE_HPP
# define COMMANDRESPONSE_HPP

# include "bot.hpp"

class CommandResponse : public Response {
	private:
		std::string					label;
		std::string					target;
		std::vector<std::string>	args;

	public:
		CommandResponse();
		CommandResponse(const CommandResponse &commandResponse);
		CommandResponse	&operator=(const CommandResponse &commandResponse);
		~CommandResponse();

		std::string					getLabel();
		void						setLabel(std::string label);
		std::string					getTarget();
		void						setTarget(std::string target);
		std::vector<std::string>	getArgs();
		void						setArgs(std::vector<std::string> args);
};

#endif
