/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:41 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/03 14:14:22 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool	isAllNumber(std::string &str){
	for (size_t i = 0; i < str.length(); i++){
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool isAllWhiteSpace(std::string const& str){
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (!isspace(*it))
			return false;
	}
	return true;
}

void removeWhiteSpace(std::string &str){
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}

void PrintExit(std::string str){
	std::cerr << str << std::endl;
	     exit(1);
}

std::vector<std::string> split(std::string str, std::string dlem = " "){
    std::vector<std::string> result;
    std::string::size_type pos1, pos2;

    pos2 = str.find(dlem);
    pos1 = 0;
    while(std::string::npos != pos2){
        result.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + dlem.size();
        pos2 = str.find(dlem, pos1);
    }
    if (pos1 != str.length())
        result.push_back(str.substr(pos1));
    return result;
}

int toInt(std::string str){
    std::stringstream ss;
    int num;

    ss << str;
    ss >> num;

    return num;
}

void    parsLine(std::string &str, std::string &key, std::string &value){
    size_t      pos;

	if (str[str.length() - 1] != ';')
		PrintExit("Error config file: missing ; in line: " + str);
	else
		str.erase(str.length() - 1, 1);
	for (pos = 0; isspace(str[pos]); pos++);
	key = str.substr(pos, str.find_first_of(" \t", pos) - pos);
	pos = str.find_first_of(" \t", pos);
	if (pos == std::string::npos || str.find_first_not_of(" \t", pos) == std::string::npos)
		PrintExit("Error config file in key " + key + " has no value");
	value = str.substr(str.find_first_not_of(" \t", pos), str.length() - 1);
}