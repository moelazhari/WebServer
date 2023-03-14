/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/13 16:12:15 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "location.hpp"
#include "Values.hpp"
#include "../response/response.hpp"

class server: public Values
{
	private:
		std::map<std::string, location>		_locations;
		response							_response;
		// client
	public:
		server(parsConfig &config);
		~server();

		void setValues(std::string &key, std::string &value);
		void setDefaultValues();
		// execPost();
		// execGET();
		// execDELEt();
		// startserver();

		void printValues();
};

#endif