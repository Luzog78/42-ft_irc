/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:50:59 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/26 03:00:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


std::string	itoa(int n) {
	std::string str;
	std::stringstream ss;
	ss << n;
	ss >> str;
	return str;
}


bool	startsWith(const std::string str, const std::string prefix) {
	return str.compare(0, prefix.size(), prefix) == 0;
}


void	log(ErrorLevel errorLevel, std::string message, std::string color) {
	std::time_t			t = std::time(0);
	std::tm*			now = std::localtime(&t);
	std::istringstream	mess(message);
	std::string			prefix;
	std::string			prefixColor = "", messageColor = "";

	switch (errorLevel)
	{
	case INFO:
		prefix = "[INFO]    ";
		messageColor = color;
		break;
	case WARNING:
		prefix = "[WARNING] ";
		prefixColor = C_YELLOW;
		messageColor = color.empty() ? C_YELLOW : color;
		break;
	case ERROR:
		prefix = "[ERROR]   ";
		prefixColor = C_RED;
		messageColor = color.empty() ? C_RED : color;
		break;
	default:
		prefix = "          ";
		messageColor = color;
		break;
	}

	for (std::string str; std::getline(mess, str);)
		std::cout	<< C_DIM << std::setfill('0') << "["
					<< std::setw(4) << now->tm_year + 1900 << "-"
					<< std::setw(2) << now->tm_mon + 1 << "-"
					<< std::setw(2) << now->tm_mday << " "
					<< std::setw(2) << now->tm_hour << ":"
					<< std::setw(2) << now->tm_min << ":"
					<< std::setw(2) << now->tm_sec << "] " << C_RESET
					<< prefixColor + C_BOLD + prefix + C_RESET
					<< prefixColor + ": " + C_RESET
					<< messageColor + str + C_RESET << std::endl;
}
