/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 19:19:00 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	server::parsLine(std::string &str, std::string &key, std::string &value){
    size_t      pos;

	if (str[str.length() - 1] != ';')
		PrintExit("Error config file: missing ; in line: " + str);
	else
		str.erase(str.length() - 1, 1);
	for (pos = 0; isspace(str[pos]); pos++);
	key = str.substr(pos, str.find_first_of(" \t", pos) - pos);
	pos = str.find_first_of(" \t", pos);
	if (pos == std::string::npos || str.find_first_not_of(" \t", pos) == std::string::npos)
		PrintExit("Error config file: key " + key + " has no value");
	value = str.substr(str.find_first_not_of(" \t", pos), str.length() - 1);
}

server::server(parsConfig &config){
	size_t      			pos = 0;
	std::string             tmp;
	std::string             key;
	std::string             value;

    if (config.content.empty())
        PrintExit("Error config file Server block: is empty");
    while (isspace(config.content[pos]))
        pos++;
	while (pos < config.content.length() - 5){
		tmp = config.content.substr(pos, config.content.find('\n', pos) - pos);
		if (!isAllWhiteSpace(tmp)){
			this->parsLine(tmp, key, value);
			this->setValues(key, value);
		}
		pos = config.content.find('\n', pos) + 1;
	}
}

void server::setValues(std::string &key, std::string &value){
	if (key == "listen")
	{
		if (value.length() > 5 || !isAllNumber(value))
			PrintExit("Error config file: key" + key + " has invalid value");
		this->_values[key] = value;
	}
	else if (key == "host"){
		std::vector<std::string>    tmp = split(value, ".");
		if (tmp.size() != 4)
			PrintExit("Error config file: key " + key + " has invalid value");
		for (size_t i = 0; i < tmp.size(); i++){
			if (!isAllNumber(tmp[i]))
				PrintExit("Error config file: key " + key + " has invalid value");
			if (toInt(tmp[i]) > 255)
				PrintExit("Error config file: key " + key + " has invalid value");
		}
		this->_values[key] = value;
	}
	else if (key == "server_name")
		this->_values[key] = value;
	else if (key == "root"){
		if (value[value.length() - 1] != '/')
			value += '/';
		this->_values[key] = value;
	}
	else if (key == "index")
		this->_values[key] = value;
	else if (key == "client_max_body_size"){
		if (!isAllNumber(value))
			PrintExit("Error config file: key" + key + " has invalid value");
		this->_values[key] = value;
	}
	else if (key == "autoindex"){
		if (value != "on" && value != "off")
			PrintExit("Error config file: key" + key + " has invalid value");
		this->_values[key] = value;
	}
	else if (key == "index"){
		// to do
	}
	else if (key == "error_page"){
		std::vector<std::string>    tmp = split(value, " ");

		if (tmp.size() != 2 || !isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
			PrintExit("Error config file: key " + key + " has invalid value");
		this->_errorPages[toInt(tmp[0])] = tmp[1];
	}
	else
		PrintExit("Error config file: key " + key + " is not valid");
}

void server::printValues(){
	std::map<std::string, std::string>::iterator it = this->_values.begin();
	std::map<std::string, std::string>::iterator ite = this->_values.end();

	while (it != ite){
		std::cout << it->first << " : " << it->second << std::endl;
		it++;
	}
	
	std::map<int, std::string>::iterator it2 = this->_errorPages.begin();
	std::map<int, std::string>::iterator ite2 = this->_errorPages.end();

	while (it2 != ite2){
		std::cout << it2->first << " : " << it2->second << std::endl;
		it2++;
	}
}

server::~server(){
}