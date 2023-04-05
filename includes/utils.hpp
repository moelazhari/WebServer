/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:15:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/20 22:59:01 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "define.hpp"

bool						isAllWhiteSpace(std::string &str);
void						removeWhiteSpace(std::string &str);
bool						isAllNumber(std::string &str);
void						PrintExit(std::string str);
std::vector<std::string>	split(std::string str, std::string dlem);
void                        replaceChar(std::string &str, char c1, char c2);
int							toInt(std::string str);
int 					   	hexToDec(std::string hex);
std::string					toStr(int num);
void						parsLine(std::string &str, std::string &key, std::string &value);
void						removeHostPortDuplicates(std::multimap<std::string, int> &hostPort);
std::string					getExtension(std::string str);
bool                        isHost(std::string str);