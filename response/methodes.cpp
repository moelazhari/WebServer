/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methodes.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:28:36 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/15 14:25:51 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server"
#include"response.hpp"

void    check_for_location(server& serv)
{
    std::map<std::string, location>::iterator it;
    std::string link;

    // looking for the longest path
    link = serv._request.getLink();
    while(link.size())
    {
        it = serv._locations.find(link);
        if (it != serv._locations.end())
        {
            serv._location = it->second;
            serv._response.setIsLocation(true);
            return ;
        }
        link = link.substr(0, link.find_last_of("/"));
    }
    // looking for the default path /
    it = serv._locations.find("/");
    if (it != serv._locations.end())
    {
        serv._location = it->second;
        serv._response.setIsLocation(true);
        return ;
    }
}

void    generate_respoonse(server& serv)
{
    check_for_location(serv);
    if (!serv._response.getIsLocation())
    {
        serv._response.setStatus("Not Found", 404);
        serv._response.setHeader("Content-Type", "text/html");
        serv._response.setBody("<html><body><h1>404 Not Found</h1></body></html>");
    }
    else
    {
        
    }
    
}