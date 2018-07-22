CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror -MMD -g
OBJECTS=main.o cell.o grid.o textdisplay.o entity.o creature.o player.o controller.o game.o item.o treasure.o treasure_small.o treasure_normal.o treasure_merchant.o treasure_dragon.o invalid_behave.o enemy.o potion.o potion_rh.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS}  -o ${EXEC}

-include ${DEPENDS}

clean-all:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean-all

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean
