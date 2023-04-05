/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:01:39 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/18 16:37:45 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "define.hpp"

class location : public Values
{
	private:
		std::map<std::string, std::string>	_cgiPaths;
		std::pair<int, std::string>			_return;
	public:
		location();
		location(std::string &content);
		~location();
		
		location &operator=(location &rhs);

		void    setValues(std::string &key, std::string &value);
		
		void	setCgiPaths(std::string value);
		void 	setReturn(std::string value);

		std::map<std::string, std::string>	getCgiPaths();
		std::pair<int, std::string>			getReturn();
};