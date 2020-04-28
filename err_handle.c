
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

#include <errno.h>
#include <stdarg.h>
#include <syslog.h>
#include "./err_handle.h"

static void err_doit( int, const char*, va_list );
char *pname=NULL;


//non-fatal error related to system call
void err_ret( const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 1, fmt, ap );
	va_end( ap );
	return ;
}


// fatal error related to system call -- print terminate
void err_sys( const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 1, fmt, ap );
	va_end( ap );
	exit( 1 );
}

// fatal error related to system call -- print dump terminate
void err_dump( const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 1, fmt, ap );
	va_end( ap );
	abort(); // dump core and terminate
	exit(1);
}

// non fatal error relate to a sys call
void err_msg( const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 0, fmt, ap );
	va_end( ap );
	return ;
}

//fatal error unrelated to system call
void err_quit( const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	err_doit( 0, fmt, ap );
	va_end( ap );
	exit(1) ;
}

static void 
err_doit( int errnoflag, const char* fmt, va_list ap)
{
	int errno_save, len=0;
	char buf[MAXLINE];

	errno_save = errno; //已经发生了错误，先保存errno
	len = vsprintf( buf, fmt, ap );
	if ( errnoflag ) 
		len += sprintf( buf+len, ": %s", strerror(errno_save));
	buf[len] = '\n';
	buf[++len] = '\0';

	fflush( stdout ); // 万一stderr和stdout是同一个fd
	fputs( buf, stderr );
	fflush( NULL );
	return ;
}

static void log_doit( int, int ,const char*, va_list );
int apue_debug=0; // 日志函数的调用者必须自己定义debug变量，0表示caller是守护进程，非零说明是前台的交互程序

void log_open( const char *ident, int option, int facility )
{
	if ( apue_debug == 0 ) openlog( ident, option, facility );

}

void log_ret( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	log_doit( 1, LOG_ERR, fmt, ap );
	va_end( ap );
	return ;
}
void log_sys( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	log_doit( 1, LOG_ERR, fmt, ap );
	va_end( ap );
	exit(2);
}
void log_msg( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	log_doit( 0, LOG_ERR, fmt, ap );
	va_end( ap );
	return ;
}
void log_quit( const char* fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	log_doit( 0, LOG_ERR, fmt, ap );
	va_end( ap );
	exit(2);
}

static void 
log_doit( int errnoflag, int priority, const char* fmt, va_list ap)
{
	int errno_save, len=0;
	char buf[MAXLINE];

	errno_save = errno; //已经发生了错误，先保存errno
	len = vsprintf( buf, fmt, ap );
	if ( errnoflag ) 
		len += sprintf( buf+len, ": %s", strerror(errno_save));
	buf[len] = '\n';
	buf[++len] = '\0';
	if ( apue_debug ) {  //debug=0则是守护进程
		fflush( stdout ); // 万一stderr和stdout是同一个fd
		fputs( buf, stderr );
		fflush( NULL );
	}	
	else{
		syslog( priority,"%s", buf );
	}
	return ;
}

