/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Values.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:55:41 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/09 17:38:21 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Values.hpp"

Values::Values(){
    this->_clientMaxBodySize = 0;
	this->_autoIndex = "";
	this->_host = "";
	this->_root = "";
	this->_serverName = "";
	this->_ports = std::vector<int>();
	this->_errorPages = std::map<int, std::string>();
	this->_allowMethods = std::vector<std::string>();
	this->_indexs = std::vector<std::string>();
	return ;
}

Values::~Values(){
    return ;
}

void Values::setClientMaxBodySize(std::string key, std::string &value){
	if (this->_clientMaxBodySize)
			PrintExit("Error config file in key " + key + " is already set");
    if (!isAllNumber(value))
			PrintExit("Error config file in key" + key + ": " + value + " must be a number");
	this->_clientMaxBodySize = toInt(value);
}

void	Values::setAutoIndex(std::string key, std::string &value){
	if	(this->_autoIndex != "")
		PrintExit("Error config file in key " + key + " is already set");
	if (value != "on" && value != "off")
		PrintExit("Error config file in key " + key + ": " + value + " invalid value");
	this->_autoIndex = value;
}

void	Values::setHost(std::string key, std::string &value){
	if (this->_host != "")
		PrintExit("Error config file in key " + key + " is already set");
    std::vector<std::string>    tmp = split(value, ".");
	if (tmp.size() != 4)
		PrintExit("Error config file in key " + key + ": " + value + " invalid ip address");
	for (size_t i = 0; i < tmp.size(); i++){
		if (!isAllNumber(tmp[i]))
			PrintExit("Error config file in key " + key + ": " + value + " invalid ip address");
		if (toInt(tmp[i]) > 255)
			PrintExit("Error config file in key " + key + ": " + value + " ip address out of range");
	}
	this->_host = value;
}

void	Values::setRoot(std::string key, std::string &value){
	if (this->_root != "")
		PrintExit("Error config file in key " + key + " is already set");
	this->_root = value;
}

void Values::setServerName(std::string key, std::string &value){
	if (this->_serverName != "")
		PrintExit("Error config file in key " + key + " is already set");
	this->_serverName = value;
}

void Values::setPorts(std::string key, std::string &value){
	if (!isAllNumber(value))
			PrintExit("Error config file in key" + key + ": " + value + " must be a number");
	if (toInt(value) > 65535 || toInt(value) < 0)
			PrintExit("Error config file in key " + key + ": " + value + "	out of range");
	this->_ports.push_back(toInt(value));
}

void Values::setErrorPages(std::string key, std::string &value){
	std::vector<std::string>    tmp = split(value, " ");

	if (tmp.size() != 2 || !isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
		PrintExit("Error config file in key " + key + ": " + tmp[0] + " is not valid error code");
	if (this->_errorPages.find(toInt(tmp[0])) != this->_errorPages.end())
		PrintExit("Error config file in key " + key + ": " + tmp[0] + " is already set");
	// std::ifstream			   	file(tmp[1]);
	// if (!file.is_open())
	// 	PrintExit("Error config file in key " + key + ": " + tmp[1] + " file not found");
	this->_errorPages[toInt(tmp[0])] = tmp[1];
}

void Values::setAllowMethods(std::string key, std::string &value){
	if (this->_allowMethods.size() != 0)
		PrintExit("Error config file in key " + key + " is already set");
	std::vector<std::string>    tmp = split(value, " ");

        if (tmp.size() == 0 || tmp.size() > 3)
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        for (size_t i = 0; i < tmp.size(); i++){
            if (tmp[i] != "GET" && tmp[i] != "POST" && tmp[i] != "DELETE")
                PrintExit("Error config file in key " + key + ": " + value + " invalid value");
            this->_allowMethods.push_back(tmp[i]);
        }
}

void Values::setIndexs(std::string key, std::string &value){
	if (this->_indexs.size() != 0)
		PrintExit("Error config file in key " + key + " is already set");
	std::vector<std::string>    tmp = split(value, " ");
	
	for (size_t i = 0; i < tmp.size(); i++){
		this->_indexs.push_back(tmp[i]);
	}
}