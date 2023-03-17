/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:11:58 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/17 17:02:16 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void cgi(server serv, request req, std::string fileName): _serv(serv) _req(req) _fileName(fileName){
//     this->setEnv();
//     this->_cmd[0] = this->getCGIPaths(std::string fileName);
//     thsi->_cmd[1] = fileName.c_str();
    
//     int fd[2];
//     pipe(fd);

//     pid_t pid = fork();
//     if (pid == 0){
//         dup2(fd[1], 1);
//         close(fd[1]);
//         execve(cmd[0], cmd, env);
//     }
//     waitpid(pid, NULL, 0);
//     dup2(fd[0], 0);
//     close(fd[0]);
//     close(fd[1]);

//     char buf[1];
//     while (read(0, buf, 1) > 0)
//        this->cgiOutput.append(buf, 1);
    
//     this->parseCgiOutput();
// }

// char *getPath(std::string fileName){
//     std::map<std::string, std::string> cgiPaths = _serv.getCgiPath();
//     if (fileName.find(".php") != std::string::npos)
//         return  cgiPaths[".php"].c_str();
//     else if (fileName.find(".py") != std::string::npos)
//         return  cgiPaths[".py"].c_str();
// }


// void    setEnv(){
//     this->env[0] = "REQUEST_METHOD=" + _req.getMethod();
//     this->env[1] = "CONTENT_LENGTH=" + _req.getContentLength();
//     this->env[2] = "CONTENT_TYPE=" + _req.getContentType();
//     this->env[3] = "SCRIPT_NAME=" + _fileName;
//     this->env[4] = "SERVER_NAME=" + _serv.getServerName();
//     this->env[5] = "SERVER_PORT=" + _req.getPort();
//     this->env[6] = "SERVER_PROTOCO=" + _req.getHttpVersion();
//     this->env[7] = "HTTP_COOKIE=" + _req.getCookie();
// }

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