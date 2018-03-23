#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv )
{
int ret;
/*判断是否传入文件名*/
if( argc < 2 ){
printf("Usage: access_test FILENAME\n");
return -1;
}
/*检查文件是否存在并具有可执行权限*/
ret = access( argv[1], F_OK | X_OK );
if( ret == -1 ){
perror( "access:" );
}else{
printf("[%s] exist and executable!\n", argv[1]);
}
return 0;
}