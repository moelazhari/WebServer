/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/04/03 01:02:52 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location(){
    return ;
}

location::location (std::string &content): _cgiPaths(std::map<std::string, std::string>()), _return(std::pair<int, std::string>(0, "")){
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
    std::string values[9] = {"client_max_body_size",  "autoindex", "root", "upload", "error_page", "allow_methods", "index", "path_info", "return"};
  
    void (location::*f[9])(std::string value) = {&location::setClientMaxBodySize, &location::setAutoIndex, \
    &location::setRoot, &location::setUpload, &location::setErrorPages, &location::setAllowMethods, &location::setIndexs, &location::setCgiPaths, &location::setReturn};
    
    for (int i = 0; i < 9; i++){
        if (key == values[i]){
            (this->*f[i])(value);
            return ;
        }
    }
    PrintExit("Error config file in key " + key + ": invalid key");
}

void  location::setCgiPaths(std::string value){
    std::vector<std::string>    tmp = split(value, " ");
    std::ifstream               file;

    if (tmp.size() != 2)
        PrintExit("Error config file: cgiPath: " + value + " invalid value");
    if (tmp[0][0] != '.')
        PrintExit("Error config file: cgiPath: " + tmp[0] + " is not valid extension");
    if (tmp[0] != ".py" && tmp[0] != ".php")
        PrintExit("Error config file: cgiPath: " + tmp[0] + " extension is not supported yet");
    if (_cgiPaths.find(tmp[0]) != _cgiPaths.end())
        PrintExit("Error config file: cgiPath: " + tmp[0] + " extension is already set");
    this->_cgiPaths[tmp[0]] = tmp[1];
}

void location::setReturn(std::string value){
    std::vector<std::string>    tmp = split(value, " ");

    if (tmp.size() != 2)
        PrintExit("Error config file: return:" + value + " invalid value");
    if (!isAllNumber(tmp[0]) || toInt(tmp[0]) < 100 || toInt(tmp[0]) > 504)
        PrintExit("Error config file: return:" + tmp[0] + " is not valid error code");
    this->_return = std::pair<int, std::string>(toInt(tmp[0]), tmp[1]);
}

std::map<std::string, std::string> location::getCgiPaths(){
    return this->_cgiPaths;
}

std::pair<int, std::string> location::getReturn(){
    return this->_return;
}

location::~location(){

}

location &location::operator=(location &rhs){
    this->_clientMaxBodySize = rhs.getClientMaxBodySize();
    this->_autoIndex = rhs.getAutoIndex();
    this->_root = rhs.getRoot();
    this->_upload = rhs.getUpload();
    this->_serverName = rhs.getServerName();
    this->_errorPages = rhs.getErrorPages();
    this->_allowMethods = rhs.getAllowMethods();
    this->_indexs = rhs.getIndexs();
    this->_cgiPaths = rhs.getCgiPaths();
    this->_return = rhs.getReturn();
    return *this;
}