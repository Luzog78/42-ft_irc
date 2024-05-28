/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:31:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 07:34:28 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICRESPONSE_HPP
# define NUMERICRESPONSE_HPP

# include "bot.hpp"

class NumericResponse : public Response {
	private:
		int							code;
		std::vector<std::string>	args;
		std::string					message;

	public:
		NumericResponse();
		NumericResponse(const NumericResponse &numericResponse);
		NumericResponse	&operator=(const NumericResponse &numericResponse);
		~NumericResponse();

		int							getCode();
		void						setCode(int code);
		std::vector<std::string>	getArgs();
		void						setArgs(std::vector<std::string> args);
		void						addArg(std::string arg);
		std::string					getMessage();
		void						setMessage(std::string message);
};

#endif
