/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMethod.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:05:27 by aboudoun          #+#    #+#             */
/*   Updated: 2023/03/10 16:49:07 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
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