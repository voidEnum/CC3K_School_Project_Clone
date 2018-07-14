CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror -MMD -g
OBJECTS=main.o cell.o grid.o textdisplay.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=fileInputGridTest

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS}  -o ${EXEC}

-include ${DEPENDS}

clean-all:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean-all

clean:
	rm ${OBJECTS} ${DEPENDS}
.PHONY: clean
