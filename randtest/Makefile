INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= -Wall -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

PRODUCT=randtest

HPPFILES=
CPPFILES= randtest.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CPPFILES:.cpp=.o}

all: randtest

clean:
	-rm -f *.o *.d randtest randstats.txt *.exe *.gcov *.gcno *.gcda

randtest: randtest.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

depend:

.cpp.o:
	$(CC) -MD $(CFLAGS) -c $<
