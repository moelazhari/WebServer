/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/28 17:16:11 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "utils.hpp"

class server
{
	private:
		std::map<std::string, std::string>	_values;
		std::map<std::string, std::string>	_errorPages;
	public:
		server(parsConfig &config);
		~server();

		void	parsLine(std::string &str, std::string &key, std::string &value);
		void    setValues(std::string &key, std::string &value);
};

void parsServers(std::vector<parsConfig> &config);

#endif