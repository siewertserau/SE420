INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS=
CFLAGS= -Wall -O0 -fprofile-arcs -ftest-coverage -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

PRODUCT=simple

HFILES=
CFILES= simple.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: simple

clean:
	-rm -f *.o *.d *.exe simple *.gcov *.gcno *.gcda

simple: simple.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
