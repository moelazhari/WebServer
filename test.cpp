/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:16:43 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/25 18:30:39 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>
#include <string>
#include <sstream>

int main(){

    std::istringstream in("first_name=ghjgh&last_name=kjjhkghkgh");
    std::string line;

    std::cin.rdbuf(in.rdbuf());
    getline(std::cin, line, '\0');
    std::cout << line << std::endl;
}
