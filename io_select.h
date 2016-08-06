/* Public Domain */

#ifndef _IO_SELECT_H_ /* Brackets this whole file */
#define _IO_SELECT_H_

#include "buffer.h"

extern int max_int (int*, int);
extern int read_readable (int*, int, int, char_buffer_t*);
extern int write_writable (int*, int, int, char_buffer_t*);

#endif /* _IO_SELECT_H_ Brackets this whole file */

