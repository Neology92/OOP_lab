
TRGDIR=./
OBJ=./obj
FLAGS= -Wall -pedantic -std=c++14 -iquote inc

__start__: ${TRGDIR}/complex_test
	${TRGDIR}/complex_test  latwy

${TRGDIR}/complex_test: ${OBJ} ${OBJ}/main.o ${OBJ}/Complex.o\
                     ${OBJ}/Expression.o ${OBJ}/Database.o ${OBJ}/Database.o
	g++ -o ${TRGDIR}/complex_test ${OBJ}/main.o ${OBJ}/Complex.o\
                     ${OBJ}/Expression.o ${OBJ}/Database.o

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: src/main.cpp inc/Complex.hh inc/Database.hh
	g++ -c ${FLAGS} -o ${OBJ}/main.o src/main.cpp

${OBJ}/Complex.o: src/Complex.cpp inc/Complex.hh
	g++ -c ${FLAGS} -o ${OBJ}/Complex.o src/Complex.cpp

${OBJ}/Database.o: src/Database.cpp inc/Database.hh inc/Expression.hh\
                       inc/Complex.hh
	g++ -c ${FLAGS} -o ${OBJ}/Database.o src/Database.cpp

${OBJ}/Expression.o: src/Expression.cpp inc/Expression.hh\
                       inc/Complex.hh
	g++ -c ${FLAGS} -o ${OBJ}/Expression.o src/Expression.cpp

${OBJ}/Database.o: src/Database.cpp inc/Database.hh inc/Expression.hh\
                       inc/Complex.hh
	g++ -c ${FLAGS} -o ${OBJ}/Database.o src/Database.cpp





clear:
	rm -f ${TRGDIR}/complex_test ${OBJ}/*
