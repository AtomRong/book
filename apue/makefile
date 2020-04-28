cc=gcc
lib_path:=..
header_path:=.
src_path:=$(header_path)/src
obj_path:=$(header_path)/obj

cflags= -ggdb 
ldflags:=-I$(header_path)  -L$(lib_path) -lerr_handle  -Wl,-rpath=`pwd`/$(lib_path)
#链接的时候需要apue书上的错误处理例程,还需要在运行时找到 err_handle.so的位置


#期望的效果：增加一个源文件 x.c, 直接make即可编译出可执行文件x
#通配符得到src目录下的全部c文件
#构造出obj文件的名字,编译输出全部在 obj文件
#
sources:=$(wildcard $(src_path)/*.c )
objects:=$(notdir $(subst .c, ,$(sources)))

all:$(objects)
	@echo  building done

$(objects):$(sources) apue.o -lm   #make 居然会自动检查系统库目录下有木有指定的lib
	@echo building object: $(objects)
	@echo building from src $(sources)
	$(warning  $@)
	-mkdir -p $(obj_path)
	$(cc) -o $(obj_path)/$@ $(cflags) $< apue.o $(ldflags)


apue.o:apue.h apue.c
	$(CC) $(CFLAGS)  -c apue.h apue.c 
	
#gcc -o test ./src/01_2.c  -I./ -L../  -lerr_handle -Wl,-rpath=/home/atom/book_src/apue/..
