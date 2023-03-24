/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/19 18:59:35 by aboudoun         ###   ########.fr       */
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
	public:
		server(parsConfig &config);
		server();
		~server();

		void setValues(std::string &key, std::string &value);
		void setDefaultValues();
		std::string							getHost();
		std::vector<int>					getPorts();
		std::map<std::string, location>		&getLocations();
		void printValues();
};

#endif