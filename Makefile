OPTFLAGS	= -Wall -Werror -Wextra -Wstrict-prototypes -pedantic -fno-common -O3 -g -std=gnu11
CC		= gcc52
MAKE		= make
rm 		= rm -f
DOXYGEN		= doxygen

%.o: %.c
	$(CC) $(OPTFLAGS) -o $@ -c $<

all: MyFind

MyFind: MyFind.o
	$(CC) $(OPTFLAGS) MyFind.o -o MyFind

clean:
	$(RM) *.o *.h.gch MyFind


clean_doc:
	$(RM) -r doc/

doc: clean_doc
	$(DOXYGEN)

clean_all: clean clean_doc
