/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFIleParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:45 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/24 16:23:03 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"

void    parseConfigFile(std::string fileName)
{
    std::ifstream   file;
    // std::string     line;
    // std::string     tmp;
    // int             i;

    file.open(fileName);
    if (!file.is_open())
    {
        std::cout << "Error: File not found" << std::endl;
        return ;
    }
    std::cout << "File opened" << std::endl;
}