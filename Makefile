CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror -MMD -g
OBJECTS=main.o cell.o grid.o textdisplay.o entity.o creature.o player.o controller.o game.o item.o treasure.o treasure_small.o treasure_normal.o treasure_merchant.o treasure_dragon.o invalid_behave.o enemy.o potion.o shade.o drow.o vampire.o troll.o goblin.o human.o elf.o orc.o dwarf.o halfling.o merchant.o dragon.o posn.o potion_RH.o potion_PH.o potion_BA.o potion_WA.o potion_BD.o potion_WD.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS}  -o ${EXEC}

-include ${DEPENDS}
-include potion_test.d

POTIONDEMOOBJ=potion_test.o entity.o creature.o cell.o player.o enemy.o item.o potion.o player_decorators.o
potionDemo: ${POTIONDEMOOBJ}
	${CXX} ${CXXFLAGS} ${POTIONDEMOOBJ} -o potionDemo

clean-all:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean-all

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean
