# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 13:49:03 by vkozlov           #+#    #+#              #
#    Updated: 2018/09/30 17:14:33 by arxcel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = nibbler

F = -Wall -Werror -Wextra

DEBUG = -g -fsanitize=address

FLAGS = -std=c++11 $(F)

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj

LIB1 = ./drawAPI/glfw_lib

LIB2 = ./drawAPI/sdl_lib

LIB3 = ./drawAPI/sfml_lib

LIB4 = ./audioAPI

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =	Game.hpp \
		GameLevel.hpp \
		GameObject.hpp \
		Snake.hpp \
		MediaAPI.hpp

HEADERS = -I$(I_DIR)

SOURCES =	main.cpp \
            MediaAPI.cpp \
			Game.cpp \
			GameLevel.cpp \
            GameObject.cpp \
            Snake.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): extra libs $(OBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS)

obj:
	mkdir -p obj

extra:
	git submodule init
	git submodule update

libs:
	make -C $(LIB1)
	make -C $(LIB2)
	make -C $(LIB3)
	make -C $(LIB4)

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(HEADERS)

clean:
		rm -f $(OBJS)
		rm -rf $(O_DIR)
		make clean -C $(LIB1)
		make clean -C $(LIB2)
		make clean -C $(LIB3)
		make clean -C $(LIB4)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIB1)
		make fclean -C $(LIB2)
		make fclean -C $(LIB3)
		make fclean -C $(LIB4)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: