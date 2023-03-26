/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:38:20 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/26 16:49:05 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void response::Post(server& serv, ParseRequest& request)
{

	std::string path;

	path = this->getLocation().getRoot();
	path = joinPaths(path, request.getLink().substr(this->getLocationPath().size()));
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
		else if (this->getLocation().getCgiPaths().empty())// this->isCGI(file)
		{
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse(serv);
		}
		else
		{
			this->cgi(serv, request);
			this->setStatus("OK", 200);
			this->setHeader("Content-Length", std::to_string(this->_body.size()));
		}
	}
	else if (is_file(path))
	{
		if (!this->isCgi(path))
		{
			this->setStatus("Forbidden", 403);
			this->setFilePath("./error_pages/403.html");
			this->fillResponse(serv);
		}
		else
		{
			this->cgi(serv, request);
			this->setStatus("OK", 200);
			this->setHeader("Content-Length", std::to_string(this->_body.size()));
		}
	}
}