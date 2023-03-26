/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/25 18:33:53 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include <unistd.h>
#include <errno.h>

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
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0){
		dup2(fd[1], 1);
		close(fd[1]);
		
		std::istringstream in("first_name=ghjgh&last_name=kjjhkghkgh");
		std::cin.rdbuf(in.rdbuf());
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
	std::cout << "CGI OUTPUT: " << output << std::endl;
}

std::string response::getCGIPath(){
	std::map<std::string, std::string> cgiPaths = this->_location.getCgiPaths();

	if (getExtension(this->_filePath) == "py")
		return cgiPaths[".py"];
	else
		return cgiPaths[".php"];
	return std::string();
}

void	response::setCgiEnv(server& serv, ParseRequest& req){
	(void)serv;
	(void)req;
	this->_env.push_back("SERVER_SOFTWARE=webserv/1.0");
	this->_env.push_back("SERVER_NAME=" + serv.getServerName());
	this->_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	this->_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	this->_env.push_back("SERVER_PORT= " + req.getPort());
	// this->_env.push_back("REQUEST_METHOD=" + req.getMethod());
	this->_env.push_back("REQUEST_METHOD=" + req.getMethod());
	this->_env.push_back("SCRIPT_NAME=" + this->getFilePath());
	this->_env.push_back("CONTENT_TYPE=" + req.getHeadr("Content-Type"));
	// this->_env.push_back("CONTENT_LENGTH=" + std::to_string(req.getBody().length()));
	this->_env.push_back("QUERY_STRING=" + req.getQuery());
}

void    response::parseCgiOutput(std::string output){
	std::istringstream  tmp(output);
	std::string         line;

	while (std::getline(tmp, line)){
		line += "\n";
		
		if (line.find(":") != std::string::npos){
			this->setHeader(line.substr(0, line.find(":")), line.substr(line.find(":") + 1));
		}
		else if (line.find("\r\n") != std::string::npos){
			break;
		}
	}
	getline(tmp, this->_body, '\0');
}