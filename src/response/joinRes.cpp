/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinRes.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:31:15 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/18 19:45:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

std::string response::joinResponse()
{
	std::string	response;

	response = this->_status + "\r\n";
	for (std::map<std::string, std::string>::iterator it = this->_header.begin(); it != this->_header.end(); it++)
		response += it->first + ": " + it->second + "\r\n";
	response += "\r\n";
	response += this->_body;
	return response;
}