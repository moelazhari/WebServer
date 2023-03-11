/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configFileParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:02:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/11 14:19:59 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

