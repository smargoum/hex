CFLAGS = -g -Wall -Wextra -std=c99
GSL_PATH?=/usr/lib/x86_64-linux-gnu
INSTALL_DIR = install
SRC_DIR = src
CPPFLAGS = -I ${GSL_PATH}/include
LFLAGS = -L${GSL_PATH}/lib
LIBFLAGS = -fPIC -shared
LDLFLAGS = -ldl
LDFLAGS = -lgcov
SERVER_DIR=server
PLAYER_DIR=player

.PHONY: all test build clean install 

all : build test install 

build: server libplayer1.so libplayer2.so

test: alltests testwin

install: build
	cp server install/
	cp *.so install/
	cp alltests install/
clean :
	rm -f *.o *.so *.gcno *.gcda server alltests testwin
	(cd install/ && rm -f *.o *.so server alltests)
	rm -r -f html/

server: ${SRC_DIR}/${SERVER_DIR}/server.c server_aux.o option.o player1.o graph.o strategy.o
	gcc -o $@ ${CPPFLAGS} ${CFLAGS} $^ ${LDLFLAGS} ${LDFLAGS} ${LFLAGS} -lgsl -lgslcblas -lm


server_aux.o: ${SRC_DIR}/${SERVER_DIR}/main_aux.c ${SRC_DIR}/${SERVER_DIR}/main_aux.h
	gcc -o $@ ${CPPFLAGS} ${CFLAGS} ${SRC_DIR}/${SERVER_DIR}/main_aux.c ${LDLFLAGS} ${LDFLAGS} ${LFLAGS} -lgsl -lgslcblas -c

option.o: ${SRC_DIR}/${SERVER_DIR}/option.c graph.o
	gcc ${CPPFLAGS} ${CFLAGS} -c $^ -o $@ ${LDLFLAGS} ${LDFLAGS} ${LFLAGS} -lgsl -lgslcblas

player1.o:${SRC_DIR}/${PLAYER_DIR}/player1.c ${SRC_DIR}/${PLAYER_DIR}/player.h ${SRC_DIR}/graph.h ${SRC_DIR}/move.h
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -c ${SRC_DIR}/${PLAYER_DIR}/player1.c -o $@ -lm

player.o:${SRC_DIR}/${PLAYER_DIR}/player.c ${SRC_DIR}/${PLAYER_DIR}/player.h ${SRC_DIR}/graph.h ${SRC_DIR}/move.h
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -c ${SRC_DIR}/${PLAYER_DIR}/player.c -o $@ -lm

strategy.o:${SRC_DIR}/${PLAYER_DIR}/strategy.c ${SRC_DIR}/${PLAYER_DIR}/strategy.h ${SRC_DIR}/graph.h ${SRC_DIR}/move.h 
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -c ${SRC_DIR}/${PLAYER_DIR}/strategy.c -o $@ -lm


graph.o: ${SRC_DIR}/graph.c ${SRC_DIR}/graph.h
	gcc ${CPPFLAGS} ${CFLAGS} -fPIC -c ${SRC_DIR}/graph.c -o $@ ${LDLFLAGS} ${LDFLAGS} ${LFLAGS} -fPIC -lgsl -lgslcblas

libplayer1.so:player1.o graph.o strategy.o
	gcc -shared -o $@ player1.o graph.o strategy.o ${LFLAGS} -lgsl -lgslcblas

libplayer2.so:player.o graph.o strategy.o 
	gcc -shared -o $@ player.o graph.o strategy.o ${LFLAGS} -lgsl -lgslcblas

test_main_aux.o:
	gcc ${LDFLAGS} ${CPPFLAGS} ${CFLAGS} -c ${SRC_DIR}/${SERVER_DIR}/test_main_aux.c -o $@

testwin : test_main_aux.o graph.o server_aux.o 
	gcc -o $@ ${CFLAGS} $^ ${LDLFLAGS} ${LDFLAGS} ${LFLAGS} -lgsl -lgslcblas -lm


alltests.o: src/player/test_player.c src/graph.h src/move.h src/player/strategy.c 
	gcc --coverage ${LDFLAGS} ${CPPFLAGS} ${CFLAGS} -c ${SRC_DIR}/player/test_player.c -o $@ 


alltests: alltests.o player1.o graph.o strategy.o
	gcc -o $@ ${CFLAGS} $^ ${LDFLAGS} ${LFLAGS} -lgsl -lgslcblas -lgcov -lm


doc: ${SRC_DIR}/${PLAYER_DIR}/*.c ${SRC_DIR}/${PLAYER_DIR}/*.h ${SRC_DIR}/${SERVER_DIR}/*.h ${SRC_DIR}/${SERVER_DIR}/*.c ${SRC_DIR}/*.c ${SRC_DIR}/*.h  
	(cd doc/ && doxygen Doxyfile)
	
	