/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:40 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/17 20:28:01 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <dirent.h>
#include "server.hpp"
#include "ParseRequest.hpp"


class response
{
	private:
		std::string							_status;
		std::map<std::string, std::string>	_header; // key, value
		std::string							_body;
		location							_location;
		std::string							_locationPath;
		bool								_isLocation;
	public:
		response();
		~response();

		std::string	getStatus();
		std::string	getHeader(std::string key);
		std::string	getBody();
		location&	getLocation();
		bool		getIsLocation();
		std::string	getLocationPath();
		
		void		setStatus(std::string status, int code);
		void		setHeader(std::string key, std::string value);
		void		setBody(std::string body);
		void		setIsLocation(bool value);
		void		setLocation(location& location);
		void		setLocationPath(std::string path);
		
		void		generateResponse(server& server, ParseRequest& request);
		std::string	joinResponse();
		void 		checkForLocation(server& server, ParseRequest& request);

		void		Get(server& server, ParseRequest& request);
		void		Post(server& server, ParseRequest& request);
		void		Delete(server& server, ParseRequest& request);
		//TODO std::string send_error(int status);
};

bool		is_dir(std::string path);
bool		is_file(std::string path);
std::string	joinPaths(std::string path, std::string add);
std::string	readFileContent(std::string path);
bool		check_method(std::string method, std::vector<std::string> methods);