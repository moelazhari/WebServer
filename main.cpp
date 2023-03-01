/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:45:25 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/01 15:09:39 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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