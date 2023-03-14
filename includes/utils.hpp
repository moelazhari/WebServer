/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:15:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/14 19:13:47 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

bool						isAllWhiteSpace(std::string const& str);
void						removeWhiteSpace(std::string &str);
bool						isAllNumber(std::string &str);
void						PrintExit(std::string str);
std::vector<std::string>	split(std::string str, std::string dlem);
int							toInt(std::string str);
void						parsLine(std::string &str, std::string &key, std::string &value);
void						removeHostPortDuplicates(std::multimap<std::string, int> &hostPort);

#endif