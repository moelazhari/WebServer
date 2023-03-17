/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:15:21 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/15 22:39:27 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "configFileParser.hpp"
#include "location.hpp"
#include "Values.hpp"
// #include "response.hpp"
#include "ParseRequest.hpp"

class server: public Values
{
	private:
		std::map<std::string, location>		_locations;
		ParseRequest						_request;
		// response							_response;
		// client
	public:
		server(parsConfig &config);
		~server();

		void setValues(std::string &key, std::string &value);
		void setDefaultValues();
		std::string			getHost();
		std::vector<int>	getPorts();
		void printValues();

		// void generateResponse(ParseRequest request);

};

#endif