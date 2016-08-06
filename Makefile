rv :      io_select.o buffer.o rv.o
	gcc -g -o rv io_select.o buffer.o rv.o
rv.o :    io_select.h buffer.h rv.c
	gcc -g -c rv.c

io_select.o : io_select.h io_select.c
	gcc -g -c io_select.c

buffer.o : buffer.h buffer.c
	gcc -g -c buffer.c

buffer_leak_test : buffer.o buffer_leak_test.o
	gcc -g -o buffer_leak_test buffer.o buffer_leak_test.o
buffer_leak_test.o : buffer.h buffer.c buffer_leak_test.c
	gcc -g -c buffer_leak_test.c

buffer_test : buffer.o buffer_test.o
	gcc -g -o buffer_test buffer.o buffer_test.o
buffer_test.o : buffer.h buffer.c buffer_test.c
	gcc -g -c buffer_test.c

.PHONY : clean
clean:
	rm -f *.o
	rm -f rv
	rm -f buffer_leak_test
	rm -f buffer_test

