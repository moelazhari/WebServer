/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:16:43 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/25 02:58:08 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>

class B {
    public:
        B() {

        }
        ~B() {
            std::cout << "B destructor" << std::endl;
        }
        B(const B &b) {
            std::cout << "B copy constructor" << std::endl;
        }
        B &operator=(const B &b) {
            std::cout << "B assignation operator" << std::endl;
            return *this;
        }
};


class A
{
    char *_env[2];
    // std::string _tmp;

    public:
        void test()
        {
            // std::string tmp;
            // tmp = "request_method=GET";
                
            // // this->ptr[0] = (char *)tmp.c_str();
            // // this->ptr[1] = NULL;

            this->env();
            for (int i = 0; this->_env[i]; i++)
                std::cout << "env: " << this->_env[i] << std::endl;
        }
        void env()
        {
            std::string tmp = std::string("request_method=GET");
                
            this->_env[0] = (char *)(tmp).c_str();
            this->_env[1] = NULL;
            tmp = "gbfgfgmh";
            // for (int i = 0; this->_env[i]; i++)
            //     std::cout << "env: " << this->_env[i] << std::endl;
        }
};

int main(){
    A a;
    a.test();
    return 0;
}