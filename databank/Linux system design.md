[TOC]

# Linux系统程序设计

## 计算机系统概论

操作系统利用一个或多个处理器的硬件资源，为系统用户提供一组服务，它还代表用户来管理辅助存储器和输入/输出(I/O)设备。因此，在开始分析操作系统之前掌握一些底层的计算机系统硬件知识是很重要的。

### 基本构成

从最顶层看，一台计算机由处理器，存储器和输入/输出部件组成，每一个部件有一个或多个模块。这些部件以某种方式互联，以实现计算机执行程序的主要功能。因此，计算机有四个主要的结构化部件：

- 处理器(processor)：控制计算机的操作，执行数据处理功能。当只有一个处理器是，它通常是指中央处理器(CPU)
- 主存储器(main memory): 存储数据和程序。此类存储器通常是易失性的，即当计算机关机时，它的内容不会丢失。主存储通常也称为实存储器(real memory)或主存储器(primary memory)
- 输入/输出模块(I/O modules): 在计算机和外部环境之间移动数据。外部环境由各种外部设备组成，包括二级存储器设备(如硬盘),通信设备和终端。
- 系统总线(System bus):为处理器，主存储器和输入/输出模块间提供通信的设施

### 处理器寄存器

处理器包括一组寄存器，它们提供一定的存储能力，比主存储器访问速度快，但比主存储器的容量小。处理器中的寄存器有两个功能

- 用户可见寄存器：优先使用这些寄存器，可以使机器语言或汇编语言的程序员减少对主存储器的访问次数。对高级语言而言，由优化编译器负责决定哪些变量应该分配给寄存器，哪些变量应该分配给主存储器，一些高级语言允许程序员建议编译器把哪些变量保存在寄存器中
- 控制和状态寄存器：用以控制处理器的操作，且主要被具有特权的操作系统历程使用，以控制程序的执行。


## 基本文件I/O

### 文件与文件访问基本概念

#### Linux文件分类

Linux文件是对大多数系统资源访问的接口。

- 普通文件(regular file)：用户可以看到的文件，有文本文件和二进制文件ls-l 第一个显示的字符是“-”
- 目录文件(directory),管理和组织系统的大量文件。"d"
- 设备文件。Linux把每一个I/O设备都看成一个文件."c" "b"
- 管道文件(named pipe),主要用于在进程传递数据。管道文件又称先进先出(FIFO)文件 "p"
- 套接字文件(socket).类似于管道文件.管道文件用于本地通信。而套接字允许网络上的通信 "s"
- 符号链接文件(stmbolic link),这个文件包含了另一个文件的陆建明。被链接的文件可以是任意文件和目录，可以链接不同文件系统的文件，"l"

#### 文件的相关最基本元素

- 目录结构。系统中的每一个目录都处于一定的目录结构当中。目录结构含有目录中所有目录的列表，每个目录项都含有一个文件名称和一个索引节点，借助于名称，应用程序可以访问目录项的内容，而索引节点提供了文件自身的信息。所以，目录只是将文件的名称和它的索引号结合在一起的一张表，目录中每一对文件名称和索引节点号，却可以有多个文件名与之对应。因此，在磁盘上的同一个文件可以通过不同的路径去访问它。
- 索引节点。目录结构包含文件名称和目录位置等信息，而索引节点本身并不包含这些信息，因此Linux允许使用多个文件名来引用磁盘上的同一块数据，多个文件名都可以访问同一个索引节点。
- 文件的数据。它的存储位置由索引节点指定，有这些特殊文件，比如管道及设备文件。在硬盘上不具有数据区域。而普通文件和目录都拥有数据区域。


#### 文件访问基本概念

​	Linux提供了丰富的文件访问接口，如我们用opendir()等函数后去目录结构信息。通过调用stat()可以从索引节点获得文件信息。通过open(),read()等等访问文件的数据。

​	Linux操作系统中各种类型的文件都采用统一的I/O方法来进行访问。从、因此，从磁盘中读取一个文件中的程序和从网络中读取数据的程序一样简单。

​	对文件执行I/O 操作，有两种基本方式：一种是系统调用的I/O方法，另一种是基于流的I/O方法。

​	系统调用的I/O方法提供了最基本的文件访问接口：open().close().write(),read()和lseek()等。基于流的I/O方法实际上是建立在系统调用的I/O方法基础上的C函数库，它基于系统调用方法的封装并增加了额外的功能。例如采用缓冲技术来提高程序的效率，输入解析以及格式化输出等。然而在处理设备，管道，网络套接字和其他特殊类型的文件的时候，必须使用系统调用I/O方法。

​	系统调用和基于流的区别:

​	1.基于流的文件函数名字都是以字母“f"开头

​	2.系统调用是更低一级的接口，调用需要更多编码的工作

​	3.系统调用直接处理文件描述符，流函数处理“FILE*”类型的文件句柄

​	4.基于流的I/O 方法是对系统调用方法的封装，流I/O 方法使用自动缓冲技术，程序性能会更高

​	5.基于流的方法支持格式化输出，类似于fprintf()这样的函数

​	6.基于流的方法替用户处理有关系统调用的细节，比如系统调用被信号中断的处理等等

​	基于流的方法会给我们带来极大的方便，但某些程序却不能使用流的I/O 方法。比如使用缓冲技术使得网络通信陷入困境，因为它会干扰网络通讯所使用的通信协议，考虑到这两种方法的不同，使用终端或者通过文件交换信息我们一般用流的I/O。而使用网络或管道通信时，通常采用系统调用的I/O方法

#### 文件访问的系统调用的API

```c
//文件的创建，打开和关闭
fd = open("/tmp/open_test",O_CREAT|O_WRONLY|O_TRUNC,0640);
fd = creat("/tmp/open_test",0640);
//原型
int open(const char *pathname, int flags); //失败返回-1
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
int close(int fd);
//保证数据写入磁盘等物理存储设备中
int fsync(int fd);
//文件的读写
ssize_t read(int fd,void *buf,size_t count);
ssize_t write(int fd, const void *buf, size_t count);
//fd:要进行对鞋的文件描述符 buf： 要写入文件内容或读出文件内容的内存地址 count: 要读写的字节数
//lseek()系统调用可以使文件指针移动到文件中的指定位置
off_t lseek(int fd,off_t offset,int whence);
/*fd 文件描述符 offset:移动的偏移量，单位的字节数 whence:文件指针移动偏移量的解释。有三个选项：
SEEK_SET:从文件头开始计算，文件指针移动到offset个字节位置
SEEK_CUR:从文件指针当前位置开始计算，向后移动offset个字节的位置
SEEK_END:文件指针移动到文件结尾
lseek()移动成功，返回为文件指针当前位置 失败返回-1*/
//access()用来判断文件是否有读写等权限
int access(const char *pathname,int mode);
R_OK是否有可读权限  W_OK写权限  X_OK执行  F_OK是否存在
//存在返回0 不存在返回-1

 //修改文件属性
 int fnctl(int fd,int cmd);
 int fnctl(int fd,int cmd,lont arg);
 int fnctl(int fd,int cmd,struct flock *lock);
/*复制一个文件描述符(cmd = F_DUPFD)。
获取/设置文件描述符标志(cmd = F_GETFD 或 cmd = F_SETFD)。
获取/设置文件状态标志(cmd = F_GETFL 或 cmd = F_SETFL)。 获取/设置文件锁(cmd = F_GETLK、 cmd = F_SETLK 或 cmd = F_SETLKW)。*/

```

#### 文件访问的C库函数

```c
//文件创建，打开和关闭
FILE *fopen(const char *path,const char* mode);
// w写 w+读写 r读 r+读写 a追加 a+清空再追加 成功返回文件句柄，失败返回NULL
int fclose(FILE *fp);
//按字符读文件
int fgetc(FILE* stream);
int getc(FILE* stream);
fgetc()用 unsigned char 的格式来读取一个字符并映射为一个 int 值，如果读取正确，返回读取的字符的 int 值；否则，当读取错误或遇到文件结束标志 EOF 时，返回 EOF， EOF在头文件的定义为-1.
//getc 是fgetc的宏定义别名
//按字符写文件
int fputc(int c,FILE* stream);
int putc(int c,FILE* stream);
第一个参数是要写入的字符，成功返回字符的值，失败赶回EOF
//按字符串读文件
char *fgets(char *s, int size, FILE *stream);
fgets()函数从文件中读入一行以“\0”或 EOF 结尾的字符串。 
第一个参数是存放读出来的字符串的地址，第二个参数指定了一次最多读取 n 个字符，第三个参数指定了文件句柄。fgets()函数将从文件偏移指针的当前位置依次读取字符存入字符串指针 s 中。函数读取字符直至 n-1 个字符或遇到换行符或文件结束标志 EOF 为止。
//成功返回s 失败返回NULL
//字符串写入文件
int fputs(const char *s, FILE *stream); 
//成功返回非负数，失败返回EOF
```

```c
//按数据块读写文件
对于非文本文件， 比如二进制文件等， 当需要一次读写一组数据的时候， 我们可以使用 fread()和 fwrite()函数来读写文件。
size_t fread(void *ptr, size_t size， size_t nmemb， FILE *stream);
size_t fwrite(const void *ptr, size_t size， size_t nmemb， FILE *stream);
第一个参数分别是要读写的数据的地址，第二个参数是数据块的大小，第三个参数是要读写的数据块的数目，第四个参数是文件句柄。
//当读写操作成功时，函数返回成功读写的数据块的数量。如果返回的数量小于第三个参数指定的读写数量时，表明发生了错误或者读文件遇到了文件结束符 EOF。这种情况下，fread()无法区分读数据时是出错还是遇到文件结束符，通常可以使用 feof()函数来判断是否读到了文件尾，或者用 ferror()函数来判断是否是读文件出错。

//格式化写入，成功写入返回字符数，错误返回负数
int fprintf(FILE *stream， const char *format， ...);
//格式化输出，成功写入返回字符数，错误返回负数
int fscanf(FILE *stream， const char *format， ...);

//文件的随机存取
int fseek(FILE *stream， long off'set， int whence);
whence：文件指针移动偏移量的解释，有三个选项：SEEK_END，SEEK_CUR，从当前偏移。SEEK_SET，从文件头开始移动
//告诉指针当前位置
long ftell(FILE *stream);
```

## 进程和线程

### 什么是进程

进程的标准定义是：“进程是一个具有独立功能的程序关于某个数据集合的一次可以并发执行的运行活动，是处于活动状态的计算机程序”。 

#### 进程的结构

Linux 是一个多处理操作系统。进程具有独立的权限与职责。如果系统中某个进程崩溃，它不会影响到其余的进程。每个进程运行在其各自的虚拟地址空间中， 进程之间可以通过由内核控制的机制相互通讯。 

#### 进程状态及状态切换

进程在生存周期中的其状态是变化的。下面是 Linux 操作系统的进程的几种常见的状态

- 运行状态，此状态下进程正在运行(即系统的当前进程)或者是准备运行状态(即就绪状态)。在ps命令列出的状态列Stat列中，字母R表示运行状态。 

- 等待状态，进程正在等待事件的发生或者等待某种系统资源。Linux操作系统中的等待进程分为可中断等待和不可中断等待。可中断等待进程可以被信号（signal）中断， ps命令看到的中断中，字母S表示程序处于可中断等待状态。不可中断状态进程不受信号干扰，直到硬件状态改变，通常是处于I/O操作过程中，字母D表示进程处于不可中断等待状态。

- 停止状态，进程被停止，通常是收到了一个控制信号或者正在被跟踪调试。字母T表示进程处于停止状态。 

- 僵尸状态：进程由于某种原因已经终止或结束，但在进程表项中仍有纪录，该纪录可由父进程收集。字母Z表示进程处于僵尸状态.


### 进程编程

```c
#include<sys/types.h>
#include<unistd.h>
pid_t getpid(void); //返回值，调用进程的进程ID
pid_t getppid(void); //返回值，调用进程的父进程ID
uid_t getuid(void); //返回值，调用进程的用户ID
gid_t getgid(void); //返回值，调用进程的组ID
```

#### 派生进程

如果想用进程同时执行多个函数有两种方法：一是使用我们将在下一章介绍的线程；二时从原程序里创建一个全新的进程，就像 init 的做法一样。

调用fork可以创建一个全新的进程。 这个系统调用对当前进程进行复制， 新进程的许多属性与当前进程是相同的。新进程几乎与原进程一模一样，执行是也是相同的代码，但新进程有自己的数据空间、自己的环境和自己的文件描述符。

在父进程中调用 fork 返回的是新子进程的 PID，新进程将继续执行，就像原进程一样，只不过在子进程里调用 fork 将返回“0”。 失败会返回-1。

```c
//派生进程
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char **argv)
{
  pid_t pid;
  printf("Current process's PID = [%d]\n",getpid() );
  pid = fork();
  if( pid == 0 ){
  	printf("This is child process,PID = [%d], my parrent PID = [%d]\n",getpid(),getppid() );  
  }else if( pid != -1 ){
  	printf("This is parent process, PID = [%d]\n",getpid());
  }else{
  	printf("There was an error with forking!\n");
  }
  return 0;
}
//在语句 pid=fork()之前，只有一个进程在执行这段代码，但在这条语句之后，就变成两个进程在执行了，这两个进程的代码部分完全相同，将要执行的下一条语句都是if(pid==0)。
```

####  执行其他程序

我们在派生一个子进程来完成某项工作的时候，经常需要让另外一个程序来完成，函数exec()可以用来执行一个可执行文件来代替当前进程的执行映像。需要注意的是，该调用并没有生成新的进程，而是在原有进程的基础上，替换原有进程的正文，调用前后是同一个进程，进程号PID不变，但执行的程序变了(执行的指令序列改不了)。

```c
#include<unistd.h>
extern char **environ;
int execl(const char *path,const char *arg,„);
int execlp(const char *file,const char *arg,„);
int execle(const char *path,const char *arg,„,char *const envp[]);
int execv(const char *path,char *const argv[]);
int execvp(const char *file,char *const argv[]);
int execve(const char *filename,char *const argv[],char *const envp[]);
```

#### 终止进程及进程返回值

exit()函数的功能是终止发出调用的进程。它的函数原型如下 ：

```c
#include <stdlib.h>
Void exit(int status);
//exit()函数会调用系统调用_exit立即终止发出调用的进程。所有属于该进程的文件描述符都关闭。该进程的所有子进程由进程 1(进程 init)接收，并对该进程的父进程发出一个 SIGCHLD(子进程僵死)的信号。参数 status 作为退出的状态值返回父进程，该值可以通过系统调用 wait()来收集。如果进程是一个控制终端进程，则 SIGHUP 信号将被送往该控制终端的前台进程
```

#### 等待进程

系统调用 wait()的功能是发出调用的进程只要有子进程，就睡眠直到它们中的一个终止。它的函数原型是 ：

```c
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait(int *status)；
pid_t waitpid(pid_t pid， int *status， int options)；
```

```c
#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
extern char **environ;
int main( int argc, char **argv )
{
	int ret;
	pid_t pid;
	pid_t pid_c;
	pid = fork();
	if( pid == 0 ){
		printf("Child PID [%d] will exit with status 0.\n", 		getpid() );
		exit(0);
  	}else if( pid != -1 ){
		pid_c = wait( &ret );
		printf("Child process PID [%d] return [%d].\n", pid_c, ret);
	}else{
		printf("There was an error with forking!\n");
	}
	return 0;
}
//waitpid()函数与调用 wait()的区别是 waitpid()等待由参数 pid 指定的子进程退出。
```

### 什么是线程

在一个程序里的多个执行路线就叫做线程（thread）。更准确的定义是：线程是“一个进程内部的一个控制序列” 。 

弄清楚 fork 系统调用和创建新线程之间的区别非常重要。当进程执行 fork 调用时，将创建出该进程的一份新拷贝。这个新进程将拥有自己的变量和自己的 PID，它的时间调度也是独立的，它的执行（通常）几乎完全独立于父进程。当在进程里创建一个新线程时，新的执行线程将拥有自己的堆栈（因此也就有自己的局部变量），但与它的创建者共享全局变量、文件描述符、信号处理函数和当前目录状态。

#### 线程的优点和缺点

一般而言，线程之间的 切换需要操作系统做的工作要比进程之间的切换少得多，因此多个线程对资源的需求要远小于多个进程。如果一个程序在逻辑上需要有多个执行线程，那么在单处理器系统上把它运行为一个多线程程序才更符合实际情况。 

多线程程序的调试要比对单线程程序的调试困难的多，因为线程之间的交互非常难于控制 

### 线程编程

本节我们主要介绍 Linux 中的 pthread 线程模型的编程。pthread 线程通过 libpthread线程函数库来实现。所以在编译多线程程序的时候，需要链接 libpthread，比如 

```shell
gcc -o pthread_test -lpthread
```

#### 线程的创建和使用

```c
#include <pthread.h>

int pthread_create(pthread_t *tidp,
                   const pthread_attr_t *attr, 
                   void* (*start_routine)(void*),
                   void *arg);
//第一个参数为指向线程标识符的指针， 线程被创建时，这个指针指向的变量中将被写入一个标识符，我们用该标识符来引用新线程。 第二个参数用来设置线程属性，大多数情况下，我们不需要设置线程的属性，那么空指针 NULL 就可以了，第三个参数是线程运行函数的起始地址。 最后一个参数是运行函数的参数。
我们来看第三个参数
void* (*start_routine)(void*)
//上面一行告诉我们必须要传递一个函数地址，该函数以一个指向 void 的指针为参数，返回的也是一个指向 void 的指针。因此，可以传递一个任一类型的参数并返回同一个任一类型的指针。用 fork 调用后，父子进程将在同一位置继续执行下去，只是 fork 调用的返回值是不同的；但对新线程来说，我们必须明确地提供给它一个函数指针，新线程将在这个新位置开始执行。
当创建线程成功时，函数返回 0，若不为 0 则说明创建线程失败，常见的错误返回代码为：
EAGAIN：前者表示系统限制创建新的线程，例如线程数目过多了。
EINVAL：后者表示第二个参数代表的线程属性值非法。
创建线程成功后，新创建的线程则运行参数三和参数四确定的函数
```

```c
//创建线程
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<liunx/unistd.h>
#include<errno.h>

void thread(void)
{
  int i=0;
  for(i=0;i<3;i++)
  {
  	printf("this is a pthread.\n");
    sleep(1);
  }
}

int main(void)
{
  pthread_t pid;
  int i,ret;
  void* result;
  ret = pthread_create( &id,NULL, (void*)thread,NULL);
  if(ret != 0){
  	printf("create pthread error!\n");
    exit(1);
  }
  for(i=0;i<3;i++){
  	printf("this is the main process.\n");
    sleep(1);
  }
  pthread_join(id,&result);
  printf("Child thread return [%d]\n",(int)result);
  return 0;
}  
```

```c
//主线程用于等待线程结束
int pthread_join(pthread_t thread,void **value_ptr)
//第一个参数为被等待的线程标识符，第二个参数为一个用户定义的指针，它可以用来存储被等待线程的返回值。这个函数是一个线程阻塞的函数，调用它的函数将一直等待到被等待的线程结束为止，当函数返回时，被等待线程的资源被收回。 此函数在线程中的作用等价于进程中用来收集子进程信息的 wait 函数
//一个线程的结束有两种途径，一种是和示例 3-10 一样，函数结束了，调用它的线程也就结束了：另一种方式是通过函数 pthread_exit()来实现。它的函数原型为：
void pthread_exit(void *value_ptr)
//函数的参数是函数的返回代码，只要 pthread_join 中的第二个参数 value_ptr 不是NULL，这个值将被传递给主线程。
```

### 线程同步-互斥锁

当我们需要控制对共享资源的存取的时候，可以用一种简单的加锁的方法来控制。我们可以创建一个读/写程序，它们共用一个共享缓冲区，使用互斥锁来控制对缓冲区的存取。 

```c
//这是一个读/写程序，它们公用一个缓冲区，缓冲区只有两个状态：有数据或没有数据，用变量 buffer_has_data 来记录 buffer 的状态。主线程先启动一个子线 程 来 执 行 read_ buffer()函 数 ， 然 后 等 待用户 输 入 ， 如 果 有 用 户 输入 ， 则 调 用write_buffer()函数把数据写入 buffer。 read_buffer()函数中，每秒 1 个循环等待buffer数据。由于用户输入数据的时间是随机的，为了避免读写操作的冲突，在读写数据前对线程进行锁定，读写数据结束后解除锁定
#include <stdio.h>
#include <pthread.h>

char buffer[128];
int buffer_has_data=0;
pthread_mutex_t mutex;

void write_buffer(char *data)
{
	//锁定互斥锁
  	pthread_mutex_lock (&mutex);
  	if(buffer_has_data == 0){
  		sprintf(buffer,"%s",data);
      	buffer_has_data=1;
	}
  	//打开互斥锁
  	pthread_mutex_unlock(&mutex);
}

void read_buffer(void)
{
  while(1){
  	//锁定互斥锁
    pthread_mutex_lock(&mutex);
    if(buffer_has_data == 1){
  		printf("Read buffer,data = [%s]\n",buffer);
      	buffer_has_data=0;
	}
    //打开互斥锁
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
}

int main(int argc,char** argv)
{
  char input[128];
  pthread_t reader;
  //用默认属性初始化一个互斥锁对象
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&reader,NULL,(void*)(read_buffer),NULL);
  while(1){
  	scanf("%s",input);
    write_buffer(input);
  }
  return 0;
}
```

### 线程同步-条件变量

前面我们了解到互斥锁一个明显的缺点是它只有两种状态：锁定和非锁定。 而条件变量通过允许线程阻塞和等待另一个线程发送信号的方法弥补了互斥锁的不足。条件变量通常和互斥锁一起使用。 

条件变量被用来阻塞一个线程，当条件不满足时，线程通常先解开相应的互斥锁进入阻塞状态，等待条件发生变化。一旦其它的某个线程改变了条件变量，它将通知相应的条件变量唤醒一个或多个正被此条件变量阻塞的线程。这些线程将重新锁定互斥锁并重新测试条件是否满足。 

```c
#include<pthread.h>
int pthreadcond_init(pthread_cond_t*restrict cond，
					const pthread_condattr_t*restrict attr)；
//当条件变量不再使用的时候，应当释放，释放一个条件变量
 int pthread_cond_destroy(pthread cond t *cond)；
//当我们需要用一个条件变量来阻塞线程的时候， 调用函数 pthread_cond_wait()。 其函数原型为：
int pthread_cond_wait(pthread_cond_t *restrict cond，
pthread_mutex_t *restrict mutex),
int pthread_cond_timedwait(pthread_cond_t *restrict cond，
pthread_mutex_t *restrict mutex，
const struct timespec *restrict abstime)；
//其中 pthread_cond_timedwait()函数相对于 pthread_cond_wait()函数多了一个时间参数， 当线程被锁定超过 abstime 段时间后， 即使条件变量不满足， 阻塞的线程也会被唤醒。
//函数的第一个参数是条件变量， 第二个参数是线程阻塞的时候要解开的互斥锁。
//线程可以被函数 pthread_cond_signal 和函数 pthread_cond_broadcast 唤醒， 其函数原型是
 int pthread_cond_broadcast(pthread_cond_t *cond)；
int pthread_cond_signal(pthread_cond_t *cond);
//他们用来释放被阻塞在条件变量 cond 上的线程。这两个函数区别在于当有多个线程都被同一个条件变量所阻塞时：
//用pthread_cond_broadcast()函数可以使所有线程都被唤醒。
//用pthread_cond_signal()时哪一个线程被唤醒是由线程的调度策略所决定的。

```

```c
//用条件变量同步线程
#include <stdio.h>
#include <pthread.h>

ch	ar buffer[128];
int buffer_has_data=0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void write_buffer(char *data)
{
  //锁定互斥锁
  pthread_mutex_lock (&mutex);
  if(buffer_has_data == 0){
  	sprintf(buffer,"%s",data);
    buffer_has_data=1;
    //条件改变，唤醒阻塞线程
    pthread_cond_signal(&cond);
  }
  //打开互斥锁
  pthread_mutex_unlock(&mutex);
}

void read_buffer(void)
{
  while(1){
  	//锁定互斥锁
    pthread_mutex_lock(&mutex);
    while(!buffer_has_data){
  		//阻塞线程
      	pthread_cond_wait(&cond,&mutex);
    }
    printf("Read buffer,data = [%s]\n",buffer);
    buffer_has_data=0;
    //打开互斥锁
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
}

int main( int argc,char **argv)
{
  char input[128];
  pthread_t reader;
  //初始化互斥锁对象
  pthread_mutex_init(&mutex,NULL);
  //初始化条件变量
  pthread_cond_init(&cond,NULL);
  pthread_create(&read,NULL,(void*)(read_buffer),NULL);
  while(1){
  	scanf("%s",input);
    write_buffer(input);
  }
  return 0;
}
```

注意：
条件变量只是起阻塞和唤醒线程的作用，具体的判断条件还需用户给出，例如一个变量是否为0等等，这一点我们示例3-13中可以看到。线程被唤醒后，它将重新检查判断条件是否满足，如果还不满足，一般说来线程应该仍阻塞在这里，被等待被下一次唤醒，这个过程通常用while语句实现。

### 线程同步-信号量

信号量从本质上是一个非负整数计数器，通常被用来控制对公共资源的访问。当可用的公共资源增加时，调用函数 sem_post()增加信号量。只有当信号量值大于 0 时，函数sem_wait()才能返回，并将信号量的值减 l，当信号量等于 0 时， sem_wait()将被阻塞直到信号量的值大于 0。函数 sem_trywait()是函数 sem_wait()的非阻塞版本 。

```c
#include<semaphore.h>
int sem_init(sem_t *sem， int pshared， unsigned value)；
//第一个参数 sem 为指向信号量结构的一个指针。第二个参数 pshared 不为 0 时此信号量在进程间共享，否则只能为当前进程的所有线程共享。第三个参数 value 给出了信号量的初始值。
int sem_post(sen_t*sem);
//当有线程阻塞在这个信号量上时，调 用sem_post()函数会使其中的一个线程解除阻塞，被解除阻塞的线程选择机制同样是由线程的调度策略决定的。当另外一个线程被解除后，信号量又会被马上减小到 0
//函数 sem_wait()被用来阻塞当前线程直到信号量 sem 的值大于 0，解除阻塞后将 sem的值减 l，表明公共资源经使用后减少。其函数原型是：
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem)；
//函数 sem_trywait()与函数 sem_wait ()的区别是当信号量的值等于 0 时，sem_trywait()函数不会阻塞当前线程
//当信号量不再使用的时候，要用函数 sem_destroy()用来释放信号量。其函数原型是
int sem_destroy(sem_t *sem)；
```

```c
//下面我们来看一个使用信号置的例子。在这个例子中，我们创建三个线程 a、 b、 C。 但是要求线程按照 c->b->a 的顺序执行。
//使用信号量同步线程
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;

void *thread_a(void *in)
{
  //等待信号量sem1
  sem_wait(&sem1);
  printf("thread_a running\n");
}

void *thread_b(void *in)
{
  //等待信号量sem2
  sem_wait($sem2);
  printf("thread_b running\n");
  //增加信号量sem1,使得thread_a可以执行
  sem_post(&sem1);
}

void *thread_c(void *in)
{
  printf("thread_c running\n");
  //增加信号量sem2，使得thread_b 可以执行
  sem_post(&sem2);
}

int main(int argc,char **argv)
{
  pthread_t a,b,c;
  //增加信号量
  sem_init(&sem1,0,0);
  sem_init(&sem2,0,0);
  //创建线程a,b,c
  pthread_create(&a,NULL,thread_a,(void*)0);
  pthread_create(&b,NULL,thread_b,(void*)0);
  pthread_create(&c,NULL,thread_c,(void*)0);
  
  //等待线程退出
  pthread_join(a,(void **)0);
  pthread_join(b,(void **)0);
  pthread_join(c,(void **)0);
  
  //删除信号量
  sem_destory(&sem1);
  sem_destory(&sem2);
  
  return 0;
}
```

## 进程间的通信

### 信号

#### 什么是信号

信号(signal)机制是 Linux 系统中最为古老的进程之间的通信机制。 Linux 信号也可以称为软中断，是在软件层次上对中断机制的一种模拟。在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。 信号是异步的， 一个进程不必通过任何操作来等待信号的到达，信号是进程间通信机制中唯一的异步通信机制，可以看作是异步通知，通知接收信号的进程发生了什么 

信号事件的发生有两个来源： 

- 硬件来源，比如我们按下了键盘或者其它硬件故障； 
- 软件来源，最常用发送信号的系统函数是 kill()， rise()， alarm()和 setitimer()等函数，软件来源还包括一些非法运算等操作 

#### 进程对信号的响应和处理

进程可以通过三种方式来响应和处理一个信号： 

- 忽略信号，对信号不做任何处理，有两个信号不能忽略，SIGKILL 和SIGSTOP。
- 捕捉信号，当信号发生时，执行用户定义的信号处理函数
- 执行缺省操作，Linux对每种信号都规定了默认操作

```c
//信号的安装函数
#include <signal.h>
void (*signal(int sig,void(*func)(int)))(int);
int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact);
//其中 signal()在可靠信号系统调用的基础上实现，是库函数。它只有两个参数，不支持信号传递信息，主要是用于前 32 种非实时信号的安装。 signal()函数的第一个参数是要安装的信号值，第二个参数是对第一个参数指定的信号的处理，可以下面两个宏：
//SIG_DEF：采用系统默认的方式处理信号，执行缺省操作。
//SIG_IGN：忽略信号
//外，第二个参数也可以是一个函数指针，这个函数是用户自定义的对信号的处理函数。
```

```c
//父进程为了回收已经终止了的子进程，需要调用 wait()函数，但是 wait()函数会阻塞主进程，影响程序流程。子进程终止的时候，都会给父进程发送 SIGCHILD 信号，那么我们可以通过信号安装的方式，来捕捉 SIGCHILD，在收到这个信号的时候调用 wait()函数来回收子进程。
//用signal()捕捉信号
#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

extern char **environ;

//SIGCHLD 捕捉SIGCHLD 信号
void handle_sig_child()
{
  int ret;
  pid_t pid_c;
  
  pid_c = wait(&ret);
  printf("Child process PID [%d] return [%d].\n",pid_c,ret);
}

int main(int argc,char **argv)
{
  pid_t pid;
  //捕捉SIGCHLD 
  signal(SIGCHLD,handle_sig_child);
  pid = fork();
  if(pid == 0){
  	printf("Child PID [%d] will exit with status 0.\n",getpid());
    exit(0);
  }else if(pid != -1){
  	while(1){
  		sleep(1);
	}
  }else{
 		printf("there was an error with forking!\n"); 
 }
  return 0;
}
```

#### 信号的发送

除了内核和超级用户， 并不是每个进程都可以向其他的进程发送信号。一般的进程只能向具有相同 uid 和 gid 的进程发送信号， 或向相同进程组中的其他进程发送信号。常用的发送信号的函数有 kill()、 raise ()、 alarm()、 setitimer()、 abort()等 

```c
//kill()函数可以给指定的进程发送某一个信号， 其函数原型是：
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid， int sig);
```

第一个参数pid的取值意义如下：

- pid>0,给PID为pid的进程发送信号
- pid=0,给同一个进程组的所有进程发送信号
- pid<0且pid!=-1,给进程组ID为-pid的所有进程发送信号
- pid=-1,给除自身之外的PID大于1的进程发送信号

第二个参数是要发送的信号值，当第二个参数为0的时候，实际上不会发送任何信号，通常用于错误检查，以此检查目标进程是否存在或者进程是否具有向目标进程发送信号的权限。

当 kill()函数成功发送一个信号时，函数返回 0，否则返回-1。通过 errno 以及使用perror 可以查看错误信息： 

- EINVAL：没有向目标进程发送信号的权限
- EPERM：目标进程不存在或者进程已经终止，处于僵尸状态
- ESRCH ：目标进程不存在或者进程已经终止，处于僵尸状态

```c
//用kill()函数发送信号
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include <signal.h>

extern char **envirom;

//自定义一个pid_printf,在每行输出前插入进程ID
void pid_printf(char *format,...)
{
  va_list ap;
  va_start(ap,format);
  printf("[%d]:",getpid());
  vprintf(format,ap);
}

//信号处理函数
void signal_handler(int signo)
{
  int ret;
  pid_t pid_c;
  
  switch(signo){
    case SIGCHLD:
      pid_c = wait(&ret);
      pid_printf("Child process PID [%d] return [%d].\n",pid_c,ret);
      break;
    case SIGUSR2:
      pid_printf("Signal SIGUSR2 received\n");
      break;
    default:
      pid_printf("Signal [%d] received\n",signo);
      break;
  }
}

int main(int argc,char** argv)
{
  pid_t pid;
  //捕捉SIGCHLD信号
  signal(SIGCHLD,signal_handler);
  //捕捉SIGUSR2信号
  signal(SIGUSR2,signal_handler);
  
  pid=fork();
  if(pid==0){
  	pid_printf("Child process send signal SIGUSR2 to parent process.\n");
    kill(getpid(),SIGUSR2);
    pid_printf("Child process will exit with status 0.\n");
    exit(0);
  }else if(pid != -1){
 	while(1){
  		sleep(1);
    } 
 }else{
  	pid_printf("There was an error with forking!\n");
 }
  return 0;
}
```

```c
//raise()函数用户给进程本身发送一个信号
#include<signal.h>
int raise(int sig);
```

```c
//alarm()函数是一个简单的定时器，专为SIGALRM信号设计
#include<unistd.h>
unsigned int alarm(unsigned int seconds);
//当设置了second秒后，将给线程发送一个SIGALRM信号，当参数为0时，清楚进程的alarm设置
//调用alarm()函数时，若进程已经有一个未结束的alarm，那么旧的alarm将被删除，并返回旧的alarm的剩余时间，否则返回0
//Setitimer()是功能强大的定时器函数，支持3种类型的定时器，但从本质上，它是和alarm共享同一个进程内的定时器
int setitimer(int which,const struct itimerval *value,struct itimerval *ovalue);
/*setitimer()第一个参数 which 指定定时器类型：
ITIMER_REAL：设定绝对时间，经过指定的时间后，内核将发送SIGALRM 号给本进程。
ITIMER_VIRTUAL：设定程序执行时间，只有程序被调度执行的时候才记录时间，经过指定的时间后，内核将发送 SIGVTALRM 信号给本进程。
ITIMER_PROF：设定进程执行以及内核因本进程而消耗的时间和，经过指定的时间后，内核将发送 ITIMER_VIRTUAL 信号给本进程。
第二个参数是结构 itimerval 的一个实例，详细结构可以查看setitimer()函数的 man手册页。 setitimer()调用成功返回 0，否则返回-1。*/
```

abort()向进程发送 SIGABORT 信号，默认情况下进程会异常退出，当然可定义自己的信号处理函数，通常可以用于做程序退出前的统一操作和处理。 

### 管道/FIFO

#### 什么是管道

管道是针对于本地计算机的两个进程之间的通信而设计的通信方法，管道建立后，实际获得两个文件描述符：一个用于读取而另外一个用于写入。任何从管道写入端写入的数据，可以从管道读取端读出。管道通信具有以下的特点： 

- 管道是半双工的，数据只能向一个方向流动，需要双方通信时，需要建立起两个管道。
- 只能用于父子进程或者兄弟进程之间(具有亲缘关系的进程)
- 单独构成一个独立的文件系统：管道对于管道两端的进程而言，就是一个文件，但它不是普通的文件，它不属于某种文件系统，而是单独构成一种文件系统，并且只存在于内存中
- 数据的读出和写入：一个进程向管道中写的内容被管道另一端的进程读出。写入的内容每次都添加在管道缓冲区的末尾，并且每次都是从缓冲区的头部读出数据

管道应用的一个重大限制是它没有名字， 因此，只能用于具有亲缘关系的进程间通信，在有名管道(也称 named pipe 或 FIFO)提出后，该限制得到了克服。 FIF0 不同于管道之处在于它提供一个路径名与之关联，以 FIF0 的文件形式存在于文件系统中。

#### 管道的创建和读写

```c
//系统调用pipe()用于创建一个管道，其函数原型如下：
#include<unistd.h>
int pipe(int filedes[2]);
//pipe()将建立一对文件描述符，然后放在函数参数的二元数组中。第一个文件描述符用于从管道读出数据，第二个文件描述符用于文件写入数据，当pipe()建立管道之后，必须要用fork()派生子进程，然后子进程和父进程分别关闭一个文件描述符。例如子进程要读取，父进程要写入，那么子进程应该关闭管道写入端，父进程关闭取端。
```

```c
//父进程创建一个管道，然后派生子进程，父进程获取用户终端输入，然后通过管道传送给子进程，子进程收到数据。遇到回车符时，在终端输出数据。
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//自定义一个pid_printf 在每行输出前插入进程ID
void pid_printf(char *format,...)
{
  va_list ap;
  va_start(ap,format);
  printf("[%d]:",getpid());
  vprintf(format,ap);
}

//Child write data to pipe
void child_process(int pfd[2])
{
  char buf[256];
  //close unused read fd
  close(pfd[0]);
  pid_printf("Child process is read.\n");
  pid_printf("Enter message(Ctrl + D to exit):");
  fflush(stdout);
  while(fgets(buf,sizeof(buf),stdin) != NULL){
  	pid_printf("Transmitting message: %s",buf);
    write(pfd[1],buf,strlen(buf));
  }
  pid_printf("Child process exiting.\n");
  close(pfd[1]);
  _exit(EXIT_SUCCESS);
}

//Parent read data from pipe
void parent_process(int pfd[2])
{
  char buf[256]={0};
  int count;
  int status;
  
  //Close unused write fd
  close(pfd[1]);
  
  pid_printf("Parent process is ready.\n");
  while(1){
  	count = 0;
    while(count<(sizeof(buf)-1)){
  		status=read(pfd[0],buf+count,1);
      	if(status < 1){
  			pid_printf("read EOF,parent exiting\n");
          	close(pfd[0]);
          	return;
		}
      	if(buf[count] == '\n'){
  			break;
		}
      	count++;
	}
    pid_printf("Receive message:%s",buf);
  }
  pid_printf("No more data,parent exiting.\n");
  close(pfd[0]);
}

int main(int argc,char **argv)
{
  int pfd[2];
  pid_t pid;
  if(pipe(pfd)==-1){
  	perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if(pid == 0){
  	child_process(pfd);
  }else if(pid != -1){
  	parent_process(pfd);
    wait(NULL);
    exit(EXIT_SUCCESS);
  }else{
  	perror("fork");
    exit(EXIT_FAILURE);
  }
}
```

### 命名管道FIFO

FIF0 是 First in First out(先进先出)的所写， FIF0 也称为“命名管道” 。 FIF0 是一种特殊类型的管道， 它在文件系统中有一个相应的文件， 称为管道文件， 这个我们在介绍Linux 文件类型的时候已经介绍过了。 FIFO 文件可以通过 mkfifo()函数创建。在 FIFO 文件创建之后，任何一个具有适当权限的进程都可以打开 FIFO 文件，从文件描述符中读取由其他打开这个 FIFO 文件的进程写入的数据。 

```c
#include<sys/types.h>
#include<sys/stat.h>
int mkfifo(const char *pathname,mode_t mode);
//第一个参数是一个FIFO文件的路径名。第二个参数与打开普通文件的open()函数中的mode参数相同。如果 mkfifo()的第一个参数是一个已经存在文件时，会返回 EEXIST错误，所以一般典型的调用代码首先会检查是否返回该错误，如果确实返回该错误，那么只要调用 I/0 函数对 FIF0 进行操作就可以了。
//当程序使用FIFO结束后，需要删除FIFO文件，可以用unlink()函数删除FIFO文件
```

```c
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define FIFO_PATH "/tmp/fifo_test"

void pid_printf(char *format,...)
{
  va_list ap;
  va_start(ap,format);
  printf("[%d]:",getpid());
  vprintf(format,ap);
}
void server()
{
  char buf[256];
  int fd;
  int count,status;
  //create a fifo
  if(mkfifo(FIFO_PATH,0600)){
  	perror("mkfifo");
  }
  pid_printf("the server is listening on /tmp/fifo_test.\n");
  //open with block mode,block until someone else connects to write
  fd=open(FIFO_PATH,O_RDONLY);
  pid_printf("client has connected.\n");
  //read data from FIFO
    while(1){
  		count=0;
      	while(count<(sizeof(buf)-1))
        {
  			status=read(fd,buf+count,1);
          	if(status<1){
  				pid_printf("read EOF,parent exiting\n");
              	goto parent_exit;
			}
          	if(buf[count] == '\n'){
  				break;
			}
          	count++;
		}
      	pid_printf("Receive message:%s",buf);
	}
  parent_exit:
  	close(fd);
  	unlink(FIFO_PATH);
}

void client(char **argv)
{
	int fd;
  	char buf[256];
  	
  	//open FIFO for write
  	fd = open(argv[1],O_WRONLY);
  	pid_printf("the client is ready,Enter message(Ctrl+D to exit).\n");
  	while(fgets(buf,sizeof(buf),stdin) != NULL){
  		write(fd,buf,strlen(buf));
	}
  	pid_printf("Client exiting.\n");
  	close(fd);	
}

int main(int argc,char **argv)
{
  	if(argc<2){
  		server();
	}else{
  		client(argv);
	}
}
```

### 信号量

在 UNIX 的 System V 版本， AT&T 引进了一种新形式的 IPC 功能(信号量、消息队列以及共享内存)。 Linux 继承了 IPC (Interprocess Communication )机制， 下面我们将分别介绍信号量、消息队列和共享内存。 

#### IPC(Interprocess Communication ) 标识符和关键字 

System IPC 中,对于每一个新建的信号量、消息队列以及共享内存，都有一个在整个系统中唯一的标识符。每个标识也都有唯一对应的关键字，关键字的数据类型由系统定义为key_t 。

在终端输入命令"ipcs",可以看到目前系统中所有的IPC信息

```c
#include<sys/types.h>
#include<sys/ipc.h>
key_t ftok(const char *pathname, int proj_id);
/*ftok()函数返回一个以 pathname 指向的文件相对应的文件和 proj_id 来确定一个 IPC关键字 ket_t。 pathname 必须是一个已经存在并具有访问权限的文件， proj_d 只有最低的 8个字节是有效的，所以通常用一个 ASCII 字符来作为 proj_id。当 pathname 和 proj_id 完全相同时，每次调用 ftok()都会获取一个相同的键值。
IPC 关键字可以由 ftok()函数获得，也可以设为 IPC_PRIVATE。这时操作系统会确保创建一个新的 IPC，其标识符需要由进程自己记录并告诉其他进程。*/
```

#### 创建或获取信号量

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int semget(key_t key,int nsems,int semflg);
/*第一个参数是信号量键值，第二个参数是信号量的数目，第三个参数是一些标志。这些标志包括：
 IPC_CREAT:如果key指定的信号量不存在，创建
 IPC_EXCL:和IPC_CREAT一起用，如果存在，返回错误
 semget()调用成功时，返回对应的信号量集标识符，错误返回-1*/
```

#### 信号量操作

当进程需要申请或者释放公共资源的时候，可以调用 semop()来对信号量进行操作， 其函数原型是：

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int semop(int semid, struct sembuf *sops, unsigned nsops);
```

参数 semid 是信号量 ID，第二个参数 sops 指向一个 sembuf 结构的数组，每一个 sembuf结构都定义了在对信号量的操作，第三个参数 nsops 为 sops 指向数组的大小。 

```c
struct sembuf{
  unsigned short sem_num;	//信号量在信号量集中的索引号
  short          sem_op;	//对信号量的操作
  short 		 sem_flg; // 操作标志位
};
```

sem_num对应信号集中的信号量的索引号，0对应第一个信号量，1对应第二个信号量，以此类推。

sem_op是一个指定了操作类型的整数，如果sem_op的一个正整数，则这个值会立刻被加到信号量的值上。如果sem_op为负，则将从信号量值中减去它的绝对值。如果这将使信号量的值小于零，则这个操作会导致进程阻塞，直到信号量的值至少等于操作值的绝对值(由其它进程增加它的值)。如果sem_op为0，这个操作会导致进程阻塞，直到信号量的值为零才恢复。

sem_flg是一个符号位。指定IPC_NOWAIT以防止操作阻塞；如果该操作本应阻塞，则semop调用会失败。如果sem_flg指定SEM_UNDO,Linux会在进程退出的时候自动撤销该次操作。semop()调用成功时返回0，否则返回-1。

semtimeop()的功能和semop()基本一样，只是增加了一个时间限制，其函数原型如下:

```c
int semtimedop(int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout);
//如果信号量操作时进程被阻塞，那么经过 timeout 时间后，还是没有可用资源，那么函数会立即返回。
```

#### 信号量控制

semctl()系统调用用于对信号量的各种控制操作，其函数原型为： 

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int semctl(int semid, int semnum, int cmd,...);
//第一个参数 semid 指定信号量集， 第二个参数 semnum 指定了对信号量集里面的哪一个信号量进行操作， 第三个参数 cmd 指定具体的操作类型 ，失败返回-1
```

semctl各种操作 

|   Cmd    |                    操作                    |
| :------: | :--------------------------------------: |
| IPC_STAT |   获取信号量信息，信息由arg.buf返回，记录在semid_ds结构体    |
| IPC_SET  |        设置信号量信息，待设置信息保存在arg.buf中。         |
| IPC_RMID |                 立即删除信号量集                 |
| IPC_INFO | 获取信号量集信息，由arg.buf返回，记录在一个struct seminfo结构 |
| SEM_INFO |  返回和IPC_INF0一样seminfo结构体，只是部分字段的含义有所区别。  |
| SEM_STAT | 返回和IPC_STAT一样的semid_ds结构体，只足部分字段含义有所区别。  |
|  GETALL  |  返回所有信号量的值，结果保存在arg.array中，参数sennum被忽略。  |
| GETNCNT  | 返回等待semnum所代表信号量的值增加的进程数，相当于目前有多少进程在等待semnum代表的信号量所代表的共享资源。 |
|  GETPID  |    返回最后一个对semnum所代表信号量执行semop操作的进程ID。    |
|  GETVAL  | 返回semnum所代表信号量的值； GETZCNT返回等待semnum所代表信号量的值变成0的进程数 |
| CETZCNT  |       返回等待semnum锁代表的信号量值成为0的进程数目。        |
|  SETALL  | 通过arg.array更新所有信号量的值；同时，更新与本信号集相关的semid_ds结构的sem_ctime成员。 |
|  SETVAL  |        设置semnum所代表信号量的值为arg.val。         |

```c
//信号量综合示例
//首先来实现两个函数，用于请求和释放信号量，每个进程只能请求一次，所以我们定义了一个全局变量 semheld 来记录请求次数，当 semheld 大于 0 时不再增加信号量，当 semheld小于 1 时，不再释放信号量

void sem_release(int id)
{
  struct sembuf sb;
  if(semheld<1){
  	pid_printf("i dont have any reources;nothing to release\n");
    return;
  }
  sb.sem_num=0;
  sb.sem_op=1;
  sb.sem_flg = SEM_UNDO;
  if(semop(id,&sb,1) == -1){
  	pid_printf("semop release error: %s\n",strerror(errno));
    exit(-1);
  }
  semheld--;
  pid_printf("Resource released.\n");
}

//请求信号量
void sem_request(int id)
{
  struct sembuf sb;
  if(semheld>0){
  	pid_printf("I already hold the resource;not requesting another one.\n");
    return;
  }
  sb.sem_num=0;
  sb.sem_op=-1;
  sb.sem_flg=SEM_UNDO;
  pid_printf("Requesting resource ...");
  fflush(stdout);
  
  if(semop(id,&sb,1)==1){
  	pid_printf("Semop request error: %s\n",strerror(errno));
    exit(-1);
  }
  semheld++;
  printf("Done.\n");
}
```

sem_delete()函数用于创建信号量的进程退出时，立即删除信号量集：

```c
void sem_delete(void)
{
  printf("Master exiting;delete semaphore.\n");
  if(semctl(id,0,IPC_RMID,0) == -1){
  	pid_printf("Error releasing semaphone.\n");
  }
}
```

下面是主函数，如果程序没有传入参数，那么程序将创建一个新的信号量集。如果程序传入了一个参数，这个参数应该是一个已经存在的信号量集 ID，那么程序直接使用这个信号量集 ID。当进程创建了新的信号量集的时候，调用了 atexit(&sem_delete)函数，使得程序退出时，信号量集被释放 。

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<sys/shm.h>

#if defined(_GUN_LIBRARY_)&&!defined(_SEM_SEMUN_UNDEFINED)

#else
union semun{
  int val;/*Value for SETVAL*/
  struct semid_ds *bur; /*Buffer for IPC_STAT,IPC_SET*/
  unsigned short *array; /*Array for GETALL,SETALL*/
  struct seminfo *__but; /*Buffer for IPC_INFO(Linux specific)*/
};
#endif

int semheld = 0;
int master = 0;
int id = 0;

void pid_printf(char *format,...)
{
  va_list ap;
  va_start(ap,format);
  printf("[%d]:",getpid());
  vprintf(format,ap);
}

int main(int argc,char **argv)
{
  union semun sunion;
  if(argc<2){
  	id = semget(IPC_PRIVATE,1,SHM_R | SHM_W);
    if(id != -1){
  		atexit(&sem_delete);
      	sunion.val=1;
      	if(semctl(id,0,SETVAL,sunion) ==1){
  			pid_printf("semctl failed: %s\n",strerror(errno));
			exit(-1);
		}
	}
    master=1;
  }else{
  	id = atoi(argv[1]);
    pid_printf("Using existing semaphore %d.\n",id);
	}
  if(id==-1){
  	pid_printf("Semaphore request failed: %s.\n", strerror(errno));
	return 0;
  }
  pid_printf("Successfully allocated semaphore id %d.\n",id);
  while(1){
	int action;
	printf("\nStatus: %d request held by this process.\n", 	semheld);
	printf("Please select:\n");
	printf("1. Release a resource\n");
	printf("2. Request a resource\n");
	printf("3. Exit this process\n");
	printf("Your choice:");
	scanf("%d",&action);
	switch(action){
		case 1:
		sem_release(id);
		break;
		case 2:
		sem_request(id);
		break;
		case 3:
		exit(0);
		break;
	}
  }
  return 0;
}
```

### 消息队列

#### 什么是消息队列

消息队列是系统内核地址空间中的一个内部的链表。消息可以按照顺序发送到队列中，也可以以几种不同的方式从队列中读取。每一个消息队列用一个唯一的IPC标识符表示。

```c
struct msgbuf{
  long mtype;		//type of message,must>0
  char mtext[1];  //message text
}
//mtext可以是任意类型，也可以是几个字段组成
//在 Linux 系统中，消息的最大的长度是 4056 个字节，其中包括 mtype，它占用 4个字节的长度。
```

#### 创建消息队列

```c
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int msgget(key_t key, int msgflg);
//系统调用 msgget()中的第一个参数是消息队列关键字值，可以由上一节我们介绍过的ftok()获得。第二个参数 msgflg 是一些标志，包括：IPC_CREAT：如果内核中没有此队列，则创建它。
//IPC_EXCL：当和 IPC_CREAT 一起使用时，如果队列已经存在，则返回错误。

```

当 msgget()执行成功时，返回消息队列的标识符， 否则返回-1，通过 errno 和 perror()函数可以查看错误信息 

```c
//创建一个消息队列
int open_queue(key_t keyval)
{
int qid;
if((qid = msgget(keyval， IPC_CREAT|0660)) == -1){
perror(”msgget”);
return(-1);
｝
return(qid);
｝
```

#### 发送和接受消息

```c
int msgsnd(int msqid,struct msgbuf *msgp,size_t msgsz,int msgflg);
/*第一个参数是消息队列标识符。第二个参数 msgp，是指向消息缓冲区的指针。参数 msgsz指定了消息的字节大小，但不包括消息类型的长度(4 个字节)。 参数 msgflg 可以设置为：
 0：此时为忽略此参数，如果消息队列已满，调用进程将会挂起， 直到消息可以写入到队列中。
IPC_NOWAIT：如果消息队列己满，那么此消息则不会写入到消息队列中， 控制将返回到调用进程中。消息队列写入成功时，函数返回 0，否则返回-1。*/
ssize_t msgrcv(int msqid, struct msgbuf *msgp, size_t msgsz, long msgtype, int msgflg);
/*第四个参数是要从消息队列中读取的消息的类型。
如果 msgtype=0,接收消息队列的第一个消息。 大于 0 接收队列中消息类型等于这个值的第一个消息。小于 0 接收消息队列中小于或者等于 msgtype 绝对值的所有消息中的最小一个消息。 一般为 0*/
/*第五个参数 msgflg 取值为：
 0：从队列中取出最长时间的一条消息。
 IPC_NOWAIT：当队列没有消息时，调用会立即返回 ENOMSG 错误。否则，调用进程将会挂起，直到队列中的一条消息满足 msgrcv()的参数要求。当函数成功时，返回写入缓冲区的数据大小，否则返回-1。*/

```

#### 消息队列的控制

消息队列标识符的属性被记录在一个 msgid_ds 结构体： 

```c
struct msqid_ds{
  struct ipc_perm msg_perm; /*所有者和权限*/
  time_t msg_stime; /*最后一次向队列发送消息的时间*/
  time_t msg_rtime; /*最后一次从队列接收消息的时间*/
  time_t msg_ctime; /*队列最后一次改动的时问*/
  unsigned long __msg_cbytes; /*当前队列所有消息的总长度*/
  msgqnum_t msg_qnum; /*当前队列中的消息数量*/
  msglen_t msg_qbytes; /*消息队列的最大消息总长度*/
  pid_t msg_lspid; /*最一次给队列发送消息的进程PID*/
  pid_t msg_lrpid; /*最后一次从队列接收消息的进程PID*/
}
```

```c
int msgctl(int msqid, int cmd, struct msqid ds *buf);
/*第一个参数是消息队列的标识符，第二个参数 cmd 指定了操作， 下面是几个常用的操作：
IPC_STAT：读取消息队列的数据结构 msqid_ds，并将其存储在 buf 指定的地址中。
IPC_SET：设置消息队列的数据结构 msqid_ds 中的 ipc_perm、 msg_qbytes、 msg_ctime元素的值。这个值取自 buf 参数。
IPC_RMID：从系统内核中移走消息队列*/
```

```c
//删除消息队列
int remove_queue(int qid){
	if(msgctl(qid, IPC_RMID, 0)==-1){
		perror(”msgctl”);
		return(-1);
	｝
	return(O);
｝
```

#### 综合示例msgtool

实现一个简单的消息队列工具，用于创建消息队列、发送、读取消息、改变权限以及删除消息队列。 

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE 80
struct mymsgbuf{
  long mtype;
  char mtext[MAX_SEND_SIZE];
};

void send_message(int qid, struct mymsgbuf *qbuf, long type, char *text);
void read_message(int qid, struct mymsgbuf *qbuf, long type);
void remove_queue(int qid);
void change_queue_mode(int qid, char *mode);
void usage(void);

int main(int argc,char** argv)
{
  key_t key;
  int msgqueue_id;
  struct mymsgbuf qbuf;
  if(argc==1)
    usage();
  //Create unique key via call to ftok()
  key = ftok(".",'m');
  //open the queue - create if necessary
  if((msgqueue_id = msgget(key, IPC_CREAT|0660)) == -1) {
	perror("msgget");
	exit(1);
  }
  printf("message queue id = [%d]\n",msgqueue_id);
  switch(tolower(argv[1][0]))//tolower,把字符转化成小写
  {
    case 's':
    	if(argc<4){
  			usage();
          	break;
		}
      	send_message(msgqueue_id,(struct mymsgbuf *)&qbuf,atol(argv[2]),argv[3]);
      	break;
    case 'r':
        if(argc<3){
  		   usage();
           break;
	    }
        read_message(msgqueue_id,&qbuf,argv[2]);
    case 'd':
      	remove_queue(msgqueue_id);
      	break;
    case 'm':
      	if(argc<3){
  			usage();
          	break;
		}
      	change_queue_mode(msgqueue_id,argv[2]);
      	break;
    default: usage();
  }
  return(0);
}
void send_message(int qid,struct mymsgbuf* qbuf,long type,char *text)
{
  //send a message to the queue
  printf("Sending a message...\n");
  qbuf->mtype = type;
  strcpy(qbuf->mtext,text);
  if((msgsend(qid,(struct msgbuf *)qbuf,strlen(qbuf->mtext)+1,0))==-1)
  {
  	perror("msgsnd");
	exit(1);
  }
}

void read_message(int qid, struct mymsgbuf *qbuf, long type)
{
	/* Read a message from the queue */
	printf("Reading a message ...\n");
	qbuf->mtype = type;
	msgrcv(qid, (struct msgbuf *)qbuf, MAX_SEND_SIZE, type, 0);
	printf("Type: %ld Text: %s\n", qbuf->mtype, qbuf->mtext);
}	

void remove_queue(int qid)
{
  //remove the queue
  msgctl(qid,IPC_RMID,0);
}

void change_queue_mode(int qid,char *mode)
{
  struct msqid_ds myqueue_ds;
  //get current info
  msgctl(qid,IPC_STAT,&myqueue_ds);
  /* Convert and load the mode */
  sscanf(mode, "%o", &myqueue_ds.msg_perm.mode);
  /* Update the mode */
  msgctl(qid, IPC_SET, &myqueue_ds);
}

void usage(void)
{
	fprintf(stderr, "msgtool - A utility for tinkering with msg queues\n");
	fprintf(stderr, "USAGE: msgtool (s)end <type> <messagetext>\n");
	fprintf(stderr, " (r)ecv <type>\n");
	fprintf(stderr, " (d)elete\n");
	fprintf(stderr, " (m)ode <octal mode>\n");
	exit(1);
}	
```

### 共享内存

共享内存可以说是最有用的进程间通信方式，也是最快的IPC形式，两个不同进程A，B共享内存的基本原理是，同一块物理内存被映射到进程A,B 各自的进程地址空间。进程A可以即时看到进程B对共享内存中数据的更新，反之亦然。由于多个进程共享同一块内存区域，必然需要某种同步机制，互斥锁和信号量都可以

#### 创建和获取共享内存

```c
#include<sys/ipc.h>
#include<sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
```

#### 连接共享内存

```c
//系统调用 shmat()可以获取一个共享内存的地址并将其连接到进程中
void *shmat(int shmid, const void *shnaddr, int shmflg);
/*第一个参数是共享内存标识符。第二个参数 shmaddr 和 shmflg 相关联：
 如果 shmaddr 为 0，则共享内存连接到由内核选择的第一个可用的地址上。
 如果 shmaddr 为非 0，并且 shmflg 没有指定 SHM_RND，则共享内存被连接到shmaddr 指定的地址上
 如果 shmaddr 为非 0，并且 shmflg 指定了 SHM_RND，则共享内存被连接到 shmaddr 指定的地址向下取最近一个 SHMLBA 的地址倍数的地址
 如果 shmflg 指定了 SHM_RDONLY，则以只读方式连接此共享内存，否则以读写方式连接。shmget()成功地连接地址时，返回该段所连接地实际地址，如果出错则返回-1*/
```

当一个进程不在需要共享的内存时，用 shmdt()系统调用把共享内存从其地址空间中脱接，但这不等于将共享内存段从系统内核中删除。 

```c
int shmdt(const void* shmaddr);
//参数 shmaddr 是调用 shmat()函数连接共享内存时获取的地址。当共享内存脱接成功时返回 0，否则返回-1。
```

#### 共享内存的控制

```c
//共享内存标识符的属性被记录在一个 shmid_ds 结构里：
struct shmid—ds{
	struct ipc_perm shm_perm; /*所有者和权限*/
	size_t shm_segsz; /*共享内存的的字节大小*/
	time_t shm_amime; /*最后一个进程连接共享内存的时间*/
	time_t shm_dtime; /*最后一个进程脱连共享内存的时间*/
	time_t shm_ctime; /*共享内存最后被修改的时间*/
	pid_t shm_cpid; /*创建共享内存的进程PID*/
	pid_t shm_lpid; /*最后一个连接或脱连的进程PID*/
	shmatt_t shm_nattch; /*当前连接到共享内存的进程总数*/
...
}
```

```c
int shmct(int shmid, ind cmd, struct shmid_ds *buf);
/*第一个参数是共享内存的标识符，第二个参数 cmd 指定了其操作，下面是几个常用的操作：
IPC_STAT： 读取一个共享内存的数据结构 shmid_ds，并将其存储在 buf 指定的地址中。
IPC_SET：设置消息队列的数据结构 shmid_ds 中各个元素的值。这个值取自 buf 参数。
IPC_RMID：把共亨内存标记为可删除，当最后一个进程脱连此共享内存的时候，系统将删除该共享内存。*/
```

#### 综合示例 shmtool

一个简单的共享内存操作工具，用于创建共享内存、写读共亨内存、改变权限以及删除共享内存。在读写操作的时候，如果已经共享内心已经存在，直接进行连接并读写，否则先创建一个共享内存

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SEGSIZE 100
void writeshm(int shmid, char *segptr, char *text)
{
	strcpy(segptr, text);
	printf("Done...\n");
}
void readshm(int shmid, char *segptr)
{
	printf("segptr: %s\n", segptr);
}
	void removeshm(int shmid) {
	shmctl(shmid, IPC_RMID, 0);
	printf("Shared memory segment marked for deletion\n");
}
void changemode(int shmid, char *mode)
{
    struct shmid_ds myshmds;
    /* Get current values for internal data structure */
    shmctl(shmid, IPC_STAT, &myshmds);
    /* Display old permissions */
    printf("Old permissions were: %o\n", myshmds.shm_perm.mode);
    /* Convert and load the mode */	
    sscanf(mode, "%o", &myshmds.shm_perm.mode);
    /* Update the mode */
    shmctl(shmid, IPC_SET, &myshmds);
    printf("New permissions are : %o\n", myshmds.shm_perm.mode);
}
void usage() {
	fprintf(stderr, "shmtool - A utility for tinkering with shared memory\n");
	fprintf(stderr, "USAGE: shmtool (w)rite <text>\n");
	fprintf(stderr, " (r)ead\n");
	fprintf(stderr, " (d)elete\n");
	fprintf(stderr, " (m)ode change <octal mode>\n");
	exit(1);	
}

int main(int argc,char **argv)
{
  key_t key;
  int shmid,cntr;
  char *segptr;
  
  if(argc == 1)
    usage();
  //create unique key via call to ftok()
  key = ftok(".",'S');
  
  //open the shared memory segment -create if necessary
  if((shmid = shmget(key,SEGSIZE,IPC_CREAT|IPC_EXCL|0666)) == -1){
  		printf("Shared memory segment exists -opening as client\n");
    	/* Segment probably already exists - try as a client */
		if((shmid = shmget(key, SEGSIZE, 0)) == -1) {
			perror("shmget");
			exit(1);
		}
  }else{
  	printf("Creating new shared memory segment id = %d\n",shmid);
  }
  /* Attach (map) the shared memory segment into the current process */
  if( ( segptr = ( char * )shmat(shmid, NULL, 0) ) == (void * )-1) {
		perror("shmat");
		exit(1);
  }
  switch(tolower(argv[1][0])){
  	case 'w':
  		writeshm(shmid, segptr, argv[2]);
  		break;
  	case 'r':
  		readshm(shmid, segptr);
  		break;
  	case 'd':
  		removeshm(shmid);
  		break;
  	case 'm':
  		changemode(shmid, argv[2]);
  		break;
  	default:
 	 usage();
  }
	return 0;
}
```

## 网络基础

### 网络分层模型

#### TCP/IP模型

TCP/IP( 通 常 它 是 指 传 输 控 制 协 议 / 网 际 协 议 ， Transmission Control Protocol/Internet Protocol)是发展至今最成功的通信协议，它被用于当今所构筑的最大的开放式网络系统 Internet 之上就是其成功的证明 。

TCP/IP 分不同层次进行开发，每一层分别负责不同的通信功能。 一个协议族，比如TCP/IP，是一组不同层次上的多个协议的组合。 TCP/IP 通常被认为是一个四层协议系统，每一层负责不同的功能：

- 链路层，有时也称作数据链路层或网络接口层，通常包括操作系统中的设备驱动程序和计算机中对应的网络接口卡。它们一起处理与电缆(或其他任何传输媒介)的物理接口细节

- 网络层，有时也称作互联网层，处理分组在网络中的活动，例如分组的选路。在TCP/IP 协议族中，网络层协议包括 IP 协议(网际协议)， ICMP 协议(Internet 互联网控制报文协议)，以及 IGMP 协议(Internet 组管理协议)。

- 传输层主要为两台主机上的应用程序提供端到端的通信。在 TCP/IP 协议族中， 有两个互不相同的传输协议： TCP(传输控制协议)和 UDP(用户数据报协议)。 TCP 为两台主机提供高可靠性的数据通信。它所做的工作包括把应用程序交给它的数据分成合适的小块交给下面的网络层，确认接收到的分组，设置发送最后确认分组的超时时钟等。由于运输层提供了高可靠性的端到端的通信，因此应用层可以忽略所有这些细节。而另一方面， UDP 则为应用层提供一种非常简单的服务。它只是把称作数据报的分组从一台主机发送到另一台主机，但并不保证该数据报能到达另一端。任何必需的可靠性必须由应用层来提供。这两种运输层协议分别在不同的应用程序中有不同的用途

- 应用层负责处理特定的应用程序细节。 几乎各种不同的 TCP/IP 实现都会提供下面这些通用的应用程序：

  - Telnet 远程登录。

  - FTP 文件传输协议。

  - SMTP 简单邮件传送协议。

  - SNMP 简单网络管理协议。


####  OSI模型

1978 年，国际标准化组织(ISO)开发了开放式系统互联(OSI)参考模型，以促进计算机系统的开放互联。

OSI 参考模型的 7 层为(从低到高)：

- 物理层：最底层，它是网络硬件设备之间的接口； 
- 数据链路层：在网络实体之间建立、维持和释放数据链路连接，以及传输数据链路服务数据单元；
- 网络层：通过网络连接交换网络服务数据单元：
- 传输层：在系统之间提供可靠的、透明的数据传送，提供端到端的错误恢复和流控制；
- 会话层：提供两个进程间的连接管理功能； 
- 表示层：处理被传输数据的表示问题，完成数据转换、格式化和文本压缩；
- 应用层：是直接面对用户的一层，提供 0SI 用户服务；

OSI 模型的 l～3 层提供了网络访问， 4～7 层用于支持端到端通信。与 OSI 参考模型相比， TCP/IP 模型更侧重于互联设备间的数据传送，而不是严格的功能层次划分。它通过解释功能层次分布的重要性来做到这一点，但它仍为设计者具体实现协议留下很大的余地。 因此， OSI 参考模型在解释互联网络通信机制上比较适合，但 TCP/IP 成为了互联网络协议的市场标准

#### 数据的封装和拆封

位于TCP/IP 四层模型各个层的数据通常用一个公共的机制来封装： 定义描述元信息和数据报的部分真实信息的报头的协议，这些元信息可以是数据源、目的地和其他的附加属性。来自于高层的协议封装在较低层的数据报中，当信息在不同的层之间传递时，都会在每一层被封装上协议的特有头部。而当我们收到数据时会一层层的剥离头部，直至取出数据。

#### IP协议

P 协议是最为通用的网络层协议。所有的 TCP、 UDP 数据都以 IP 数据报文的格式传输。IP协议是一个无连接、不可靠的协议。不可靠(unreliable)的意思是它不能保证 I P 数据报能成功地到达目的地。 IP 仅提供最好的传输服务，如果发生某种错误时，如途中某个路由器故障， IP 有一个简单的错误处理算法：丢弃该数据报，然后发送 ICMP 消息报给信源端。任何可靠性要求必须由传输层来提供(如 TCP)。无连接(connectionless)这个术语的意思是IP 并不维护任何关于后续数据报的状态信息。每个数据报的处理是相互独立的。这也说明，IP 数据报可以不按发送顺序接收。如果一“信源” 向相同的“信宿” 发送两个连续的数据报文(先是 A，然后是 B)，每个数据报都是独立地进行路由选择，可能选择不同的路线，因此 B 可能在 A 到达之前先到达。关于 IP 的正式规范文件，可参考 RFC791。

#### TCP 协议

TCP 提供一种面向连接的、可靠的字节流服务，它位于 TCP/IP 模型的传输层。面向连接意味着两个使用 TCP 的应用(通常是一个客户和一个服务器)在彼此交换数据之前必须先建立一个 TCP 连接。这一过程与打电话很相似。 

TCP 通过下列方式来提供可靠性：

- 应用数据被分割成 TCP 认为最适合发送的数据块。由 TCP 传递给 IP 层的信息单位称为报文段或段(segment)。当 TCP 发出一个段后，它启动一个定时器，等待目的端确认收到这个报文段。如果不能及时收到一个确认，将重发这个报文段。
- 当 TCP 收到发自 TCP 连接另一端的数据，它将发送一个确认(这个确认不被立即发送，通常将推迟几分之一秒，尽可能的和数据一起发送)。
- TCP通过检验和的形式，提供对 TCP 首部和 TCP 数据的基本校验功能。这是一个端到端的检验和，目的是检测数据在传输过程中的任何变化。如果收到端计算出的检验和， 和原始的相比有差错， TCP 将丢弃这个报文段，并不确认收到此报文段(发送端将超时并重发)。
- 既然TCP 报文段作为 IP 数据报来传输，而 IP 数据报的到达可能会失序，因此 TCP 报文段的到达也可能会失序。如果有必要， TCP 将对收到的数据进行重新排序，将收到的数据以正确的顺序交给上层。 
- 既然 IP 数据报会发生重复， TCP 的接收端必须丢弃重复的数据。
- TCP 还能提供流量控制。 TCP 连接的每一方都有固定大小的缓冲空间。 TCP 的接收端只允许另一端发送接收端缓冲区所能接纳的数据。这将防止较快主机致使较慢主机的缓冲区溢出

综上所述， TCP 是一个较为可靠的数据传输协议。但是 TCP 确认的数据不能保证被应用层收到。比如，当 TCP 确认后的数据已放入套接字缓冲区，而此时恰巧应用进程非正常退出，所以编写一个好的网络程序，我们需要注意的细节很多。 

#### IP地址

在网络中，计算机的唯一性是通过 IP 地址来标识的。也就是说，为了实现 Internet上不同计算机之间的通信，每台计算机都必须有一个不与其他计算机重复的地址，即 IP 地址。连接到 lnternet 上的每一台主机都有一个或多个 IP 地址，它是在 Internet 的所有计算机中唯一标识该计算机的一个 32 位的无符号整数。

IP地址的标准点分十进制表示法一般记为“A.B.C.D” ， 4 个字母分别代表 4 个字节中的十进制整数的字符串表示。这样表示的地址除了方便记忆外，更重要的是它反映了网络的层次结构。实际上，主机的 IP 地址是根据它所在的 Internet 网络位置指定的。这四个字节数据可以分成 3 部分： netID， subnetID， hostID (网络地址，子网地址，主机地址)，网络地址可以由前 1-3 个字节表示，剩余的字节则为子网地址， netID 在网络信息中心(NIC)注册，并分为 A， B， C 三类。各个主机的主机地址在具体的网络管理单位注册。

A 类网络具有一字节的网络地址(最高字节)，其范围为 0～127， 因此只有少量的 A 类网络，但它们中的每一个网络都支持巨大的主机数量(允许 24 位作为主机地址)。中等规模的B 类网络具有两个字节的网络地址，其中第一个字节的范围为 l92-255。因此， Internet地址的第 1， 2 或 3 字节指明网络地址， Internet 地址的其余字节指明那个网络内的地址。例如：与 lnternet 相连的某公司的网络号为 15(即，地址的第一个 8 位为二进制的00001111)，这是一个 A 类网络。该公司将这个私有网络进一步划分为若干的子网，公司中的每一个子网指定一个子网地址，每个子网地址均由 IP 地址的前一个 8 位所标识。例如该公司的某个子网具有地址 15.255.152，属于这个子网的每一台主机的 IP 地址均以 15.255.152 开头。 A 类网络 l27 保留作为本地环回地(loopback)，我们总是可用 Internet 地址l27.0.0.1 访问主机自身。

#### 服务和端口

Internet 通信域中套接字地址由主机的 IP 地址加上端口号组成， IP 地址用来标识Internet 中唯一的主机，端口号则用来区别同一台主机中不同的服务程序。同一台计算机中每一个网络服务程序使用不同端口号，因为可以有很多个服务程序，因此我们需要告诉计算机数据应传送给哪个服务程序 。

端口号是一个 l6 位无符号整数，每一台计算机可以有 65535 个端口号(端口号 0 被保留)。 Internet 中大部分计算机中相同的服务程序均使用相同的端口号，这些端口号是“知名的”，例如 rlogin 远程登录使用端口号 513， ftp 文件传输服务程序使用端口号 21， SMPT 邮件服务程序使用端口号 25，而端口号 23 则专门用于 telnet。这些著名的端口号的使用使得客户程序能够方便的找到任意目标计算机上的适当服务程序。

Linux 中，小于 l024 的端口号保留用于标准的服务程序，它们也称之为特权端口号，因为只有 root 用户执行的服务程序才能使用它们。特权端口号的这种特征可以防止普通用户用任意的服务程序从知名端口号接收数据获取他人重要的信息。 

Linux 系 统 有 一 个 记 录 “知 名 ” 服 务 的 配 置 文 件 ， 这 个 配 置 文 件 通 常 命 名 为/etc/services， 它里面记录IANA（Internet Assigned Numbers Authority 因特网号码指派管理局） “知名端口号” 与服务的对应关系。

| 端口(port) | 服务(service)  |
| -------- | ------------ |
| 7        | Echo(应答)     |
| 21       | FTP(文件传输)    |
| 22       | SSH(加密传输)    |
| 23       | Telnet(远程登录) |
| 25       | SMTP(邮件服务)   |
| 79       | Finger()     |
| 80       | HTTP(消息传输)   |
| 513      | rlogin(远程登录) |

### Socket编程

#### 套接字(Socket)和Socket API

套接字是一种通讯机制，是一种使用标准 Unix/Linux 文件描述字与其他主机进程通讯的手段。从程序员的角度来看，套接字很像文件描述字(一个整数)，因为它同文件和管道一样可以使用read()/write()来读写数据。但是，套接字与普通文件描述字不同，首先， 套接字不像文件描述字那么简单，它除了需要地址端口等信息之外，还明确包含有关于通信的其他属性(如地址族，协议类型，协议族)。其次，套接字的使用可以是非对称的， 它通常明确的区分通信的两个进程为客户进程和服务进程，并且允许不同系统或主机上的多个客户与单个服务进程相连。最后，套接字的创建以及控制套接字的各种操作与文件描述字也有所不同，这些操作的不同是由于建立套接字网络连接比磁盘访问要复杂而带来的。

Socket API(套接字接口)包含完整的调用接口和数据结构的定义，它为应用程序提供对套接字进行操作的手段。进程可以通过调用 Socket API 对套接字进行操作从而实现访问网络并使用各式各样的网络协议进行通讯。

### 网络编程基础知识

在开始学习如何使用套接字编程之前，我们需要先学习一些重要的相关知识和概念， 这其中包括服务器客户端模型，字节序，地址族，地址结构，域名解析等相关内容。

#### 服务器和客户端模型

客户端和服务器端之间使用 TCP 协议通信，这种情形类似于电话通信，相互通信的两个进程之间需显式的调用套接字连接函数建立连接，而且客户和服务进程的角色进一步被使用和建立套接字的方法所增强。这种模式被称为面向连接的客户/服务模型。流套接字(如使用TCP 的套接字)通讯属于这种模式

服务进程通过系统调用 socket()创建一个套接字，随后，服务进程要给该套接字捆绑一个众所周知的端口，以便其他程序能够向服务进程请求并与之通讯，这个过程通过给套接字调用 bind()来实现。在套接字捆绑端口号之后，服务进程便等待客户进程与该套接字连接。因为服务器必须允许多个客户同时与该套接字连接，所以 listen()函数用于为客户端连接创建一个连接列队。服务进程通过调用 accept()接受这些连接。

服务进程每调用一次 accept()便创建一个新的套接字，它不同于前面由 socket()创建的套接字，这个新的套接字完全只用于与特定的客户通信，而 socket()创建的套接字则保留用于与等待其他客户连接的到来。利用这一特征，我们可以使服务进程服务于多个客户。对于简单的服务，后继的客户则要等待在 listen()列队中直到服务进程就绪后再次调用accept()为止。

客户端的动作比服务器端要直观一些。客户进程通过调用 socket()创建一个套接字，然后通过将服务进程套接字的捆绑的地址和端口作为参数，调用 connect()与服务进程建立连接。一旦连接建立，客户和服务进程两端就可以像对普通文件描述字一样的使用套接字进行通信。客户端通常对它所使用的端口号和地址并不关心，只需保证该端口号在本机上是唯一的就可以了，当客户端调用 connect()时，系统将为客户端套接字分配一个空闲的端口号，所以客户端口号义称作临时端口号。

TCP 使用 SYN、 FIN、 RST 等控制报文来转换连接状态， ACK 是 TCP 对数据和控制报文进行确认的报文，它有可能单独存在，但绝大多数时候是随着其他报文一同发送(在数据或控制报文中进行确认)，所以并不认为 ACK 为控制报文。

TCP 不同的控制报文的作用如下：

- SYN 报文：建立连接的请求。
- FIN 报文：用来关闭连接的请求。
- RST 报文：用来复位一条连接，使之成为未连接状态。
- ACK 报文：用来确认数据，不过 ACK 很少作为单独的报文发送。

TCP 建立一次连接需要经历三次握手过程：

- 服务器端做好监听准备，通常是服务器端通过调用 socket()， bind()和 listen()函数监听服务器的某个已知端口

- 客户端应用通过设置服务器端的 IP 地址和端口号并调用 socket()和 connect()函数，导致客户端的 TCP 层发送一个 SYN 报文以请求连接，以及初始序号(例如 I)。

- 服务器端 TCP 层收到客户端的 SYN 报文后，发送包含服务器的初始序号的 SYN 报文段作为应答(初始序列号例如 J)，同时，该 SYN 报文将头部的确认序号设置为 I+l(客户端的序号加 1)对客户的 SYN 报文段进行确认。

- 客户端 TCP 层在收到服务器端的 SYN 后对服务器进行确认，发送的 ACK 的确认序号J+1(服务器端 SYN 的序号加 l)，此时连接建立的过程完成。


TCP 连接关闭的过程

建立一个连接需要一次握手，而终止一个连接要经过四次握手。这是由 TCP 支持半关闭状态造成的，因为 TCP 连接是全双工的，所以每个方向须单独进行关闭。

- 当 A 主机完成它的数据发送任务后就能发送一个 FIN 来终止这个方向连接，序号为 M，发送 FIN 通常是应用程序通过调用 close()或 shutdown()导致的

- B 主机收到 FIN 后将响应一个 ACK， ACK 的确认序号为收到的 FIN 的序号 M 加 1，同时它必须通知应用程序对方已经终止了那个方向的数据传送，通常是对 I/O 操作函数返回文件结束标志(应用程序可以通过调用 read()、 write()、 select()、 poll()等系统调用察觉这个文件结束标志)。

- 如果 B 主机的应用程序在察觉到这个变化时也调用 close()或 shutdown()，这会导致 B主机发送一个 FIN 给 A 主机，序号为(N)。

- 主机 A 收到 FIN 后也将响应一个 ACK，序号为 N 加 1

- 此时关闭的过程结束，TCP 将进入 TIME WAIT 状态


#### 字节序

不同种类的计算机在存储“字” 数据时， 使用不同的字节序协定， 一些计算机把最重要字节(Byte)放置在字(Word)的最前面， 称之为大端(big-endian)字节序， 另外一些体系的计算机把最重要字节(Byte)放在最后， 称之为小端(little-endian)字节序。 这里所说的最重要字节(Byte)是相对计算机所表示的一个数字而言，指的是用来存放数字“最重要位(MSB)” 的字节，如对于整数而言，最重要的位是最高位，而对于浮点数而言，是存放阶码最高位的字节。

我们常见的 x86 构架就采用小端字节序，而有些 RISC 处理器会使用大端字节序如Sparc，作为嵌入式产品常见的 ARM 处理器在启动时可设定小端字节序或大端字节序。

互联网是个复杂的结合体，由各式各样的主机构成，不同体系结构的主机对整数的存储方式是不同的，如果它们各自使用不同的字节序在网络中通讯，将导致严重的问题，为了使得具有不同字节序的机器之间能够通讯， Internet 协议为网络上传输的数据规定了一种规范的字节顺序约定，称之为网络字节序，网络字节序采用大端字节序

```c
//判断字节序
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/lnet.h>
static int isBigEndian()
{
  uint32_t thisx = 0X01020304;
  uint8_t *thisp = (uint8_t *)&thisx;
  return (*thisp == 1) ? 1:0;
}

int main(int argc,char **argv)
{
  printf("Byte order: %s Endian\n",isBigEndian()?"Big":"Little");
  return 0;
}
//我们对一个 32 位整数赋予值 0X01020304，然后我们使用一个 8 位的指针指向这个整数在内存中的首地址，通过判断旨地址是 0x01 还是 0x04 就能判断主机字节序。
```

多数情况下，我们不需要判断主机字节序，而直接使用 C 库中的字节序转换函数：

```c
#include <sys/socket.h>
#include<arpa/inet.h>

unit32_t htonl(unit32_t hostlong);
unit16_t htons(unit_t hostshort);
unit32_t ntohl(unit32_t netlong);
unit16_t ntohs(unit16_t netshort);

/*htonl 将一个 32 位整数由主机字节序转换成网络字节序。
htons 将一个 l6 位整数由主机字节序转换成网络字节序。
ntohl 将一个 32 位整数由网络字节序转换成主机字节序。
ntohs 将一个 l6 侮整数由网络字节序转换成主机字节序*/
```

#### 地址族

一般而言，在使用套接字通信之前，我们首先要为套接字选定一个地址族，简单的说，为套接字指定地址族的目的是告诉套接字使用哪一种网络层进行通讯（如 IPv4 或 IPv6）。

```c
//Sys/socket.h 中定义的地址族：
#define AF_UNSPEC 0 /*未指定*/
#define AF_LOCAL 1 /*UNXI socket*/
#define AF_UNIX AF_LOCAL /*UNIX socket*/
#define AF_INET 2 /*IPv4*/
#define AF_IMPLINK 3 /*arpanet imp 地址*/
#define AF_PUP 4 /*pup 协议： 例如 BSP*/
#define AF_CHAOS 5 /*MIT CHAOS 协议*/
#define AF_NS 6 /*施乐(XEROX)NS 协议*/
#define AF_ISO 7 /*ISO 协议*/
#define AF_OSI AF_ISO
#define AF_ECMA 8 /*欧洲计算机制造商协会*/
#define AF_DATAKIT 9 /*datakit 协议*/
#define AF_CCITT 10 /*CCITT 协议， X.25 等*/
#define AF_SNA 11 /*IBM SNA*/
#deftne AF_DECnet 12 /*DECnet*/
#define AF_DLI 13 /*DEC 直接数据链路接口*/
#define AF_LAT 14 /*LAT*/
#define AF_HYLINK 15 /*NSC Hyperchannel*/
#define AF_APPLETALK 16 /*Apple Talk*/
#define AF_ROUTE 17 /*内部路由协议*/
#define AF_LINK 18 /*协路层接口*/
#define pseudo_AF_XTP 19 /*eXpress Transfer Protocol(noAF)*/
#define AF_COIP 20 /*ST II*/
#define AF_CNT 21 /*Computer Network Technology*/
#define pseudo_AF_RTIP 22 /*用于识别 RTIP 包*/
#define AF_IPX 23 /*Novell 网间协议*/
#define AF_SIP 24 /*Simple 网间协议*/
#define pseudo_AF_PIP 25 /*用于识别 PIP 包*/
#define AF_ISDN 26 /*综合业务数字网(Integrated Services DigitalNetwork)*/
#define AF_El64 AF_ISDN /*CCITT E.164 推荐*/
#define pseudo_AF_KEY 27 /*内部密匙管理功能*/
#define AF_INET6 28 /*IPv6*/
#define AF_NATM 29 /*本征 ATM 访问*/
#define AF_ATM 30 /*ATM*/
#define pseudo_AF_HDRCMPLT 31 /*由 BPF 使用*/
#define AF_NETGRAPH 32 /*Netgraph 套接字*/
#define AF_SLOW 33 /*802.3ad 慢速协议*/
#define AF_SCLUSTER 34 /*Sitara 集群协议*/
#define AF_ARP 35 /*APR 协议*/
#define AF_BLUETOOTH 36 /*蓝牙套接字*/
#define AF_MAX 37
```

#### 地址结构

在开始编写基于套接字的网络程序之前需要先学习如何填充地址结构。大多数SocketAPI 函数都需要一个指向地址结构的指针作为参数。每个地址族都定义了它自己的套接字地址结构。这些结构的名字以“sockaddr_” 开头，并以对应每个协议族的唯一后缀结束 (如 sockaddr_in 表示 AF_ INET 地址族结构)。

在 sys/socket.h 文件中有各种各样的地址结构定义，分别针对不同的地址族，可是Socket API 只有少量且固定的几个接口定义，如何才能传递多种地址族结构给 Socket API函数呢？ Berkeley Socket 专门为此声明了一个通用地址结构 sockaddr：

```c
typedef unsigned short sa_family_t;
#include<sys/socket.h>
struct sockaddr {
	sa_family_t sa_family; /*地址族*/
	char sa _data[14]; /*地址值， 实际可能更长*/
};
#define SOCK_MAXADDRLEN 255 /*可能的最长的地址长度*/
```

sockaddr 结构的 sa_data 域的定义并不明确。 它只是被定义为 l4 字节的数组，SOCK_MAXADDRLEN 宏暗示内容可能超过 l4 字节。这种不确定性是经过深思熟虑的。 SocketAPI 是个非常强大的接口，它能处理多种多样网络层地址族，这包括我们常常提到的 IPv4、IPv6、 IPX。

Socket API 为了能够传递繁多的地址族结构，它使用通用地址结构类型 sockaddr 作为地址参数类型，在该类型的前面包含了所有地址结构共有的 16bits 域来存放地址族类型(它是主机字节序的，用来表明该结构的地址族类型，如 AF_INET， AF_UNIX 等等)， Socket API会根据这个域判断如何对待结构的后续数据。这也就是说，我们不会真的用到 sockaddr 结构，我们需要填写真正的与地址族相关的地址结构，然后在传递给需要地址结构的函数时，把指向该结构的指针转换成 sockaddr 结构类型的指针传递进去。例如，当我们要使用 IPv4地址族，此时需要填写的是 sockaddr_in 结构类型，我们把 sockaddr_in 的 sin_family 域设定为 AF_INET，然后把 sockaddr_in 结构的地址传递给需要 sockaddr 结构指针参数的函数。

#### IPv4地址族结构

IPv4是如今最通用的网络层协议，所以它对应的地址结构被称为“网络套接字地址结构”，以sockaddr_in命名

```c
//IPv4 地址族结构定义
#include<netinet/in.h>
struct in_addr{
	in_addr_t s_addr;
};
struct sockaddr_in {
    uint16_t sin_family;
    uint16_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};
/*sin_family 是一个 16 位的无符号整数，它需要填写主机字节序的地址结构类型(如AF_INET)。
  sin_port 为 l6 位无符号整数值，这个域用来存放网络字节序的端口号。
  sin_addr 用来存放 IPv4 地址，地址值为网络字节序。 		  sin_addr 由于历史原因被声明为in_addr 结构类型，但它实际上只包含一个名为 s_addr 的 32 位无符号整数值，这个类
型定义在 netinet/in.h 之中*/

//假设远程的主机地址是192.168.2.1 端口号3001，现在我们尝试填充它
struct sockaddr_in sin;
memset(&sin,0,sizeof(sin));
sin.sin_port = hons(3001);
sin.sin_addr.s_addr = htonl(0x0a80201);//192.168.2.1
//sin_family 需要填充正确的地址族类型 AF_INET。
```

0xc0a80201 是地址 192.168.2.1 的 IPv4 地址值， 我们需要把它转换成网络字节序， 但这么做很麻烦， 我们需要自己计算 32 位的地址值。幸好 Socket API 已经定义了转换字符串至 IP 地址值的函数， 函数原型如下：

```c
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int inet_aton(const char* strptr,struct in_addr *addrptr);
in_addr_t inet_addr(const char *strptr);
char *inet_ntoa(struct in_addr in);
const char *inet_ntop(int af,const void* restrict src,char *restrict dst,socklen_t size);
//第一个函数 inet_aton()将 strptr 指向的字符串转换成网络字节序的 32 位的 IPv4 地址， 并通过指针 addrptr 来存储转换后的结果， 如果转换成功返回 1， 否则返回 0。
/*inet_addr()执行和 inet_aton()相同的转换， 返回值是网络字节序的 IPv4 地址， 这个函数存在一个严重的问题， 因为 IPv4 地址是 32 位的， 也就说明所有 32 位无符号整数能表示的数字都是有效的地址(Ox00000000 到 0xffffffff 的 32 位整数对应地址 0.0.0.0 到255.255.255.255)， 在 inet_addr 的相关文档中提到， 如果 inet addr()执行出错， 它将返回 INADDR_NONE 表示错误，这个值在绝大多数操作系统中被定义为一 1(补码为0xffffffff)，这也同时说明 inet add()不能处理 255.255.255.255(值为 0xffffffff)这个受限广播地址。
函数 inet_ntoa()将一个网络字节序的 IPv4 地址转换成字符串，并将字符串作为返回值返回。用于保存返回值的字符串驻留在静态内存中，这意味着这个函数是不可重入的，也就是说我们把它用在并发操作(线程或 vfork())函数中要非常小心。*/
```

以上三个函数或多或少都存在问题，我们并不推荐使用，下面将着重介绍两个用于同样目地的转换函数，它们不仅可以用于转换 IPv4 地址，还可以用来转换 IPv6 的地址。

```c
int inet_pton(int af,const char* restrict src,void *restrict dst);
//inet_ntop()把网络字节序的 ip 地址 src 转换成字符串保存在 dst 中作为返回值返回，参数 size 为 dst 所包含的字节数。
//inet_pton()把字符串 src 转换成 ip 地址保存在 dst 中。该函数调用成功返回大于 0的整数。
//inet_ntop()和 inet_pton()有个共有的地址族参数 af， 如果我们要转换 IPv4 的地址，这里需要填写 AF_INET
//假设远程的主机地址是192.168.2.1 端口号3001，现在我们尝试填充它
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
# include <arpa/inet.h>
struct sockaddr_in sin;
char buf[16];
memset(&sin,0,sizeof(sin));
sin.sin_family=AF_INET;
sin.sin_port=htons(3001);
if(inet_pton(AF_INET,"192.168.2.1",&sin.sin_addr.s_addr)<=0)
{
  //错误处理
}
printf("%s\n",inet_ntop(AF_INET,&sin.sin_addr.s_addr,buf,sizeof(buf)));
```

上例中我们首先把端口号 3001 用 htons()变成网络字节序并填充地址族结构的sin_port 域， 然后调用 inet_pton()将字符串表述的 IPv4 地址转换成协议族大端字节序地址。最后， 我们调用 inet_ntop()再将它转换成字符串表述的 IPv4 地址， 并调用 printf 输出它，在调用 inet_ntop 的时候，我们必须给它传递一个用于保存结果的缓冲区，我们在栈中分配 l6 字节的数组 buf,之所以这么做的原因是因为 16 字节足够存储一个字符串表示点分 lPv4 的地址。

#### 域名解析

```c
//域名不能直接传送给任何 Socket API 函数，解析器库(Resolver library)包含了域名解析函数，它将域名转换成网络字节序的协议地址：
#include<netdb.h>
struct hostent{
  char *h_name;
  char *h_aliases;
  int h_addrtype;
  int h_length;
  char **h_addr_list;
};
#define h_addr h_addr_list[0]
struct hostent *gethostbyname(const char *hostname);
extern int h_errno;
char *hstrerror(int err);
/*hostent 结构体成员：
h_name 被称为主机的正式(canonical)名(例如 www.google.cn 的正式主机名是cn.l.google.com)。
h_aliases 是主机的别名列表， 有的主机可能有几个别名(www.google.cn 就是 google他自己的别名)。
h_addrtype 表示的是主机地址族的类型， AF_INET 或 AF_INET6。
h_length 表示返回地址的长度，如果返回的是 IPv4 地址，这个长度为 4。
h_addr_list 返回主机的地址列表，以网络字节序存储*/
//gethostbyname()根据配置文件(/etc/resolv.conf)里的 DNS 主机列表向 DNS 服务器发送 UDP 的查询或通过查找本地静态主机文件/etc/hosts 来实现域名解析。参数 hostname 是一个包含主机域名的字符串(如“www.google.cn”)或包含 IPv4 地址的字符串(如“l92.168.2.1”)。
//当 gethostbyname()成功执行将返回非空的 hostent 结构地址， 失败则返回空指针， 并用错误码设置全局变量 h_errno， 可以通过调用 hstrerror()并传递 h_errno 作为参数取得错误描述信息
```

```c
//域名解析程序
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
  char **pptr;
  char str[46];
  struct hostent *hptr;
  if(argc<2)
  {
  	fprintf(stderr,"usage:domain<domain>\n");
    return -1;
  }
  if((hptr = gethostbyname(argv[1])) == NULL)
   {
  		fprintf(stderr,"gethostbyname call failed.%s\n",hstrerror(h_errno));
    	return -1;
    }
  	printf("offical name:%s\n",hptr->h_name);
  	for(pptr = hptr->h_aliases;*pptr != NULL; pptr++)
    {
  		printf("\t alias:%s\n",*pptr);
	}
  	if(hptr->h_addtype != AF_INET)
    {
      fprintf(stderr,"Invalid address type %d\n",hptr->h_addrtype);
      	return -1;
	}
  pptr = hptr->h_addr_list;
  for(;*pptr != NULL;pptr ++)
  {
  	printf("\t address: %s\n",inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
  }
  return 0;
}
```

#### 建立套接字

```c
#include<sys/socket.h>
int socket(int domain, int type, int protocol);
//成功返回非负套接字，失败返回-1
/*参数数 domain 告诉系统你需要使用什么地址协议族，他们都是用 AF_或 P_ 开头的数字常量宏定义，地址族的声明在 sys/socket.h 中，如 AF_INET 适用于地址族(IPv4)。
参数 type 有五个定义好的值，也在 sys/socket.h 中。这些值都以“SOCK_” 开头。其中最通用的是 SOCK_STREAM，它告诉系统你需要一个可靠的流传送服务，当使用 AF_INET 和SOCK_STREAM 作为参数调用 socket()将指明创建一个使用 TCP 协议的套接字。如果指定SOCK_DGRAM，则将请求一个无连接报文传送服务(如 UDP)。如果你需要存取原始套接字，你就需要指定 SOCK_RAW。*/
//protocol 参数可以指定一个更精确的协议(如 IPPROTO_TCP 对应与 TCP 协议)，它取决于前两个参数，而且并非总是有意义，多数时候可以不关心它，在大多数情况下可以传递 0，系统会根据前两个参数为我们选择一个合适的协议族。
```

#### 连接远程主机(connect )

动请求连接是客户端的动作， TCP/IP 客户端通常要调用 connect()去连接一个服务端

```c
#include<sys/types.h>
#include<sys/socket.h>
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
//成功返回0，失败返回-1并将错误码代存放于全局变量 errno 之中。
//参数 sockfd 是成功调用 socket()返回的套接字。
//参数 serv_addr 形式上是一个指向 sockaddr 的指针，而实际上需要传递的是特定地址族的地址结构(如 struct sockaddr_in)的地址
//参数 addrlen 表示第二个参数的字节数(如 sizeof(struct sockaddr_in))。
```

调用connect()函数会引发一次三次握手过程(发送 SYN)。等待连接建立后（三次握手完成)或出错才返回。在连接的起始阶段套接字层首先会为我们找到一个空闲的端口号，并根据服务器地址查询路由表选择一个本地 IP 地址，在连接完成后将使用这个地址和端口与服务器通讯。  

有些可能导致 connect()失败的原因。例如，指定 IP 地址的主机可能不存在，没有到指定主机的路由，远程服务器端未启动，或者指定端口在远程服务器上并未启动监听等等，出错原因可以使用 perror()函数来输出错误信息。 

#### 关闭套接字

```c
#include<unistd.h>
int close(int sockfd);
```

其中，参数 sockfd 可以是打开的任何类型的文件描述字，包括套接字。close()调用成功返回 0， 失败返回-1，并用出错代码设置 errno。

通常情况下(指末使用 SO_LINGER 套接字选项修改 close()的行为)对一个已连接套接字成功调用 close()。 它表示套接字缓冲区中的数据发送给对方的 TCP 层并成功执行 TCP 关闭连接的 4 个过程， close()要等待关闭过程完成才返回。 

有个例外：当我们对一个已打开的文件描述字或套接字调用 dup()进行复制， 或进程调用 fork()时，系统会增加套接字的引用计数器。当套接字的引用计数器大于 1 时，它并不关闭连接，而是简单的递减套接字引用计数器后直接返回。 

当调用 shutdown()关闭写操作时(SHUT_WR)，系统将不顾套接字引用计数而直接引发 TCP 连接关闭过程 

```c
#include<sys/socket.h>
int shutdown(int sockfd,int howto);
/*howto的三个取值
SHUT_RD 关闭连接的读一半，进程不能接收套接字缓冲区中的未读数据，且留在套接字缓冲区中的数据将作废。进程不能再对套接字调用 read()读取数据。在调用 shutdown()后， TCP 套接字在接收到数据时仍然发送 ACK 进行确认，但数据都被丢弃掉
SHUT_WR 关闭连接的写这一半。我们称之为 TCP 的半关闭(half-close)状态，程序不能再对该套接字进行写操作，当前套接字缓冲区中的已有数据都将被发送出去，在数据发送完毕后，将发送 TCP 的关闭序列(FIN)。这个操作不管套接字的引用计数而直接引发 TCP 关闭。
SHUT_RDWR 关闭连接读和写，这等效于调用 shutdown()两次，第一次调用时使用 SHUT_RD参数，第二次使用 SHUT_WR 参数。 shutdown()调用成功返回 0，失败返回-1，并用出错代码设置 errno。*/
```

#### Socket I/O

对于套接字的 I/O(读写)有很多 API 可用，如 send()、 recv()、 readv()、 writev()、sendmsg()、 recvmsg()、 sendto()、 recvfrom()、 read()、 write()等等。 

```c
#include<unistd.h>
int read(int sockfd, void *buf, size_t nbytes);
int write(int sockfd, void *buf, size_t nbytes);
//而这个 read()函数将返回读入的字节数，返回 0 表示套接字已关闭， 出错返回-1 并设置 errno。
//write()函数将成功返回写入的字节数，出错返回-1 并设置 errno，向一个已关闭套接字多次调用 write()将引发 SIGPIPE 信号。
```

我们曾经学过，一个文件描述字的 I/O 可以是阻塞或非阻塞的方式(通过调用对 fcntl()设置 0_NONBLOCK 选项或调用 ioctl()对文件描述字设置 FIONBIO)，这对于套接字也同样适用，默认时套接字为阻塞方式，此时 read()和 write()会阻塞在 I/O 操作上， 直至以下几种情况发生才会返回：

- 有数据到来或写出的数据被对方TCP层确认才返回
- 套接字出错，如 TCP 超时或收到了 RST， read()和 write()返到-1。 
- 套接字关闭， read()调用返回 0， write()调用返回-1。 
- 阻塞时受到了信号，read()和 write()调用返回-1，并设置 errno 为 EINTR。 

```c
//下面是 ECHO 客户端代码(它接收用户输入发送给服务器端的 2029 端口，接收服务器端的响应并将它显示给用户)
#ifndef _MYNET_H
#define _MYNET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define RET_OK 0
#define RET_ERR -1

#define LISTEN_QUEUE_NUM 5
#define BUFFER_SIZE 256
#define ECHO_PORT 2029

#endif
```

```c
//client.c
#include "mynet.h"

int main(int argc,char **argv)
{
  int sockfd,ret = RET_OK;
  structe sockaddr_in servaddr;
  struct hostent *server;
  
  char buffer[BUFFER_SIZE];
  
  if(argc<2){
  	fprintf(stderr,"usage %s hostname\n",argv[0]);
    return RET_ERR;
  }
  
  if(server = gethostbyname(argv[1]) == NULL)
  {
  	herror("gethostbyname.");
    return RET_ERR;
  }
  
  if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
  {
  	perror("ERROR opening socket");
    return RET_ERR;
  }
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = *(uint32_t *)server->h_addr;
  servaddr.sin_port = htons((uint16_t)ECHO_PORT);
  
  if((ret = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))<0)
  {
  	perror("ERROR connecting");
    goto failed;
  }
  while(1)
  {
  	printf("Enter the message:");
    if(fgets(buffer,sizeof(buffer)-1,stdin)==NULL)
    {
      	break;
	}
    if((ret = write(sockfd,buffer,strlen(buffer)))<0)
    {
  		perror("ERROR writing to socket");
      	break;
    }
    if((ret = read(sockfd,buffer,sizeof(buffer)-1))<0)
    {
  		perror("ERROR reading from socket");
      	break;
    }
    if(ret == 0)
    {
  		printf("Server disconnect\n");
      	break;
    }
    buffer[ret] = 0;
    printf("Server echo message:%s\n",buffer);
  }
failed:
  close(sockfd);
  return ret<0?RET_ERR : RET_OK;
}
```

#### 给本地套接字赋予地址和端口(bind)

服务器端和客户端不同，它并不调用 connect()主动连接其他主机，而是监听本地端口和地址被动的等待客户端的连接请求。另外，服务器端程序不同于客户端程序，他不能依赖 TCP 为我们选择的空闲端口(客户端也可以调用 bind()为自己指定一个本地端口和本地地址，但很少这么做)， 而是需要明确指出要监听的端口号，这样才能让客户端连接服务器。通常需要调用bind()函数为套接字捆绑本地端口和地址。