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
	/* printf ("DEBUG: addr of *buf = %p\n", buf); */

	printf ("==== #010 Creating buffer with size=1024 ====\n");
	if (create_char_buffer (buf, 1024) != 0)
	{ err (errno, "ERROR: create_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");
	
	printf ("==== #020 Appending 'Hello world.' to buffer  ====\n");
	if (append_to_char_buffer (buf, "Hello world.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #030 Appending ' Here is another sentence.' to buffer  ====\n");
	if (append_to_char_buffer (buf, " Here is another sentence.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #040 Clearing the buffer without resizing ====\n");
	if (clear_char_buffer (buf, 0) != 0)
	{ err (errno, "ERROR: clear_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #050 Appending 'Hello foobar.' to buffer  ====\n");
	if (append_to_char_buffer (buf, "Hello foobar.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #060 Resizing buffer DOWN by 2048 ====\n");
	status = resize_char_buffer (buf, -2048);
	if (status > 0)
	{ err (errno, "ERROR: resize_char_buffer"); }
	if (status == -1)
	{ printf ("ABORT: resize would lose data (expected result).\n"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #070 Resizing buffer DOWN by 768 ====\n");
	status = resize_char_buffer (buf, -768);
	if (status > 0)
	{ err (errno, "ERROR: resize_char_buffer"); }
	if (status == -1)
	{ printf ("ABORT: resize would lose data (UNexpected).\n"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #080 Resizing buffer UP by 2048 ====\n");
	status = resize_char_buffer (buf, 2048);
	if (status > 0)
	{ err (errno, "ERROR: resize_char_buffer"); }
	if (status == -1)
	{ printf ("ABORT: resize would lose data (UNexpected).\n"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #090 Appending ' Here is yet another sentence.' to buffer  ====\n");
	if (append_to_char_buffer (buf, " Here is yet another sentence.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #100 Appending ' Doodle.' to buffer  ====\n");
	if (append_to_char_buffer (buf, " Doodle.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #110 Clearing the buffer WITH resize to 32 ====\n");
	if (clear_char_buffer (buf, 32) != 0)
	{ err (errno, "ERROR: clear_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #120 Appending 'Start filling the buffer.' to buffer  ====\n");
	if (append_to_char_buffer (buf, "Start filling the buffer.") != 0)
	{ err (errno, "ERROR: append_to_char_buffer"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #130 Appending ' Try to overfill the buffer.' to buffer  ====\n");
	if (append_to_char_buffer (buf, "Try to overfill the buffer.") != 0)
	{ printf ("ERROR: append_to_char_buffer: not enough space (expected).\n"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #140 Appending ' asdfgh' to buffer  ====\n");
	if (append_to_char_buffer (buf, " asdfgh") != 0)
	{ printf ("ERROR: append_to_char_buffer: not enough space.\n"); }
	printf ("Size of buffer: %zu\n", get_char_buffer_size (buf));
	printf ("Space remaining: %zu\n", get_char_buffer_space (buf));
	printf ("Content length: %zu\n", get_char_buffer_contlen (buf));
	printf ("Buffer contains: %s\n", get_char_buffer_read_ptr (buf));
	printf ("\n");

	printf ("==== #150 Destroying the buffer ====\n");
	destroy_char_buffer (buf);

	return 0;
}

// USED
// create_char_buffer       (char_buffer_t *bufptr, size_t size)
// append_to_char_buffer    (char_buffer_t *bufptr, char *message)
// get_char_buffer_read_ptr (char_buffer_t *bufptr)
// clear_char_buffer        (char_buffer_t *bufptr, size_t resize_to) no resize
// get_char_buffer_size     (char_buffer_t *bufptr)
// resize_char_buffer       (char_buffer_t *bufptr, size_t sizedelta) DOWN
// resize_char_buffer       (char_buffer_t *bufptr, size_t sizedelta) UP
// clear_char_buffer        (char_buffer_t *bufptr, size_t resize_to) w/ resize
// get_char_buffer_space    (char_buffer_t *bufptr)
// get_char_buffer_contlen  (char_buffer_t *bufptr)
// destroy_char_buffer      (char_buffer_t *bufptr)

