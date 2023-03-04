/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loction.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/04 17:06:28 by mazhari          ###   ########.fr       */
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

    std::cout << "content: " << content << std::endl;
    if (content.empty())
        PrintExit("Error config file Location block: is empty");
    while (isspace(content[pos]))
        pos++;
    while (1){
        tmp = content.substr(pos, content.find('\n', pos) - pos);
        std::cout << "tmp: " << tmp << std::endl;
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

void location::setValues(std::string &key, std::string &value){
    if (this->_values.find(key) != this->_values.end())
		PrintExit("Error config file in key " + key + ": is duplicated");
    if (key == "allow_methods"){
        //to do
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
    else if (key == ""){
        
    }
    else if (key == ""){
        
    }
    else if (key == ""){
        
    }

}

location::~location(){

}