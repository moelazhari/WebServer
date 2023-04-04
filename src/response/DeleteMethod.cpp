/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:37:47 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/04 02:17:22 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Delete(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			indexs;
	
	std::cout << "DELETE" << std::endl;
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));

	if (!is_file(path) && !is_dir(path))
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
			// check if index exist
			if (it == indexs.end() || !is_file(joinPaths(path, *it)))
			{
				this->setStatus(403);
				this->fillResponse(serv, "");
			}
			// check if index is a cgi
			else if (isCgi(joinPaths(path, *it)))
			{
				this->setFilePath(joinPaths(path, *it));
				this->cgi(request);
			}
			// delete index
			else
			{
				if (deleteFile(joinPaths(path, *it)) == false)
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
			this->cgi(request);
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