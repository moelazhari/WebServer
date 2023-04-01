/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:37:47 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/31 03:28:05 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Delete(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::string							file;
	
	std::cout << "DELETE" << std::endl;
	return;
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));

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
			// check if index exist
			if (it == this->getLocation().getIndexs().end())
			{
				this->setStatus(403);
				this->fillResponse(serv, "");
			}
			// check if index is a cgi
			else if (isCgi(file))
			{
				this->setFilePath(joinPaths(path, file));
				this->cgi(serv, request);
			}
			// delete index
			else
			{
				if (deleteFile(joinPaths(path, file)) == false)
				{
					this->setStatus(500);
					this->fillResponse(serv, "");
				}
				else
				{
					this->setStatus(204);
					this->fillResponse(serv, "");
				}
			}
			
		}
	}	
	else if (is_file(path))
	{
		if (this->isCgi(path))
		{
			this->setFilePath(path);
			this->cgi(serv, request);
		}
		else
		{
			if (deleteFile(path) == false)
			{
				this->setStatus(500);
				this->fillResponse(serv, "");
			}
			else
			{
				this->setStatus(204);
				this->fillResponse(serv, "");	
			}
		}
	}
}