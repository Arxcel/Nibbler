# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 13:49:03 by vkozlov           #+#    #+#              #
#    Updated: 2018/08/25 11:16:37 by vkozlov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

NAME = ../../libSDL.so

F = -Wall -Werror -Wextra

FLAGS = -std=c++11

LIB_FLAGS = -shared -fPIC

L_DIR = ../../nibbler_3rdparty/

I_DIR = ./inc

S_DIR = ./src

O_DIR = ./obj

GS_DIR = ../src
GI_DIR = ../inc

libSDL_DIR = $(L_DIR)/sdl
libFREETYPE_DIR = $(L_DIR)/build/freetype
libGLAD_DIR = $(L_DIR)/build/glad
libGLM_DIR = $(L_DIR)/glm
libSTB_DIR = $(L_DIR)/stb

libFreeType = -L $(libFREETYPE_DIR)/ -lfreetype

SDL2_F		= -framework SDL2 -F $(libSDL_DIR)

SDL2_P		= -rpath @loader_path/nibbler_3rdparty/sdl/

libGLAD = -L $(libGLAD_DIR)/ -lglad

FRAMEWORKS = -framework OpenGl -framework Cocoa -framework IOKit -framework CoreVideo $(SDL2_P) $(SDL2_F)

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT =	nibbler_sdl.hpp \
		drawer_sdl.hpp 

GEXT = 	Shader.hpp \
		CustomException.hpp \
		Texture.hpp \
		ResourceManager.hpp \
		SpriteRenderer.hpp \
		TextRenderer.hpp \
		Character.hpp

HEADERS =	-I$(I_DIR) \
			-I$(GI_DIR) \
			-I $(libSDL_DIR)/SDL2.framework/Headers/ \
			-I$(libGLAD_DIR)/include/ \
			-I$(libSTB_DIR) \
			-I$(libGLM_DIR)/ \
			-I$(L_DIR)/freetype/include/

SOURCES =	nibbler_sdl.cpp \
			drawer_sdl.cpp 

GSOURCES =	CustomException.cpp \
			ResourceManager.cpp \
			Shader.cpp \
			Texture.cpp \
			SpriteRenderer.cpp \
			TextRenderer.cpp \
			Character.cpp

SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o)) $(O_DIR)/stb_image.o

GSRCS = $(addprefix $(GS_DIR)/,$(GSOURCES))

GOBJS = $(addprefix $(O_DIR)/,$(GSOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): libs $(OBJS) $(GOBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(GOBJS) $(FLAGS) $(F) $(HEADERS) $(LIB_FLAGS) $(libGLAD) $(libSDL) $(libFreeType) $(FRAMEWORKS)

libs:
		sh $(L_DIR)/buildLibs.sh

		[ -f "$(S_DIR)/stb_image.cpp" ] \
		&& : \
		|| echo "#define STB_IMAGE_IMPLEMENTATION\n#include \"stb_image.h\"" > $(S_DIR)/stb_image.cpp \
		&& $(CC) -c -o $(O_DIR)/stb_image.o $(S_DIR)/stb_image.cpp $(HEADERS)

obj:
	mkdir -p obj

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(F) $(HEADERS)

$(O_DIR)/%.o: $(GS_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(F) $(HEADERS)

clean:
		rm -rf $(O_DIR)

fclean: clean
		rm -f $(NAME)
		rm -rf $(L_DIR)/build
		rm -rf $(S_DIR)/stb_image.cpp

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: