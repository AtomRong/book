#ifndef APUE_H
#define APUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../err_handle.h"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH )

typedef void Sigfunc(int); // signal handlers

#define min(a,b)  ((a) < (b)? (a):(b))
#define max(a,b)  ((a) > (b)? (a):(b))

char	*path_alloc( int * );
int		open_max(void);
void	clr_fl( int, int );
void	set_fl( int, int );
void	pr_exit( int );
void	pr_mask( const char * );
Sigfunc	*signal_intr( int, Sigfunc );


#endif
