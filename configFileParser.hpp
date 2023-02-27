/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/25 20:23:35 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEPARSER_HPP
# define CONFIGFILEPARSER_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <map>

class ConfigFileParser
{
    private:
        //Server                              _server;
        std::map<std::string, std::string>  _location;
    public:
        ConfigFileParser(std::string fileName);
        ~ConfigFileParser();
        
        void getLocatoins(std::string content);
        void parsServer(std::string content);
        void parsLocation(std::string content);
};


#endif