/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/05 18:00:07 by mazhari          ###   ########.fr       */
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

	std::map<std::string, std::string>::iterator it = config.locations.begin();
	std::map<std::string, std::string>::iterator ite = config.locations.end();
	while (it != ite){
				this->_locations[it->first] = location(it->second, this->_values, this->_errorPages, this->_allowMethods);
		it++;
	}
}

void	server::setValues(std::string &key, std::string &value){
	if (key == "listen")
	{
		if (toInt(value) > 65535 || toInt(value) < 0)
			PrintExit("Error config file in key " + key + ": " + value + "	out of range");
		this->_values[key] = value;
	}
	else if (key == "host"){
		std::vector<std::string>    tmp = split(value, ".");
		if (tmp.size() != 4)
			PrintExit("Error config file in key " + key + ": " + value + " invalid ip address");
		for (size_t i = 0; i < tmp.size(); i++){
			if (!isAllNumber(tmp[i]))
				PrintExit("Error config file in key " + key + ": " + value + " invalid ip address");
			if (toInt(tmp[i]) > 255)
				PrintExit("Error config file in key " + key + ": " + value + " ip address out of range");
		}
		this->_values[key] = value;
	}
	else if (key == "server_name")
		this->_values[key] = value;
	else if (key == "root"){
		this->_values[key] = value;
	}
	else if (key == "index"){
		this->_values[key] = value;
	}
	else if (key == "client_max_body_size"){
		if (!isAllNumber(value))
			PrintExit("Error config file in key" + key + ": " + value + " must be a number");
		this->_values[key] = value;
	}
	else if (key == "autoindex"){
		if (value != "on" && value != "off")
			PrintExit("Error config file in  key" + key + ": " + value + " must be on or off");
		this->_values[key] = value;
	}
	else if (key == "error_page"){
		this->_errorPages.clear();
		std::vector<std::string>    tmp = split(value, " ");

		if (tmp.size() != 2 || !isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
			PrintExit("Error config file in key " + key + ": " + tmp[0] + " is not valid error code");
		std::ifstream			   	file(tmp[1]);
		if (!file.is_open())
			PrintExit("Error config file in key " + key + ": " + tmp[1] + " file not found");
		this->_errorPages[toInt(tmp[0])] = tmp[1];
	}
	else if (key == "allow_methods"){
		this->_allowMethods.clear();
        std::vector<std::string>    tmp = split(value, " ");

        if (tmp.size() == 0 || tmp.size() > 3)
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        for (size_t i = 0; i < tmp.size(); i++){
            if (tmp[i] != "GET" && tmp[i] != "POST" && tmp[i] != "DELETE")
                PrintExit("Error config file in key " + key + ": " + value + " invalid value");
            this->_allowMethods.push_back(tmp[i]);
        }
	}
	else
		PrintExit("Error config file in key " + key + " is not valid");
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

	std::map<std::string, location>::iterator it3 = this->_locations.begin();
	std::map<std::string, location>::iterator ite3 = this->_locations.end();

	while (it3 != ite3){
		std::cout << it3->first << " : " << std::endl;
		it3->second.printValues();
		it3++;
	}
}

server::~server(){
}