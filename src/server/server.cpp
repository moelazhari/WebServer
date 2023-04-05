/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/04/03 01:57:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.hpp"

server::server(){
}

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

	for  (std::map<std::string, std::string>::iterator it = config.locations.begin(); it != config.locations.end(); it++)
			this->_locations.insert(std::pair<std::string, location>(it->first, location(it->second)));
}

void	server::setValues(std::string &key, std::string &value){
	std::string values[11] = {"client_max_body_size",  "autoindex", "host", "root", "server_name", "upload", "listen", "error_page", "allow_methods", "index", "meme_types"};
	
	void (server::*f[11])(std::string value) = {&server::setClientMaxBodySize, &server::setAutoIndex, &server::setHost,\
	 &server::setRoot, &server::setServerName, &server::setUpload, &server::setPorts, &server::setErrorPages, &server::setAllowMethods, &server::setIndexs, &server::parsMemeTypes};

	for (int i = 0; i < 11; i++){
		if (key == values[i]){
			(this->*f[i])(value);
			return ;
		}
	}
	PrintExit("Error config file in key " + key + ": invalid key");
}

void	server::setDefaultValues(){
	if (this->_root == "")
		this->_root = DEFAULT_ROOT;
	if (this->_clientMaxBodySize == 0)
		this->_clientMaxBodySize = DEFAULT_CLIENT_MAX_BODY_SIZE;
	if (this->_autoIndex == "")
		this->_autoIndex = DEFAULT_AUTOINDEX;
	if (this->_upload == "")
		this->_upload = DEFAULT_UPLOAD;
	if (this->_host == "")
		this->_host = DEFAULT_HOST;
	if (this->_ports.size() == 0)
		this->_ports.push_back(DEFAULT_PORT);
	
	if (this->_memeTypes.size() == 0){
		this->parsMemeTypes(TYPES);
	}

	if (this->_allowMethods.size() == 0){
		this->_allowMethods.push_back("GET");
		this->_allowMethods.push_back("DELETE");
		this->_allowMethods.push_back("POST");
	}

	if (this->_errorPages.find(201) == this->_errorPages.end())
		this->_errorPages[201] = DEFAULT_ERROR_PAGES_201;
	if (this->_errorPages.find(204) == this->_errorPages.end())
		this->_errorPages[204] = DEFAULT_ERROR_PAGES_204;
	if (this->_errorPages.find(400) == this->_errorPages.end())
		this->_errorPages[400] = DEFAULT_ERROR_PAGES_400;
	if (this->_errorPages.find(403) == this->_errorPages.end())
		this->_errorPages[403] = DEFAULT_ERROR_PAGES_403;
	if (this->_errorPages.find(404) == this->_errorPages.end())
		this->_errorPages[404] = DEFAULT_ERROR_PAGES_404;
	if (this->_errorPages.find(405) == this->_errorPages.end())
		this->_errorPages[405] = DEFAULT_ERROR_PAGES_405;
	if (this->_errorPages.find(413) == this->_errorPages.end())
		this->_errorPages[413] = DEFAULT_ERROR_PAGES_413;
	if (this->_errorPages.find(414) == this->_errorPages.end())
		this->_errorPages[414] = DEFAULT_ERROR_PAGES_414;
	if (this->_errorPages.find(500) == this->_errorPages.end())
		this->_errorPages[500] = DEFAULT_ERROR_PAGES_500;
	if (this->_errorPages.find(501) == this->_errorPages.end())
		this->_errorPages[501] = DEFAULT_ERROR_PAGES_501;
	if (this->_errorPages.find(502) == this->_errorPages.end())
		this->_errorPages[502] = DEFAULT_ERROR_PAGES_502;
	if (this->_errorPages.find(505) == this->_errorPages.end())
		this->_errorPages[505] = DEFAULT_ERROR_PAGES_505;
}

void	server::parsMemeTypes(std::string path){
	std::ifstream	file(path);
	std::string		line;
	std::string		key;
	std::string		value;

	if (!file.is_open())
		std::cout << "Error config file: meme_types: can't open file: " + path << std::endl;
	while (std::getline(file, line))
	{
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
		this->_memeTypes[keys[i]] = value;
	}
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