/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:41 by mazhari           #+#    #+#             */
/*   Updated: 2023/04/01 03:09:07 by aboudoun         ###   ########.fr       */
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

bool isAllWhiteSpace(std::string &str){
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

	if (dlem == " ")
		replaceChar(str, '\t', ' ');

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

void replaceChar(std::string &str, char c1, char c2){
	for (size_t pos = str.find(c1); pos != std::string::npos; pos = str.find(c1, pos)){
		str.replace(pos, 1, 1, c2);
	}
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

void removeHostPortDuplicates(std::multimap<std::string, int> &hostPort){
	std::multimap<std::string, int>::iterator it = hostPort.begin();
	std::multimap<std::string, int>::iterator it2 = hostPort.begin();
	while (it != hostPort.end()){
		it2 = it;
		it2++;
		while (it2 != hostPort.end()){
			if (it->first == it2->first && it->second == it2->second){
				hostPort.erase(it2++);
			}
			else
				it2++;
		}
		it++;
	}
}

std::string getExtension(std::string str){
	size_t pos = str.find_last_of(".");
	if (pos == std::string::npos)
		return ("html");
	return (str.substr(pos + 1, str.length() - 1));
}