/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:23:29 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/24 02:28:05 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

bool	check_method(std::string method, std::vector<std::string> methods)
{
	std::vector<std::string>::iterator it;
	
	it = std::find(methods.begin(), methods.end(), method);
	if (it != methods.end())
		return true;
	return false;
}

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
	if (path.size() == 0)
		return add;
	if (add.size() > 0)
	{	
		if (path[path.size() - 1] != '/')
			path += '/';
		if (add[0] == '/')
			add = add.substr(1);
		path += add;
	}
	return path;
}

std::string	readFileContent(std::string path)
{
	std::string content;
	std::string	line;

	std::ifstream file(path.c_str());
	if (file.good())
	{
		// read line by line
		while (getline(file, line)){
			content += line + "\n";
		}
	}
	file.close();
	return content.substr(0, content.size() - 1);
}

void	autoIndex(std::string path, std::string link)
{
	DIR	*dir;
	struct dirent *ent;
	std::ofstream file("error_pages/autoindex.html");

	file << "<!DOCTYPE html>\n<html>\n<head><title>Index of /</title></head>\n<body bgcolor=\"white\">" << std::endl;
	file << "<h1>Index of " << path << "</h1><hr><pre>" << std::endl;
	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (opendir(joinPaths(path, ent->d_name).c_str()) == NULL)
				file << "<a href=\"" << joinPaths(link, ent->d_name) << "\">" << ent->d_name << "</a>" << std::endl;
			else
				file << "<a href=\"" << joinPaths(link, ent->d_name) << "/\">" << ent->d_name <<"/</a>" << std::endl;
		}
		closedir(dir);
	}
}

static	std::string vecToStr(std::vector<std::string> vec)
{
	std::string str = "";

	for (size_t i = 0; i < vec.size(); i++)
	{
		str += vec[i];
		if (i != vec.size() - 1)
			str += " ";
	}
	return str;
}

void	response::fillLocaiton(server &serv)
{
	if (this->getLocation().getAllowMethods().size() == 0 && serv.getAllowMethods().size() != 0)
		this->getLocation().setAllowMethods(vecToStr(serv.getAllowMethods()));
	if (this->getLocation().getAutoIndex().size() == 0 && serv.getAutoIndex().size() != 0)
		this->getLocation().setAutoIndex(serv.getAutoIndex());
	if (this->getLocation().getRoot().size() == 0 && serv.getRoot().size() != 0)
		this->getLocation().setRoot(serv.getRoot());
	if (this->getLocation().getIndexs().size() == 0 && serv.getIndexs().size() != 0)
		this->getLocation().setIndexs(vecToStr(serv.getIndexs()));
	// this->getLocation().setClientMaxBodySize();
	// this->getLocation().setHost();
	// this->getLocation().setServerName();
	// this->getLocation().setPorts();
	// this->getLocation().setErrorPages();
}