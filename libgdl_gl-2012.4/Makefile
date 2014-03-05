EXEC	=	bomberman

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

all	:	$(EXEC)

$(EXEC)	:	$(OBJ)
		g++ -o $(EXEC) $(OBJ) -I./include -L./lib -Wl,--rpath=./lib -lgdl_gl -lGL -lGLU

clean	:
		rm -rf *~ $(OBJ)

fclean	:	clean
		rm -rf $(EXEC)

re	:	fclean all
