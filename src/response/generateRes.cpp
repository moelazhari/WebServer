/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateRes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/05 01:24:56 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"response.hpp"

void	response::checkForLocation(server& serv, ParseRequest& request)
{
	std::map<std::string, location>::iterator 	it;
	std::string									link;
	size_t 										pos;
	
	it = serv.getLocations().begin();
	link = fixLink(request.getLink());
	while(link.size() > 1)
	{
		it = serv.getLocations().find(link);
		
		if (it != serv.getLocations().end())
		{
			this->setLocation(it->second);
			this->setLocationPath(it->first);
			this->fillLocaiton(serv);
			this->setIsLocation(true);
			return ;
		}
		pos = link.find_last_of("/");
		if (pos == std::string::npos)
			break;
		link = link.substr(0, pos);
	}
	// looking for the default path /
	it = serv.getLocations().find("/");
	if (it != serv.getLocations().end())
	{
		this->setLocation(it->second);
		this->setLocationPath(it->first);
		this->fillLocaiton(serv);
		this->setIsLocation(true);
	}
}

void	response::generateResponse(server& serv, ParseRequest& request)
{
	void (response::*f[3])(server& serv, ParseRequest& request) = {&response::Get, &response::Post, &response::Delete};
	std::string methods[] = {"GET", "POST", "DELETE"};
	
	this->checkForLocation(serv, request);
	if (!this->getIsLocation())
	{
		this->setLocationPath("");
		this->fillLocaiton(serv);
	}
	//check for return redirection
	if (this->getLocation().getReturn().second.size())
	{
		this->setStatus(this->getLocation().getReturn().first);
		this->setHeader("Content-type", "text/html");
		//return link
		this->setHeader("Location", this->getLocation().getReturn().second);
		this->fillResponse(serv, "");
	}
	
	//check if method allowed
	else if (checkForElement(request.getMethod(), this->getLocation().getAllowMethods()) == false)
	{
		this->setStatus(405);
		this->fillResponse(serv, "");
	}
	else
	{
		//check which method to call
		for (int i = 0; i < 3; i++)
		{
			if (request.getMethod() == methods[i]){
				(this->*f[i])(serv, request);
			}
		}
	}
}