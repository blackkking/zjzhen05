#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv )
{
int fd_lseek;
char buf[100];
int file_size;
/*判断是否传入文件名*/
if( argc < 2 ){
printf("Usage: lseek_test FILENAME\n");
return -1;
}
/*打开要读取的文件*/
fd_lseek = open( argv[1], O_RDONLY );
if( fd_lseek == -1 ){
perror( "open error" );
return -1;
}
/*/*移动指针到文件尾*/
file_size = lseek( fd_lseek, 0, SEEK_END );
if( file_size >= 0 ){
printf("size of [%s] = %d\n", argv[1], file_size );
}else{
perror( "lseek error" );
}
close( fd_lseek );
return 0;
}