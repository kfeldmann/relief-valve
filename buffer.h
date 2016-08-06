/* Public Domain */

#ifndef _BUFFER_H_ /* Brackets this whole file */
#define _BUFFER_H_

typedef struct
char_buffer_struct
{
	char *memory;
	size_t size;
	size_t space_remaining;
	char *ptr; /* append pointer */
}
char_buffer_t;

extern int create_char_buffer (char_buffer_t*, size_t);
extern void destroy_char_buffer (char_buffer_t*);
extern int resize_char_buffer (char_buffer_t*, long);
extern int append_to_char_buffer (char_buffer_t*, char*);
extern int read_fd_into_char_buffer (char_buffer_t*, int);
extern int clear_char_buffer (char_buffer_t*, size_t);
extern size_t get_char_buffer_size (char_buffer_t*);
extern size_t get_char_buffer_space (char_buffer_t*);
extern size_t get_char_buffer_contlen (char_buffer_t*);
extern char * get_char_buffer_read_ptr (char_buffer_t*);

#endif /* _BUFFER_H_ Brackets this whole file */

