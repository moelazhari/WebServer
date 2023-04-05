/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/03 21:43:34 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.hpp"

void response::Post(server& serv, ParseRequest& request)
{
	std::string 						path;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			indexs;
	
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	if (this->getLocation().getUpload() == "on" && this->isUploadRequest(request))
	{
		if (checkUploadRequest(request))
			createUploadFiles();
		else
			this->setStatus(400);
		this->fillResponse(serv, "");
	}
	else if (!is_file(path) && !is_dir(path))
	{
		this->setStatus(404);
		this->fillResponse(serv, "");
	}
	else if (is_dir(path))
	{
		indexs = this->getLocation().getIndexs();
		if (indexs.empty())
		{
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
		else
		{
			it = indexs.begin();
			while(it != indexs.end() && !is_file(joinPaths(path, *it)))
				it++;
			if (it == indexs.end() || !this->isCgi(joinPaths(path, *it)))
			{
				this->setStatus(403);
				this->fillResponse(serv, "");
			}
			else
			{
				this->setFilePath(joinPaths(path, *it));
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
