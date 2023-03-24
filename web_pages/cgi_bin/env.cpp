/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:27:26 by mazhari           #+#    #+#             */
/*   Updated: 2023/03/24 00:18:49 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv, char **envp)
{
    for (int i = 0; envp[i]; i++)
        std::cout << envp[i] << std::endl;
    std::cout << "argc: gjghjgh" << std::endl;
    return 0;
}