/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:45:25 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/17 18:35:31 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"
#include "server.hpp"
#include "connection.hpp"

int main (int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: Wrong number of arguments" << std::endl;
		std::cout << "Usage: ./configFileParser <config_file>" << std::endl;
		return (1);
	}
	
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
	

	// connection.createsocket();
	
	//print hostPort
	// std::multimap<std::string, int>::iterator it;
	//  for (it = hostPort.begin(); it != hostPort.end(); it++){
	// 	std::cout << "      " << it->first << ":" << it->second << std::endl;
	// }

	// print Servers
	// for (size_t i = 0; i < servers.size(); i++){
	// 	std::cout << "      Server " << i << ": " << std::endl;
	// 	servers[i].printValues();
	// }
    return (0);
}
