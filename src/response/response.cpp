/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:58:09 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/03 01:54:27 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

response::response()
{
	this->_status = "";
	this->_header = std::map<std::string, std::string>();
	this->_uploadFiles = std::map<std::string, std::string>();
	this->_body = "";
	this->_locationPath = "";
	this->_isLocation = false;
	this->_filePath = "";
	this->_statusString[200] = "OK";
	this->_statusString[201] = "Created";
	this->_statusString[204] = "No Content";
	this->_statusString[400] = "Bad Request";
	this->_statusString[403] = "Forbidden";
	this->_statusString[404] = "Not Found";
	this->_statusString[405] = "Method Not Allowed";
	this->_statusString[413] = "Content Too Large";
	this->_statusString[414] = "URI Too Long";
	this->_statusString[500] = "Internal Server Error";
	this->_statusString[501] = "Not Implemented";
	this->_statusString[300] = "Multiple Choices";
	this->_statusString[301] = "Moved Permanently";
	this->_statusString[302] = "Found";
	this->_statusString[303] = "See Other";
	this->_statusString[304] = "Not Modified";
	this->_statusString[305] = "Use Proxy";
	this->_statusString[307] = "Temporary Redirect";
	this->_statusString[308] = "Permanent Redirect";
	this->_env = std::vector<std::string>();
}

response::~response()
{
	return ;
}
// --------------------------------- SETTER --------------------------------- //
void	response::setStatus(int code)
{
	this->_status = "HTTP/1.1 " + toStr(code) + " " + this->_statusString[code];
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

// void	response::setUploadAlowed(bool value)
// {
// 	this->_uploadAlowed = value;
// }

// void	response::setUploadPath(std::string path)
// {
// 	this->_uploadPath = path;
// }
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
	if (this->_header.find(key) == this->_header.end())
		return "";
	return this->_header[key];
}

std::vector<std::string>	&response::getCookies()
{
	return this->_cookies;
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

// bool	response::getUploadAlowed()
// {
// 	return this->_uploadAlowed;
// }

// std::string	response::getUploadPath()
// {
// 	return this->_uploadPath;
// }
// --------------------------------- GENERATE RESPONSE --------------------------------- //	

void	response::fillResponse(server &serv, std::string path)
{
	std::string	ext;
	std::map<std::string, std::string>	mime;
	
	mime = serv.getMemeTypes();
	if (path.empty() && (_code != 200 || _header.find("Location") == _header.end()))
		this->setFilePath(serv.getErrorPages()[this->_code]);
	else
		this->setFilePath(path);

	ext = getExtension(this->getFilePath());
	if (this->_header.find("Content-type") == this->_header.end())
		this->setHeader("Content-type", mime[ext]);
	if (this->getBody().empty())
		this->setBody(readFileContent(this->getFilePath()));
	if (this->_header.find("Content-Length") == this->_header.end())
		this->setHeader("Content-Length", toStr(this->getBody().size()));
	this->setHeader("Server", "Webserv/1.0");
	//TODO change content type to t miniscule
}