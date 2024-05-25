/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:50:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/25 19:57:22 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"


/* ************************************************************************** */
/* ------------------------ Constructors/Destructor ------------------------- */
/* ************************************************************************** */


Channel::Channel() {
	inviteOnly = false;
	topicRestricted = true;
	limited = false;
}


Channel::Channel(std::string name, std::string owner) {
	this->name = name;
	this->owner = owner;
	inviteOnly = false;
	topicRestricted = true;
	limited = false;
}


Channel::Channel(const Channel &channel) {
	*this = channel;
}


Channel &Channel::operator=(const Channel &channel) {
	if (this != &channel) {
		name = channel.name;
		owner = channel.owner;
		members = channel.members;
		operators = channel.operators;
		inviteOnly = channel.inviteOnly;
		invited = channel.invited;
		topicRestricted = channel.topicRestricted;
		key = channel.key;
		limited = channel.limited;
		limit = channel.limit;
	}
	return *this;
}


Channel::~Channel() {
}


/* ************************************************************************** */
/* ---------------------------- Member functions ---------------------------- */
/* ************************************************************************** */


bool	Channel::isLegalName(std::string name) {
	if (name.length() < 2 || name.size() > 50 || name[0] != '#')
		return false;
	for (size_t i = 1; i < name.size(); i++)
		if (!std::isprint(name[i]) || std::isspace(name[i])
			|| name[i] == ',' || name[i] == ':')
			return false;
	return true;
}


bool	Channel::isLegalKey(std::string key) {
	if (key.length() < 1 || key.length() > 23)
		return false;
	for (size_t i = 0; i < key.length(); i++) {
		if (!isprint(key[i]) || isspace(key[i])
			|| key[i] == ',' || key[i] == ':')
			return false;
	}
	return true;
}


std::vector<Client>	Channel::getOnlineClients(Server &server) {
	std::vector<Client>	onlineClients;

	for (std::vector<int>::iterator it = members.begin(); it != members.end(); it++)
		try {
			onlineClients.push_back(server.getClientBySocket(*it));
		} catch (Server::ServerException &ignored) {
		}
	return onlineClients;
}


bool	Channel::hasRight(std::string nick, std::string addr) {
	if (owner == addr)
		return true;
	if (std::find(operators.begin(), operators.end(), addr) != operators.end())
		return true;
	if (std::find(invited.begin(), invited.end(), nick) != invited.end())
		return true;
	return !inviteOnly;
}


bool	Channel::isMember(int socket) {
	return std::find(members.begin(), members.end(), socket) != members.end();
}


bool	Channel::isFull() {
	return limited && members.size() >= limit;
}


std::string	Channel::getMemberNicks() {
	std::string	memberNicks;

	for (std::vector<int>::iterator it = members.begin(); it != members.end(); it++)
		try {
			Client	&client = server.getClientBySocket(*it);

			if(this->isOperator(client.getFullAddress()) || client.getFullAddress() == owner) {
				memberNicks += " @" + client.getNick();
			} else
				memberNicks += " " + client.getNick();
		} catch (Server::ServerException &ignored) {
		}
	return memberNicks.empty() ? "" : memberNicks.substr(1);
}


bool	Channel::isOperator(std::string addr) {
	return std::find(operators.begin(), operators.end(), addr) != operators.end();
}


bool	Channel::isInvited(std::string nick) {
	return std::find(invited.begin(), invited.end(), nick) != invited.end();
}


void	Channel::broadcast(Server &server, std::string command) {
	for (std::vector<int>::iterator it = members.begin(); it != members.end(); it++)
		try {
			server.getClientBySocket(*it).send(server, command);
		} catch (Server::ServerException &ignored) {
		}
}


void	Channel::broadcast(Server &server, std::string command, std::string prefix) {
	for (std::vector<int>::iterator it = members.begin(); it != members.end(); it++)
		try {
			server.getClientBySocket(*it).send(command, prefix);
		} catch (Server::ServerException &ignored) {
		}
}


/* ************************************************************************** */
/* ------------------------------ Getter/Setter ----------------------------- */
/* ************************************************************************** */


std::string	Channel::getName() {
	return name;
}


void	Channel::setName(std::string name) {
	this->name = name;
}


std::string	Channel::getOwner() {
	return owner;
}


void	Channel::setOwner(std::string ownerAddr) {
	this->owner = ownerAddr;
}


std::vector<int>	Channel::getMembers() {
	return members;
}


void	Channel::addMember(int socket) {
	members.push_back(socket);
}


void	Channel::removeMember(int socket) {
	std::vector<int>::iterator	it = std::find(
		members.begin(), members.end(), socket);
	if (it != members.end())
		members.erase(it);
}


void	Channel::setMembers(std::vector<int> sockets) {
	members = sockets;
}


std::vector<std::string>	Channel::getOperators() {
	return operators;
}


void	Channel::addOperator(std::string operatorAddr) {
	operators.push_back(operatorAddr);
}


void	Channel::removeOperator(std::string operatorAddr) {
	std::vector<std::string>::iterator	it = std::find(
		operators.begin(), operators.end(), operatorAddr);
	if (it != operators.end())
		operators.erase(it);
}


void	Channel::setOperators(std::vector<std::string> operators) {
	this->operators = operators;
}


bool	Channel::isInviteOnly() {
	return inviteOnly;
}


void	Channel::setInviteOnly(bool inviteOnly) {
	this->inviteOnly = inviteOnly;
}


std::vector<std::string>	Channel::getInvited() {
	return invited;
}


void	Channel::addInvited(std::string invited) {
	this->invited.push_back(invited);
}


void	Channel::removeInvited(std::string invited) {
	std::vector<std::string>::iterator	it = std::find(
		this->invited.begin(), this->invited.end(), invited);
	if (it != this->invited.end())
		this->invited.erase(it);
}


void	Channel::setInvited(std::vector<std::string> invited) {
	this->invited = invited;
}


bool	Channel::isTopicRestricted() {
	return topicRestricted;
}


void	Channel::setTopicRestricted(bool topicRestricted) {
	this->topicRestricted = topicRestricted;
}


std::string	Channel::getTopic() {
	return topic;
}


void	Channel::setTopic(std::string topic) {
	this->topic = topic;
}


std::string	Channel::getKey() {
	return key;
}


void	Channel::setKey(std::string key) {
	this->key = key;
}


bool	Channel::isLimited() {
	return limited;
}


void	Channel::setLimited(bool limited) {
	this->limited = limited;
}


size_t	Channel::getLimit() {
	return limit;
}


void	Channel::setLimit(size_t limit) {
	this->limit = limit;
}
