/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:48:30 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/16 17:37:11 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "configFileParser.hpp"
# include "server.hpp"
#i nclude "request.hpp"


class cgi{
    private:
        server      _serv;
        request     _req;
        std::string _fileName;
        char        *env[8];
    public:
        cgi(server serv, std::string path);
        ~cgi();

    void    setEnv();
};

#endif