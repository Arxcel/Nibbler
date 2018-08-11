# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 13:49:03 by vkozlov           #+#    #+#              #
#    Updated: 2018/03/18 15:51:46 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = nibbler

FLAGS = -std=c++11

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj

LIB1 = ./nibbler_glfw

LIB2 = ./nibbler_sdl

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =	Game.hpp \
		GameLevel.hpp \
		GameObject.hpp \
		Snake.hpp

HEADERS = -I$(I_DIR)

SOURCES =	main.cpp \
			Game.cpp \
			GameLevel.cpp \
            GameObject.cpp \
            Snake.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): libs $(OBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS)

obj:
	mkdir -p obj

libs:
	make -C $(LIB1)
	make -C $(LIB2)

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(HEADERS)

clean:
		rm -f $(OBJS)
		rm -rf $(O_DIR)
		make clean -C $(LIB1)
		make clean -C $(LIB2)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIB1)
		make fclean -C $(LIB2)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: