/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/29 03:22:51 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string>

void    response::cgi(server& serv, ParseRequest& req){
	std::string output;
	this->setCgiEnv(serv, req);
	char        *env[this->_env.size() + 1];
	// string to char
	int i = 0;
	for (std::vector<std::string>::iterator it = this->_env.begin(); it != this->_env.end(); it++)
	{
		env[i] = (char *)(*it).c_str();
		i++;
	}
	env[i] = NULL;
	// set cmd 
	this->_cmd[0] = (char *)this->getCGIPath().c_str();
	this->_cmd[1] = (char *)this->_filePath.c_str();
	this->_cmd[2] = NULL;
	
	// exec cgi
	int tmp = dup(0);
	int fd[2];
	if (pipe(fd) < 0)
		std::cout << "pipe error" << std::endl;
	pid_t pid = fork();
	if (pid < 0)
		std::cout << "fork error" << std::endl;
	if (pid == 0){
		dup2(fd[1], 1);
		close(fd[1]);

		std::string body = "first_name=mohamed&last_name=azhari";

		std::FILE *tmp;
		tmp = tmpfile();
		
    	if (tmp) {
        	std::fputs(body.c_str(), tmp);
        	std::rewind(tmp);
    	}

		dup2(fileno(tmp), 0);
		close(fileno(tmp));

		execve(this->_cmd[0], this->_cmd, env);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);

	char buf[1];
	while (read(0, buf, 1) > 0)
	   output.append(buf, 1);

	dup2(tmp, 0);
	close(tmp);
	this->parseCgiOutput(output);
}

std::string response::getCGIPath(){
	std::map<std::string, std::string> cgiPaths = this->_location.getCgiPaths();
	std::string extension = "." + getExtension(this->_filePath);

	return cgiPaths[extension];
}

void	response::setCgiEnv(server& serv, ParseRequest& req){
	(void)serv;
	(void)req;
	this->_env.push_back("SERVER_SOFTWARE=webserv/1.0");
	this->_env.push_back("SERVER_NAME=" + serv.getServerName());
	this->_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	this->_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	this->_env.push_back("SERVER_PORT= " + req.getPort());
	this->_env.push_back("REQUEST_METHOD=" + req.getMethod());
	this->_env.push_back("SCRIPT_NAME=" + this->getFilePath());
	this->_env.push_back("CONTENT_TYPE=" + req.getHeadr("Content-Type"));
	this->_env.push_back("CONTENT_LENGTH=35");
	this->_env.push_back("QUERY_STRING=" + req.getQuery());
}

void    response::parseCgiOutput(std::string output){
	std::istringstream  tmp(output);
	std::string         line;

	while (std::getline(tmp, line)){
		line += "\n";
		
		if (line.find(":") != std::string::npos){
			size_t pos = line.find(":");
			this->setHeader(line.substr(0, pos), line.substr(pos + 1, line.find("\r\n") - pos - 1));
		}
		else if (line.find("\r\n") != std::string::npos){
			break;
		}
	}
	getline(tmp, this->_body, '\0');
	if (!this->_body.empty())
		this->setStatus(200);
	else 
		this->setStatus(500);
}

bool  response::isCgi(std::string file){
	std::map<std::string, std::string> 	extensions = this->_location.getCgiPaths();
	std::string							extension = "." + getExtension(file);
	
	if (this->_location.getCgiPaths().empty())
		return false;
	if (extensions.find(extension) == extensions.end())
		return false;
	return true;
}