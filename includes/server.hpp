/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/20 21:39:39 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "location.hpp"
#include "Values.hpp"

class server: public Values
{
	private:
		std::map<std::string, location>		_locations;
		std::map<std::string, std::string>	_memeTypes;
	public:
		server(parsConfig &config);
		server();
		~server();
		
		void setValues(std::string &key, std::string &value);
		void setDefaultValues();
		
		void	parsMemeTypes(std::string path);
		void	setMemeTypes(std::string value, std::string key);
		
		// getters
		std::string							getHost();
		std::vector<int>					getPorts();
		std::map<std::string, location>		&getLocations();
		std::map<std::string, std::string>	&getMemeTypes();
		
		void printValues();
};

#endif