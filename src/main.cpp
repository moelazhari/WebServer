/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:45:25 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/20 22:45:50 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"
#include "server.hpp"
#include "connection.hpp"
#include "define.hpp"

int main (int ac, char **av)
{
	if (ac != 2)
		av[1] = (char *)CONFIG;
	
	std::vector<parsConfig>					config;
	std::vector<server>						servers;
	std::multimap<std::string, int>			hostPort;

	parsFile(av[1], config);
	for (size_t i = 0; i < config.size(); i++){
		servers.push_back(server(config[i]));
		std::vector<int> ports = servers[i].getPorts();
		for (size_t j = 0; j < ports.size(); j++){
			hostPort.insert(std::pair<std::string, int>(servers[i].getHost(), ports[j]));
		}
	}
	
	removeHostPortDuplicates(hostPort);
	Connection connection(hostPort, servers);
	
    return (0);
}
