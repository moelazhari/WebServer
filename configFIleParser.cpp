/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFIleParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:45 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/25 19:12:54 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"

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

// void parsLine(std::string str){
//     size_t      pos;
//     std::string key;
//     std::string value;
    
//     for (pos = 0; isspace(str[pos]); pos++);
//     key = str.substr(pos, str.find_first_of(" \t", pos));
//     pos = str.find_first_of(" \t", pos);
//     value = str.substr(str.find_first_not_of(" \t", pos), str.length() - 1);
//     std::cout << key << std::endl;
//     std::cout << value << std::endl;
// }

void parsServerBlock(std::string content){
    std::string     tmp;
    if (content.find(';') == std::string::npos)
        PrintExit("Error: No semicolon");
    tmp = content.substr(0, content.find(';'));
    // parsLine(tmp);
}

void    parsConfigFile(std::string fileName)
{
    std::ifstream   file;
    std::string     line;
    std::string     content;
    std::string     tmp;
    // bool             server = false;

    file.open(fileName);
    if (!file.is_open())
        PrintExit("Error: File not found");
    // geting blocks
    while (std::getline(file, line))
    {
        // remove comments
        if (line.find("#") != std::string::npos)
            line = line.substr(0, line.find("#"));
        if (isAllWhiteSpace(line)){
            removeWhiteSpace(line);
            continue;
        }
        content.append(line);
    }
    // check if file is empty
    if (content.empty())
        PrintExit("Error: File is empty");
    // cheking if there is a server block
    if (content.find("{") != std::string::npos)
        tmp = content.substr(0, content.find("{") + 1);
    removeWhiteSpace(tmp);
    if (tmp != "server{")
        PrintExit("Error: No server block");
    parsServerBlock(content.substr(content.find("{") + 1, content.length() - 1));
}