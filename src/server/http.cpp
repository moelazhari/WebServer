/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:36:08 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/05 15:28:15 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

http::http(){
    // set default values
    this->_values["listen"] = "80";
    this->_values["host"] = "127.0.0.1";
    this->_values["root"] = "web_pages";
    this->_values["autoindex"] = "off";
    this->_values["index"] = "index.html";
    this->_values["client_max_body_size"] = "1000000";
    // set default error pages
    this->_errorPages[400] = "400.html";
    this->_errorPages[404] = "404.html";
    this->_errorPages[413] = "413.html";
    this->_errorPages[414] = "414.html";
    this->_errorPages[501] = "501.html";
    // set default allowed methods
    this->_allow_methods.push_back("GET");
    this->_allow_methods.push_back("HEAD");
    this->_allow_methods.push_back("POST");
}

http::~http(){
}