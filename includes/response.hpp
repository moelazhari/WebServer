/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:40 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/02 01:20:55 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include "server.hpp"
#include "ParseRequest.hpp"
#include "utils.hpp"


class response
{
	private:
		std::string							_status;
		int									_code;
		std::map<int, std::string>			_statusString;
		std::map<std::string, std::string>	_header; // key, value
		std::string							_body;
		location							_location;
		std::string							_locationPath;
		bool								_isLocation;
		std::string							_filePath;
		// bool								_uploadAlowed;
		// std::string							_uploadPath;
		// cgi
		std::vector<std::string>			_env;
		std::vector<std::string>			_cmd;
	public:
		response();
		~response();

		std::string							getStatus();
		std::string							getHeader(std::string key);
		std::string							getBody();
		location							&getLocation();
		bool								getIsLocation();
		std::string							getLocationPath();
		std::map<std::string, std::string>	&getHeaderMap();
		std::string							getFilePath();
		// bool								getUploadAlowed();
		// std::string							getUploadPath();
		
		void								setStatus(int code);
		void								setHeader(std::string key, std::string value);
		void								setBody(std::string body);
		void								setIsLocation(bool value);
		void								setLocation(location &location);
		void								setLocationPath(std::string path);
		void								setFilePath(std::string file);
		// void								setUploadAlowed(bool value);
		// void								setUploadPath(std::string path);

		void								generateResponse(server& server, ParseRequest& request);
		std::string							joinResponse();
		void 								checkForLocation(server& server, ParseRequest& request);
		void								fillLocaiton(server &serv);
		void								fillResponse(server &serv, std::string path);

		void								Get(server& server, ParseRequest& request);
		void								Post(server& server, ParseRequest& request);
		void								Delete(server& server, ParseRequest& request);
		//TODO std::string send_error(int status);

		//cgi
		void		cgi(ParseRequest& request);
		bool		isCgi(std::string file);
		void		setCgiEnv(ParseRequest& req);
		void		setCgiCmd();
		void		parseCgiOutput(std::string output);
		bool		checkUpload(ParseRequest& req);
		
};

bool		is_dir(std::string path);
bool		is_file(std::string path);
std::string	joinPaths(std::string path, std::string add);
std::string	readFileContent(std::string path);
bool		checkForElement(std::string method, std::vector<std::string> methods);
void		autoIndex(std::string path, std::string link);
bool		isSlash(std::string path);
// bool		deleteAllFiles(std::string path);
bool		deleteFile(std::string path);
std::string	fixLink(std::string link);
// std::string	getDateTime();
std::string	toStr(int num);