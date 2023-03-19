/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:58:09 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/19 00:43:52 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

response::response()
{
	_isLocation = false;
	this->_location = new location();
	return ;
}

response::~response()
{
	return ;
}
// --------------------------------- SETTER --------------------------------- //
void	response::setStatus(std::string status, int code)
{
	this->_status = "HTTP/1.1 " + std::to_string(code) + " " + status;
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

void	response::setLocation(location *location)
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

location	*response::getLocation()
{
	return this->_location;
}

std::map<std::string, std::string>	&response::getHeaderMap()
{
	return this->_header;
}

std::string	getFilePath()
{
	return this->_filePath;
}

// --------------------------------- GENERATE RESPONSE --------------------------------- //	