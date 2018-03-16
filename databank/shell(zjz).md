[TOC]

# shell(zjz)

## 用shell进行数学运算

在Bash shell环境中，可以利用let、(( ))和[]执行基本的算术操作。而在进行高级操作时，expr和bc这两个工具也会非常有用。

```shell
#!/bin/bash
no1=4;
no2=5;
let result=no1+no2
echo $result
let no+=6
#使用[]
result=$[ no1 + no2 ]
result=$[ $no1 + 5 ]
#也可以使用(()),但是使用时，变量名前需要加上$
result=$(( no1 + 50 ))
#expr
result=`expr 3 + 4`
result=$(expr $no1 + 5)
#这些方法只能用做整数运算，而不支持浮点数。
```

```shell
echo "4 * 0.56" | bc

no=54;
result=`echo "$no * 1.5" | bc`
echo $resulte
#设定小数精度。
echo "scale=2;3/8" | bc
#进制转换。
#!/bin/bash
no=100
echo "obase=2;$no" | bc
1100100
no=1100100
echo "obase=10;ibase=2;$no" | bc
100
#计算平方和平方根
echo "sqrt(100)" | bc #Square root
echo "10^10" | bc #Square
```

## 设置颜色输出

```shell
echo -e "\e[1;31m this is red text \e[0m"
```

```shell
echo -e "\e[1;42m green background \e[0m"
```

\e[1;31将颜色设为红色，\e[0m将颜色重新置回。只需要将31替换成想要的颜色码就可以了

## 环境变量  

假设有一个叫gedit的应用程序正在运行。我们可以用pgrep命令获得gedit的进程ID:

```shell
pgrep gedit
12501
```

```shell
cat /proc/12501/environ
#用tr 把\0 替换为\n
cat /proc/12501/environ | tr '\0' '\n'
```

环境变量是未在当前进程中定义，而从父进程中继承而来的变量 。例如环境变量HTTP_PROXY，它定义了互联网连接应该使用哪个代理服务器。

```shell
#该环境变量通常被设置成：
HTTP_PROXY=192.168.1.23：3128
export HTTP_PROXY
```

export命令用来设置环境变量。至此之后，从当前shell脚本执行的任何应用程序都会继承这个变量。我们可以按照自己的需要，在执行的应用程序或者shell脚本中导出特定的变量。在默认情况下，有很多标准环境变量可供shell使用。

## 关于变量的小技巧

- 获得字符串长度 length=${#var}

- 识别当前所使用的shell: 

  ```shell
  echo $SHELL
  echo $0
  ```


- UID可以检测是否为超级用户

  ```shell
  $UID -ne 0
  #root用户的UID是0
  ```


- 修改bash提示字符串(username@hostname:~$)

  ​我们可以利用PS1环境变量来定制提示文本。默认的shell提示文本是在文件~/.bashrc中的某一行设置的。

  ​cat ~/.bashrc | grep PS1

  ​设置一个定制的提示字符串，可以输入

```shell
PS1="PROMPT>"
#也可以利用\e[1;31的特定转义序列来设置彩色的提示字符串
```

还有一些特殊的字符可以扩展成系统参数。例如： \u可以扩展为用户名， \h可以扩展为主机名，而\w可以扩展为当前工作目录。

```shell
fname;#执行函数
echo $1, $2; #访问参数1和参数2
echo "$@"; #以列表的方式一次性打印所有参数
echo "$0"; #命令含命令所在的路径
echo "$*"; #类似于$@，但是参数被作为单个实体
echo $?; #读取命令返回值
echo $!; #输出最近一个后台进程的PID
& #shell将命令至于后台并继续执行脚本
```

## 添加环境变量函数

假设我们要把myapp安装在/opt/myapp,它的二进制文件在bin目录中，库文件在lib目录中。

```shell
#实现方法如下：
export PATH=/opt/myapp/bin:$PATH
export LD_LIBRARY_PATH=/opt/myapp/lib;$LD_LIBRARY_PATH=/opt/myapp/lib;$LD_LIBRARY_PATH
#PATH和LD_LIBRARY_PATH现在看起来应该像这样：
PATH=/opt/myapp/bin:/usr/bin:/bin
LD_LIBRARY_PATH=/opt/myapp/lib:/usr/lib;/lib
#不过我们可以把下面的函数加入.bashrc-,让一切变得更轻松些：
prepend() { [ -d "$2" ] && eval $1=\"$2\$\{$1:+':'\$$1\}\" && export $1 ; }
#像下面这样来使用该函数：
prepend PATH /opt/myapp/bin
prepend LD_LIBRARY_PATH /opt/myapp/lib
```

我们定义了名为prepend()的函数，它首先检查该函数第二个参数所指定的目录是否存在。如果存在， eval表达式将第一个参数所指定的变量值设置成第二个参数的值加上“:”（路径分隔符），随后再跟上首个参数的原始值。

```shell
#在这个函数中，我们引入了一种shell参数扩展的形式：
${parameter:+expression}
#如果parameter有值且不为空，则使用expression的值
```



## 把错误流和输出流输出到同一个文件

```shell
#命令的退出状态可以用$?获得。非0就是失败
cmd 2>&1 output.txt
cmd &> output.txt
```

## 把命令定向到文件

```shell
cat a* | tee out.txt | cat -n
#在上面的代码中，tee命令接收到来自stdin的数据，它将stdout的一份副本写入到文件out.txt中，同时将另一份副本作为后续命令的stdin.命令cat -n将从stdin中接受到的每一行数据前加上行号写入stdout
#stderr的内容不会出现，tee只能从stdin中读取
#tee -a 可以在文件中追加内容而不是覆盖
#>和>>不同，两者都可以把文件重定向到文件，但是前者会先清空文件，然后再写入内容，而后者会将内容追加到现有的文件的尾部。
```

## 自定义文件描述符

```shell
#使用exec命令创建自己的文件描述符。文件打开方式有三种，1：只读2：截断写入3：追加写入
#创建一个文件描述符进行文件读取：
exec 3<input.txt
cat<&3 #使用文件描述符3
#创建一个文件描述符进行写入(截断模式)
exec 4>output.txt
echo newline >&4
#创建一个文件描述符用于写入(追加模式)
exec 5>>input.txt
echo appended line >&5
```

## 数组和关联数组

```shell
#打印数组长度
echo ${#array_var[*]}
#定义关联数组
declare -A ass_array
ass_array=([index1]=val1 [index2]=val2)#赋值1
ass_array[index1]=val1#赋值2
echo ${!array_var[*]}#打印数组的索引
```

## 使用别名

```shell
#可以按照下面的方式创建一个别名
alias new_command='command sequence'
alias install='sudo apt-get install'#example
#alias的作用是暂时的，关闭终端后会失效，要让别名一直保持作用，可以将它放入~/.bashrc文件中，因为每当一个新的shell进程生成时，都会执行~/.bashrc中的命令
echo 'alias cmd="command seq"' >> ~/.bashrc
#删除别名，把对应语句从~/.bashrc中删除，或者用unalias.或者使用alias example=，这会取消名为example的别名
#对别名进行转义
\command
```

## 终端命令处理

tput和stty是两款终端处理工具。

tput cols 打印列数 tput lines 打印终端行数

tuput longname打印当前终端名

tput cup 100 100 把光标移动到坐标(100,100)处

tputsetb n 设置终端背景色 n在0到7之间

tput bold 设置粗体 tput smul设置下划线的起  tput rmul 设置下划线的止

tput ed 删除从当前光标位置到行尾的所有内容

```shell
#输入密码时不显示密码
#!/bin/sh
echo -e "Enter password： "
stty -echo		#选项-echo 禁止将输出发送到终端
read password
stty echo		#选项 echo 允许发送输出
echo
echo Password read.
```

## 时间与延时

获取时间date

```shell
#打印纪元时
date +%s
date --date "Thu Nov 18 08:0721 IST 2010" +%s #转化为纪元时
date --date "Jan 20 2001" +%A #给的日期是星期几
date "+%d %B %Y"  #按格式输出时间
date -s "格式化的日期字符串"  #设置日期和时间

#检查一组命令所花费的时间
#!/bin/bash
start=$(date +%s)
commands;
statements;

end=$(date+%s)
difference=$((end - start))
echo Time taken to execute commands is $difference seconds.
#另一种方法则是使用time<scriptpath>来得到执行脚本所花费的时间
```

```shell
#! /bin/bash
# 在脚本中生成延时
echo -n Count:
tput sc			#储存光标位置

count=0;
while true;
do
	if [ $count -lt 40 ];
	then 
		let count++;
		sleep 1;
		tput rc		#恢复光标位置
		tput ed		#清除当前光标位置到行尾之间的内容
		echo -n $count;
	else exit 0;
	fi
done
```

## 调试脚本

```shell
#! /bin/bash
function DEBUG()
{
  [ "$_DEBUG"=="on" ] && $@ || :
}
for i in {1..10}
do
	DEBUG echo $i
done
//调试
_DEBUG=on ./script.sh
```

把shebang从#! /bin/bash 改成 #!/bin/bash -xv,这样一来，不用任何其他选项就可以启用调试功能了。

## 子shell

子shell本身就是独立的进程。可以使用()操作符来定义一个子shell

当命令在子shell中执行时，不会对当前shell有任何影响；所有的改变仅限于子shell内。例如，当用cd命令改变子shell的当前目录时，这种变化不会反映到主shell环境中。

假设我们使用子shell或反引用的方法将命令的输出读入一个变量中，可以将它放入双引号中，以保留空格和换行符（\n）。例如：

```shell
cat text.txt
1
2
3

out=$(cat text.txt)
echo $out
1 2 3 #Lost \n spacing in 1,2,3

out="$(cat text.txt)"
echo $out
1
2
3
```

## fork炸弹

```shell
:(){ :|:& };:
```

可以通过修改配置文件/etc/security/limits.conf来限制可生成的最大进程数来避开这枚炸弹。

## read

下面的语句从输入中读取n个字符并存入变量variable_name：

```shell
read -n number_of_chars variable_name
read -n 2 var
echo $var
#用无回显的方式读取密码
read -s var
#显示提示信息
read -p "Enter input:" var
#在特定时限内读取输入
read -t timeout var
read -t 2 var #在2秒内将键入的字符串读入变量var
#用特定的定界符作为输入行的结束
read -d delim_char var
read -d ":" var #hello:var 被设置为 hello
```

## 运行命令直至执行成功

```shell
repeat()
{
  while true
  do
  	$@ && return
  done
}
```

我们创建了函数repeat，它包含了一个无限while循环，该循环执行以参数形式（通过$@访问）传入函数的命令。如果命令执行成功，则返回，进而退出循环。

```shell
repeat() { while :; do $@ && return; done }
repeat() { while :; do $@ && return; sleep 30; done }
#延时
repeat wget -c http://www.example.com/software-0.1.tar.gz#假设用repeat()从Internet上下载一个暂时不可用的文件
```

[ condition ] && action; # 如果condition为真，则执行action；

[ condition ] || action; # 如果condition为假，则执行action。

## 字符分隔符和迭代器

IFS是存储定界符的环境变量。它是当前shell环境使用的默认定界字符串。考虑一种情形：我们需要迭代一个字符串或逗号分隔型数值（Comma Separated Value， CSV）中的单词。如果是前一种，则使用IFS="."；如果是后一种，则使用IFS=","。接下来看看具体的做法。

```shell
data="name,sex,rollno.location"
#我们可以使用IFS读取变量中的每一个条目
oldIFS=$IFS
IFS=","
for item in $data;
do
	echo Item: $item
done

IFS=$oldIFS
```

IFS的默认值为空白字符（换行符、制表符或者空格）。

### 循环

```shell
##for
for var in list;
do
	commands; #使用变量$var
done     #list 可以是一个字符串，也可以是一个序列
echo {1..50} echo {a..z}
for ((i=0; i<10; i++))
{
	commands; #使用变量$i
}
##while
while condition
do
	commands;
done
#用true作为循环条件可以生成无限循环

##until
x=0;
until [ $x -eq 9 ]; 
do
	let x++; echo $x;
done
```

### 文件系统相关测试

```shell
[ -f $file_var ]: 如果给定的变量包含正常的文件路径或文件名，返回真
[ -x $var ]: 如果给定的变量包含的文件可执行，返回真
[ -d $var ]:如果给定的变量是目录，则返回真
[ -e $var ]:如果给定的变量包含的文件存在，返回真
[ -c $var ]:如果给定的变量包含的是一个字符设备文件的路径，返回真
[ -b $var ]:如果给定的变量包含的是一个块设备文件的路径，返回真
[ -w $var ]:如果给定的变量包含的文件可写，返回真
[ -r $var ]:如果给定的变量包含的文件可读，返回真
[ -L $var ]:如果给定的变量包含的是一个符号链接，返回真
```

使用字符串比较时，最好用双中括号，因为有时候采用单个中括号会产生错误，所以最好避开它们

```shell
[[ $str1 = $str2 ]] #判断两个字符串是否相同
[[ $str1 == $str2 ]]
[[ -z $str1 ]] #str1是空返回真
[[ -n $str1 ]] #str1非空返回真
```

### test

test命令可以用来执行条件检测。用test可以避免使用过多的括号。之前讲过的[]中的测试条件同样可以用于test命令例如：

if [ $var -eq 0 ]; then echo "True"; fi
也可以写成：
if test $var -eq 0 ; then echo "True"; fi

## 命令之乐

### cat

cat命令不仅可以读取文件、拼接数据，还能够从标准输入中进行读取。从标准输入中读取需要使用管道操作符:OUTPUT_FROM_SOME COMMANDS | cat

类似地，我们可以用cat将来自输入文件的内容与标准输入拼接在一起，将stdin和另一个文件中的数据结合起来。方法如下：

$ echo 'Text through stdin' | cat - file.txt

在上面的代码中， -被作为stdin文本的文件名。

```shell
cat -s file #压缩相邻的空白行
cat -T file #将制表符显示为^
cat -n file #显示行号
```

### 录制并回放终端会话

```shell
#开始录制终端会话
$ script -t 2> timing.log -a output.session
type commands;
...
..
exit
#按播放命令序列输出
$ scriptreplay timing.log output.session
```

两个配置文件被当做script命令的参数。其中一个文件（timing.log）用于存储时序信息，描述每一个命令在何时运行；另一个文件（output.session）用于存储命令输出。 -t选项用于将时序数据导入stderr。 2>则用于将stderr重定向到timing.log。

### find查找

```shell
#find命令有一个选项-iname会忽略字母的大小写
find . \( -name "*.txt" -o -name "*.pdf" \) -print
#\(以及\)会让中间的内容视为一个整体 -o 匹配多个条件中的一个
find . ! -name "*.txt" -print #否定参数"!"
```

- 基于目录深度的搜索

find命令在使用时会遍历所有的子目录。我们可以采用深度选项-maxdepth和 -mindepth来限制find命令遍历的目录深度。使用下列命令将find命令向下的最大深度限制为1：find . -maxdepth 1 -name "f*" -print 打印出深度距离当前目录至少两个子目录的所有文件:

find . -mindepth 2 -name "f*" -print

- 根据文件类型 -type

  普通文件 f  符号链接 l目录 d	字符设备 c	块设备 b	套接字 s	FIFO p

- 根据时间

  访问时间(-atime)修改时间(-mtime)内容修改	变化时间(-ctime)权限改变

单位是天，-表示小于，+表示大于

```shell
find . type -f -atime -7 -print #最近7天被访问的
find . type -f -atime 7 -print #7天前访问的文件
find . type -f -atime +7 -print #访问时间超过7天
#单位是分钟的 amin mmin cmin 
```

- 根据文件大小 -size

  b块512字节c字节	w字 2字节	k 1024字节	M 1024K 	G 1024M

- 删除匹配的文件 -delete

find . -type f -name "*.swp" -delete

- 基于文件权限和所有权的匹配

find . -type f -perm 664 -print 打印权限是644的文件

-user USER 找到某个特定用户所拥有的文件

- 利用find执行命令或动作 -exec

```shell
find . -type -user root -exec chown slynux {} \;
```

在这个命令中， {}是一个与 -exec选项搭配使用的特殊字符串。对于每一个匹配的文件，{}会被替换成相应的文件名。例如， find命令找到两个文件test1.txt和test2.txt，其所有者均为slynux，那么find就会执行：chown slynux {}

有时候我们并不希望对每个文件都执行一次命令。我们更希望使用文件列表作为命令参数，这样就可以少运行几次命令了。如果是这样，可以在exec中使用+来代替;。

$ find . -type f -name "*.c" -exec cat {} \;>all_c_files.txt

将给定目录中的所有C程序文件拼接起来写入单个文件all_c_files.txt

我们无法在-exec参数中直接使用多个命令。它只能够接受单个命令，不过我们可以耍一个小花招。把多个命令写到一个shell脚本中（例如command.sh），然后在-exec中使用这个脚本

- 让find跳过特定的目录

```shell
find devel/source_path \( -name ".git" -prune \) -o \( -type f -print \) #Instead of \( -type -print \),而是选择需要的过滤器
```

以上命令打印出不包括在.git目录中的所有文件的名称（路径）

#### 玩转xargs

我们可以用管道将一个命令的stdout（标准输出）重定向到另一个命令的stdin（标准输入）。例如：
cat foo.txt | grep "test"
但是，有些命令只能以命令行参数的形式接受数据，而无法通过stdin接受数据流。在这种情况下，我们没法用管道来提供那些只有通过命令行参数才能提供的数据。

xargs命令应该紧跟在管道操作符之后，以标准输入作为主要的源数据流。它使用stdin并通过提供命令行参数来执行其他命令。

xargs命令把从stdin接收到的数据重新格式化，再将其作为参数提供给其他命令xargs可以作为一种替代，其作用类似于find命令中的 -exec。

xargs有一个选项-I，可以提供上面这种形式的命令执行序列。我们可以用-I指定替换字符串，这个字符串在xargs扩展时会被替换掉。如果将-I与xargs结合使用，对于每一个参数，命令都会被执行一次。

```shell
cat args.txt | xargs -I {} ./cecho.sh -p {} -1
-p arg1 -1 #
-p arg2 -1 #
-p arg3 -1 #
#-I {}指定了替换字符串。对于每一个命令参数，字符串{}都会被从stdin读取到的参数替换掉。
```

正则表达式-regex

E-mail地址通常采用name@host.root这种形式，所以可以将其一般化为[a-z0-9]+@[a-z0-9]+.[a-z0-9]+。符号+ 指明在它之前的字符类中的字符可以出现一次或多次。

```shell
find . -type f -user root -exec chown slynux {} \;
```

在这个命令中，{}是一个与 -exec选项搭配使用的特殊字符串。对于每一个匹配的文件，{}会被替换成相应的文件名。

```shell
find . -type f -name "*.c" -exec cat {} \;>all_c_files.txt
#执行脚本
-exec ./commands.sh {} \;
```

```shell
find devel/source_path	\( -name ".git" -prune \) -o \( -type f -print \)
# Instead of \( -type -print \),而是选择需要的过滤器
```

\( -name ".git" -prune \)的作用是用于进行排除，它指明了 .git目录应该被排除在外，而\( -type f -print \)指明了需要执行的动作。这些动作需要被放置在第二个语句块中（打印出所有文件的名称和路径）。

```shell
#! /bin/bash
#文件名：cecho.sh
echo $*'#'

cat args.txt | xargs -I {} ./cecho.sh -p {} -l
-p arg1 -l #
-p arg2 -l #
-p arg3 -l #
```

#### 统计源代码目录中所有C程序文件的行数

```shell
find source_code_dir_path f -name "*.c" -print0 | xargs -0 wc -l
#-0 将\0作为输入定界符 
```

#### 结合stdin，巧妙运用while语句和子shell

xargs只能以有限的几种方式来提供参数，而且它也不能为多组命令提供参数。要执行包含来自标准输入的多个参数的命令，有一种非常灵活的方法。包含while循环的子shell可以用来读取参数，然后通过一种巧妙的方式执行命令

```shell
cat files.txt | (while read arg; do cat $arg; done )
#等同于 cat files.txt | xargs -I {} cat {}
```

### 用tr进行转换

tr只能通过stdin（标准输入），而无法通过命令行参数来接受输入。它的调用格式如下：	tr [options] set1 set2

如果两个字符集的长度不相等，那么set2会不断重复其最后一个字符，直到长度与set1相同。如果set2的长度大于set1，那么在set2中超出set1长度的那部分字符则全部被忽略。

#### ROT13加密算法

```shell
echo "tr came, tr saw, tr conquered." | tr 'a-zA-Z' 'n-za-mN-ZA-M'
```

```shell
echo hello 1 char 2 next 4 | tr -d -c '0-9 \n'
1 2 4
```

```shell
#用tr将文件中的数字列表进行相加
cat sum.txt
1
2
3
4
5

cat sum.txt | echo $[ $(tr '\n' '+' ) 0 ]
15
```

在上面的命令中，tr用来将'\n'替换成'+'，因此我们得到了字符串"1+2+3+…5+"，但是在字符串的尾部多了一个操作符+。为了抵消这个多出来的操作符，我们再追加一个0

#### 补充内容

```shell
echo "Hello 123 world 456" | tr -d '0-9' #将stdin中的数字删除并打印出来
tr -c [set1] [set2] #使用set1的补集
echo hello 1 char 2 next 4 | tr -d -c '0-9 \n' #将不在补集的字符全部删除
echo "GNU is     not    UNIX. Recursive   right ?" | tr -s ' '
#压缩空白字符
tr -s '[set]' #连续的重复字符应该压缩成单个字符
```

#### 字符类

tr可以像使用集合一样使用各种不同的字符类，这些字符类如下所示：
 alnum：字母和数字。
 alpha：字母。
 cntrl：控制（非打印）字符。
 digit：数字。
 graph：图形字符。
 lower：小写字母。
 print：可打印字符。
 punct：标点符号。
 space：空白字符。
 upper：大写字母。
 xdigit：十六进制字符。

可以按照下面的方式选择并使用所需的字符类：

```shell
tr [:class:] [:class:]
tr '[:lower:]' '[:upper:]'
```

## 校验和与核实

### md5sum 32个字符的十六进制串

```shell
md5sum filename > file_sum.md5
```

```
md5sum -c file_sum.md5
md5sum -c *.md5
```

```
md5deep -rl directory_path > directory.md5
```

```shell
find directory_path -type f -print0 | xargs -0 md5sum >> directory.md5
#对目录进行校验
```

### SHA-1 40个字符的十六进制串

```
sha1sum filename > file_sum.sha1
```

## 批量重命名和移动文件

```shell
#!/bin/bash
#filename: rename.sh
#desc: rename .jpg & .png

count=1;
for img in `find . -iname '*.png' -o -iname '*.jpg' -type f -maxdepth 1`
do
	new=image-$count.${img##*.}
	
	echo "renaming $img to $new"
	mv "$img" "$new"
	let count++
	
done
```

```shell
rename 's/ /_/g' *
#把文件名中的空格替换为字符'_'
```

## 拼写检查与词典操作

```shell
#!/bin/bash
#文件名: checkword.sh
word=$1
grep "^$1$" /usr/share/dict/british-english -q
if [ $? -eq 0 ]; then
echo $word is a dictionary word;
else
echo $word is not a dictionary word;
fi
```

在grep中，^ 标记着单词的开始，$ 标记着单词的结束。-q 禁止产生任何输出。

## 并行进程加速命令

```shell
#!/bin/bash
PIDARRAY=()
for file in File1.iso File2.so
do
	md5sum $file &
	PIDARRAY+=("$!")
done
wait ${PIDARRAY[@]}
```

我们利用了Bash的操作符&，它使得shell将命令置于后台并继续执行脚本。这意味着一旦循环结束，脚本就会退出，而md5sum命令仍在后台运行。为了避免这种情况，我们使用$!来获得进程的PID，在Bash中，$!保存着最近一个后台进程的PID。我们这些PID放入数组，然后使用wait命令等待这些进程结束。

## 文本文件的交集与差集

```shell
comm A.txt B.txt -3 | sed 's/^\t//'
#A,B 文件的求差
```

在生成统一输出时，sed命令通过管道获取comm的输出。它删除行首的 \t字符。sed中的s表示替换（substitute）。/^\t/ 匹配行前的 \t（^是行首标记）。//（两个/操作符之间没有任何字符）是用来替换行首的\t的字符串。如此一来，就删除了所有行首的\t。

## 查找并删除重复文件

```shell
# !/bin/bash
# 文件名: remove_duplicates.sh
# 用途: 查找并删除重复文件，每一个文件只保留一份
ls -lS --time-style=long-iso | awk 'BEGIN {
getline; getline;
name1=$8; size=$5
}
{
name2=$8;
if (size==$5)
{
"md5sum "name1 | getline; csum1=$1;
"md5sum "name2 | getline; csum2=$1;
if ( csum1==csum2 )
{
print name1; print name2
}
};
size=$5; name1=name2;
}' | sort -u > duplicate_files

cat duplicate_files | xargs -I {} md5sum {} | sort | uniq -w 32 | awk '{ print"^"$2"$" }' | sort -u > duplicate_sample
echo Removing..
comm duplicate_files duplicate_sample -2 -3 | tee /dev/stderr | xargs rm
echo Removed duplicates files successfully.
```

ls -lS对当前目录下的所有文件按照文件大小进行排序，并列出文件的详细信息。awk读取ls -lS的输出，对行列进行比较，找出重复文件。

我们将文件依据大小排序并列出，这样大小接近的文件就会排列在一起。识别大小相同的文件是我们查找重复文件的第一步。接下来，计算这些文件的校验和。如果校验和相同，那么这些文件就是重复文件，将被删除。

第1行输出告诉我们文件数量，这个信息在本例中没什么用处。我们用getline读取第1行，然后丢弃。由于需要对每一行及其下一行来比对文件大小，因此用getline读取长文件列表的第一行，并存储文件名和大小（它们分别是第8列和第5列）。这样我们就先得到了一行。接下来，awk进入{}语句块（在这个语句块中读取余下的文本行），读取到的每一行文本都会执行该语句块。它将当前行中读取到的文件大小与之前存储在变量size中的值进行比较。如果相等，那就意味着两个文件至少在大小上是相同的，随后再用md5sum执行进一步的检查。

在awk中，外部命令的输出可以用下面的方法读取：
"cmd"| getline
随后就可以在$0中获取命令的输出，在$1,$2,…$n中获取命令输出中的每一列。我们将文件的md5sum保存在变量csum1和csum2中。变量name1和name2保存文件列表中位置连续的文件名。如果两个文件的校验和相同，那它们肯定是重复文件，其文件名会被打印出来。
我们需要从每组重复文件中找出一个文件，这样就可以删除其他副本了。计算重复文件的md5sum，从每一组重复文件中打印出其中一个。这是通过-w 32比较每一行的md5sum（md5sum输出中的前32个字符，md5sum的输出通常由32个字符的散列值和文件名组成），然后找出那些不相同的行。这样，每组重复文件中的一个采样就被写入duplicate_sample。

现在需要将duplicate_files中列出的、且未包含在duplicate_sample之内的全部文件删除。这些文件由comm命令负责打印出来。我们可以使用差集操作来实现（参考3.3节）。

comm通常只接受排序过的文件。所以，在重定向到duplicate_files和duplicate_sample之前，首先用sort -u作为一个过滤器。
tee命令在这里有一个妙用：它在将文件名传递给rm命令的同时，也起到了print的作用。tee将来自stdin的行写入文件，同时将其发送到stdout。我们也可以将文本重定向到stderr来实现终端打印功能。/dev/stderr是对应于stderr（标准错误）的设备。通过重定向到stderr设备文件，来自stdin的文本将会以标准错误的形式出现在终端中。

## charttr 设置文件

```shell
chattr +i file
#文件设置为不可修改
```

## 文件统计信息

```shell
#! /bin/bash

if [ $# -ne 1];
then
	echo "Usage is $0 basepath";
	exit
fi
path=$1
declare -A statarray;
while read line;
do 
	ftype=`file -b "$line" | cut -d, -f1`
	let statarray["$ftype"]++;
done < < (find $path -type f -print)

echo ===============File types and counts ================
for ftype in "$(!statarray[@])";
do 
	echo $ftype : ${statarrat["$ftype"]}
done

```

在脚本中声明了一个关联数组statarray，这样可以用文件类型作为数组索引，将每种文件类型的数量存入数组。每次遇到一个文件类型，就用let增加计数。find命令以递归的方式获取文件路径列表。脚本中的ftype='file -b "$line"'使用file命令获得文件类型信息。选项-b告诉file命令只打印文件类型（不包括文件名）。输出的文件类型信息包含很多细节，比如图像编码以及分辨率（如果是图像文件的话）。对于这些细节我们并不感兴趣，我们只需要基本的信息就够了。各种细节信息是由逗号分隔的，例如：

$ file a.out -b
ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.15, not stripped

我们只需要从上面这些细节中提取ELF 32-bit LSB executable。因此我们使用cut -d,-f1，指明以逗号作为定界符，并且只打印第一个字段。

done<<(find $path –type f –print);是一段很重要的代码。它的执行逻辑如下：

while read line;
do something
done < filename

我们不用filename，而是用find命令的输出。

<(find $path -type f -print)等同于文件名。只不过它用子进程输出来代替文件名。注意，第一个<用于输入重定向，第二个<用于将子进程的输出装换成文件名。在两个<之间有一个空格，避免shell将其解释为<<操作符。

${!statarray[@]}用于返回一个数组索引列表。

## diff 生成目录的差异信息

```shell
diff -Naur directory1 directory2
```

-N: 将所有确实的文件视为空文件

-a: 将所有文件视为文本文件

-u：生成一体化输出

-r: 遍历目录下的所有文件

## tail 终端持续更新

```shell
tail -f growing_file
tail -f /var/log/messages
dmsg | tail -f
#假设我们正在读取一个不断增长的文件，进程Foo一直在向该文件追加数据，那么tail -f 就会一直执行到进程Foo结束
PID=$(pidof Foo)
tail -f file --pid $PID
```

我们经常会运行dmeg 查看内核的环形缓冲区消息，要么是调试USB设备，要么是查看sdX（X是对应于SCSI磁盘的sd设备的次序列号）。tail -f也可以加入一个睡眠间隔 -s，这样我们就可以设置监视文件更新的时间间隔。

## 正则表达式

```shell
#IP地址
[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}
```

[0-9]或[:digit:]匹配数字0~9。{1,3}匹配1到3个数字，\.匹配"."。

表 4-1：

| 正则表达式 | 描述                    | 示例                                       |
| :---: | :-------------------- | :--------------------------------------- |
|   -   | 行起始标记                 | -tux匹配以tux起始的行                           |
|   $   | 行尾标记                  | tux$ 匹配以tux结尾的行                          |
|   .   | 匹配任意一个字符              | hack.匹配hackl和hacki,但是不能匹配hackl2和hackil 它只能匹配单个字符 |
|  []   | 匹配包含在[字符]之中的任意一个字符    | coo[kl]匹配cook或cool                       |
|  [^]  | 匹配除[^字符]之外的任意一个字符     | 9[^01]匹配92，93，但是不能匹配colouur              |
|  [-]  | 匹配[]中指定外围内的任意一个字符     | [1-5]匹配1~5的任意一个数字                        |
|   ?   | 匹配之前的项1次或0次           | colou?r匹配color或colour,但是不能匹配colouur      |
|   +   | 匹配之前的项1次或多次           | Rollno-9+匹配Rollno-99.Rollno-9,但是不能匹配Rollno- |
|   *   | 匹配之前的项0次或多次           | co*l 匹配cl,col,coool等                     |
|  ()   | 创建一个用于匹配的子串           | ma(tri)?x匹配max或maxtrix                   |
|  {n}  | 匹配之前的项n次              | [0-9]{3} 匹配任意一个三位数，[0-9]{3}可以扩展为[0-9][0-9][0-9] |
| {n,}  | 之前的项至少需要匹配n 次         | [0-9]{2,}匹配任意一个两位数或更多位的数字                |
| {n,m} | 指定之前的项所必需匹配的最小次数和最大次数 | [0-9]{2,5}匹配两位数到五位数之间的任意一个字数             |
|  \|   | 交替---匹配\|两边的任意一项      | Oct {1st \| 2nd} 匹配Oct 1st或Oct 2nd       |
|      | 转义符可以将上面介绍的特殊字符进行转义   | a .b 匹配a.b,但不能匹配ajb。通过在.之前加上前缀\，从而忽略了.的特殊意义 |

grep命令只解释match_text中的某些特殊字符。如果要使用正则表达式，需要添加-E选项——这意味着使用扩展（extended）正则表达式。或者也可以使用默认允许正则表达式的grep命令——egrep

```shell
grep -l linux sample1.txt sample2.txt
```

和-l相反的选项是-L，它会返回一个不匹配的文件列表。

```shell
grep "test_function()" . -R -n
```

这是开发人员使用最多的命令之一。它用于查找某些文本位于哪些源码文件中。

## cut 按列切分文件

```shell
cat student_data.txt
NO	Name	Mark Percent
1	Sarath	45	90
2	Alex	49	98
3	Anu		45	90
cut -f3 --complement student_data.txt
```

## 使用sed进行文本替换

```shell
sed 's/pattern/replace_string/' file
#打印的同时替换结果应用于原文件
sed -i 's/text/replace/' file
sed -i 's/pattern/replace_string/g' file
#后缀/g意味着sed会替换每一处匹配。但是有时候我们只需要从第n处匹配开始替换。对此，可以使用/Ng选项
#已匹配字符串标记(&)
echo this is an example | sed 's/\w\+/[&]/g'
#正则表达式\w\+匹配每一个单词，然后我们用[&]替换它。
echo seven EIGHT | sed 's/\([a-z]\+\) \([A-Z]\+\)/\2 \1/'
```

([a-z]\+\)匹配第一个单词，([A-Z]\+\)匹配第二个单词。\1和\2用来引用它们。这种引用被称为向后引用（back reference）。在替换部分，它们的次序被更改为\2 \1，因此结果就呈现出逆序的形式。



## awk命令编程

### 特殊变量

- NR: 表示记录数量，在执行过程中对应当前行号  
- NF:表示字段数量，在执行过程中对应当前行的字段数
- $0:这个变量包含执行过程中当前行的文本内容
- $1:这个变量包含第一个字段的文本内容
- $2:这个变量包含第二个字段的文本内容

### awk内建的字符串控制函数

- length(string): 返回字符串的长度
- index(string,  search_string):返回search_string在字符串出现的位置
- split(string, array, delimiter):用定界符生成一个字符串列表，并将该列表存入数组
- substr(string, start-position, end-position): 在字符串中用字符起止偏移量生成子串，并返回该子串
- sub(regex, replacement_str, string): 将正则表达式匹配到第一处内容替换成replacment_str.
- gsub(regex,replacement_str, string): 和sub()类似。不过该函数会替换正则表达式匹配到的所有内容
- match(regex, string): 检查正则表达式是否能够匹配字符串。如果能够匹配,返回非0值；否则，返回0.math()有两个相关的特殊变量，分别是RSTART和RLENGTH.变量RSTART包含正则表达式所匹配内容的起始位置，而变量RLENGTH包含正则表达式所匹配内容的长度

## 统计特定文件中的词频

```shell
#!/bin/bash
#用途：计算文件中单词的词频

if [ $# -ne 1 ];
then
	echo "Usage: $0 filename";
	exit -1
fi

filename=$1

egrep -o "\b[[:alpha:]]+\b" $filename | \

awk '{ count[$0]++ }
END{ printf("%-14s%s\n","Word","Count") ;
for(ind in count)
{ printf("%-14s%d\n",ind,count[ind]); }
}'

```

egrep -o "\b[[:alpha:]]+\b" $filename只用于输出单词。用 -o选项打印出由换行符分隔的匹配字符序列。这样我们就可以在每行中列出一个单词。

\b 是单词边界标记符。[:alpha:] 是表示字母的字符类。awk命令用来避免对每一个单词进行迭代。因为awk默认会逐行执行{}块中的语句，所以我们就不需要再为同样的事编写循环了。借助关联数组，当执行count[$0]++时，单词计数就增加。最后，在END{}语句块中通过迭代所有的单词，就可以打印出单词及它们各自出现的次数。

## 压缩或解压缩JavaScript

```javascript
#filename: sample.js
function sign_out()
{
  $("#loading").show();
  $.get("log_in",{logout:"True"}),
    function(){
  		window.location="";
	});
}
```

下面是压缩JavaScript所需要完成的工作：
(1) 移除换行符和制表符；
(2) 压缩空格；
(3) 替换注释 /*内容*/。
要解压缩或者恢复JavaScript的可读性，我们则需要：
 用 ;\n 替换;；
 用 {\n 替换 {，\n} 替换}。

压缩

```shell
cat sample.js | \
tr -d '\n\t' | tr -s ' ' \
| sed 's:/\*.*\*/::g' \
| sed 's/ \?\([{}();,:]\) \?/\1/g'
```

解压缩

```shell
cat obfuscated.txt | sed 's/;/;\n/g; s/{/{\n\n/g; s/}/\n\n}/g'
#或者
cat obfuscated.txt | sed 's/;/;\n/g' | sed 's/{/\n\n/g' | sed 's/}/\n\n}/g'
```

该脚本在使用上存在局限：它会删除本不该删除的空格。假如有下列语句：
var a = "hello world"
两个空格会被转换成一个。这种问题可以使用我们讲解过的模式匹配工具
来解决。如果需要处理关键JavaScript代码，最好还是使用功能完善的工具
来实现。

通过执行下面的步骤来进行压缩。
(1) 移除 '\n' 和 '\t'：
tr -d '\n\t'
(2) 移除多余的空格：
tr -s ' '或者sed 's/[ ]\+/ /g'
(3) 移除注释：
sed 's:/\*.*\*/::g'
因为我们需要使用 /* 和 */，所以用:作为sed的定界符，这样就不必对 / 进行转义了。

*在 sed 中被转义为 \\*。
.* 用来匹配 /* 与 */ 之间所有的文本。

(4) 移除{、}、(、)、;、:以及,前后的空格。
sed 's/ \?\([{}();,:]\) \?/\1/g'
上面的sed语句含义如下。
 sed代码中的 / \?\([{ }();,:]\) \?/ 用于匹配，/\1/g 用于替换。
 \([{ }();,:]\) 用于匹配集合 [ { }( ) ; , : ]（出于可读性方面的考虑，
在这里加入了空格）中的任意一个字符。\(和\)是分组操作符，用于记忆所匹配的内容，以便在替换部分中进行向后引用。对(和)转义之后，它们便具备了另一种特殊的含义，进而可以将它们作为分组操作符。位于分组操作符前后的 \? 用来匹配可能出现在字符集合前后的空格。

 在命令的替换部分，匹配字符串（也就是一个可选的空格、一个来自字符集的字符再加一个可选的空格）被匹配的子字符串所替换。对于匹配的子字符串使用了向后引用，并通过分组操作符()记录了匹配内容。可以用符号 \1向后引用分组所匹配的内容。

解压缩命令工作方式如下：

 s/;/;\n/g 将;替换为;\n；
 s/{/{\n\n/g 将 { 替换为 {\n\n；
 s/}/\n\n}/g 将 } 替换为 \n\n}。

## 以逆序形式打印行

```shell
seq 9 | \
awk '{ lifo[NR]=$0 }
END{ for(lno=NR;lno>-1;lno--){ print lifo[lno]; }
}'
```

这个awk脚本非常简单。我们将每一行都存入一个关联数组中，用行号作为数组索引（行号由NR给出），最后由awk执行END语句块。为了得到最后一行的行号，在{ }语句块中使用lno=NR。因此，这个脚本从最后一行一直迭代到第0行，将存储在数组中的各行以逆序方式打印出来。

## 解析文本中的电子邮件地址和URL

```shell
egrep -o '[A-Za-z0-9._]+@[A-Za-z0-9.]+\.[a-zA-Z]{2,4}' 1.txt
#email
```

```shell
egrep -o "http://[a-zA-Z0-9.]+\.[a-zA-Z]{2,3}" 1.txt
#URL
```

## 在文件中移除包含某个单词的句子

```shell
sed 's/ [^.]*mobile phones[^.]\.//g' 1.txt
```

## 列出网络上所有的活动主机

```shell
#!/bin/bash
#desc:根据网络配置对网络地址192.168.0进行修改

for ip in 192.168.0.{1..255};
do 
	ping $ip -c 2 &> /dev/null;
	if [ $? -eq 0 ];
	then
		echo $ip is alive
	fi
done
```

## 计算一个小时内CPU的占用情况

```shell
#!/bin/bash
SECS=3600
UNIT_TIME=60
#将SECS更改成需要进行监视的总秒数
#UNIT_TIME是取样的时间间隔，单位是秒
STEPS=$(( $SECS / $UNIT_TIME ))
echo Watching CPU usage...
for((i=0;i<STEPS;i++))
do
	ps -eocomm,pcpu | tail -n +2 >> /tmp/cpu_usage.$$
	sleep $UNIT_TIME
done
echo
echo CPU eaters :

cat /tmp/cpu_usage.$$ | \
awk '
{ process[$1]+=$2; }
END{
	for(i in process)
	{
		printf("%-20s %s\n",i,process[i]);
	}
	
		}' | sort -nrk 2 | head
		
	rm /tmp/cpu_usage.$$
```

在上面的脚本中，主要的输入源是ps -eo comm,pcpu，其中comm表示命令名（command name），pcpu表示CPU使用率（CUP usage in percent）。该命令输出所有进程名及CPU使用率。每个进程对应一行输出。因为需要监视一小时内CPU的使用情况，所以我们得在一个每次迭代时间为60秒的for循环中不停地用ps -eo comm,pcpu | tail -n +2来获取CPU的使用统计数据，并将这些数据添加到文件 /tmp/cpu_usage.$$ 中。60秒的迭代时间通过sleep 60来提供。这就使得每分钟执行一次ps。tail -n +2用来将 ps 输出中的头部和 COMMAND %CPU剥除。
cpu_usage.$$ 中的 $$ 表示当前脚本的进程 ID。假设进程 ID为1345，那么在脚本执行时它会被替换成 /tmp/cpu_usage.1345。因为这是一个临时文件，所以我们把它放在 /tmp中。统计文件在1小时后就准备妥当了，文件中包含了60项，分别对应每分钟的进程状态。然后用awk求出每个进程总的CPU使用情况。我们用了一个关联数组来统计CPU使用情况。其中进程名作为数组索引。最后根据总的CPU使用情况依数值逆序排序，并通过head获得前10项。

## 用logrotate管理日志文件

logrotate的配置目录位于/etc/logrotate.d。如果列出这个目录中的内容，你会发现很多其他的日志文件配置。

```shell
#我们可以为自己的日志文件(such as /var/log/program.log)编写一个特定的配置：
cat /etc/logrotate.d/program
/var/log/program.log {
  missingok
  notifempty
  size 30k
  	compress
  weekly
  	rotate 5
  create 0600 root root
}
```

|          参数           |                    描述                    |
| :-------------------: | :--------------------------------------: |
|       missingok       |      如果日志文件丢失，则忽略；然后返回(不对日志文件进行轮替)       |
|      notifempty       |            仅当源日志文件非空时才对其进行轮替             |
|       size 30k        |        限制实施轮替的日志文件的大小。可以用1M表示1MB         |
|       compress        |              允许用gzip压缩较旧的日志              |
|        weekly         |    指定进行轮替的时间间隔。可以是weekly，yearly或daily    |
|       rotate 5        | 这是需要保留的旧日志文件的归档数量。在这里指定的是5，所以这些文件名将会是program.log1gz、program.log2.gz等知道program.log5.gz |
| create 0600 root root |          指定所要创建的归档文件的模式，用户以及用户组          |

## 通过监视用户登录找出入侵者

我们可以编写一个shell脚本，对日志文件进行扫描并从中收集所需要的信息。为了处理SSH登录失败的情况，还得知道用户认证会话日志会被记录在日志文件/var/log/auth.log中。脚本需要扫描这个日志文件来检测出失败的登录信息，执行各种检查来获取所需要的数据。我们可以用host命令找出IP地址所对应的主机。

```shell
#!/bin/shell
#文件名：intruder_detect.sh
#用途：入侵报告工具，以auth.log作为日志文件
AUTHLOG= /var/log/auth.log

if	[[ -n $1 ]];
then
	AUTHLOG=$1
	echo Using log file : $AUTHLOG
fi

LOG=/tmp/valid.$$.log
grep -V "invalid" $AUTHLOG > $LOG
users=$(grep "Failed password" $LOG | awk '{ print $(NF-5) }' | sort | uniq)
printf "%-5s|%-10s|%-10s|%-13s|%-33s|%s\n" "Sr#" "User" "Attempts" "IP address" "Host_Mapping" "Time range"

ucount=0;

ip_list="$(egrep -o "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" $LOG | sort |uniq)"
for ip in $ip_list;
do
	grep $ip $LOG > /tmp/temp.$$.log
for user in $users;
do
	grep $user /tmp/temp.$$.log> /tmp/$$.log
	cut -c-16 /tmp/$$.log >$$.time
	tstart=$(head -l $$.time);
	start=$(date -d "$tstart" "+%s");
	tend=$(tail -l $$.time);
	end=$(date -d "$tend" "+%s")
	
	limit=$(( $end - $start ))
	
	if [ $limit -gt 120 ];
	then
		let ucount++;
		
		IP=$(egrep -o "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" /tmp/$$.log | head -1 );
		TIME_RANGE="$tstart-->$tend"
		ATTEMPTS=$(cat /tmp/$$.log|wc-1);
		HOST=$(host $IP | awk '{ print $NF }')
		
	printf "%-5s|%-10s|%-10s|%-10s|%-33s|%-s\n" "$ucount" "$user" "$ATTEMPTS" "$IP" "$HOST" "$TIME_RANGE";
	fi
done
done

rm /tmp/vaild.$$.log/tmp/$$.log $$.time/tmp/temp.$$.log 2>/dev/null

		
```

在intruder_detect.sh脚本中，我们将auth.log文件作为输入。也可以用脚本的命令行参数来提供一个日志文件作为输入，或者默认读取/var/log/auth.log。我们只需要记录合法用户的登录日志详情。如果有非法用户企图登录，则类似Failed password for invalid user bob from203.83. 248.32 port 7016 ssh2的日志就会出现在auth.log中。因此我们需要排除日志文件中所有包含invalid的行。grep命令的反转选项（-v）可以用来移除对应非法用户的所有日志内容。下一步是找出试图登录并且失败的用户列表。对于密码错误，SSH会记录类似的日志信息：sshd[21197]: Failed password for bob1 from 203.83.248.32 port 50035 ssh2，所以我们应找出所有包含“failed password”的行。

接下来，要找出所有不重复的IP地址以提取对应于每一个IP地址的日志行。提取IP地址列表可以用匹配IP地址的正则表达式和egrep命令来完成。用for循环对IP地址进行迭代，并用grep找出对应的日志行并将其写入临时文件。日志行中倒数第6个单词是用户名（例如bob1），可用awk命令提取用户名（倒数第6个单词）。NF返回最后一个单词的列号，因此NF -5就是倒数第6个单词的列号。我们再用sort和uniq生成一个没有重复的用户列表。

现在我们要收集表明登录失败的日志行，这些行中包含了用户名。for循环用来读取对应每一位用户的日志行，并将这些行写入临时文件。每一行的前16个字符是时间戳，可用cut命令进行提取。一旦得到了一个用户所有登录失败的时间戳，就要检查第一次和最后一次试图登录之间的时间差。第一行日志对应第一次登录，最后一行日志对应最后一次登录。我们用head -1提取首行，用tail -1提取末行。这样就有了首次登录（tstart）和末次登录（tends）的字符串格式的时间戳。使用date命令，我们可以将字符串形式的日期转换成Unix纪元时的总秒数（1.10节讲解了Unix纪元时）。

变量start和end中包含着秒数，分别对应于字符串形式的起始时间戳。对这两个时间求差，并检查差值是否大于2分钟（即120秒）。如果某个用户被确认为入侵者，其对应的细节信息就要生成日志。IP地址可以用正则表达式和egrep命令从日志中提取。试图登录的次数就是含有某个用户的日志行数。这个行数可以用wc命令获得。IP地址到主机名的映射可以将IP地址作为host命令的参数，然后从命令输出中提取。时间范围可以用已经提取到的时间戳来打印。最后，删除脚本使用过的临时文件。

上节的脚本旨在演示一个用于扫描日志并从中生成报告的模型。我们尽力让脚本更短小简单，以避免过于复杂，因此难免存在一些bug。你可以使用更好的处理逻辑来改进该脚本。

## 监视远程磁盘的健康情况

我们需要从网络中收集每台主机的磁盘使用情况信息，然后写入中央主机的日志文件中。可以将负责收集信息并写入日志的脚本调度为每天的特定时间执行。可以使用SSH来登录远程系统收集磁盘使用情况。

首先得在网络中的所有远程主机上设置一个共用账户。这个账户供脚本disklog登录系统使用。我们需要为这个账户配置SSH自动登录（7.8节讲解了自动登录的配置方法）。假设在所有配置了自动登录的远程主机上都有一个叫做test的用户，那么来看看这个shell脚本：

```shell
#!/bin/bash
#文件名：disklog.sh
#desc:jianshi 远程系统的磁盘使用情况

logfile="diskusage.log"

if [[ -n $1 ]]
then
	logfile=$1
fi

if [ ! -e $logfile ]
then
	printf "%-8s %-14s %-9s %-8s %-6s %-6s %-6s %s\n" "Date" "IP address" "Device" "Capacity" "Used" "Free" "Percent" "Status" > $logfile
fi

IP_LIST="127.0.0.1 0.0.0.0"
#提供远程主机IP地址列表

(
for ip in $IP_LIST;
do
	#slynux是用户名
	ssh slynux@$ip 'df -H' | grep ^/dev/ > /tmp/$$.df
	while read line;
	do
		cur_date=$(date +%D)
		printf "%-8s %-14s " $cur_date $ip
		echo $line | awk '{ printf("%-9s %-8s %-6s %-6s %-8s",$1,$2,$3,$4,$5); }'
		
		pusg=$(echo $line | egrep -o "[0-9]+%")
		pusg=$(pusg/\%/);
		if [ $pusg -lt 80 ];
		then
			echo SAFE
		else
			echo ALERT
		fi
		
		done< /tmp/$$.df
	done
) >> $logfile
```

我们可以用cron以固定的间隔来调度脚本执行，例如在crontab中写入以下条目，就可以在每天上午10点运行该脚本：

```shell
00 10 * * *  /home/path/disklog.sh  /home/user/diskusg.log
```

执行命令crontab -e，然后添加上面一行。也可以手动执行脚本

在脚本disklog.sh中，我们可以提供日志文件路径作为命令行参数，否则脚本使用默认的日志文件。如果日志文件不存在，它会将日志文件头部写入新文件中。-e logfile用来检查文件是否存在。远程主机的IP地址列表被存储在变量IP_LIST中，彼此之间以空格分隔。要确保在IP_LIST中列出的所有远程系统中都有用户test，并且SSH已经配置了自动登录。for循环用来对IP地址进行逐个迭代。通过ssh使用远程命令df -H获取磁盘剩余空间。这项数据被存储在一个临时文件中。while循环用来逐行读取这个文件。利用awk提取并打印数据，同时一并打印的还有日期。用egrep提取使用率，并将%删除以获取使用率的数值部分。检查得到的数值，看是否超过了80。如果不足80，将状态设置为SAFT；如果大于或等于80，则将状态设置为ALERT。打印出来的所有数据要被重定向到日志文件中。因此代码被放入子shell()中，并将标准输出重定向到日志文件。

## 找出系统中用户的活跃时段

考虑一个使用共享主机的Web服务器。每天都会有很多用户登录和注销，用户活动都被记入了服务器的系统日志。这则攻略是一项实践任务：利用系统日志找出每个用户在服务器上停留了多久，并根据其时间长短来进行分级，最后生成一份包含等级、用户名、首次登录时间、末次登录时间、登录次数以及总使用时长等细节信息的报告。让我们看看如何解决这个问题。

last命令用来列出系统中有关用户登录会话的细节。这些会话数据被存储在/var/log/wtmp文件中。通过分别累计各用户的会话时间，就能得出他们的总使用时间。

```shell
#!/bin/bash
#desc:查找活跃用户
log=/var/log/wtmp

if [[ -n $1 ]];
then
	log=$1;
fi

printf "%-4s %-10s %-10s %-6s %-8s\n" "Rank" "User" "Start" "Logins" "Usage hours"
last -f $log | head -n -2 > /tmp/ulog.$$
cat /tmp/ulog.$$ | cut -d' ' -fi | sort | uniq> /tmp/users.$$

(
while read user;
do
	grep ^$user /tmp/ulog.$$ > /tmp/user.$$
	minutes=0
	
	while read t
	do
		s=$(echo $t | awk -F: '{ print ($1 * 60) + $2 }')
		let minutes=minutes+s
	done< <(cat /tmp/user.$$ | awk '{ print $NF }' | tr -d ')(')
	firstlog=$(tail -n 1 /tmp/user.$$ | awk '{ print $5,$6 }')
	nlogins=$(cat /tmp/user.$$ | wc -l)
	hours=$(echo "$minutes / 60.0" | bc)
	printf "%-10s %-10s %-6s %-8s\n" $user "$firstlog" $nlogins $hours done< /tmp/user.$$
	
) | sort -nrk 4 | awk '{ printf("%-4s %s\n",NR, $0) }'
rm /tmp/users.$$ /tmp/user.$$ /tmp/ulog.$$
```

在脚本active_users.sh中，需要提供日志文件作为命令行参数，否则就使用默认的日志文件wtmp。命令last -f用来打印日志文件的内容。日志文件的第一列是用户名。我们用cut从中提取第一列，然后用sort和uniq找出不重复的用户。对于每一位用户，用grep找出其对应登录会话的日志行并写入一个临时文件。日志的最后一列是用户登录会话的时长。为了找出用户总的使用时间，需要累加所有的会话时长。使用时间的格式是（小时：秒），需要用一个简单的awk脚本将其转换成分钟。
要提取用户的会话时长，得使用awk命令。要移除括号，得使用tr -d。用<( COMMANDS )操作符将使用时长字符串列表作为标准输入传递给while循环，其作用就相当于文件输入。利用date命令将每一个时长字符串转换成秒数，并累加到变量seconds中。把出现在最后一行的用户的首次登录时间提取出来。登录次数就是日志的行数。要根据总的使用时间来计算每位用户的等级，数据记录以使用时长为键，进行降序排列。用sort命令的-nr选项指定按照数值逆序排列。-k4指定键的列号（即使用时长）。最后，sort的输出被传递给awk。awk命令为每一行添加上行号，这个行号就是每一位用户的等级。

## 检查磁盘及文件系统错误

要检查分区或文件系统的错误，只需要将路径作为fsck的参数：

```shell
fsck /dev/sdbs
```

检查/etc/fstab中所配置的所有文件系统：

```
fsck -A
```

指定fsck自动修复错误，无需询问是否进行修复：

```
fsck -a /dev/sda2
```

模拟fsck要执行的操作：

```
fsck -AN
```

## 收集进程信息

ps -e  -f  (e,every;f,full显示多列 )

选项-o可以使用不同的参数

|  参数   |     描述     |
| :---: | :--------: |
| pcpu  |   CPU占用率   |
|  pid  |    进程ID    |
| ppid  |   父进程ID    |
| pmem  |   内存使用率    |
| comm  |   可执行文件名   |
|  cmd  |    简单命令    |
| user  |  启动进程的用户   |
| nice  |    优先级     |
| time  |  累计的CPU时间  |
| etime | 进程启动后流逝的时间 |
|  tty  | 所关联的TTY设备  |
| euid  |   有效用户ID   |
| stat  |    进程状态    |

```shell
ps -eo comm,pcpu | head
```

top对于系统管理员来说是一个极为重要的命令。它默认会输出一个占用CPU最多的进程列表。输出结果每隔几秒就会更新。

## 杀死进程以及发送或响应信号

列出所有可用的信号  kill -l

终止进程：kill PROCESS_ID_LIST

kill命令默认发出一个TERM信号。进程ID列表使用空格作为进程ID之间的定界符。

要通过kill命令向进程发送指定的信号，可以使用：kill -s SIGNAL PID 经常使用的有：

- SIGHUP 1	对控制进程或终端的终结进行挂起检测。
- SIGINT 2         当按下Ctrl + C 时发送该信号 
- SIGKILL 9         用于强行杀死进程
- SIGTERM 15        默认用于终止进程
- SIGTSTP 20         当按下Ctrl + Z时发送该信号

当我们要强行杀死一个程序时，可以使用

```shell
kill -s SIGKILL PROCESS_ID
kill -9 PROCESS_ID
killall process_name #通过命令名终止进程
killall -s SIGNAL process_name #通过名称向进程发送信号
killall -9 process_name #通过名称强行杀死进程
```

## 能够响应信号SIGINT 的shell脚本

```shell
#!/bin/bash

function handler()
{
  echo Hey, received signal : SIGINT
}

echo My process ID is $$
#$$是一个特殊的变量，它可以返回当前进程/脚本的进程的ID
trap 'handler' SIGINT
#handler是信号SIGINT的信号处理程序的名称

while true；
do
	sleep 1
done
```

## 向用户终端发送消息

向终端中所有的当前登录用户发送广播消息：

```shell
cat message | wall 
wall< message
```

向指定用户的终端发送消息的脚本

```shell
#!/bin/bash

USERNAME=$1

devices=`ls /dev/pts/* -l | awk '{ print $3,$10 }' | grep $USERNAME | awk '{ print $2 }'`
for dev in $devices;
do
	cat /dev/stdin > $dev
done
```

运行脚本：

```shell
./message_user.sh USERNAME < message.txt
#通过stdin传递消息，USERNAME作为参数
```

## 用cron进行调度

cron利用的是一个叫做cron表的文件，这个文件中存储了需要执行的脚本或命令的调度列表以及执行时间。一个常见的用法是设置在免费时段（一些ISP提供免费使用时间，通常是在午夜），从Internet上进行下载。用户完全不需要在夜里熬红双眼等待下载。只需要编写一个cron条目，然后调度下载即可。你也可以安排当免费时段结束后自动断开Internet连接并关机。

```shell
#每天每小时第二分钟执行脚本
02 * * * * /home/slynux/test.sh
#每天第5，6，7小时执行脚本
00 5,6,7 * * /home/slynux/test.sh
#在每周日的每个小时执行脚本
00 */12 * * 0 /home/slynux/script.sh
#在每天凌晨2点关闭计算机
00 02 * * * * /sbin/shutdown -h
#调度cron作业
crontab -e
#输入crontab -e 后，会打开默认的文本编辑器供用户输入cron作业并保存。该cron作业将会在指定的时间被调度执行
#创建一个文本文件，并写入cron作业，将文件名最为参数命令，运行crontab
crontab task.cron
#在行内(inline)指定cron作业，而无需创建单独的文件。例如：
crontab<<EOF
02 * * * * /home/slynux/script.sh
EOF
```

cron表中的每一个条目都由6部分组成，并按照下列顺序排列：

- 分钟(0-59)
- 小时(0-23)
- 天(1-31)
- 月份(1-12)
- 工作日(0-6)
- 命令

如果你希望在某个特定时段执行命令，那么就在对应的时间字段中指定时段，并用逗号分隔（例如要在5分钟和10分钟时运行命令，那就在分钟字段中输入"5,10"）。在分钟字段使用*/5，可以每5分钟运行一次命令。这个技巧可以用在任何时间字段。

要在启动时运行命令，请将下面一行加入crontab：
@reboot command





