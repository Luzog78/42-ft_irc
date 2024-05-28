/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curlRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:22:31 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 07:22:44 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


static std::string		err(std::string msg) {
	std::cerr << msg;
	return "";
}


std::string	curlRequest(std::string url) {
	int			status;
	int			fd[2], fderr[2];
	char		buf[1024] = {0};
	std::string	res;
	char	*av[] = {
		(char *) "/usr/bin/curl",
		(char *) url.c_str(),
		(char *) 0
	};
	char	*env[] = {
		(char *) 0
	};

	if (pipe(fd) == -1 || pipe(fderr) == -1)
		return err("error: fatal\n");
	
	int pid = fork();
	if (!pid) {
		if (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1
			|| dup2(fderr[1], 2) == -1 || close(fderr[0]) == -1 || close(fderr[1]) == -1)
			return err("error: fatal\n");
		execve(av[0], av, env);
		err("error: cannot execute " + std::string(av[0]) + "\n");
		exit(1);
	} else {
		waitpid(pid, &status, 0);
		close(fd[1]);
		close(fderr[1]);
		while (read(fd[0], buf, 1024) > 0)
			res += buf;
		close(fd[0]);
		while (read(fderr[0], buf, 1024) > 0)
			;
		close(fderr[0]);
		return res;
	}
	return res;
}
