/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:58:09 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/29 03:03:30 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

response::response()
{
	this->_status = "";
	this->_header = std::map<std::string, std::string>();
	this->_body = "";
	this->_locationPath = "";
	this->_isLocation = false;
	this->_upload = false;
	this->_filePath = "";
	this->_statusString[200] = "OK";
	this->_statusString[201] = "Created";
	this->_statusString[403] = "Forbidden";
	this->_statusString[404] = "Not Found";
	this->_statusString[405] = "Method Not Allowed";
	this->_statusString[500] = "Internal Server Error";
	this->_statusString[300] = "Multiple Choices";
	this->_statusString[301] = "Moved Permanently";
	this->_statusString[302] = "Found";
	this->_statusString[303] = "See Other";
	this->_statusString[304] = "Not Modified";
	this->_statusString[305] = "Use Proxy";
	this->_statusString[307] = "Temporary Redirect";
	this->_statusString[308] = "Permanent Redirect";
	this->_env = std::vector<std::string>();
	// this->_location = new location();
	return ;
}

response::~response()
{
	return ;
}
// --------------------------------- SETTER --------------------------------- //
void	response::setStatus(int code)
{
	this->_status = "HTTP/1.1 " + std::to_string(code) + " " + this->_statusString[code];
	this->_code = code;
}

void	response::setHeader(std::string key, std::string value)
{
	this->_header[key] = value;
}

void	response::setBody(std::string body)
{
	this->_body = body;
}

void	response::setIsLocation(bool value)
{
	this->_isLocation = value;
}

void	response::setLocation(location &location)
{
	this->_location = location;
}

void	response::setLocationPath(std::string path)
{
	this->_locationPath = path;
}

void	response::setFilePath(std::string file)
{
	this->_filePath = file;
}

void	response::setUpload(bool value)
{
	this->_upload = value;
}
// --------------------------------- GETTER --------------------------------- //
bool	response::getIsLocation()
{
	return this->_isLocation;
}

std::string	response::getStatus()
{
	return this->_status;
}

std::string	response::getHeader(std::string key)
{
	return this->_header[key];
}

std::string	response::getBody()
{
	return this->_body;
}

std::string	response::getLocationPath()
{
	return this->_locationPath;
}

location	&response::getLocation()
{
	return this->_location;
}

std::map<std::string, std::string>	&response::getHeaderMap()
{
	return this->_header;
}

std::string	response::getFilePath()
{
	return this->_filePath;
}

bool	response::getUpload()
{
	return this->_upload;
}
// --------------------------------- GENERATE RESPONSE --------------------------------- //	

void	response::fillResponse(server &serv, std::string path)
{
	std::string	ext = getExtension(this->getFilePath());
	std::map<std::string, std::string>	mime = serv.getMemeTypes();
	
	if (path.empty())
		this->setFilePath(serv.getErrorPages()[this->_code]);
	else
		this->setFilePath(path);

	this->setHeader("Server", "Webserv/1.0");

	if (this->_header.find("Content-Type") == this->_header.end())
		this->setHeader("Content-Type", mime[ext]);
	if (this->getBody().empty())
		this->setBody(readFileContent(this->getFilePath()));
	if (this->_header.find("Content-Length") == this->_header.end())
		this->setHeader("Content-Length", std::to_string(this->getBody().size()));
}