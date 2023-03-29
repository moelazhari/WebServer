/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:16:43 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/27 20:12:27 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <iostream>
// #include <string>
// #include <unistd.h>
// #include <string>
// #include <sstream>

// int main(){

//     std::istringstream in("first_name=ghjgh&last_name=kjjhkghkgh");

//     std::cin.rdbuf(in.rdbuf());
//     std::string        line;
//     getline(std::cin, line, '\0');
//     std::cout << line << std::endl;
// }

#include <iostream>
using namespace std;
int main()
{
    cout << "this is a test" << endl;
    string line;
    getline(cin, line, '\n');
    cout << "line = " + line << endl;
}