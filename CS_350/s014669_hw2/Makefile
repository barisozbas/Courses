HEADERS	= meal.h
default: kitchen

kitchen: kitchen.o 
	gcc kitchen.o -o kitchen -lpthread

kitchen.o: kitchen.c $(HEADERS)
	gcc -c	kitchen.c -o kitchen.o -lpthread
	
clean:
	-rm -f	kitchen.o
	-rm -f	kitchen