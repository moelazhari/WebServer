/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/21 19:53:36 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include <unistd.h>

void    response::cgi(server& serv, ParseRequest& req){
    this->setCgiEnv(serv, req);
    std::string cgi = this->getCGIPath();
    std::string output;

    std::cout << "CGI PATH: " << cgi << std::endl;
    // std::cout << "CGI PATH: " << this->_cmd[1] << std::endl;
    
    // int fd[2];
    // pipe(fd);

    // pid_t pid = fork();
    // if (pid == 0){
        // dup2(fd[1], 1);
        // close(fd[1]);
    //     execve(this->_cmd[0], this->_cmd, this->_env);
    // }
    // waitpid(pid, NULL, 0);
    // dup2(fd[0], 0);
    // close(fd[0]);
    // close(fd[1]);

    // char buf[1];
    // while (read(0, buf, 1) > 0)
    //    output.append(buf, 1);

    // std::cout << output << std::endl;
    
    exit(0);
    // this->parseCgiOutput(fileName);
}

std::string response::getCGIPath(){
    std::map<std::string, std::string> cgiPaths = this->_location.getCgiPaths();

    std::cout << "cgiPaths[.py]: " << cgiPaths[".py"] << std::endl;
    std::cout << "cgiPaths[.php]: " << cgiPaths[".php"] << std::endl;
    // if (getExtension(this->_filePath) == "py")
    //     return cgiPaths[".py"];
    // else
    //     return cgiPaths[".php"];
    return std::string();
}

void	response::setCgiEnv(server& serv, ParseRequest& req){
    std::string tmp;

    this->_env[0] = (char *)std::string("REQUEST_METHOD=" + req.getMethod()).c_str();
    this->_env[1] = (char *)std::string("CONTENT_LENGTH=" + this->_header["Content-Length"]).c_str();
    this->_env[2] = (char *)std::string("CONTENT_TYPE=" + this->_header["Content-Type"]).c_str();
    this->_env[4] = (char *)std::string("SERVER_NAME=" + serv.getServerName()).c_str();
    // this->_env[5] = std::string("SERVER_PORT=" + req.getPort()).c_str();
    // this->_env[6] = std::string("SERVER_PROTOCO=" + req.getHttpVersion()).c_str();
    // this->_env[7] = std::string("HTTP_COOKIE=" + req.getCookie()).c_str();
}

// void cgi::parseCgiOutput(std::string fileName){
//     if (fileName.find(".py") != std::string::npos){
//         if (this->cgiOutput.find("CONTENT_LENGTH=") != std::string::npos){
//             int pos = this->cgiOutput.find("CONTENT_LENGTH=");
//             std::string contentLength = this->cgiOutput.substr(pos, this->cgiOutput.find("\n") - pos);
//             this->_serv._response._headers["Content-Length"] = contentLength;
//         }
//         else
//             this->_serv._response._headers["Content-Length"] = this->cgiOutput.length();
//     }
//     this->_serv._response._body = this->cgiOutput.substr(this->cgiOutput.find("<html"));
// }