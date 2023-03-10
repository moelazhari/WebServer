/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:39:41 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/10 16:49:36 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <fcntl.h>

#include "configFileParser.hpp"
#include "server.hpp"

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Wrong number of arguments" << std::endl;
        std::cout << "Usage: ./configFileParser <config_file>" << std::endl;
        return (1);
    }
    
    std::vector<parsConfig> config;
    std::vector<server>     servers;

    parsFile(av[1], config);
    for (size_t i = 0; i < config.size(); i++){
        servers.push_back(server(config[i]));
    }

    //print Servers
    for (size_t i = 0; i < servers.size(); i++){
        std::cout << "      Server " << i << ": " << std::endl;
        servers[i].printValues();
    }

    return (0);
}
