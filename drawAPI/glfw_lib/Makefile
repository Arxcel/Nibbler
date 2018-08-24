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

NAME = ../../libGLFW.so

F = -Wall -Werror -Wextra

FLAGS = -std=c++11

LIB_FLAGS = -shared -fPIC

L_DIR = ../../nibbler_3rdparty/

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj

libFREETYPE_DIR = $(L_DIR)/build/freetype
libGLAD_DIR = $(L_DIR)/build/glad
libGLM_DIR = $(L_DIR)/glm
libSTB_DIR = $(L_DIR)/stb

libFreeType = -L $(libFREETYPE_DIR)/ -lfreetype

libGLFW = -L $(L_DIR)/build/glfw/src/ -lglfw3

libGLAD = -L $(libGLAD_DIR)/ -lglad

FRAMEWORKS = -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =	nibbler_glfw.hpp \
		Shader.hpp \
		CustomException.hpp \
		Texture.hpp \
		ResourceManager.hpp \
		Drawer.hpp \
		SpriteRenderer.hpp \
		TextRenderer.hpp \
		Character.hpp

HEADERS =	-I$(I_DIR) \
			-I$(L_DIR)/glfw/include/ \
			-I$(libGLAD_DIR)/include/ \
			-I$(libSTB_DIR) \
			-I$(libGLM_DIR)/ \
			-I$(L_DIR)/freetype/include/

SOURCES =	CustomException.cpp \
			nibbler_glfw.cpp \
			Drawer.cpp \
			ResourceManager.cpp \
			Shader.cpp \
			Texture.cpp \
			SpriteRenderer.cpp \
			TextRenderer.cpp \
			Character.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o)) $(O_DIR)/stb_image.o

all: obj $(NAME)

$(NAME): libs $(OBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS) $(LIB_FLAGS) $(libGLAD) $(libGLFW) $(libFreeType) $(FRAMEWORKS)

libs:
		sh $(L_DIR)/buildLibs.sh

		[ -f "$(S_DIR)/stb_image.cpp" ] \
		&& : \
		|| echo "#define STB_IMAGE_IMPLEMENTATION\n#include \"stb_image.h\"" > $(S_DIR)/stb_image.cpp \
		&& $(CC) -c -o $(O_DIR)/stb_image.o $(S_DIR)/stb_image.cpp $(HEADERS)

obj:
	mkdir -p obj

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(HEADERS)

clean:
		rm -f $(OBJS)
		rm -rf $(O_DIR)

fclean: clean
		rm -f $(NAME)
		rm -rf $(L_DIR)/build/glfw
		rm -rf $(libFREETYPE_DIR)
		rm -rf $(libGLAD_DIR)
		rm -rf $(S_DIR)/stb_image.cpp

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: