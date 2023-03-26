/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/26 01:20:07 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void response::Post(server& serv, ParseRequest& request)
{
	std::string path;

	path = this->getLocation().getRoot();
	path = joinPaths(path, request.getLink().substr(this->getLocationPath().size()));
	return;
	// if (/*location supports upload*/)
	// {
	// 	// upload file
	// }
	// else if (!is_file(path) && !is_dir(path))
	// {
	// 	this->setStatus("Not Found", 404);
	// 	this->setFilePath("./error_pages/404.html");
	// 	this->fillResponse(serv);
	// }
	// else if (is_dir(path))
	// {
	// 	if (this->getLocation().getIndexs().empty())
	// 	{
	// 		// TODO do i need to check if the index is present in the directory? or just pss it to the cgi?
	// 		this->setStatus("Forbidden", 403);
	// 		this->setFilePath("./error_pages/403.html");
	// 		this->fillResponse(serv);
	// 	}
	// 	else if (this->getLocation().getCgiPaths().empty())
	// 	{
	// 		this->setStatus("Forbidden", 403);
	// 		this->setFilePath("./error_pages/403.html");
	// 		this->fillResponse(serv);
	// 	}
	// 	else
	// 	{
	// 		//run cgi on requested file with Post method
	// 	}
	// }
	// else if (is_file(path))
	// {
	// 	if (this->getLocation().getCgiPaths().empty())
	// 	{
	// 		this->setStatus("Forbidden", 403);
	// 		this->setFilePath("./error_pages/403.html");
	// 		this->fillResponse(serv);
	// 	}
	// 	else
	// 	{
	// 		//run cgi on requested file with Post method
	// 	}
	// }
}