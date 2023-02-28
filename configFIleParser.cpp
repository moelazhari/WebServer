/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFileParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:45 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 17:16:48 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"
#include "utils.hpp"

void parsFile(std::string fileName, std::vector<parsConfig> &config)
{
	std::ifstream   			file;
	std::string     			line;
	std::string     			content;
	std::string     			tmp;

	file.open(fileName);
	if (!file.is_open())
		PrintExit("Error config file: File not found");
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
		content.append(line + "\n");
	}
	// check if file is empty
	if (content.empty())
		PrintExit("Error config file: File is empty");
	getServers(content, config);
}

void		getServers(std::string &content, std::vector<parsConfig> &config){
	size_t      pos;
	size_t      serverB;
	size_t      serverE;
	std::string tmp;

	parsConfig server;

	pos = content.find("server");
	while (pos != std::string::npos)
	{
		// ckecking if there is {
		serverB = content.find("{", pos);
		if (serverB == std::string::npos)
			PrintExit("Error config file server block: { not found");
		// cheking server name
		tmp = content.substr(pos, serverB - pos);
		removeWhiteSpace(tmp);
		if (tmp != "server")
			PrintExit("Error config file server: server block not found");
		// get location blocks
		getLocations(content, server.locations);
		// ckecking if there is }
		serverE = content.find("}", serverB);
		if (serverE == std::string::npos)
			PrintExit("Error config file server block: } not found");
		// geting server block
		tmp = content.substr(serverB + 1, serverE - serverB - 1);
		server.content = tmp;
		config.push_back(server);
		content.erase(pos, serverE - pos + 1);
		pos = content.find("server", pos + 1);
	}
	// // print config
	// for (size_t i = 0; i < config.size(); i++)
	// {
	// 	std::cout << "server: " << i << std::endl;
	// 	std::cout << config[i].content << std::endl;
	// 	for (std::map<std::string, std::string>::iterator it = config[i].locations.begin(); it != config[i].locations.end(); ++it)
	// 		std::cout << it->first << " => " << it->second << std::endl;
	// }
}

void getLocations(std::string &content, std::map <std::string, std::string> &locations){
	size_t      pos;
	size_t      locationB;
	size_t      locationE;
	std::string tmp;

	pos = content.find("location");
	if (pos == std::string::npos){
		locations = std::map <std::string, std::string>();
		return;
	}
	while (pos != std::string::npos)
	{
		// ckecking if there is {
		locationB = content.find("{", pos);
		if (locationB == std::string::npos)
			PrintExit("Error config file location block: { not found");
		// geting location name
		tmp = content.substr(pos, locationB - pos);
		removeWhiteSpace(tmp);
		if (tmp.find("location") != std::string::npos)
			tmp = tmp.substr(tmp.find("location") + 9, tmp.length() - 1);
		// ckecking if there is }
		locationE = content.find("}", pos);
		if (locationE == std::string::npos)
			PrintExit("Error config file location block: } not found");
		// geting location content
		locations[tmp] = content.substr(locationB + 1, locationE - locationB - 1);
		content.erase(pos, locationE - pos + 1);
		pos = content.find("location", pos + 1);
	}
}