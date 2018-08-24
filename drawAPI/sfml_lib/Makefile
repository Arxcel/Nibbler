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

NAME = nibbler_sfml.so

F = -Wall -Werror -Wextra

FLAGS = -std=c++11

LIB_FLAGS = -shared -fPIC

L_DIR = ./lib

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj


libSDL_DIR = $(L_DIR)/sdl
libFREETYPE_DIR = $(L_DIR)/freetype
libGLM_DIR = $(L_DIR)/glm
libSTB_DIR = $(L_DIR)/stb

libFreeType = -L $(libFREETYPE_DIR)/build/ -lfreetype

SFML_F		= -framework SFML -framework SFML-window -framework SFML-system -F ./lib/sfml

SFML_P		= -rpath @loader_path/lib/sfml

FRAMEWORKS = -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo $(SFML_P) $(SFML_F)

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =	nibbler_sfml.hpp \
		Shader.hpp \
		CustomException.hpp \
		Texture.hpp \
		ResourceManager.hpp \
		Drawer.hpp \
		SpriteRenderer.hpp \
		TextRenderer.hpp \
		Character.hpp

HEADERS =	-I$(I_DIR) \
			-I ./lib/sfml/SFML.framework/Headers/ \
			-I$(libSTB_DIR)/ \
			-I$(libGLM_DIR)/ \
			-I$(libFREETYPE_DIR)/include/

SOURCES =	CustomException.cpp \
			nibbler_sfml.cpp \
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
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS) $(LIB_FLAGS) $(libFreeType) $(FRAMEWORKS)

libs:

	! [ -d "$(libFREETYPE_DIR)/build" ] \
    			&& sh createBuild.sh $(libFREETYPE_DIR) \
    			&& make -C $(libFREETYPE_DIR)/build \
    			|| :

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
		rm -rf $(libSDL_DIR)/build
		rm -rf $(libFREETYPE_DIR)/build
		rm -rf $(libGLAD_DIR)/build src/glad.cpp
		rm -rf $(S_DIR)/stb_image.cpp

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: