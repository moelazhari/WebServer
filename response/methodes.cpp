/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methodes.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/15 17:53:49 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server"
#include"response.hpp"

void	check_for_location(server& serv)
{
	std::map<std::string, location>::iterator it;
	std::string link;
	
	// looking for the longest path
	link = serv._request.getLink();
	while(link.size())
	{
		it = serv._locations.find(link);
		if (it != serv._locations.end())
		{
			serv._location = it->second;
			serv._response.setIsLocation(true);
			return ;
		}
		link = link.substr(0, link.find_last_of("/"));
	}
	// looking for the default path /
	it = serv._locations.find("/");
	if (it != serv._locations.end())
	{
		serv._location = it->second;
		serv._response.setIsLocation(true);
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

void	generate_respoonse(server& serv)
{
	void (*f[3])(server& serv) = {&Get, &Post, &Delete};
	std::string methods[] = {"GET", "POST", "DELETE"};
	
	check_for_location(serv);
	if (!serv._response.getIsLocation())
	{
		serv._response.setStatus("Not Found", 404);
		serv._response.setHeader("Content-Type", "text/html");
		serv._response.setBody("<html><body><h1>404 Not Found</h1></body></html>");
	}
	else
	{
		//check for return redirection
		if (serv._response._location.getReturnRedirection().size())
		{
			serv._response.setStatus("Moved Temporarily", serv._response._location.getReturnRedirection().first);
			serv._response.setHeader("Content-Type", "text/html");
			//return link
			serv._response.setHeader("Location", serv._response._location.getReturnRedirection().second);
		}
	}
		//check if method allowed
		else if (check_method(serv._request.getMethode(), serv._location.getMethodes()))
		{
			serv._response.setStatus("Method Not Allowed", 405);
			serv._response.setHeader("Content-Type", "text/html");
			serv._response.setBody("<html><body><h1>405 Method Not Allowed</h1></body></html>");
		}
		else
		{
			// set the root path
			if (serv._location.getRoot().size())
				serv._response.setRootPath(serv._location.getRoot());
			else
				serv._response.setRootPath(serv.getRoot());
			//check which method to call
			for (int i = 0; i < 3; i++)
			{
				if (serv._request.getMethode() == methods[i])
					f[i](serv);
			}
		}
}