/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loction.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/04 18:20:22 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location() {
    return ;
}

location::location(std::string &content) {
    size_t      			pos = 0;
    std::string             tmp;
    std::string             key;
    std::string             value;

    if (content.empty())
        PrintExit("Error config file Location block: is empty");
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
    if (this->_values.empty())
        PrintExit("Error config file Location block: is empty");
}

void    location::setValues(std::string &key, std::string &value){
    if (this->_values.find(key) != this->_values.end())
		PrintExit("Error config file in key " + key + ": is duplicated");
    if (key == "allow_methods"){
        if (!this->_allow_methods.empty())
            PrintExit("Error config file in key " + key + ": is duplicated");
        std::vector<std::string>    tmp = split(value, " ");

        if (tmp.size() == 0 || tmp.size() > 3)
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        for (size_t i = 0; i < tmp.size(); i++){
            if (tmp[i] != "GET" && tmp[i] != "POST" && tmp[i] != "DELETE")
                PrintExit("Error config file in key " + key + ": " + value + " invalid value");
            this->_allow_methods.push_back(tmp[i]);
        }
    }
    else if (key == "return"){
        this->_values[key] = value;
    }
    else if (key == "root"){
        this->_values[key] = value;
    }
    else if (key == "autoindex"){
        if (value != "on" && value != "off")
            PrintExit("Error config file in key " + key + ": " + value + " invalid value");
        this->_values[key] = value;
    }
    else if (key == "index"){
        this->_values[key] = value;
    }
    else if (key == "path_info"){
        this->_values[key] = value;
    }
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
    for (size_t i = 0; i < this->_allow_methods.size(); i++){
        std::cout << this->_allow_methods[i] << std::endl;
    }
}

location::~location(){

}