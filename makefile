# Tetris-Clone Makefile

CC=g++
CFLAGS=-Wall -std=c++11 -s -O2 -Iinclude
LDFLAGS=-L/usr/local/lib -s -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
EXEC=Tetris

all: $(EXEC)

$(EXEC): BlockMap.o Figure.o GameObject.o GameState.o main.o ScoreManager.o StateHelp.o StateHighScores.o StateMenu.o StateNewScore.o StatePlay.o StateTitle.o Tetris.o
	$(CC) -o $@ $^ $(LDFLAGS)

BlockMap.o: include/BlockMap.hpp include/Figure.hpp

Figure.o: include/Figure.hpp include/BlockMap.hpp

GameObject.o: include/GameObject.hpp include/Tetris.hpp

GameState.o: include/GameState.hpp

main.o: include/Tetris.hpp

ScoreManager.o: include/ScoreManager.hpp

StateHelp.o: include/StateHelp.hpp include/Tetris.hpp

StateHighScores.o: include/StateHighScores.hpp include/Tetris.hpp include/ScoreManager.hpp

StateMenu.o: include/StateMenu.hpp include/Tetris.hpp

StateNewScore.o: include/StateNewScore.hpp include/Tetris.hpp include/ScoreManager.hpp

StatePlay.o: include/StatePlay.hpp include/Tetris.hpp include/ScoreManager.hpp include/BlockMap.hpp include/Figure.hpp

StateTitle.o: include/StateTitle.hpp include/Tetris.hpp

Tetris.o: include/Tetris.hpp include/StateTitle.hpp include/StateMenu.hpp include/StateHighScores.hpp include/StateHelp.hpp include/StatePlay.hpp include/StateNewScore.hpp

%.o : src/%.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
