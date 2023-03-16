/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/15 20:20:44 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

cgi::cgi(server serv, std::string fileName): _serv(serv) _req(serv.getRequest()) _fileName(fileName){
    std::string path = this->getCGIPath();
    int fd = 0;
    this->setEnv();

    int pid = fork();
    if (pid = 0){
        dup2(fd, 1);
        if (execve(path.c_str(), this->fileName.c_str(), this->env) == -1){
            std::cout << "Error: execve failed" << std::endl;
            exit(1);
        }
    }
    else if (pid < 0){
        std::cout << "Error: fork failed" << std::endl;
        exit(1);
    }
    else{
         waitpid(pid, NULL, 0);
    }
}

cgi::~cgi(){
    return ;
}

void cgi::setEnv(){
    this->env[0] = "REQUEST_METHOD" + _req.getMethod();
    this->env[1] = "CONTENT_LENGTH" + _req.getContentLength();
    this->env[2] = "CONTENT_TYPE" + _req.getContentType();
    this->env[3] = "SCRIPT_NAME" + _fileName;
    this->env[4] = "SERVER_NAME" + _serv.getServerName();
    if (_req.getPort())
        this->env[5] = "SERVER_PORT" + _req.getPort();
    else
        this->env[5] = "SERVER_PORT" + _serv.getPort()[0];
    this->env[6] = "SERVER_PROTOCOL" + _req.getHttpVersion();
    this->env[7] = "HTTP_COOKIE" + _req.getCookie();
}