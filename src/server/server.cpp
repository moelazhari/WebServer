/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/24 22:55:15 by aboudoun         ###   ########.fr       */
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
			this->_locations.insert(std::pair<std::string, location>(it->first, location(it->second)));
		it++;
	}
}

void	server::setValues(std::string &key, std::string &value){
	std::string values[10] = {"client_max_body_size",  "autoindex", "host", "root", "server_name", "listen", "error_page", "allow_methods", "index", "meme_types"};
	
	void (server::*f[10])(std::string value) = {&server::setClientMaxBodySize, &server::setAutoIndex, &server::setHost,\
	 &server::setRoot, &server::setServerName, &server::setPorts, &server::setErrorPages, &server::setAllowMethods, &server::setIndexs, &server::parsMemeTypes};

	for (int i = 0; i < 10; i++){
		if (key == values[i]){
			(this->*f[i])(value);
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
	if (this->_memeTypes.size() == 0){
		this->parsMemeTypes("./configs/types.conf");
	}
}

void	server::parsMemeTypes(std::string path){
	std::ifstream	file(path);
	std::string		line;
	std::string		key;
	std::string		value;
	// size_t pos;
	if (!file.is_open())
		std::cout << "Error config file: meme_types: can't open file: " + path << std::endl;
	while (std::getline(file, line))
	{
		// remove comments
		if (line.find("#") != std::string::npos)
			line = line.substr(0, line.find("#"));
		if (isAllWhiteSpace(line)){
			removeWhiteSpace(line);
			continue ;
		}
		parsLine(line, key, value);
		this->setMemeTypes(value, key);
	}
}

void	server::setMemeTypes(std::string key, std::string value){
	std::vector<std::string> keys = split(key, " ");

	for (size_t i = 0; i < keys.size(); i++){
		if (this->_memeTypes.find(keys[i]) != this->_memeTypes.end())
			PrintExit("Error config file: meme_types: extension " + keys[i] + " already exists");
		this->_memeTypes.insert(std::pair<std::string, std::string>(keys[i], value));
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
	//print meme types
    std::cout << "meme types: ";
    for (std::map<std::string, std::string>::iterator it = this->_memeTypes.begin(); it != this->_memeTypes.end(); it++)
        std::cout << it->first << " " << it->second << " ";
    std::cout << std::endl;
	// // print locations
	// std::map<std::string, location>::iterator it3 = this->_locations.begin();
	// std::map<std::string, location>::iterator ite3 = this->_locations.end();

	// std::cout << "locations:" << std::endl;	

	// while (it3 != ite3){
	// 	std::cout << it3->first << " : " << std::endl;
	// 	it3->second.printValues();
	// 	it3++;
	// }
	
}

std::string server::getHost(){
	return (this->_host);
}

std::vector<int> server::getPorts(){
	return (this->_ports);
}

std::map<std::string, location> &server::getLocations()
{
	return (this->_locations);
}

std::map<std::string, std::string> &server::getMemeTypes()
{
	return (this->_memeTypes);
}

server::~server(){
}