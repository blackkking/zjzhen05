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

