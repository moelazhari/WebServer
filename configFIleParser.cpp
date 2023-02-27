/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFIleParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:45 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/27 14:04:03 by mazhari          ###   ########.fr       */
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

// // parse line geting key and value
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

// void ConfigFileParser::getLocatoins(std::string content){
//     size_t      pos;
//     size_t      locationB;
//     size_t      locationE;
//     std::string tmp;

//     pos = content.find("location");
//     while (pos != std::string::npos)
//     {
//         // ckecking if there is {
//         locationB = content.find("{", pos);
//         if (locationB == std::string::npos)
//             PrintExit("Error: location block { not found");
//         // geting location name
//         tmp = content.substr(pos, locationB - pos);
//         removeWhiteSpace(tmp);
//         if (tmp.find("location") != std::string::npos)
//             tmp = tmp.substr(tmp.find("location") + 9, tmp.length() - 1);
//         // ckecking if there is }
//         locationE = content.find("}", pos);
//         if (locationE == std::string::npos)
//             PrintExit("Error: location block } not found");
//         // geting location content
//         _location[tmp] = content.substr(locationB + 1, locationE - locationB - 1);
//         content.erase(pos, locationE - pos + 1);
//         pos = content.find("location", pos + 1);
//     }
//     // print locations
//     for (std::map<std::string, std::string>::iterator it = _location.begin(); it != _location.end(); ++it)
//     {
//         std::cout << it->first << std::endl;
//         std::cout << it->second << std::endl;
//     }
// }

void ConfigFileParser::parsServer(std::string content){
    (void)content;
}

void ConfigFileParser::parsLocation(std::string content){
    (void)content;
}

ConfigFileParser::ConfigFileParser(std::string fileName)
{
    std::ifstream   file;
    std::string     line;
    std::string     content;
    std::string     tmp;

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
        content.append(line + '\n');
    }
    // check if file is empty
    if (content.empty())
        PrintExit("Error: File is empty");
    // cheking is there server block
    if (content.find("{") != std::string::npos)
        tmp = content.substr(0, content.find("{") + 1);
    removeWhiteSpace(tmp);
    if (tmp != "server{")
        PrintExit("Error: server block");
    getLocatoins(content);
    parsServer(content.substr(content.find("{") + 1, content.length() - 1));
    parsLocation(content);
}

ConfigFileParser::~ConfigFileParser(){
    return ;
}