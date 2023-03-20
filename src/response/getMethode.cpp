/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/20 16:24:29 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

bool	is_file(std::string path)
{
	bool is_file = false;
	std::ifstream file(path.c_str());
	if (file.good())
	{
		file.close();
		is_file = true;
	}
	return is_file;
}

bool	is_dir(std::string path)
{
	bool is_dir = false;
	DIR* dir = opendir(path.c_str());
	if (dir != NULL)
	{
		closedir(dir);
		is_dir = true;	
	}
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
	(void)serv;
	std::string							path;
	std::vector<std::string>::iterator	it;

	path = this->getLocation().getRoot();
	path = joinPaths(path, request.getLink().substr(this->getLocationPath().size()));
	// TODO make this a funcion to work with it inside the dir loop
	if (is_dir(path))
	{
		if (this->getLocation().getIndexs().size())
		{
			// loop on indexs and check if file exist
			it = this->getLocation().getIndexs().begin();
			while(it < this->getLocation().getIndexs().end() && !is_file(joinPaths(path, *it)))
				it++;
			if (it < this->getLocation().getIndexs().end() && is_file(joinPaths(path, *it)))
			{
				if (this->getLocation().getCgiPaths().size())
				{
					// TODO run cgi if file format is in cgiPaths
					this->setStatus("OK", 200);
					this->setFilePath("error_pages/cgi.html");
					this->fillResponse();
				}
				else
				{
					this->setStatus("OK", 200);
					this->setFilePath(joinPaths(path, *it));
				}
			}
			else{
				this->setStatus("Forbidden", 403);
				this->setFilePath("./error_pages/403.html");
				this->fillResponse();
			}
		}
		// check if index.html exist
		else if (is_file(joinPaths(path, "index.html")))
		{
			this->setStatus("OK", 200);
			this->setFilePath(joinPaths(path, "index.html"));
			this->fillResponse();
		}
		else if (this->getLocation().getAutoIndex().size() && this->getLocation().getAutoIndex() == "on")
		{
			//TODO generate autoindex page
			this->setStatus("OK", 200);
			this->setFilePath("error_pages/autoindex.html");
			this->fillResponse();
		}
		else
		{
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse();
		}
	}
	else if (is_file(path))
	{
		if (this->getLocation().getCgiPaths().size())// TODO && file format is in cgiPaths
		{
			this->setStatus("OK", 200);
			this->setFilePath("error_pages/cgi.html");
			this->fillResponse();
		}
		else
		{
			this->setStatus("OK", 200);
			this->setFilePath(path);
			this->fillResponse();
		}
	}
	else
	{
		this->setStatus("Not Found", 404);
		this->setFilePath("./error_pages/404.html");
		this->fillResponse();
	}
}

