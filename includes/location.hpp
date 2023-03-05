/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:01:39 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/05 18:32:35 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

#include "configFileParser.hpp"

class location
{
    private:
        std::map<std::string, std::string>    _values;
        std::map<int, std::string>            _errorPages;
        std::vector<std::string>              _allowMethods;
        std::pair<int, std::string>           _return;
    public:
        location();
        location(std::string &content, std::map<std::string, std::string> values, 
        std::map<int, std::string> errorPages, std::vector<std::string> allowMethods);

        ~location();
        void    printValues();
    private:
        void    setValues(std::string &key, std::string &value);
};

#endif