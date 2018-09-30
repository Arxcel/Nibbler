# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arxcel <arxcel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 13:49:03 by vkozlov           #+#    #+#              #
#    Updated: 2018/09/30 16:58:16 by arxcel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = ../libAudio.so

F = -Wall -Werror -Wextra

FLAGS = -std=c++11

LIB_FLAGS = -shared -fPIC

L_DIR = ../nibbler_3rdparty/

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj

libSDL_DIR = $(L_DIR)/sdl

SDL2_F		= -framework SDL2 -framework SDL2_mixer -F $(libSDL_DIR)

SDL2_P		= -rpath @loader_path/nibbler_3rdparty/sdl/

libSDL		= $(SDL2_P) $(SDL2_F)

HEADERS =	-I$(I_DIR) \
			-I$(libSDL_DIR)/SDL2.framework/Headers/ \
			-I$(libSDL_DIR)/SDL2_mixer.framework/Headers/

SOURCES =	nibbler_audio.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(GOBJS) $(FLAGS) $(F) $(HEADERS) $(LIB_FLAGS) $(libSDL)

obj:
	mkdir -p obj

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS)
		$(CC) -c -o $@ $< $(FLAGS) $(F) $(HEADERS)

$(O_DIR)/%.o: $(GS_DIR)/%.cpp $(DEPS)
		$(CC) -c -o $@ $< $(FLAGS) $(F) $(HEADERS)

clean:
		rm -rf $(O_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: