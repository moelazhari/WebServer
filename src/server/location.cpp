/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/09 17:47:06 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location(){
    return ;
}

location::location (std::string &content): _cgiPath(""), _return(std::pair<int, std::string>(0, "")){
    size_t      			pos = 0;
    std::string             tmp;
    std::string             key;
    std::string             value;

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
    std::string values[11] = {"client_max_body_size",  "autoindex", "host", "root", "error_page", "allow_methods", "index", "path_info", "return"};

    void (location::*f[11])(std::string key, std::string &value) = {&location::setClientMaxBodySize, &location::setAutoIndex, &location::setHost,\
    &location::setRoot, &location::setErrorPages, &location::setAllowMethods, &location::setIndexs, &location::setCgiPath, &location::setReturn};
    
    for (int i = 0; i < 11; i++){
        if (key == values[i]){
            (this->*f[i])(key, value);
            return ;
        }
    }
    PrintExit("Error config file in key " + key + ": invalid key");
}

void  location::setCgiPath(std::string key, std::string &value){
    if (_cgiPath != "")
        PrintExit("Error config file in key " + key + ": " + value + " already set");
    this->_cgiPath = value;
}

void location::setReturn(std::string key, std::string &value){
    std::vector<std::string>    tmp = split(value, " ");

    if (tmp.size() != 2)
        PrintExit("Error config file in key " + key + ": " + value + " invalid value");
    if (!isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
        PrintExit("Error config file in key " + key + ": " + tmp[0] + " is not valid error code");
    this->_return = std::pair<int, std::string>(toInt(tmp[0]), tmp[1]);
}
void location::printValues(){
    std::cout << "client_max_body_size: " << this->_clientMaxBodySize << std::endl;
    std::cout << "autoindex: " << this->_autoIndex << std::endl;
    std::cout << "host: " << this->_host << std::endl;
    std::cout << "root: " << this->_root << std::endl;
    //prtint error pages
    std::cout << "allow_methods: ";
    for (size_t i = 0; i < this->_allowMethods.size(); i++)
        std::cout << this->_allowMethods[i] << " ";
    std::cout << std::endl;
    //print indexs
    std::cout << "index: ";
    for (size_t i = 0; i < this->_indexs.size(); i++)
        std::cout << this->_indexs[i] << " ";
    std::cout << std::endl;
}

location::~location(){

}