/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/04/05 19:45:08 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "define.hpp"
class server: public Values
{
	private:
		std::map<std::string, location>		_locations;
		std::map<std::string, std::string>	_memeTypes;
	public:
		server(parsConfig &config);
		server();
		~server();
		
		void 	setValues(std::string &key, std::string &value);
		void 	setDefaultValues();
		
		void	parsMemeTypes(std::string path);
		void	setMemeTypes(std::string value, std::string key);
		
		// getters
		std::string							getHost();
		std::vector<int>					getPorts();
		std::map<std::string, location>		&getLocations();
		std::map<std::string, std::string>	&getMemeTypes();
};