# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hilton <hilton@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 01:46:08 by hilton            #+#    #+#              #
#    Updated: 2019/01/24 15:23:10 by hmthimun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = bomberman

CC = clang++ -std=c++14
CCFLAGS = #-Wall -Werror -Wextra

SRC_FOLDER = src
INCLUDE_FOLDER = include

SRCDIR = src/
SRCS =	AudioEngine.cpp         Gameengine.cpp          IOManager.cpp           ParticleBatch2D.cpp     ScreenList.cpp          SpriteFont.cpp          Timing.cpp              stb_image.cpp \
		Camera2D.cpp            Graphics.cpp            ImageLoader.cpp         ParticleEngine2D.cpp    Sound.cpp               Texture.cpp             Window.cpp              screen.cpp \
		Error.cpp               IGameScreen.cpp         InputManager.cpp        PicoPNG.cpp             Sprite.cpp              TextureCache.cpp        Window2.cpp             settings.cpp \
		GLSLPrograme.cpp        IMainGame.cpp           MainMenu.cpp            ResourceManager.cpp     SpriteBatch.cpp         TileSheet.cpp           WindowKeyEvents.cpp     shader.cpp \

SRC	= $(addprefix $(SRCDIR), $(SRCS)) Agent.cpp  Bomb.cpp  Emo.cpp  Gun.cpp  Human.cpp  Level.cpp  main.cpp  MainGame.cpp  Player.cpp  Zombie.cpp BombManager.cpp
INCLUDE = $(wildcard $(INCLUDE_FOLDER)/*.h)

BREW_REPO = https://github.com/Tolsadus/42homebrewfix.git
BREW_TMP = .brew
BREW = ${HOME}/.brew
# BREW = /home/linuxbrew/.linuxbrew

_GLEW_FOLDER = $(BREW)/Cellar/glew
GLEW_FOLDER = $(_GLEW_FOLDER)/$(shell ls -r $(_GLEW_FOLDER) | head -n 1)
GLEW = -L $(GLEW_FOLDER)/lib -lGLEW -I $(GLEW_FOLDER)/include/

_GLU_FOLDER = $(BREW)/Cellar/glu
GLU_FOLDER = $(_GLU_FOLDER)/$(shell ls -r $(_GLU_FOLDER) | head -n 1)
GLU = -L $(GLU_FOLDER)/lib -lGLU -I $(GLU_FOLDER)/include/

_GLFW_FOLDER = $(BREW)/Cellar/glfw
GLFW_FOLDER = $(_GLFW_FOLDER)/$(shell ls -r $(_GLFW_FOLDER) | head -n 1)
GLFW = -L $(GLFW_FOLDER)/lib -lglfw -I $(GLFW_FOLDER)/include/GLFW

_MESA_FOLDER = $(BREW)/Cellar/mesa
MESA_FOLDER = $(_MESA_FOLDER)/$(shell ls -r $(_MESA_FOLDER) | head -n 1)
MESA = -L $(MESA_FOLDER)/lib -lGL -I $(MESA_FOLDER)/include/

_BOOST_FOLDER = $(BREW)/Cellar/boost
BOOST_FOLDER = $(_BOOST_FOLDER)/$(shell ls -r $(_BOOST_FOLDER) | head -n 1)
BOOST = -L $(BOOST_FOLDER)/lib -lboost_serialization -I $(BOOST_FOLDER)/include/

_SDL2_FOLDER = $(BREW)/Cellar/sdl2
SDL2_FOLDER = $(_SDL2_FOLDER)/$(shell ls -r $(_SDL2_FOLDER) | head -n 1)
SDL2 = -L $(SDL2_FOLDER)/lib -lSDL2 -I $(SDL2_FOLDER)/include/ -I $(SDL2_FOLDER)/include/SDL2

_SDL2_MIXER_FOLDER = $(BREW)/Cellar/sdl2_mixer
SDL2_MIXER_FOLDER = $(_SDL2_MIXER_FOLDER)/$(shell ls -r $(_SDL2_MIXER_FOLDER) | head -n 1)
SDL2_MIXER = -L $(SDL2_MIXER_FOLDER)/lib -lSDL2_mixer -I $(SDL2_MIXER_FOLDER)/include/

_SDL2_TTF_FOLDER = $(BREW)/Cellar/sdl2_ttf
SDL2_TTF_FOLDER = $(_SDL2_TTF_FOLDER)/$(shell ls -r $(_SDL2_TTF_FOLDER) | head -n 1)
SDL2_TTF = -L $(SDL2_TTF_FOLDER)/lib -lSDL2_ttf -I $(SDL2_TTF_FOLDER)/include/

_GLM_FOLDER = $(BREW)/Cellar/glm
GLM_FOLDER = $(_GLM_FOLDER)/$(shell ls -r $(_GLM_FOLDER) | head -n 1)
GLM = -I $(GLM_FOLDER)/include/

INC_DIR = -I ~/include

LIB_DIR = -L ~/lib -lGLEW -L ~/lib -lSDL2_mixer -L ~/lib -lSDL2_ttf -L ~/lib -lSDL2 -L ~/lib -lglfw -L ~/lib -lboost_serialization

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE) $(BREW) $(_BOOST_FOLDER) $(_GLFW_FOLDER) $(_MESA_FOLDER) $(_GLM_FOLDER) $(_GLEW_FOLDER) $(_SDL2_FOLDER) $(_SDL2_MIXER_FOLDER) $(_SDL2_TTF_FOLDER)
	$(CC) $(INC_DIR) $(CCFLAGS) -o $(NAME) $(SRC) -I $(INCLUDE_FOLDER) $(LIB_DIR) -framework OpenGL
	./$(NAME) $(LIB_DIR)

$(BREW):
	git clone $(BREW_REPO) $(BREW_TMP)
	sh $(BREW_TMP)/install.sh && rm -rf $(BREW_TMP)
	reset

$(_BOOST_FOLDER):
	brew install boost || true

$(_MESA_FOLDER):
	# brew install mesalib-glw || true

$(_GLFW_FOLDER):
	brew install glfw3

$(_GLM_FOLDER):
	brew install glm || true

$(_GLEW_FOLDER):
	brew install glew || true

$(_SDL2_FOLDER):
	brew install sdl2 || true

$(_SDL2_MIXER_FOLDER):
	brew install sdl2_mixer || true

$(_SDL2_TTF_FOLDER):
	brew install sdl2_ttf || true

pre:
	mkdir -p ~/lib
	cp -rf $(GLEW_FOLDER)/lib/* ~/lib || true
	cp -rf $(GLU_FOLDER)/lib/* ~/lib || true
	cp -rf $(MESA_FOLDER)/lib/* ~/lib || true
	cp -rf $(BOOST_FOLDER)/lib/* ~/lib || true
	cp -rf $(SDL2_FOLDER)/lib/* ~/lib || true
	cp -rf $(SDL2_MIXER_FOLDER)/lib/* ~/lib || true
	cp -rf $(SDL2_TTF_FOLDER)/lib/* ~/lib || true
	cp -rf $(GLFW_FOLDER)/lib/* ~/lib || true
	export LD_LIBRARY_PATH=~/lib
	mkdir -p ~/include
	cp -rf $(GLM_FOLDER)/include/* ~/include || true
	cp -rf $(SDL2_MIXER_FOLDER)/include/* ~/include || true
	cp -rf $(SDL2_TTF_FOLDER)/include/* ~/include || true
	cp -rf $(SDL2_FOLDER)/include/* ~/include || true
	cp -rf $(SDL2_FOLDER)/include/SDL2/* ~/include || true
	cp -rf $(BOOST_FOLDER)/include/* ~/include || true
	cp -rf $(MESA_FOLDER)/include/* ~/include || true
	cp -rf $(GLU_FOLDER)/include/* ~/include || true
	cp -rf $(GLEW_FOLDER)/include/* ~/include || true
	cp -rf $(GLFW_FOLDER)/include/* ~/include || true


clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
