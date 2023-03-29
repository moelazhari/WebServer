/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Values.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:55:41 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/29 00:48:03 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Values.hpp"

Values::Values(){
    this->_clientMaxBodySize = 0;
	this->_autoIndex = "";
	this->_host = "";
	this->_root = "";
	this->_serverName = "";
	this->_upload = "";
	this->_ports = std::vector<int>();
	this->_errorPages = std::map<int, std::string>();
	this->_allowMethods = std::vector<std::string>();
	this->_indexs = std::vector<std::string>();
	return ;
}

Values::~Values(){
    return ;
}

void	Values::setClientMaxBodySize(std::string value){
	if (this->_clientMaxBodySize)
			PrintExit("Error config file: clientMaxBodySize is already set");
    if (!isAllNumber(value))
			PrintExit("Error config file: clientMaxBodySize " + value + " must be a number");
	this->_clientMaxBodySize = toInt(value);
}

void	Values::setAutoIndex(std::string value){
	if	(this->_autoIndex != "")
		PrintExit("Error config file: autoIndex is already set");
	if (value != "on" && value != "off")
		PrintExit("Error config file: autoIndex: " + value + " invalid value");
	this->_autoIndex = value;
}

void	Values::setHost(std::string value){
	if (this->_host != "")
		PrintExit("Error config file: host is already set");
    std::vector<std::string>    tmp = split(value, ".");
	if (tmp.size() != 4)
		PrintExit("Error config file: host: " + value + " invalid ip address");
	for (size_t i = 0; i < tmp.size(); i++){
		if (!isAllNumber(tmp[i]))
			PrintExit("Error config file: host: " + value + " invalid ip address");
		if (toInt(tmp[i]) > 255)
			PrintExit("Error config file: host: " + value + "ip address out of range");
	}
	this->_host = value;
}

void	Values::setRoot(std::string value){
	if (this->_root != "")
		PrintExit("Error config file: root is already set");
	this->_root = value;
}

void 	Values::setServerName(std::string value){
	if (this->_serverName != "")
		PrintExit("Error config file: serverName is already set");
	this->_serverName = value;
}

void Values::setUpload(std::string value){
	if (this->_upload != "")
		PrintExit("Error config file: upload is already set");
	if (value != "on" && value != "off")
		PrintExit("Error config file: upload: " + value + " invalid value");
	this->_upload = value;
}

void Values::setPorts(std::string value){
	if (!isAllNumber(value))
			PrintExit("Error config file: port:" + value + " must be a number");
	if (toInt(value) > 65535 || toInt(value) < 0)
			PrintExit("Error config file in key: port: " + value + " out of range");
	this->_ports.push_back(toInt(value));
}

void	Values::setErrorPages(std::string value){
	std::vector<std::string>    tmp = split(value, " ");

	if (tmp.size() != 2 || !isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
		PrintExit("Error config file: error Page: " + tmp[0] + " is not valid error code");
	if (this->_errorPages.find(toInt(tmp[0])) != this->_errorPages.end())
		PrintExit("Error config file: error Page:" + tmp[0] + " is already set");
	this->_errorPages[toInt(tmp[0])] = tmp[1];
}

void	Values::setAllowMethods(std::string value){
	if (this->_allowMethods.size() != 0)
		PrintExit("Error config file: allowMethods is already set");
	std::vector<std::string>    tmp = split(value, " ");

        if (tmp.size() == 0 || tmp.size() > 3)
            PrintExit("Error config file: allowMethods:" + value + " invalid value");
        for (size_t i = 0; i < tmp.size(); i++){
            if (tmp[i] != "GET" && tmp[i] != "POST" && tmp[i] != "DELETE")
                PrintExit("Error config file: allowMethods: " + value + " invalid value");
            this->_allowMethods.push_back(tmp[i]);
        }
}

void	Values::setIndexs(std::string value){
	if (this->_indexs.size() != 0)
		PrintExit("Error config file: index is already set");
	std::vector<std::string>    tmp = split(value, " ");
	
	for (size_t i = 0; i < tmp.size(); i++){
		this->_indexs.push_back(tmp[i]);
	}
}

int	Values::getClientMaxBodySize(){
	return this->_clientMaxBodySize;
}

std::string	Values::getAutoIndex(){
	return this->_autoIndex;
}

std::string	Values::getHost(){
	return this->_host;
}

std::string	Values::getRoot(){
	return this->_root;
}

std::string	Values::getServerName(){
	return this->_serverName;
}

std::string	Values::getUpload(){
	return this->_upload;
}

std::vector<int>	Values::getPorts(){
	return this->_ports;
}

std::map<int, std::string>	Values::getErrorPages(){
	return this->_errorPages;
}

std::vector<std::string>	Values::getAllowMethods(){
	return this->_allowMethods;
}

std::vector<std::string>	Values::getIndexs(){
	return this->_indexs;
}