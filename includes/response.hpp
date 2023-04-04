/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:45:40 by aboudoun          #+#    #+#             */
/*   Updated: 2023/04/04 18:18:49 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include "server.hpp"
#include "ParseRequest.hpp"
#include "utils.hpp"

#define TIMEOUT 5

class response
{
	private:
		std::string							_status;
		int									_code;
		std::map<int, std::string>			_statusString;
		std::map<std::string, std::string>	_header;
		std::vector<std::string>			_cookies;
		std::string							_body;
		location							_location;
		std::string							_locationPath;
		bool								_isLocation;
		std::string							_filePath;
		std::map<std::string, std::string>	_uploadFiles;
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
		std::vector<std::string>			&getCookies();
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

		//cgi
		void		cgi(ParseRequest& request);
		bool		isCgi(std::string file);
		void		setCgiEnv(ParseRequest& req);
		void		setCgiCmd();
		char		**stringToChar(std::vector<std::string> &vec);
		void		parseCgiOutput(std::string output);
		bool		isUploadRequest(ParseRequest& req);
		bool		checkUploadRequest(ParseRequest& req);
		void 		createUploadFiles();
		
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