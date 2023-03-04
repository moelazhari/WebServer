/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/04 17:01:32 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "location.hpp"

class server
{
	private:
		std::map<std::string, std::string>	_values;
		std::map<int, std::string>			_errorPages;
		std::map<std::string, location>		_locations;
	public:
		server(parsConfig &config);
		~server();

		void	setValues(std::string &key, std::string &value);
		void	checkValues();
		void	printValues();
};

void parsServers(std::vector<parsConfig> &config);

#endif