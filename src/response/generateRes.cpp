/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateRes.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/20 19:10:33 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"response.hpp"

void	response::checkForLocation(server& serv, ParseRequest& request)
{
	std::map<std::string, location>::iterator 	it;
	std::string									link;
	size_t 										pos;
	
	it = serv.getLocations().begin();
	link = request.getLink();
	while(link.size() > 1)
	{
		it = serv.getLocations().find(link);
		
		if (it != serv.getLocations().end())
		{
			this->setLocation(it->second);
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
	
	// this->checkForLocation(serv, request);
	if (!this->getIsLocation())
	{
		//test a htmlfile		
		// this->setStatus("OK", 200);
		// this->setHeader("Content-Type", "text/html");
		// this->setFilePath("./web_pages/400.html");
		// this->setBody(readFileContent(this->getFilePath()));
		// this->setHeader("Content-Length", std::to_string(this->getBody().size()));
		
		// test the video
		this->setStatus("OK", 200);
		this->setHeader("Content-Type", "video/mp4");
		this->setFilePath("./web_pages/mngil.mp4");
		this->setBody(readFileContent(this->getFilePath()));
		this->setHeader("Content-Length", std::to_string(this->getBody().size()));
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
		else if (check_method(request.getMethod(), this->getLocation().getAllowMethods()) == false)
		{
			this->setStatus("Method Not Allowed", 405);
			this->setFilePath("./error_pages/405.html");
			this->fillResponse();
		}
		else
		{
			// set the root in location to the root in server if the root in location is empty
			if (this->getLocation().getRoot().size() == 0)
				this->getLocation().setRoot(serv.getRoot());
			//check which method to call
			for (int i = 0; i < 3; i++)
			{
				if (request.getMethod() == methods[i]){
					(this->*f[i])(serv, request);
				}
			}
		}
	}
}