/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:50:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 07:23:06 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef bot_HPP
# define bot_HPP

# include "ft_irc.hpp"
# include "codes.hpp"

# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>


class Bot;
class Response;
class CommandResponse;
class NumericResponse;
class Executor;
class ExecutorManager;

# include "Bot.hpp"
# include "Response.hpp"
# include "NumericResponse.hpp"
# include "CommandResponse.hpp"
# include "Executor.hpp"
# include "ExecutorManager.hpp"


extern Bot				bot;
extern ExecutorManager	executorManager;


std::string	curlRequest(std::string url);

#endif
