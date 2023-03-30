/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:23:29 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/30 02:48:40 by aboudoun         ###   ########.fr       */
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

bool	isSlash(std::string path)
{
	for (size_t i = 0; i < path.length(); i++)
	{
		if (path[i] != '/')
			return false;
	}
	return true;
}

std::string joinPaths(std::string path, std::string add)
{
	if (path.size() == 0)
		return add;
	if (add.size() > 0)
	{	
		if (path.back() != '/')
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
	std::ofstream file("./www/html/autoindex.html");

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

static	std::vector<std::string> strToVec(std::string str, char c)
{
	std::vector<std::string> vec;
	std::string tmp = "";
	
	for(size_t i = 0; i < str.size(); i++)
	{
		//add the last element
		if ((str[i] == c && tmp.size() != 0) || i == str.size() - 1)
		{
			//add the last element if it is not the same as c
			if (i == str.size() - 1 && str[i] != c)
				tmp += str[i];
			vec.push_back(tmp);
			tmp = "";
		}
		else
			tmp += str[i];
	}
	return vec;
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
	if (this->getLocation().getClientMaxBodySize() == 0 && serv.getClientMaxBodySize() != 0)
		this->getLocation().setClientMaxBodySize(std::to_string(serv.getClientMaxBodySize()));
	// TODO remove to_string funtion
}

/*---------------------------------------------------------------------------------*/
bool	deleteFile(std::string path)
{
	if (std::remove(path.c_str()) == 0)
		return true;
	return false;
}

bool	deleteAllFiles(std::string path)
{
	DIR	*dir;
	struct dirent *ent;
	std::string file_path;

	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] != '.')
			{
				file_path = joinPaths(path, ent->d_name);
				if (is_dir(file_path))
					deleteAllFiles(file_path);
				else if (is_file(file_path))
					if(std::remove(file_path.c_str()) != 0)
						return false;
			}
		}
		// check if al files are deleted
		if (readdir(dir) != NULL)
		{
			closedir(dir);
			return false;
		}
		closedir(dir);
	}
	return true;
}

std::string fixLink(std::string link)
{
	std::deque<std::string> path;
	std::vector<std::string> vecLink;
	std::string newLink = "";

	vecLink = strToVec(link, '/');
	for (size_t i = 0; i < vecLink.size(); i++)
	{
		if (vecLink[i] == "..")
		{
			if (path.size() > 0)
				path.pop_back();
		}
		else if (vecLink[i] != ".")
			path.push_back(vecLink[i]);
	}
	newLink = "";
	for (size_t i = 0; i < path.size(); i++)
	{
		newLink += path[i];
		if (i != path.size() - 1)
			newLink += "/";
	}
	return newLink;
}