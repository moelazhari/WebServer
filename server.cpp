/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 16:23:06 by mazhari          ###   ########.fr       */
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
	key = str.substr(pos, str.find_first_of(" \t", pos));
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
			// this->setValues(key, value);
		}
		pos = config.content.find('\n', pos) + 1;
	}
}

server::~server(){
}