/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:44:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/28 01:28:04 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Bot::Bot() {
	running = false;
	connected = false;
	serverAddr = (struct sockaddr_in){};
	pollFd = (struct pollfd){};

	pthread_mutex_init(&runningMutex, NULL);
	pthread_mutex_init(&responsesMutex, NULL);
	pthread_mutex_init(&waitingForResponseMutex, NULL);
	pthread_mutex_init(&executingCommandMutex, NULL);
}


Bot::Bot(const Bot &bot) {
	*this = bot;
}


Bot &Bot::operator=(const Bot &bot) {
	if (this != &bot) {
		ip = bot.ip;
		port = bot.port;
		password = bot.password;
	}
	return *this;
}


Bot::~Bot() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


void	Bot::start(std::string ip, int port, std::string password) {
	this->ip = ip;
	this->port = port;
	this->password = password;

	if (port < 1024 || port > 65535)
		throw BotException("Illegal port number (port: " + itoa(port) + ")");

	clientSckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSckt < 0)
		throw BotException("Socket creation failed");

	if (fcntl(clientSckt, F_SETFL, O_NONBLOCK) < 0)
		throw BotException("fcntl failed");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0)
		throw BotException("IP address not supported (" + ip + ")");
	connect(clientSckt, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	// connect will return -1 and set errno to EINPROGRESS
	//  because the connection is in progress. We will check
	//  the connection status in poll() function.
	setRunning(true);
}


void	Bot::close() {
	if (clientSckt >= 0)
		::close(clientSckt);
	clientSckt = -1;
	log(INFO, "Disconnected from " + ip + ":" + itoa(port));

	pthread_mutex_lock(&responsesMutex);
	for (size_t i = 0; i < queue.size(); i++)
		delete queue[i];
	queue.clear();
	for (size_t i = 0; i < responses.size(); i++)
		delete responses[i];
	responses.clear();
	pthread_mutex_unlock(&responsesMutex);

	pthread_mutex_destroy(&runningMutex);
	pthread_mutex_destroy(&responsesMutex);
	pthread_mutex_destroy(&waitingForResponseMutex);
	pthread_mutex_destroy(&executingCommandMutex);
}


void	Bot::poll() {
	if (!isRunning())
		return;
	pollFd.fd = clientSckt;
	pollFd.events = connected ? POLLIN | POLLOUT : POLLOUT;

	if (::poll(&pollFd, 1, 0) < 0)
		throw BotException("Poll failed");

	if (connected)
		receive();
	else if (pollFd.revents & (POLLHUP | POLLNVAL) || pollFd.revents & POLLERR)
		throw BotException("Connection failed (" + ip + ":" + itoa(port) + ")");
	else if (pollFd.revents & POLLOUT) {
		connected = true;
		log(INFO, "Connected to " + ip + ":" + itoa(port));
		send("PASS :" + password);
		send("NICK :bot");
		send("USER bot 0 * :bot");
		send("JOIN #bot");
	}
}


void	Bot::receive() {
	if (!isRunning())
		return;
	if (pollFd.revents & POLLIN) {
		char	buffer[1025];
		int		ret = recv(clientSckt, buffer, 1024, 0);

		if (ret < 0)
			return;

		if (ret == 0) {
			log(INFO, "XXX | Server disconnected", C_MAGENTA);
			setRunning(false);
		}

		buffer[ret] = 0;
		cmdBuffer += std::string(buffer);
		if (cmdBuffer.find("\n") == std::string::npos)
			return;

		std::istringstream	ss(cmdBuffer);
		cmdBuffer = "";
		for (std::string line; std::getline(ss, line, '\n');) {
			if (line.find("\n") != std::string::npos) {
				cmdBuffer = line;
				break;
			}
			if (isWaitingForResponse()) {
				pthread_mutex_lock(&responsesMutex);
				log(INFO, "<-- | " + line, C_CYAN);
				responses.push_back(Response::parse(line));
				pthread_mutex_unlock(&responsesMutex);
			} else {
				pthread_mutex_lock(&responsesMutex);
				log(INFO, "<-- | " + line, C_CYAN);
				queue.push_back(Response::parse(line));
				pthread_mutex_unlock(&responsesMutex);
			}
		}
	}
}


void	Bot::execute() {
	if (!isRunning() || isExecutingCommand())
		return;
	pthread_mutex_lock(&responsesMutex);
	if (queue.size() > 0) {
		setExecutingCommand(true);
		pthread_create(&executingThread, NULL, &executeCommand, this);
		pthread_detach(executingThread);
	}
	pthread_mutex_unlock(&responsesMutex);
}


void	*Bot::executeCommand(void *_bot) {
	Bot			*bot = static_cast<Bot *>(_bot);
	Response	*response;

	pthread_mutex_lock(&bot->responsesMutex);
	response = bot->queue[0];
	bot->queue.erase(bot->queue.begin());
	pthread_mutex_unlock(&bot->responsesMutex);

	if (!response->isNumeric())
		executorManager.exec(bot, response->asCommand());

	delete response;
	bot->setWaitingForResponse(true);
	bot->setWaitingForResponse(false);
	bot->setExecutingCommand(false);
	return NULL;
}


void	Bot::send(std::string target, std::string command) {
	ssize_t		ret;
	std::string	finalCommand = command + "\n";

	if (!target.empty()) {
		command.insert(0, "[" + target + "] ");
		finalCommand = "PRIVMSG " + target + " :" + finalCommand;
	}
	ret = ::send(clientSckt, finalCommand.c_str(), finalCommand.length(), 0);
	if (ret < 0)
		throw BotException("Send failed");
	if (ret != (ssize_t) finalCommand.length())
		throw BotException("Only " + itoa(ret)
			+ " bytes sent out of " + itoa(finalCommand.length()));
	log(INFO, "--> | " + command, C_GREEN);
}


void	Bot::send(std::string target, std::string command, long long waiting) {
	struct timeval	t;
	long long		start;
	long long		now;

	send(target, command);
	if (waiting != 0) {
		setWaitingForResponse(true);
		gettimeofday(&t, NULL);
		start = t.tv_sec * 1000 + t.tv_usec / 1000;
		while (isRunning()) {
			if (waiting < 0) {
				pthread_mutex_lock(&responsesMutex);
				if (responses.size() > 0) {
					pthread_mutex_unlock(&responsesMutex);
					setWaitingForResponse(false);
					break;
				}
				pthread_mutex_unlock(&responsesMutex);
			} else {
				gettimeofday(&t, NULL);
				now = t.tv_sec * 1000 + t.tv_usec / 1000;
				if (now - start > waiting) {
					setWaitingForResponse(false);
					break;
				}
			}
			usleep(10);
		}
	}
}


void	Bot::send(std::string command) {
	send("", command);
}


void	Bot::send(std::string command, long long waiting) {
	send("", command, waiting);
}


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


bool	Bot::isRunning() {
	bool	running;
	
	pthread_mutex_lock(&runningMutex);
	running = this->running;
	pthread_mutex_unlock(&runningMutex);
	return running;
}


void	Bot::setRunning(bool running) {
	pthread_mutex_lock(&runningMutex);
	this->running = running;
	pthread_mutex_unlock(&runningMutex);
}


std::string	Bot::getIp() {
	return ip;
}


int	Bot::getPort() {
	return port;
}


std::string	Bot::getPassword() {
	return password;
}


bool	Bot::isConnected() {
	return connected;
}


bool	Bot::isWaitingForResponse() {
	bool	waitingForResponse;
	
	pthread_mutex_lock(&waitingForResponseMutex);
	waitingForResponse = this->waitingForResponse;
	pthread_mutex_unlock(&waitingForResponseMutex);
	return waitingForResponse;
}


void	Bot::setWaitingForResponse(bool waitingForResponse) {
	pthread_mutex_lock(&waitingForResponseMutex);
	this->waitingForResponse = waitingForResponse;
	pthread_mutex_unlock(&waitingForResponseMutex);
	if (waitingForResponse) {
		pthread_mutex_lock(&responsesMutex);
		for (size_t i = 0; i < responses.size(); i++)
			queue.push_back(responses[i]);
		responses.clear();
		pthread_mutex_unlock(&responsesMutex);
	}
}


bool	Bot::isExecutingCommand() {
	bool	executingCommand;
	
	pthread_mutex_lock(&executingCommandMutex);
	executingCommand = this->executingCommand;
	pthread_mutex_unlock(&executingCommandMutex);
	return executingCommand;
}


void	Bot::setExecutingCommand(bool executingCommand) {
	pthread_mutex_lock(&executingCommandMutex);
	this->executingCommand = executingCommand;
	pthread_mutex_unlock(&executingCommandMutex);
}
