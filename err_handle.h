#ifndef ERR_HANDLE_H
#define ERR_HANDLE_H

#define MAXLINE 4096
void err_dump( const char *, ... );
void err_msg( const char *, ... );
void err_quit( const char *, ... );
void err_ret( const char *, ... );
void err_sys( const char *, ... );

void log_msg( const char *, ... );
void log_ret( const char *, ... );
void log_sys( const char *, ... );
void log_quit( const char *, ... );
void log_open( const char *, int, int );
#endif
