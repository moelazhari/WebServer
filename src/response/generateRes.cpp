/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateRes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/18 19:48:37 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"response.hpp"

void	response::checkForLocation(server& serv, ParseRequest& request)
{
	std::map<std::string, location> 			locations;
	std::map<std::string, location>::iterator 	it;
	std::string									link;
	size_t 										pos;
	
	locations = serv.getLocations();
	it = locations.begin();
	link = request.getLink();
	while(link.size())
	{
		it = locations.find(link);
		
		if (it != locations.end())
		{
			this->setLocation(&(it->second));
			this->setLocationPath(it->first);
			this->setIsLocation(true);
			return ;
		}
		pos = link.find_last_of("/");
		if (pos == std::string::npos)
			break;
		link = link.substr(0, pos);
	}
	// looking for the default path /
	it = locations.find("/");
	if (it != locations.end())
	{
		this->setLocation(&(it->second));
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
		this->setBody(readFileContent("/Users/aboudoun/Desktop/webserv/web_pages/index.html"));
		// std::cout<<readFileContent("/Users/aboudoun/Desktop/webserv/web_pages/index.html")<<std::endl;
	}
	else
	{
		//check for return redirection
		if (this->getLocation()->getReturn().second.size())
		{
			this->setStatus("Moved Temporarily", this->getLocation()->getReturn().first);
			this->setHeader("Content-Type", "text/html");
			//return link
			this->setHeader("Location", this->getLocation()->getReturn().second);
		}
		
		//check if method allowed
		else if (check_method(request.getMethod(), this->getLocation()->getAllowMethods()) == false)
		{
			this->setStatus("Method Not Allowed", 405);
			this->setHeader("Content-Type", "text/html");
			this->setBody("<html><body><h1>405 Method Not Allowed</h1></body></html>");
		}
		else
		{
			// set the root in location to the root in server if the root in location is empty
			if (this->getLocation()->getRoot().size() == 0)
				this->getLocation()->setRoot(serv.getRoot());
			//check which method to call
			for (int i = 0; i < 3; i++)
			{
				if (request.getMethod() == methods[i])
					(this->*f[i])(serv, request);
			}
		}
	}
}