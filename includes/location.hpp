/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:01:39 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/17 18:35:48 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

#include "configFileParser.hpp"
#include "Values.hpp"

class location : public Values
{
	private:
		std::map<std::string, std::string>	_cgiPaths;
		std::pair<int, std::string>			_return;
	public:
		location();
		location(std::string &content);
		~location();

		void    setValues(std::string &key, std::string &value);
		
		void setCgiPaths(std::string key, std::string &value);
		void setReturn(std::string key, std::string &value);

		std::map<std::string, std::string>	getCgiPaths();
		std::pair<int, std::string>			getReturn();

		void printValues();
};

#endif