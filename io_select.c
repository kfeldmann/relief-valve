/* Public Domain */


#include <sys/select.h>
#include <unistd.h>
#include <limits.h>
#include "buffer.h"
#include "io_select.h"


/**********************************************************************
** max_int (int*, int)
** 
** Find the highest int in a list of ints, with intcount being the
** length of the list.
** 
** Return value: the highest integer from the list. If intcount is
** zero, the return value will be INT_MIN from limits.h.
** 
*/
int
max_int (int *ints, int intcount)
{
	int maxint = INT_MIN;
	int i;
	for (i = 0; i < intcount; i++)
	{
		if (ints[i] > maxint) maxint = ints[i];
	}
	return maxint;
}


/**********************************************************************
** read_readable (int*, int, int, char_buffer_t*)
** 
** Call select() on a list of file descriptors. If any are readable,
** read from each readable descriptor, appending the data to the
** provided char_buffer_t.
** 
** Return value:
**   0 on success
**  -1 if select() fails
**  -3 if no fd's became readable before the timeout
**   value of the bad fd on failure (e.g. if stderr encountered an
**     error, the return value would be 2)
*/
int
read_readable (int *fds, int fdcount, int timeoutsec, char_buffer_t *ls_buffer)
{
	fd_set readfds, errorfds;
	struct timeval timeout;
	int i, readycount;

	FD_ZERO (&readfds);
	FD_ZERO (&errorfds);
	for (i = 0; i < fdcount; i++)
	{
		FD_SET (fds[i], &readfds);
		FD_SET (fds[i], &errorfds);
	}
	timeout.tv_sec = timeoutsec;
	timeout.tv_usec = 0;

	readycount = select (max_int(fds, fdcount) + 1,
	  &readfds, NULL, &errorfds, &timeout);
	if (readycount == -1) return -1;
	if (readycount == 0) return -3;
	if (readycount > 0)
	{
		for (i = 0; i < fdcount; i++)
		{
			if (FD_ISSET (fds[i], &errorfds)) return fds[i];
			if (FD_ISSET (fds[i], &readfds))
			{
				if (read_fd_into_char_buffer (ls_buffer, fds[i]) != 0)
				{ return fds[i]; }
			}
		}
	}
	return 0;
}


/**********************************************************************
** write_writable (int*, int, int, char_buffer_t*)
** 
** Call select() on a list of file descriptors. If any are writable,
** write the contents of the provided char_buffer_t to each writable
** descriptor.
** 
** Return value:
**   0 on success
**  -1 if select() fails
**  -2 if only part of the buffer was written to the descriptor
**  -3 if no fd's became writable before the timeout
**   value of the bad fd on failure (e.g. if stderr encountered an
**     error, the return value would be 2)
*/
int
write_writable (int *fds, int fdcount, int timeoutsec, char_buffer_t *ls_buffer)
{
	fd_set writefds, errorfds;
	struct timeval timeout;
	int i, readycount;
	ssize_t byteswritten;

	FD_ZERO (&writefds);
	FD_ZERO (&errorfds);
	for (i = 0; i < fdcount; i++)
	{
		FD_SET (fds[i], &writefds);
		FD_SET (fds[i], &errorfds);
	}
	timeout.tv_sec = timeoutsec;
	timeout.tv_usec = 0;

	readycount = select (max_int(fds, fdcount) + 1,
	  NULL, &writefds, &errorfds, &timeout);
	if (readycount == -1) return -1;
	if (readycount == 0) return -3;
	if (readycount > 0)
	{
		for (i = 0; i < fdcount; i++)
		{
			if (FD_ISSET (fds[i], &errorfds)) return fds[i];
			if (FD_ISSET (fds[i], &writefds))
			{
				byteswritten = write (fds[i],
				 get_char_buffer_read_ptr (ls_buffer),
				 get_char_buffer_contlen (ls_buffer));
				if (byteswritten == -1) return fds[i];
				if (byteswritten < get_char_buffer_contlen (ls_buffer))
				{ return -2; }
			}
		}
	}
	return 0;
}

