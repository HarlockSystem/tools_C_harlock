CC = gcc
COPTS = -c -g -O3 -DDEBUG -W -Wall -pedantic
OBJS = tools.o mfile.o intarray.o array.o jstr.o stringarray.o hcharpix.o KVdata.o himage.o lifegame.o array.o

#ALL : test_graph make_unit_graphs cours219
#	echo "Compilation terminée"

lifegame.o : lifegame.c lifegame.h tools.h jstr.h intarray.h hcharpix.h mfile.h KVdata.h
	$(CC) $(COPTS) lifegame.c

mfile.o : mfile.c mfile.h tools.h jstr.h
	$(CC) $(COPTS) mfile.c

tools.o : tools.c tools.h
	$(CC) $(COPTS) tools.c

jstr.o : jstr.c jstr.h tools.h intarray.h jfile.h
	$(CC) $(COPTS) jstr.c -o jstr.o

intarray.o : intarray.c intarray.h tools.h btree.h
	$(CC) $(COPTS) intarray.c -o intarray.o

array.o : array.c array.h tools.h
	$(CC) $(COPTS) array.c -o array.o

hcharpix.o : hcharpix.c hcharpix.h jstr.h
	$(CC) $(COPTS) hcharpix.c -o hcharpix.o

himage.o : himage.c himage.h tools.h
	$(CC) $(COPTS) himage.c -o himage.o

KVdata.o: KVdata.c KVdata.h tools.h stringarray.h mfile.h jstr.h
	$(CC) $(COPTS) KVdata.c -o KVdata.o

clean :
	rm -f *.o *~ \#*\# *.stackdump $(ALL)
