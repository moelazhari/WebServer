/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/25 02:54:06 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Get(server& serv, ParseRequest& request)
{
	std::string							path;
	std::vector<std::string>::iterator	it;
	std::string							file;

	path = this->getLocation().getRoot();
	path = joinPaths(path, request.getLink().substr(this->getLocationPath().size()));
	
	if (isSlash(path) && this->getLocation().getRoot().empty())
	{
		this->setStatus("OK", 200);
		this->setFilePath("error_pages/welcome.html");
		this->fillResponse(serv);
	}
	// TODO make this a funcion to work with it inside the dir loop
	else if (is_dir(path))
	{
		if (this->getLocation().getIndexs().size())
		{
			// loop on indexs and check if file exist
			it = this->getLocation().getIndexs().begin();
			while(it < this->getLocation().getIndexs().end() && !is_file(joinPaths(path, *it)))
				it++;
			file = *it;
			if (it < this->getLocation().getIndexs().end() && is_file(joinPaths(path, file)))
			{
				if (this->getLocation().getCgiPaths().size() && (getExtension(file) == "py" || getExtension(file) == "php"))
				{
					// TODO run cgi if file format is in cgiPaths
					std::cout << "run cgi" << std::endl;
					this->cgi(serv, request);
				}
				else
				{
					this->setStatus("OK", 200);
					this->setFilePath(joinPaths(path, file));
					this->fillResponse(serv);
				}
			}
			else{
				this->setStatus("Forbidden", 403);
				this->setFilePath("./web_pages/error_pages/403.html");
				this->fillResponse(serv);
			}
		}
		// check if index.html exist
		else if (is_file(joinPaths(path, "index.html")))
		{
			this->setStatus("OK", 200);
			this->setFilePath(joinPaths(path, "index.html"));
			this->fillResponse(serv);
		}
		else if (this->getLocation().getAutoIndex() == "on")
		{
			//TODO generate autoindex page
			this->setStatus("OK", 200);
			autoIndex(path, request.getLink());
			this->setFilePath("error_pages/autoindex.html");
			this->fillResponse(serv);
		}
		else
		{
			this->setStatus("Forbidden", 403);
			this->setFilePath("./web_pages/error_pages/403.html");
			this->fillResponse(serv);
		}
	}
	else if (is_file(path))
	{
		if (this->getLocation().getCgiPaths().size() &&  (getExtension(path) == "py" || getExtension(path) == "php") )
		{
			this->setStatus("OK", 200);
			this->setFilePath("error_pages/cgi.html");
			this->fillResponse(serv);
		}
		else
		{
			this->setStatus("OK", 200);
			this->setFilePath(path);
			this->fillResponse(serv);
		}
	}
	else
	{
		this->setStatus("Not Found", 404);
		this->setFilePath("./web_pages/error_pages/404.html");
		this->fillResponse(serv);
	}
}

