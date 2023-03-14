/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/13 19:02:02 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "configFileParser.hpp"

server::server(parsConfig &config){
	size_t      			pos = 0;
	std::string             tmp;
	std::string             key;
	std::string             value;

    while (isspace(config.content[pos]))
        pos++;
	while (1){
		tmp = config.content.substr(pos, config.content.find('\n', pos) - pos);
		if (!isAllWhiteSpace(tmp)){
			parsLine(tmp, key, value);
			this->setValues(key, value);
		}
		pos = config.content.find('\n', pos);
		if (pos == std::string::npos)
			break;
		pos++;
	}
	this->setDefaultValues();
	// set locations
	std::map<std::string, std::string>::iterator it = config.locations.begin();
	std::map<std::string, std::string>::iterator ite = config.locations.end();
	while (it != ite){
				this->_locations[it->first] = location(it->second);
		it++;
	}
}

void	server::setValues(std::string &key, std::string &value){
	std::string values[9] = {"client_max_body_size",  "autoindex", "host", "root", "server_name", "listen", "error_page", "allow_methods", "index"};
	
	void (server::*f[9])(std::string key, std::string &value) = {&server::setClientMaxBodySize, &server::setAutoIndex, &server::setHost,\
	 &server::setRoot, &server::setServerName, &server::setPorts, &server::setErrorPages, &server::setAllowMethods, &server::setIndexs};

	for (int i = 0; i < 9; i++){
		if (key == values[i]){
			(this->*f[i])(key, value);
			return ;
		}
	}
	PrintExit("Error config file in key " + key + ": invalid key");
}

void	server::setDefaultValues(){
	if (this->_clientMaxBodySize == 0)
		this->_clientMaxBodySize = 10000;
	if (this->_autoIndex == "")
		this->_autoIndex = "off";
	if (this->_host == "")
		this->_host = "web_pages";
	if (this->_root == "")
		this->_root = "web_pages";
	if (this->_ports.size() == 0)
		this->_ports.push_back(80);
	if (this->_errorPages.size() == 0){
		this->_errorPages[404] = "400.html";
		this->_errorPages[500] = "500.html";
	}
	if (this->_allowMethods.size() == 0){
		this->_allowMethods.push_back("GET");
		this->_allowMethods.push_back("HEAD");
		this->_allowMethods.push_back("POST");
	}
	if (this->_indexs.size() == 0){
		this->_indexs.push_back("index.html");
	}
}

void server::printValues(){
	std::cout << "client_max_body_size: " << this->_clientMaxBodySize << std::endl;
	std::cout << "autoindex: " << this->_autoIndex << std::endl;
	std::cout << "host: " << this->_host << std::endl;
	std::cout << "root: " << this->_root << std::endl;
	std::cout << "server_name: " << this->_serverName << std::endl;
	// print ports
	std::cout << "ports: ";
	for (size_t i = 0; i < this->_ports.size(); i++){
		std::cout << this->_ports[i] << " ";
	}
	std::cout << std::endl;
	// print error pages
	std::cout << "error_pages: ";
	std::map<int, std::string>::iterator it = this->_errorPages.begin();
	std::map<int, std::string>::iterator ite = this->_errorPages.end();
	while (it != ite){
		std::cout << it->first << " : " << it->second << " ";
		it++;
	}
	std::cout << std::endl;
	// print allow methods
	std::cout << "allow_methods: ";
	for (size_t i = 0; i < this->_allowMethods.size(); i++){
		std::cout << this->_allowMethods[i] << " ";
	}
	std::cout << std::endl;
	// print indexs
	std::cout << "indexs: ";
	for (size_t i = 0; i < this->_indexs.size(); i++){
		std::cout << this->_indexs[i] << " ";
	}
	// print locations
	std::map<std::string, location>::iterator it3 = this->_locations.begin();
	std::map<std::string, location>::iterator ite3 = this->_locations.end();

	std::cout << "locations:" << std::endl;	

	while (it3 != ite3){
		std::cout << it3->first << " : " << std::endl;
		it3->second.printValues();
		it3++;
	}
}

server::~server(){
}