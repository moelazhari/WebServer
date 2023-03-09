/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:58:09 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/09 17:50:49 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

response::response()
{
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
