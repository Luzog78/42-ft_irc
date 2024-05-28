/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:26:47 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:03:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "bot.hpp"

class Response {
	protected:
		std::string	raw;
		std::string	prefix;
		std::string	sender;

		bool		numeric;

	public:
		Response();
		Response(const Response &response);
		Response	&operator=(const Response &response);
		virtual ~Response();

		static Response	*parse(std::string raw);

		NumericResponse	*asNumeric();
		CommandResponse	*asCommand();

		std::string		getRaw();
		void			setRaw(std::string raw);
		std::string		getPrefix();
		void			setPrefix(std::string prefix);
		std::string		getSender();
		void			setSender(std::string sender);
		bool			isNumeric();
};

#endif
