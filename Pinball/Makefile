GAMEFRAMEWORK=../GameFramework
OBJS=main.o
SDL_INCLUDE=-I/usr/include/SDL -I${GAMEFRAMEWORK}/SDL_ext
SDL_LIBS=-lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

all: Pinball
Pinball: ${OBJS}
	${CC} ${OBJS} -L${GAMEFRAMEWORK} ${SDL_LIBS} -lgameframework -o Pinball
%.o: %.cpp
	${CC} -I${GAMEFRAMEWORK} ${SDL_INCLUDE} -c $< -o $@
clean:
	-rm ${OBJS}
distclean: clean
	-rm Pinball

