CCFLAGS  = -ansi -pedantic -Wall -Werror -Wextra -std=c++11 -O3
OBJFILES = main.o
OUTFILE  = bfl

$(OUTFILE): $(OBJFILES)
	g++ $(CCFLAGS) $(OBJFILES) -o $(OUTFILE)

main.o: main.cc
	g++ $(CCFLAGS) -c main.cc

clean:
	-rm *.o $(OUTFILE)
