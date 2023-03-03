/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/03 15:19:41 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "configFileParser.hpp"

server::server(parsConfig &config){
	size_t      			pos = 0;
	std::string             tmp;
	std::string             key;
	std::string             value;

    if (config.content.empty())
        PrintExit("Error config file Server block: is empty");
    while (isspace(config.content[pos]))
        pos++;
	while (pos < config.content.length()){
		tmp = config.content.substr(pos, config.content.find('\n', pos) - pos);
		if (!isAllWhiteSpace(tmp)){
			parsLine(tmp, key, value);
			this->setValues(key, value);
		}
		pos = config.content.find('\n', pos) + 1;
	}
	this->checkValues();
	// set locations and cgis
		// std::map<std::string, std::string>::iterator it = config.cgis.begin();
		// std::map<std::string, std::string>::iterator ite = config.cgis.end();

		// while (it != ite){
		// 	if (it->first[0] == '/')
		// 		this->_cgis[it->first] = cgi(it->second);
		// 	else 
		// 		this->_locations[it->first] = location(it->second);
		// 	it++;
		// }
}

void server::setValues(std::string &key, std::string &value){
	if (this->_values.find(key) != this->_values.end())
		PrintExit("Error config file in key " + key + ": is duplicated");
	if (key == "listen")
	{
		if (!isAllNumber(value))
			PrintExit("Error config file in key " + key + ": " + value + "	must be a number"); 
		if (toInt(value) > 65535)
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
		if (value[value.length() - 1] != '/')
			value += '/';
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
		std::vector<std::string>    tmp = split(value, " ");

		if (tmp.size() != 2 || !isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
			PrintExit("Error config file in key " + key + ": " + tmp[0] + " is not valid error code");
		std::ifstream			   	file(tmp[1]);
		if (!file.is_open())
			PrintExit("Error config file in key " + key + ": " + tmp[1] + " file not found");
		this->_errorPages[toInt(tmp[0])] = tmp[1];
	}
	else
		PrintExit("Error config file in key " + key + " is not valid");
}

void server::checkValues(){
	// if (this->_values.find("autoindex") != this->_values.end() && this->_values["autoindex"] == "on"
	// 	&& this->_values.find("index") == this->_values.end())
	// 	this->_values["index"] = "index.html";
	if (this->_values.find("listen") == this->_values.end())
		PrintExit("Error config file: missing port to listen");
	if (this->_values.find("host") == this->_values.end())
		PrintExit("Error config file: missing host");
	if (this->_values.find("root") == this->_values.end())
		PrintExit("Error config file: missing root");
	// geting index file
	// if (this->_values.find("index") == this->_values.end()) {
	// 	PrintExit("Error config file: missing index");
	// }
	// else {
	// 	std::string			tmp = this->_values["root"] + this->_values["index"];
	// 	std::ifstream		file(tmp);
	// 	if (!file.is_open())
	// 		PrintExit("Error config file: index " + tmp + " file not found");
	// }
	if (this->_values.find("client_max_body_size") == this->_values.end())
		PrintExit("Error config file: missing client_max_body_size");
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