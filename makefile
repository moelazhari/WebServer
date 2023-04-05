# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 20:21:22 by mazhari           #+#    #+#              #
#    Updated: 2023/04/05 00:47:22 by aboudoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=$'\x1b[31m
GREEN=$'\x1b[32m
PURPLE=$'\x1b[35m

CC= c++
FLAGS = -Wall -Werror -Wextra -fsanitize=address
NAME= webserver

INCLUDES= ./includes

B_DIR = ./build

PARSING= $(addprefix parsing/, configFileParser utils)
CGI= $(addprefix cgi/, cgi)
RESPONSE= $(addprefix response/, response generateRes getMethode DeleteMethod postMethod respUtils ${CGI})
SERVER= $(addprefix server/, server location Values connection ParseRequest client)


FILES= $(addprefix src/, main $(PARSING) $(SERVER) $(RESPONSE))
OBJS= $(addprefix $(B_DIR)/, $(FILES:=.o))

all: $(NAME)

$(B_DIR)/src/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(CC) -I$(INCLUDES) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)" "Compiling $<";

$(NAME): $(OBJS) $(HEDEAR)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(B_DIR)
	@echo "$(RED)" "Cleaning ..."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)" "Full cleaning ..."

re: fclean all

.PHONY: all clean f re 