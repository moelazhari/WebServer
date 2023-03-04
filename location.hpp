/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:01:39 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/04 18:15:12 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONS_HPP
# define LOCATIONS_HPP

#include "configFileParser.hpp"

class location
{
    private:
        std::map<std::string, std::string>    _values;
        std::vector<std::string>              _allow_methods;
    public:
        location();
        location(std::string &content);
        
        ~location();

        void    setValues(std::string &key, std::string &value);
        void    printValues();
};

#endif