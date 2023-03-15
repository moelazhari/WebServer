/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:40 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/15 19:31:44 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <fcntl.h>
#include <map>
#include <sys/stat.h>
#include"../includes/server.hpp"

class response
{
	private:
		std::string							_status;
		std::map<std::string, std::string>	_header; // key, value
		std::string							_body;
		location&							_location;
		bool								_isLocation;
	public:
		response();
		~response();

		std::string	getStatus();
		std::string	getHeader(std::string key);
		std::string	getBody();
		bool		getIsLocation();
		
		void		setStatus(std::string status, int code);
		void		setHeader(std::string key, std::string value);
		void		setBody(std::string body);
		void		setIsLocation(bool value);
		void		setLocation(location& location);
};