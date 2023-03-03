/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loction.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:05:47 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/03 15:07:58 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

location::location() {
    return ;
}

location::location(std::string &content) {
    size_t      			pos = 0;
    std::string             tmp;
    std::string             key;
    std::string             value;

    if (content.empty())
        PrintExit("Error config file Location block: is empty");
     while (isspace(content[pos]))
        pos++;
}

location::~location(){

}