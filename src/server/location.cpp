/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/05 19:28:52 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location() {
    return ;
}

location::location (std::string &content, std::map<std::string, std::string> values, 
std::map<int, std::string> errorPages, std::vector<std::string> allowMethods, std::vector<std::string>  index) {
    size_t      			pos = 0;
    std::string             tmp;
    std::string             key;
    std::string             value;

    this->_values = values;
    this->_errorPages = errorPages;
    this->_allowMethods = allowMethods;
    this->_index = index;

    while (isspace(content[pos]))
        pos++;
    while (1){
        tmp = content.substr(pos, content.find('\n', pos) - pos);
        if (!isAllWhiteSpace(tmp)){
            parsLine(tmp, key, value);
            this->setValues(key, value);
        }
        pos = content.find('\n', pos);
        if (pos == std::string::npos)
            break;
        pos++; 
    }

}

void    location::setValues(std::string &key, std::string &value){
    if (key == "root"){
        this->_values[key] = value;
    }
    else if (key == "autoindex"){
        if (value != "on" && value != "off")
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        this->_values[key] = value;
    }
    else if (key == "path_info"){
        this->_values[key] = value;
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
    else if (key == "index"){
        this->_index.clear();
		std::vector<std::string>    tmp = split(value, " ");
		
		for (size_t i = 0; i < tmp.size(); i++){
			this->_index.push_back(tmp[i]);
		}
    }
    else if (key == "return"){
        std::vector<std::string>    tmp = split(value, " ");

        if (tmp.size() != 2)
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        if (!isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
            PrintExit("Error config file in key " + key + ": " + tmp[0] + " is not valid error code");
        this->_errorPages[toInt(tmp[0])] = tmp[1];
    }
    else
        PrintExit("Error config file in key " + key + ": invalid key");
}

void location::printValues(){
    std::map<std::string, std::string>::iterator it = this->_values.begin();
    std::map<std::string, std::string>::iterator ite = this->_values.end();

    std::cout << "Location values:" << std::endl;
    while (it != ite){
        std::cout << it->first << " : " << it->second << std::endl;
        it++;
    }
    std::cout << "Allow methods:" << std::endl;
    for (size_t i = 0; i < this->_allowMethods.size(); i++){
        std::cout << this->_allowMethods[i] << std::endl;
    }
}

location::~location(){

}