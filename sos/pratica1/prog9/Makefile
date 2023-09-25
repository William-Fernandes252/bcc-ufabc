CFLAGS: -std=gnu99 -pedantic -Wall -Werror
GDBFLAGS: -g

cons: cons.o producer-consumer.o
	gcc -o cons cons.o producer-consumer.o

cons.o: cons.c producer-consumer.h
	gcc -c cons.c

prod: prod.o producer-consumer.o
	gcc -o prod prod.o producer-consumer.o

prod.o: prod.c producer-consumer.h
	gcc -c prod.c

producer-consumer.o: producer-consumer.c producer-consumer.h
	gcc -c producer-consumer.c

.PHONY: clean
clean:
	rm $@ -f *.o *.c~ *.o~ prod cons