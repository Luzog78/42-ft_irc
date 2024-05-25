/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCException.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:55:45 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/24 18:55:59 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCEXCEPTION_HPP
# define IRCEXCEPTION_HPP

# include "ft_irc.hpp"

class IRCException : public std::exception {
	private:
		std::string	message;

	public:
		IRCException(std::string prefix = "IRCException", std::string message = "") {
			if (message.empty())
				this->message = prefix.empty() ? "Unknown exception" : prefix;
			else
				this->message = prefix + ": " + message;
		}
		~IRCException() throw() {}

		const char	*what() const throw() {
			return message.c_str();
		}
};

#endif
