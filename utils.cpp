/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:41 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 17:17:00 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool	isAllNumber(std::string &str){
	for (size_t i = 0; i < str.length(); i++){
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool isAllWhiteSpace(std::string const& str){
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (!isspace(*it))
			return false;
	}
	return true;
}

void removeWhiteSpace(std::string &str){
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
}

void PrintExit(std::string str){
	std::cerr << str << std::endl;
	     exit(1);
}
