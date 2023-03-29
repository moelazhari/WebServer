/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/29 05:22:45 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void response::Post(server& serv, ParseRequest& request)
{
	std::string 						path;
	std::vector<std::string>::iterator	it;
	std::string							file;
	
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	
	// TODO if (this->getLocation().getUpload() && this->getLocation().getUpload() == "on")
	// {
	// 	if ()
	// 	{
	// 		this->setUpload(true);
	// 		this->setFilePath(path);
	// 		return;	
	// 	}
	// }
	// if (/*shouldUpload*/)
	// {
	// 	std::ofstream file(path, std::ios::app);
	// 	if (file.is_open())
	// 		{
	// 		file << request.getBody();
	// 		file.close();
	// 		this->setStatus("Created", 201);
	// 		this->setFilePath(path);
	// 		this->fillResponse(serv);
	// 		}
	// 	else
	// 		{
	// 			this->setStatus("Internal Server Error", 500);
	// 			this->setFilePath("./error_pages/500.html");
	// 			this->fillResponse(serv);
	// 		}
	// }
	if (!is_file(path) && !is_dir(path))
	{
		this->setStatus(404);
		this->fillResponse(serv, "");
	}
	else if (is_dir(path))
	{
		if (this->getLocation().getIndexs().empty())
		{
			//TODO it = this->getLocation().getIndexs().begin();
			// while(it < this->getLocation().getIndexs().end() && !is_file(joinPaths(path, *it)))
			// 	it++;
			// file = *it;
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
		else if (this->getLocation().getCgiPaths().empty())
		{
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
		else
		{
			this->cgi(serv, request);
			this->setStatus(200);
			this->setHeader("Content-Length", std::to_string(this->_body.size()));
		}
	}
	else if (is_file(path))
	{
		if (this->getLocation().getCgiPaths().empty())
		{
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
		else
		{
			this->setFilePath(path);
			this->cgi(serv, request);
			this->setStatus(200);
			this->setHeader("Content-Length", std::to_string(this->_body.size()));
		}
	}
}
