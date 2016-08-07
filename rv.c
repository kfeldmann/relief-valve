/*
**
** rv: A relief valve for pipelines
** 
** KPF - 2016-08-06
**
** Copyright (c) 2016, Kris Feldmann
** All rights reserved.
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 
**   1. Redistributions of source code must retain the above copyright
**      notice, this list of conditions and the following disclaimer.
** 
**   2. Redistributions in binary form must reproduce the above
**      copyright notice, this list of conditions and the following
**      disclaimer in the documentation and/or other materials provided
**      with the distribution.
** 
**   3. Neither the name of the copyright holder nor the names of its
**      contributors may be used to endorse or promote products derived
**      from this software without specific prior written permission.
** 
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
** PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
** OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <sys/types.h> /* open */
#include <sys/stat.h> /* open */
#include <fcntl.h> /* open */
#include <stdlib.h> /* exit */
#include <unistd.h> /* getpid */
#include <stdio.h> /* stdin, stdout, stderr */
#include <errno.h>
#include <malloc.h>
#include "io_select.h"
#include "buffer.h"

#define BUFFERSIZE 8192
#define MAX_BUFFERSIZE 1048576 /* 1M */
#define SELECT_TIMEOUT_SEC 1

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;



/**********************************************************************
** usage ()
** 
** Print usage statement to STDOUT and exit.
** The value of `appname' should be the `argv[0]' name of
** this executable.
** 
** Causes exit unconditionally.
*/
void
usage (char *appname)
{
    fprintf (stdout,
     "Usage: %s < input_stream > ouput_stream 2> error_stream\n", appname);
    fprintf (stdout,
     "\nData will be read from input and written to output.\n");
    fprintf (stdout,
     "If the output stream blocks, a message will be announced\n");
    fprintf (stdout,
     "to the error stream, which could feed an alerting system.\n");

    exit (EXIT_FAILURE);
}


/**********************************************************************
** main ()
*/
int
main (int argc, char *argv[])
{
    /* BUFFERSIZE - preproc define at the top of this file */
    /* SELECT_TIMEOUT_SEC - preproc define at the top of this file */

    int io_status;
    int fds[1];

    /* log stream buffer */
    char_buffer_t *ls_buffer = malloc (sizeof (char_buffer_t));
    int resize_status;

    if (argc > 1)
    {
        usage(argv[0]);
    }

    if (create_char_buffer (ls_buffer, BUFFERSIZE) != 0)
    {
        exit (errno);
    }

    /* main loop: read from stdin and write to stdout */
    while (1)
    {
        /* shrink stream buffer if needed */
        if (get_char_buffer_space (ls_buffer) >= BUFFERSIZE * 2)
        {
            resize_status = resize_char_buffer (ls_buffer, -1 * BUFFERSIZE);
            if (resize_status > 0)
            {
                exit (errno);
            }
        }

        /* extend stream buffer if needed */
        if (get_char_buffer_space (ls_buffer) <= BUFFERSIZE / 2)
        {
            if (get_char_buffer_size (ls_buffer) + BUFFERSIZE
                <= MAX_BUFFERSIZE)
            {
                resize_status = resize_char_buffer (ls_buffer, BUFFERSIZE);
                if (resize_status > 0)
                {
                    exit (errno);
                }
            }
            else
            {
                fprintf (stderr,
                    "ERROR: rv[%d] Buffer is at max size. Data being lost.\n", getpid());
            }
        }

        /* Read from readable file descriptors */

        fds[0] = fileno(stdin);
        io_status = read_readable (fds, 1, SELECT_TIMEOUT_SEC, ls_buffer);

        /* Write buffer to output if writable */
        fds[0] = fileno(stdout);
        io_status = write_writable (fds, 1, SELECT_TIMEOUT_SEC, ls_buffer);
        if (io_status == -1)
        {
            fprintf (stderr,
                "ERROR: rv[%d] select() failed (errno = %d).\n", getpid(), errno);
        }
        else if (io_status == -3)
        {
            fprintf (stderr,
                "ERROR: rv[%d] stdout is not writable.\n", getpid());
        }
        else
        {
            if (clear_char_buffer (ls_buffer, 0) != 0)
            {
                exit (errno);
            }
        }

    } /* while loop */

    exit (EXIT_SUCCESS);
}

