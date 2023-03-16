/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethod.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/16 21:54:36 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

bool	is_file(std::string path)
{
	bool is_file = false;
	std::ifstream file(path.c_str());
	if (file.good())
		is_file = true;
	file.close();
	return is_file;
}

bool	is_dir(std::string path)
{
	bool is_dir = false;
	DIR* dir = opendir(path.c_str());
	if (dir != NULL)
		is_dir = true;
	closedir(dir);
	return is_dir;
}

void joinPaths(std::stirng& path, std::string add)
{
	if (path[path.size() - 1] != '/')
		path += '/';
	if (add[0] == '/')
		add = add.substr(1);
	path += add;
}

std::string	readFileContent(std::string path)
{
	std::string content;

	content = "";
	std::ifstream file(path.c_str());
	if (file.good())
	{
		getline(file, content, '\0');
	}
	file.close();
	return content;
}

void	Get(server& serv)
{
	std::string		path;
	// TODO add location path to root
	//TODO check if root or location have / at the end or not and add it if needed
	path = serv._response._location.getRoot();
	joinPaths(path, serv._request.getLink());
	if (is_file(path))
	{
		if (serv._response._location.getCgiPaths.size())
		{
			// TODO run cgi
		}
		else
		{
			serv._response.setStatusCode(200);
			serv._response.setReasonPhrase("OK");
			serv._response.setBody(readFileContent(path));
		}
	}
	else if (is_dir(path))
	{
		//TODO loop on indexs
		if (serv._response._location.getIndexs().size())
		{
			// get the index file
			//look for the index file if not found return 403
		}
		else if (is_file(path + "index.html"))
		{
			serv._response.setStatusCode(200);
			serv._response.setReasonPhrase("OK");
			//TODO readFileContent
			serv._response.setBody(readFileContent(path + "/index.html"));
		}
		else if (serv._response._location.getAutoIndex())
		{
			//TODO generate autoindex page
		}
		else
		{
			serv._response.setStatusCode(403);
			serv._response.setReasonPhrase("Forbidden");
		}
	}
	else
	{
		serv._response.setStatusCode(404);
		serv._response.setReasonPhrase("Not Found");
	}
}

