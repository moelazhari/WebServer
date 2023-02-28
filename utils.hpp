/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:15:11 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 17:17:18 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

bool    isAllWhiteSpace(std::string const& str);
void    removeWhiteSpace(std::string &str);
bool	isAllNumber(std::string &str);
void	PrintExit(std::string str);

#endif