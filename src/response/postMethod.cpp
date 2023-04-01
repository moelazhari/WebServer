/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/01 19:38:59 by aboudoun         ###   ########.fr       */
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
		else
		{
			it = this->getLocation().getIndexs().begin();
			while(it < this->getLocation().getIndexs().end() && !is_file(joinPaths(path, *it)))
				it++;
			file = *it;
			if (it == this->getLocation().getIndexs().end() || !this->isCgi(file))
			{
				this->setStatus(403);
				this->fillResponse(serv, "");
			}
			else
			{
				this->setFilePath(joinPaths(path, file));
				this->cgi(request);
				this->fillResponse(serv, "");
			}
		}
	}
	else if (is_file(path))
	{
		if (this->isCgi(path))
		{
			this->setFilePath(path);
			this->cgi(request);
			this->fillResponse(serv, "");
		}
		else
		{
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
	}
}
