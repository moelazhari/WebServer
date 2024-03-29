/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Values.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:44:48 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/29 00:47:40 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "define.hpp"

class Values{
	protected:
		size_t						_clientMaxBodySize;
		std::string					_autoIndex;
		std::string					_host;
		std::string					_root;
		std::string					_serverName;
		std::string					_upload;
		std::vector<int>			_ports;
		std::map<int, std::string>	_errorPages;
		std::vector<std::string>	_allowMethods;
		std::vector<std::string>	_indexs;
	public:
		Values();
		virtual ~Values();
		virtual void    setValues(std::string &key, std::string &value) = 0;

		// setters
		void setClientMaxBodySize(std::string value);
		void setAutoIndex(std::string value);
		void setHost(std::string value);
		void setRoot(std::string value);
		void setServerName(std::string value);
		void setUpload(std::string value);
		void setPorts(std::string value);
		void setErrorPages(std::string value);
		void setAllowMethods(std::string value);
		void setIndexs(std::string value);
		// getters
		std::string					getAutoIndex();
		size_t							getClientMaxBodySize();
		std::string					getHost();
		std::string					getRoot();
		std::string					getServerName();
		std::string					getUpload();
		std::vector<int>			getPorts();
		std::map<int, std::string>	getErrorPages();
		std::vector<std::string>	getAllowMethods();
		std::vector<std::string>	getIndexs();
};