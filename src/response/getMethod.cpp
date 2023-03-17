/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethod.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/17 18:48:26 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "response.hpp"

// bool	is_file(std::string path)
// {
// 	bool is_file = false;
// 	std::ifstream file(path.c_str());
// 	if (file.good())
// 		is_file = true;
// 	file.close();
// 	return is_file;
// }

// bool	is_dir(std::string path)
// {
// 	bool is_dir = false;
// 	DIR* dir = opendir(path.c_str());
// 	if (dir != NULL)
// 		is_dir = true;
// 	closedir(dir);
// 	return is_dir;
// }

// std::string joinPaths(std::string path, std::string add)
// {
// 	if (path[path.size() - 1] != '/')
// 		path += '/';
// 	if (add[0] == '/')
// 		add = add.substr(1);
// 	path += add;
// 	return path;
// }

// std::string	readFileContent(std::string path)
// {
// 	std::string content;
// 	std::string line;

// 	content = "";
// 	std::ifstream file(path.c_str());
// 	if (file.good())
// 	{
// 		// read line by line and remove \n
// 		line = "";
// 		while (getline(file, line))
// 		{
// 			if (line[line.size() - 1] == '\n')
// 				line = line.substr(0, line.size() - 1);
// 			content += line;
// 		}
// 	}
// 	file.close();
// 	return content;
// }

// void	Get(server& serv)
// {
// 	std::string		path;
// 	std::vector<std::string>::iterator it;

// 	path = serv._response._location.getRoot();
// 	path = joinPaths(path, serv._request.getLink());
// 	// TODO make this a funcion to work with it inside the dir loop
// 	if (is_file(path))
// 	{
// 		if (serv._response._location.getCgiPaths.size())
// 		{
// 			// TODO run cgi if file format is in cgiPaths
// 		}
// 		else
// 		{
// 			serv._response.setStatus("OK", 200);
// 			serv._response.setBody(readFileContent(path));
// 		}
// 	}
// 	else if (is_dir(path))
// 	{
// 		if (serv._response._location.getIndexs().size())
// 		{
// 			// loop on indexs and check if file exist
// 			it = serv._response._location.getIndexs().begin();
// 			while(it < serv._response._location.getIndexs().end() && !is_file(joinPaths(path, *it)))
// 				it++;
// 			if (it < serv._response._location.getIndexs().end() && is_file(joinPaths(path, *it)))
// 			{
// 				if (serv._response._location.getCgiPaths.size())
// 				{
// 					// TODO run cgi if file format is in cgiPaths
// 				}
// 				else
// 				{
// 					serv._response.setStatus("OK", 200);
// 					serv._response.setBody(readFileContent(joinPaths(path, *it)));
// 				}
// 			}
// 			else
// 				serv._response.setStatus("Forbidden", 403);
// 		}
// 		// check if index.html exist
// 		else if (is_file(joinPaths(path, "index.html")))
// 		{
// 			serv._response.setStatus("OK", 200);
// 			serv._response.setBody(readFileContent(path + "/index.html"));
// 		}
// 		else if (serv._response._location.getAutoIndex())
// 		{
// 			//TODO generate autoindex page
// 		}
// 		else
// 		{
// 			serv._response.setStatus("Forbidden", 403);
// 		}
// 	}
// 	else
// 	{
// 		serv._response.setStatus("Not Found", 404);
// 	}
// }

