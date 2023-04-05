/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:37:47 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/05 00:37:02 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.hpp"

void	response::Delete(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			indexs;
	
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
				std::cout << "cgi" << std::endl;
				this->setFilePath(joinPaths(path, *it));
				this->cgi(request);
				this->fillResponse(serv, "");
			}
			// delete index
			else
			{
				std::cout << "delete index" << std::endl;
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
			std::cout << "cgi" << std::endl;
			this->setFilePath(path);
			this->cgi(request);
			this->fillResponse(serv, "");
		}
		else
		{
			std::cout << "delete file" << std::endl;
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