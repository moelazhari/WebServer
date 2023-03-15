/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:58:09 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/15 15:13:56 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

response::response()
{
    _isLocation = false;
    
    return ;
}

response::~response()
{
    return ;
}

void response::setStatus(std::string status, int code)
{
    this->_status = "HTTP/1.1 " + std::to_string(code) + " " + status;
}

void response::setHeader(std::string key, std::string value)
{
    this->_header[key] = value;
}

void response::setBody(std::string body)
{
   this->_body = body;
}

bool response::getIsLocation()
{
    return this->_isLocation;
}

void response::setIsLocation(bool value)
{
    this->_isLocation = value;
}

std::string response::getStatus()
{
    return this->_status;
}

std::string response::getHeader(std::string key)
{
    return this->_header[key];
}

std::string response::getBody()
{
    return this->_body;
}