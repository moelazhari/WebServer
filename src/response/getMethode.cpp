/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/04 18:18:35 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Get(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			indexs;

	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	
	if (is_dir(path))
	{
		indexs = this->getLocation().getIndexs();
		if (!indexs.empty())
		{
			// loop on indexs and check if file exist
			it = indexs.begin();
			while(it < indexs.end() && is_file(joinPaths(path, *it)) == false)
				it++;
			if (it != indexs.end() && is_file(joinPaths(path, *it)))
			{
				if (this->isCgi(joinPaths(path, *it)))
				{
					this->setFilePath(joinPaths(path, *it));
					this->cgi(request);
					this->fillResponse(serv, "");
				}
				else
				{
					this->setStatus(200);
					this->fillResponse(serv, joinPaths(path, *it));
				}
			}
			else
			{
				this->setStatus(404);
				this->fillResponse(serv, "");
			}
		}
		// check if index.html exist
		else if (is_file(joinPaths(path, "index.html")))
		{
			this->setStatus(200);
			this->fillResponse(serv, joinPaths(path, "index.html"));
		}
		else if (this->getLocation().getAutoIndex() == "on")
		{
			autoIndex(path, request.getLink());
			this->setStatus(200);
			this->fillResponse(serv, "./www/html/autoindex.html");
		}
		else
		{
			this->setStatus(404);
			this->fillResponse(serv, "");
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
			this->setStatus(200);
			this->fillResponse(serv, path);
		}
	}
	else
	{
		this->setStatus(404);
		this->fillResponse(serv, "");
	}
}

