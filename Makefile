CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror -MMD -g
OBJECTS=main.o cell.o grid.o textdisplay.o entity.o creature.o player.o controller.o game.o item.o treasure.o treasure_small.o treasure_normal.o treasure_merchant.o treasure_dragon.o invalid_behave.o enemy.o potion.o potion_rh.o potion_ph.o potion_ba.o potion_wa.o potion_bd.o potion_wd.o shade.o drow.o vampire.o troll.o goblin.o human.o elf.o orc.o dwarf.o halfling.o merchant.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS}  -o ${EXEC}

-include ${DEPENDS}
-include potion_test.d

POTIONDEMOOBJ=potion_test.o entity.o item.o potion.o potion_rh.o potion_ph.o
potionDemo: ${POTIONDEMOOBJ}
	${CXX} ${CXXFLAGS} ${POTIONDEMOOBJ} -o potionDemo

clean-all:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean-all

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean
