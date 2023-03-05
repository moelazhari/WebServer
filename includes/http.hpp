/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:33:27 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/05 16:42:16 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
# define HTTP_HPP

# include "configFileParser.hpp"

class http
{
    protected:
        std::map<std::string, std::string>    _values;
        std::map<int, std::string>            _errorPages;
        std::vector<std::string>              _allowMethods;
    public:
        http();
        ~http();
};

#endif