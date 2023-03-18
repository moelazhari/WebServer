/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/18 22:45:28 by mazhari          ###   ########.fr       */
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

std::string joinPaths(std::string path, std::string add)
{
	if (path[path.size() - 1] != '/')
		path += '/';
	if (add[0] == '/')
		add = add.substr(1);
	path += add;
	return path;
}

std::string	readFileContent(std::string path)
{
	std::string content;
	std::string	line;

	std::ifstream file(path.c_str());
	if (file.good())
	{
		// read line by line and remove \n
		while (getline(file, line)){
			content += line + "\n";
		}
	}
	file.close();
	return content.substr(0, content.size() - 1);
}

void	response::Get(server& serv, ParseRequest& request)
{
	(void)	serv;
	std::string		path;
	std::vector<std::string>::iterator it;

	path = this->getLocation()->getRoot();
	path = joinPaths(path, request.getLink());
	// TODO make this a funcion to work with it inside the dir loop
	if (is_file(path))
	{
		if (this->getLocation()->getCgiPaths().size())// TODO && file format is in cgiPaths
		{
			// TODO run cgi if file format is in cgiPaths
		}
		else
		{
			this->setStatus("OK", 200);
			this->setBody(readFileContent(path));
		}
	}
	else if (is_dir(path))
	{
		if (this->getLocation()->getIndexs().size())
		{
			// loop on indexs and check if file exist
			it = this->getLocation()->getIndexs().begin();
			while(it < this->getLocation()->getIndexs().end() && !is_file(joinPaths(path, *it)))
				it++;
			if (it < this->getLocation()->getIndexs().end() && is_file(joinPaths(path, *it)))
			{
				if (this->getLocation()->getCgiPaths().size())
				{
					// TODO run cgi if file format is in cgiPaths
				}
				else
				{
					this->setStatus("OK", 200);
					this->setBody(readFileContent(joinPaths(path, *it)));
				}
			}
			else
				this->setStatus("Forbidden", 403);
		}
		// check if index.html exist
		else if (is_file(joinPaths(path, "index.html")))
		{
			this->setStatus("OK", 200);
			this->setBody(readFileContent(path + "/index.html"));
		}
		else if (this->getLocation()->getAutoIndex().size())
		{
			//TODO generate autoindex page
		}
		else
		{
			this->setStatus("Forbidden", 403);
		}
	}
	else
	{
		this->setStatus("Not Found", 404);
	}
}

