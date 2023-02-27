/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:17 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/27 20:20:25 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void	parsLine(std::string str, std::string &key, std::string &value){
    size_t      pos;
	
	if (!isAllWhiteSpace(str))
	{
		if (str[str.length() - 2] != ';')
			PrintExit("Error config file server block: missing ;");
		else
			str.erase(str.length() - 2, 2);
		for (pos = 0; isspace(str[pos]); pos++);
		key = str.substr(pos, str.find_first_of(" \t", pos));
		pos = str.find_first_of(" \t", pos);
		value = str.substr(str.find_first_not_of(" \t", pos), str.length() - 1);
	}
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
	tmp = config.content.substr(pos, config.content.length());
	std::cout << tmp;
}

server::~server(){
}