#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <err.h>
#include "buffer.h"


int
main ()
{
	int status;
	char_buffer_t *buf
	 = malloc (sizeof (char_buffer_t));

	printf ("==== #010 Creating buffer with size=1024 ====\n");
	if (create_char_buffer (buf, 1024) != 0)
	{ err (errno, "ERROR: create_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", buf->space_remaining);
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");
	
	while (1)
	{
		printf ("==== #020 Appending 'Hello world.' to buffer  ====\n");
		if (append_to_char_buffer (buf, "Hello world.") != 0)
		{ err (errno, "ERROR: append_to_char_buffer"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	
		printf ("==== #070 Resizing buffer DOWN by 512 ====\n");
		status = resize_char_buffer (buf, -512);
		if (status > 0)
		{ err (errno, "ERROR: resize_char_buffer"); }
		if (status == -1)
		{ printf ("ABORT: resize would lose data (UNexpected).\n"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	
		printf ("==== #080 Appending ' Here is yet another sentence.' to buffer  ====\n");
		if (append_to_char_buffer (buf, " Here is yet another sentence.") != 0)
		{ err (errno, "ERROR: append_to_char_buffer"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	
		printf ("==== #090 Resizing buffer UP by 8192 ====\n");
		status = resize_char_buffer (buf, 8192);
		if (status > 0)
		{ err (errno, "ERROR: resize_char_buffer"); }
		if (status == -1)
		{ printf ("ABORT: resize would lose data (UNexpected).\n"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	
		printf ("==== #100 Appending ' Doodle.' to buffer  ====\n");
		if (append_to_char_buffer (buf, " Doodle.") != 0)
		{ err (errno, "ERROR: append_to_char_buffer"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	
		printf ("==== #110 Clearing the buffer WITH resize to 1024 ====\n");
		if (clear_char_buffer (buf, 1024) != 0)
		{ err (errno, "ERROR: clear_char_buffer"); }
		printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
		printf ("Space remaining: %zu\n", buf->space_remaining);
		printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
		printf ("\n");
	}
	return 0;
}

