# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 20:21:22 by mazhari           #+#    #+#              #
#    Updated: 2023/03/17 20:36:13 by aboudoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= c++
FLAGS = -Wall -Werror -Wextra 
NAME= webserver

INCLUDES= ./includes

B_DIR = ./build

PARSING= $(addprefix parsing/, configFileParser utils)
SERVER= $(addprefix server/, server location Values connection ParseRequest)
RESPONSE= $(addprefix response/, response generateRes getMethod joinRes)


FILES= $(addprefix src/, main $(PARSING) $(SERVER) $(RESPONSE))
OBJS= $(addprefix $(B_DIR)/, $(FILES:=.o))

all: $(NAME)

$(B_DIR)/src/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CC) -I$(INCLUDES) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEDEAR)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(B_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean f re 