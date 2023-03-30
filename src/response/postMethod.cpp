/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/30 02:50:22 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void response::Post(server& serv, ParseRequest& request)
{
	std::string 						path;
	// std::vector<std::string>::iterator	it;
	// std::string							file;
	std::cout << "POST" << std::endl;
	
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	
	// if (request.getIsUpload())
	// {
	// 	if (this->getLocation().getUpload() == "on")
	// 	{
	// 		this->setUploadAlowed(true);
	// 		this->setUploadPath(path);
	// 		// TODO add status after uploading the file 201 or 500
	// 	}
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
			this->setFilePath(joinPaths(path, this->getLocation().getIndexs()[0]));
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
