NAME =		bomberman

SRC =		main.cpp \
		Arrow.cpp \
		Menu.cpp \
		Floor.cpp \
		Explosion.cpp \
		Stone.cpp \
		Box.cpp \
		Range.cpp \
		BombSup.cpp \
		Speed.cpp \
		Bomb.cpp \
		Skills.cpp \
		Vector2f.cpp \
		APlayer.cpp \
		Settings.cpp \
		MenuManager.cpp \
		Map.cpp \
		Run.cpp \
		MyGame.cpp\
		Vector3f.cpp\
		Camera.cpp\
		Song.cpp \
		Ia.cpp \
		Save.cpp\
		Introduce.cpp \
		Pause.cpp \
		Victory.cpp \
		FontImage.cpp \
		Tools.cpp \
		FileContent.cpp

OBJ =		$(SRC:.cpp=.o) 

CPPFLAGS =	-I./libgdl_gl-2012.4/include -O3 -g

LDFLAGS =	-L./libgdl_gl-2012.4/lib -Wl,--rpath=./libgdl_gl-2012.4/lib,--rpath=/usr/local/lib -lgdl_gl -lGL -lGLU -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lGLEW -ldl

all:		$(NAME) 

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDFLAGS)

%.o:		%.cpp
		g++ $(CPPFLAGS) -o $@ -c $<

clean:
		rm -fr $(OBJ)
		rm -fr *~
		rm -fr *#

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
