/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:01:39 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/13 17:12:54 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

#include "configFileParser.hpp"
#include "Values.hpp"

class location : public Values
{
	private:
		std::string							_cgiPath;
		std::pair<int, std::string>			_return;
	public:
		location();
		location(std::string &content);
		~location();

		void    setValues(std::string &key, std::string &value);
		void    checkValues();
		
		void setCgiPath(std::string key, std::string &value);
		void setReturn(std::string key, std::string &value);

		void printValues();
};

#endif