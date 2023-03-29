/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:37:47 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/29 03:28:52 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Delete(server& serv, ParseRequest& request)
{
	std::string path;
	
	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));

	if (is_dir(path))
	{
		if (this->getLocation().getCgiPaths().size())
		{
			if (this->getLocation().getIndexs().size())
			{
				// TODO run cgi on requested file with Delete method
			}
			else
			{
				this->setStatus(403);
				this->fillResponse(serv, "");
			}
		}
		else
		{
			//dlete all files in directory
			if (deleteAllFiles(path) == false)
			{
				// if (hasAccess(path)
				// {
				// 	this->setStatus("Internal Server Error", 500);
				// 	this->setFilePath("./error_pages/500.html");
				// 	this->fillResponse(serv);
				// }
				// else
				// {
				// 	this->setStatus("Forbidden", 403);
				// 	this->setFilePath("./error_pages/403.html");
				// 	this->fillResponse(serv);
				// }
				
			}
			else
			{
				this->setStatus(204);
				this->fillResponse(serv, "");
			}
		}
		
	}	
	else if (is_file(path))
	{
		if (this->getLocation().getCgiPaths().size())
		{
			// TODO run cgi on requested file with Delete method
		}
		else
		{
			if (deleteFile(path) == false)
			{
				if (hasAccess(path))
				{
					this->setStatus(500);
					this->fillResponse(serv, "");
				}
				else
				{
					this->setStatus(403);
					this->fillResponse(serv, "");
				}
				
			}
			else
			{
				this->setStatus(204);
				this->fillResponse(serv, "");	
			}
		}
		
	}
	else
	{
		this->setStatus(404);
		this->fillResponse(serv, "");
	}
}