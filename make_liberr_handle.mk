liberr_handle.so: err_handle.*
	gcc -fpic -shared -o liberr_handle.so err_handle.c err_handle.h
