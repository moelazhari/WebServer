/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/24 23:42:10 by mazhari          ###   ########.fr       */
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
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if (pid == 0){
		dup2(fd[1], 1);
		close(fd[1]);
		execve(this->_cmd[0], this->_cmd, env);
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);

	//
	char buf[1];
	while (read(0, buf, 1) > 0)
	   output.append(buf, 1);
	// this->parseCgiOutput(output);
	std::cout << "output: " << output << std::endl;
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
	this->_env.push_back("fgkgjkhj=jkhjk");
	this->_env.push_back("SERVER_SOFTWARE=webserv/1.0.0");
	// env.push_back("SERVER_NAME=" + serv.getServerName());

	// // this->_env[2] = (char *)std::string("SERVER_NAME=" + serv.getServerName()).c_str();
	// // this->_env[3] = NULL;
	// // this->_env[4] = (char *)std::string("SERVER_PROTOCOL=HTTP/1.1" + ).c_str();
	// // this->_env[5] = std::string("SERVER_PORT=" + req.getPort()).c_str();
	// // this->_env[6] = std::string("SERVER_PROTOCO=" + req.getHttpVersion()).c_str();
	// // this->_env[7] = std::string("HTTP_COOKIE=" + req.getCookie()).c_str();
}


void    response::parseCgiOutput(std::string output){
	std::istringstream  tmp(output);
	std::string         line;

	while (std::getline(tmp, line)){
		line += "\n";
		if (line.find("Content-Type:") != std::string::npos){
			this->setHeader("Content-Type", line.substr(line.find(":") + 1, line.length() - 1));
		}
		else if (line.find("\r\n") != std::string::npos){
			break;
		}
	}
	getline(tmp, this->_body, '\0');
	std::cout << "body: " << this->_body << std::endl;
}