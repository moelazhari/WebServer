/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/27 00:50:46 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void response::Post(server& serv, ParseRequest& request)
{
	std::string path;

	path = this->getLocation().getRoot();
	path = joinPaths(path, fixLink(request.getLink().substr(this->getLocationPath().size())));
	// if (/*location supports upload*/)
	// {
	// 	std::ifstream file(path);

	// 	file << request.getBody();
		
	// }
	if (!is_file(path) && !is_dir(path))
	{
		this->setStatus("Not Found", 404);
		this->setFilePath("./error_pages/404.html");
		this->fillResponse(serv);
	}
	else if (is_dir(path))
	{
		if (this->getLocation().getIndexs().empty())
		{
			// TODO do i need to check if the index is present in the directory? or just pss it to the cgi?
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse(serv);
		}
		else if (this->getLocation().getCgiPaths().empty())
		{
			std::cout << "run cgi" << std::endl;
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse(serv);
		}
		else
		{
			//run cgi on requested file with Post method
		}
	}
	else if (is_file(path))
	{
		if (this->getLocation().getCgiPaths().empty())
		{
			std::cout << "run cgi" << std::endl;
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse(serv);
		}
		else
		{
			//run cgi on requested file with Post method
		}
	}
}