/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methodes.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/17 20:24:00 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"response.hpp"

void	response::checkForLocation(server& serv, ParseRequest& request)
{
	std::map<std::string, location>::iterator it;
	std::string link;
	
	// looking for the longest path
	link = request.getLink();
	while(link.size())
	{
		it = serv.getLocations().find(link);
		if (it != serv.getLocations().end())
		{
			this->setLocation(it->second);
			this->setLocationPath(it->first);
			this->setIsLocation(true);
			return ;
		}
		link = link.substr(0, link.find_last_of("/"));
	}
	// looking for the default path /
	it = serv.getLocations().find("/");
	if (it != serv.getLocations().end())
	{
		this->setLocation(it->second);
		this->setLocationPath(it->first);
		this->setIsLocation(true);
		return ;
	}
}

bool	check_method(std::string method, std::vector<std::string> methods)
{
	std::vector<std::string>::iterator it;
	
	it = std::find(methods.begin(), methods.end(), method);
	if (it != methods.end())
		return true;
	return false;
}

void	response::generateResponse(server& serv, ParseRequest& request)
{
	
	void (response::*f[3])(server& serv, ParseRequest& request) = {&response::Get, &response::Post, &response::Delete};
	std::string methods[] = {"GET", "POST", "DELETE"};
	
	this->checkForLocation(serv, request);
	if (!this->getIsLocation())
	{
		this->setStatus("Not Found", 404);
		this->setHeader("Content-Type", "text/html");
		this->setBody("<html><body><h1>404 Not Found</h1></body></html>");
	}
	else
	{
		//check for return redirection
		if (this->getLocation().getReturn().second.size())
		{
			this->setStatus("Moved Temporarily", this->getLocation().getReturn().first);
			this->setHeader("Content-Type", "text/html");
			//return link
			this->setHeader("Location", this->getLocation().getReturn().second);
		}
		
		//check if method allowed
		else if (check_method(request.getMethode(), this->getLocation().getAllowMethods()) == false)
		{
			this->setStatus("Method Not Allowed", 405);
			this->setHeader("Content-Type", "text/html");
			this->setBody("<html><body><h1>405 Method Not Allowed</h1></body></html>");
		}
		else
		{
			// set the root in location to the root in server if the root in location is empty
			if (this->getLocation().getRoot().size() == 0)
				this->getLocation().setRoot(serv.getRoot());
			//check which method to call
			for (int i = 0; i < 3; i++)
			{
				if (request.getMethode() == methods[i])
					(this->*f[i])(serv, request);
			}
		}
	}
}