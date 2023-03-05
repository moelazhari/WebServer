/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/01 19:01:15 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILEPARSER_HPP
# define CONFIGFILEPARSER_HPP

#include "utils.hpp"

struct parsConfig{
    std::string                         content;
    std::map <std::string, std::string> locations;
};

void parsFile(std::string fileName, std::vector<parsConfig> &config);
void getServers(std::string &content, std::vector<parsConfig> &config);
void getLocations(std::string &content, std::map <std::string, std::string> &locations);

void removeWhiteSpace(std::string &str);
bool isAllWhiteSpace(std::string const& str);
void PrintExit(std::string str);

#endif