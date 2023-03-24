/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteMethod.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:37:47 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/23 20:45:49 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"

void	response::Delete(server& serv, ParseRequest& request)
{
	(void)(serv);
	(void)(request);
	std::cout << "Delete" << std::endl;
	// std::string path;
	
	// path = this->getLocation().getRoot();
	// path = joinPaths(path, request.getLink().substr(this->getLocationPath().size()));

	// if (is_dir(path))
	// {
	// 	if (this->getLocation().getCgiPaths().size())
	// 	{
	// 		if (this->getLocation().getIndexs().size())
	// 		{
	// 			// run cgi on requested file with Delete method
	// 		}
	// 		else
	// 		{
	// 			this->setStatus("Forbidden", 403);
	// 			this->setFilePath("./error_pages/403.html");
	// 			this->fillResponse(serv);
	// 		}
			
	// 	}
	// 	else
	// 	{
	// 		//dlete all files in directory
	// 		if (/*delete failed*/)
	// 		{
	// 			if (/*has write acces on folder*/)
	// 			{
	// 				this->setStatus("Internal Server Error", 500);
	// 				this->setFilePath("./error_pages/500.html");
	// 				this->fillResponse(serv);
	// 			}
	// 			else
	// 			{
	// 				this->setStatus("Forbidden", 403);
	// 				this->setFilePath("./error_pages/403.html");
	// 				this->fillResponse(serv);
	// 			}
				
	// 		}
	// 		else
	// 		{
	// 			this->setStatus("NO CONTENT", 204);
	// 			this->setFilePath("./error_pages/204.html");
	// 			this->fillResponse(serv);	
	// 		}
	// 	}
		
	// }	
	// else if (is_file(path))
	// {
	// 	if (this->getLocation().getCgiPaths().size())
	// 	{
	// 		// run cgi on requested file with Delete method
	// 	}
	// 	else
	// 	{
	// 		if (/*delete failed*/)
	// 		{
	// 			if (/*has write acces on file*/)
	// 			{
	// 				this->setStatus("Internal Server Error", 500);
	// 				this->setFilePath("./error_pages/500.html");
	// 				this->fillResponse(serv);
	// 			}
	// 			else
	// 			{
	// 				this->setStatus("Forbidden", 403);
	// 				this->setFilePath("./error_pages/403.html");
	// 				this->fillResponse(serv);
	// 			}
				
	// 		}
	// 		else
	// 		{
	// 			this->setStatus("NO CONTENT", 204);
	// 			this->setFilePath("./error_pages/204.html");
	// 			this->fillResponse(serv);	
	// 		}
	// 	}
		
	// }
	// else
	// {
	// 	this->setStatus("Not Found", 404);
	// 	this->setFilePath("./error_pages/404.html");
	// 	this->fillResponse(serv);
	// }
}