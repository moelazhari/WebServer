/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:23:05 by mazhari           #+#    #+#             */
/*   Updated: 2023/02/24 16:23:17 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configFileParser.hpp"

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Wrong number of arguments" << std::endl;
        std::cout << "Usage: ./configFileParser <config_file>" << std::endl;
        return (1);
    }
    parseConfigFile(av[1]);
    return (0);
}