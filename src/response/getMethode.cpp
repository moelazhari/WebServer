/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/01 19:48:31 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Get(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::string							file;

	std::cout<< "GET" << std::endl;
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	
	// TODO make this a funcion to work with it inside the dir loop
	if (is_dir(path))
	{
		if (!this->getLocation().getIndexs().empty())
		{
			// loop on indexs and check if file exist
			it = this->getLocation().getIndexs().begin();
			while(it < this->getLocation().getIndexs().end() && !is_file(joinPaths(path, *it)))
				it++;
			file = *it;
			if (it < this->getLocation().getIndexs().end() && is_file(joinPaths(path, file)))
			{
				if (this->isCgi(file))
				{
					this->setFilePath(joinPaths(path, file));
					this->cgi(request);
					this->fillResponse(serv, "");
				}
				else
				{
					this->setStatus(200);
					this->fillResponse(serv, joinPaths(path, file));
				}
			}
			else
			{
				this->setStatus(403);
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
			this->setStatus(403);
			this->fillResponse(serv, "");
		}
	}
	else if (is_file(path))
	{
		if (this->isCgi(path))
		{	
			this->setFilePath(joinPaths(path, file));
			//print headers
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

