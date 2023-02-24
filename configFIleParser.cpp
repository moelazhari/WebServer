/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFIleParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:45 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/24 17:10:21 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"

bool isAllWhiteSpace(std::string const& str)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (!isspace(*it))
            return false;
    }
    return true;
}

void PrintExit(std::string str)
{
    std::cout << str << std::endl;
    exit(1);
}

void    parseConfigFile(std::string fileName)
{
    std::ifstream   file;
    std::string     line;
    // std::string     tmp;
    // int             i;

    file.open(fileName);
    if (!file.is_open())
        PrintExit("Error: File not found");
    getline(file, line);
    while (isAllWhiteSpace(line)) {
        if (file.eof())
            PrintExit("Error: Empty file");
        getline(file, line);
    }
    std::cout << "line" <<  std::endl;
}