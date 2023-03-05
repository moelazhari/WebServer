/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/04 20:38:00 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "location.hpp"
#include "http.hpp"

class server : public http
{
	private:
		std::map<std::string, location>		_locations;
	public:
		server(parsConfig &config);
		~server();

		void	printValues();
	private:
		void	setValues(std::string &key, std::string &value);
};

void parsServers(std::vector<parsConfig> &config);

#endif