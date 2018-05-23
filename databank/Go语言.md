[TOC]

# Go语言

## 初识Go语言

### 语言特性

Go语言最主要的特性： 

- 自动垃圾回收
- 更丰富的内置类型
- 函数多返回值
- 错误处理
- 匿名函数和闭包
- 类型和接口
- 并发编程
- 反射
- 语言交互性


### 第一个Go程序

```go
package main
import "fmt"  //我们需要使用fmt包中的Println()函数
func main(){
  fmt.Println("Hello,world.")
}
```

#### 代码解读

每个Go源代码文件的开头都是一个package声明，表示该Go代码所属的包。包是Go语言里最基本的分发单位，也是工程管理中依赖关系的体现。要生成Go可执行程序，必须建立一个名字为main的包，并且在该包中包含一个叫main()的函数（该函数是Go可执行程序的执行起点） 

Go语言的main()函数不能带参数，也不能定义返回值。命令行传入的参数在os.Args变量中保存。如果需要支持命令行开关，可使用flag包。

在包声明之后，是一系列的import语句，用于导入该程序所依赖的包。由于本示例程序用到了Println()函数，所以需要导入该函数所属的fmt包。有一点需要注意，不得包含在源代码文件中没有用到的包，否则Go编译器会报编译错误。这与下面提到的强制左花括号{的放置位置以及之后会提到的函数名的大小写规则，均体现了Go语言在语言层面解决软件工程问题的设计哲学。

所有Go函数（包括在对象编程中会提到的类型成员函数）以关键字func开头。一个常规的函数定义包含以下部分：

```go
func 函数名(参数列表)(返回值列表){
  //函数体
}
//对应的实例如下:
func Compute(value1 int, value2 float64)(result float64, err error){
  //函数体
}
//Go支持多个返回值，以上的示例函数Compute()返回了两个值，一个叫result，另一个err.并不是所有返回值都必须赋值。在函数返回时没有被明确赋值的返回值都会被设置为默认值，比如result会被设为0.0， err会被设为nil。
```

#### 编译程序

假设之前介绍的hello,world代码被保存为了hello.go,并位于~/goyard目录下，那么可以用以下命令直接运行该程序

```shell
cd ~/goyard
go run hello.go  #直接运行
#使用这个命令，会将编译、链接和运行3个步骤合并为一步，运行完后在当前目录下也看不到任何中间文件和最终的可执行文件。如果要只生成编译结果而不自动运行，我们也可以使用 Go命令行工具的build命令
cd ~/goyard
go build hello.go
./hello
#从根本上说， Go命令行工具只是一个源代码管理工具，或者说是一个前端。真正的Go编译器和链接器被Go命令行工具隐藏在后面，我们可以直接使用它们：
6g	helloworld.go
6l	helloworld.6
./6.out
#6g和6l是64位版本的GO编译器和连接器，对应32位版本工具为8g和8l.
```

#### 工程管理

在实际的开发工作中，直接调用编译器进行编译和链接的场景是少而又少，因为在工程中不会简单到只有一个源代码文件，且源文件之间会有相互的依赖关系。如果这样一个文件一个文件逐步编译，那不亚于一场灾难。 Go语言的设计者作为行业老将，自然不会忽略这一点。早期Go语言使用makefile作为临时方案，到了Go 1发布时引入了强大无比的Go命令行工具。

Go命令行工具的革命性之处在于彻底消除了工程文件的概念，完全用目录结构和包名来推导工程结构和构建顺序。 

为了能够构建这个工程，需要先把这个工程的根目录加入到环境变量GOPATH中。假设calcproj目录位于~/goyard下，则应编辑~/.bashrc文件，并添加下面这行代码：

```shell
export GOPATH=-/goyard/calcproj
#然后执行以下命令应用该设置
source ~/.bashrc
#GOPATH和PATH环境变量一样，也可以接受多个路径，并且路径和路径之间用冒号分割
#设置完GOPATH后，现在我们开始构建工程。假设我们希望把生成的可执行文件放到calcproj/bin目录中，需要执行的一系列指令如下：
cd ~/goyard/calcproj
mkdir bin
cd bin
go build calc
#顺利的话，将在该目录下发现生成的一个叫做calc的可执行文件，执行该文件以查看帮助信息并进行算术运算：
#从上面的构建过程中可以看到，真正的构建命令就一句 go build calc
#另外，我们在写simplemath包时，为每一个关键的函数编写了对应的单元测试代码，分别位于add_test.go和sqrt_test.go中。那么我们到底怎么运行这些单元测试呢？这也非常简单。因为已经设置了GOPATH，所以可以在任意目录下执行以下命令：
go test simplemath
```

### 问题追踪和调试

#### 打印日志

Go语言包中包含一个fmt包，其中提供了大量易用的打印函数，我们会接触到的主要是Printf()和Println()。这两个函数可以满足我们的基本调试需求，比如临时打印某个变量。 

#### GDB调试

不用设置什么编译选项，Go语言编译的二进制程序直接支持GDB调试，比如之前用go build calc编译出来的可执行文件calc，就可以直接用以下命令以调试模式运行： 

gdb calc

## 顺序编程

### 变量

#### 变量声明

Go语言的变量声明方式与C和C++语言有明显的不同。对于纯粹的变量声明， Go语言引入了关键字var，而类型信息放在变量名之后，示例如下： 

```go
var v1 int
var v2 string 
var v3 [10]int   //数组
var v4 []int    //数组切片
var v5 struct {
  f int
}
var v6 *int   
var v7 map[string]int //map,key为string类型，value为int
var v8 func(a int) int 
//var关键字的另一种用法是可以将若干个需要声明的变量放置在一起，免得程序员需要重复写var关键字，如下所示：
var (
	v1 int 
  	v2 string
)
```

#### 变量初始化

对于声明变量时需要进行初始化的场景， var关键字可以保留，但不再是必要的元素，如下所示： 

```go
var v1 int = 10 
var v2 = 10
v3 := 10
//这里Go语言也引入了另一个C和C++中没有的符号（冒号和等号的组合:=），用于明确表达同时进行变量声明和初始化的工作
//出现在:=左侧的变量不应该是已经被声明过的，否则会导致编译错误
```

#### 变量赋值

在Go语法中，变量初始化和变量赋值是两个不同的概念。下面为声明一个变量之后的赋值过程：

```go
var v10 int 
v10 = 123
```

Go语言的变量赋值与多数语言一致，但Go语言中提供了C/C++程序员期盼多年的多重赋值功能，比如下面这个交换i和j变量的语句：

```go
i,j = j,i
```

#### 匿名变量

我们在使用传统的强类型语言编程时，经常会出现这种情况，即在调用函数时为了获取一个值，却因为该函数返回多个值而不得不定义一堆没用的变量。在Go中这种情况可以通过结合使用多重返回和匿名变量来避免这种丑陋的写法，让代码看起来更加优雅。

```go
//假 设 GetName() 函 数 的 定 义 如 下 ， 它 返 回 3 个 值 ， 分 别 为firstName 、 lastName 和nickName：
func GetName() (firstName,lastName,nickName string){
  return "May","Chan","Chibi Maruko"
}
//若只想获得nickName，则函数调用语句可以用如下方式编写：
_,_,nickName := GetName()
```

### 常量

在Go语言中，常量是指编译期间就已知且不可改变的值。常量可以是数值类型（包括整型、浮点型和复数类型）、布尔类型、字符串类型等。 

#### 字面常量

所谓字面常量（literal），是指程序中硬编码的常量。在其他语言中，常量通常有特定的类型，比如-12在C语言中会认为是一个int类型的常量。如果要指定一个值为-12的long类型常量，需要写成-12l，这有点违反人们的直观感觉。 Go语言的字面常量更接近我们自然语言中的常量概念，它是无类型的。只要这个常量在相应类型的值域范围内，就可以作为该类型的常量，比如上面的常量-12，它可以赋值给int、 uint、 int32、int64、 float32、 float64、 complex64、 complex128等类型的变量。

#### 常量定义

通过const关键字，你可以给字面常量指定一个友好的名字：

```go
const Pi float64 = 3.14159265358979323846
const zero = 0.0	//无类型浮点常量
const (
	size int64 = 1024
  	eof = -1
)
const u,v float32 = 0,3   //u =0.0,v=3.0,常量的多重赋值
const a,b,c = 3,4,"foo"
```

Go的常量定义可以限定常量类型，但不是必需的。如果定义常量时没有指定类型，那么它与字面常量一样，是无类型常量。 

常量定义的右值也可以是一个在编译期运算的常量表达式,比如：

```go
const mask = 1 << 3
```

由于常量的赋值是一个编译期行为，所以右值不能出现任何需要运行期才能得出结果的表达式 

#### 预定义常量

Go语言预定义了这些常量： true、 false和iota。

iota比较特殊，可以被认为是一个可被编译器修改的常量，在每一个const关键字出现时被重置为0，然后在下一个const出现之前，每出现一次iota，其所代表的数字会自动增1。

```go
//从下面的例子来理解iota
const (
	a = iota	//a == 0
  	b = iota	//b == 1
  	c = iota	//c == 2
 )

const (
	a = 1<<iota	//a ==1
  	b = 1<<iota	//b == 2
  	c = 1<<iota //C == 4
)

cosnt x = iota	// x ==0
cosnt y = iota 	// y ==0
//如果li两个const的赋值语句的表达式是一样的，那么可以省略后一个赋值表达式。因此上面老公const语句可简写为：
const (
	a = iota	//a == 0
  	b			//b == 1
  	c			//c	== 2
)

const (
	a = 1<<iota		//a == 1
  	b				//b == 2
  	c				//c == 4
)
```

####  枚举

枚举指一系列相关的常量，比如下面关于一个星期中每天的定义。通过上一节的例子，我们看到可以用在const后跟一对圆括号的方式定义一组常量，这种定义枚举值。GO不支持众多其他语言支持的enum关键字

```go
//下面是一个常规的枚举表示法，其中定义了一系列整型常量:
const (
	Sunday = iota
  	Monday
  	Tuesday
  	Wednesday
  	Thursday
  	Friday
  	Saturday
  	numberofDays	//这个常量没有导出
)
//同go语言的其他符号(symbol)一样，以大写字母开头的常量在包外可见。以上例子中numberofDays 为包内私有，其他符号则可被其他包访问。
```

### 类型

Go语言内置一下这些基础类型：

- 布尔类型: bool
- 整型: int8,byte,int16,int,uint,uintptr
- 浮点类型:float32,float64
- 复数类型: complex64,complex128
- 字符串：string
- 字符类型：rune
- 错误类型：error

此外，Go语言也支持以下这些复合类型：

- 指针(pointer)
- 数组(array)
- 切片(slice)
- 字典(map)
- 通道(chan)
- 结构体(struct)
- 接口(interface)

#### 浮点数比较

因为浮点数不是一种精确的表达方式，所以像整型那样直接用==来判断两个浮点数是否相等是不可行的，这可能会导致不稳定的结果。

```go
//浮点数比较(下面是一种推荐的替代方案)
import "math"

// p为用户自定义的比较精度，比如0.00001
func IsEqual(f1,f2,p float64) bool{
  return math.Fdim(f1,f2) < p
}
```

#### 复数类型

复数实际上由两个实数(在计算机中用浮点数表示)构成，一个表示实部(real),一个表示虚部(imag)。

##### 复数表示

```go
//复数表示的示例如下
var value1 complex64	//由两个float32构成的复数类型

value1 = 3.2 + 12i
value2 := 3.2 + 12i		//value2是complex128类型
value3 := complex(3.2, 12)	//value3结果同 value2
```

##### 实部与虚部

对于一个复数z = complex(x,y),就可以通过Go语言内置函数real(z)获得该复数的实部，也就是x，通过imag(z)获得该复数的虚部，也就是y

#### 数组

数组是Go语言编程中最常用的数据结构之一。顾名思义，数组就是指一系列同一类型数据的集合。数组中包含的每个数据被称为数组元素（element），一个数组包含的元素个数被称为数组的长度。

```go
//以下为一些常规的数组声明方法
[32]byte	//长度为32的数组，每个元素为一个字节
[2*N]struct{ x, y int32 } //复杂类型数组
[1000]*float64	//指针数组
[3][5]int		//二维数组
[2][2][2]float64	//等同于[2]([2]([2]float64))
```

#####  元素访问

```go
//获取数组arr元素个数
arrLength := len(arr)
//元素访问，数组下标从0开始，len(array)-1是表示最后一个元素的下标
for i := 0;i < len(array); i++{
  fmt.Println("Element",i,"of array is",array[i])
}
//GO语言还有一个关键字range,用于便捷地遍历容器中的元素。
for i,v := range array{
  fmt.Println("Array element[",i,"]=",v)
}
//range具有两个返回值，第一个返回值是元素的数组下标，第二个返回值是元素的值。
```

##### 值类型

需要特别注意的是，在go语言中数组是一个值类型(value type).所有的值类型变量在赋值和作为参数传递时都将产生一次复制动作。如果将数组作为函数的参数类型，则在函数调用时该参数将发生数据复制。因此，在函数体中无法修改传入的数组的内容，因此函数内操作的只是所传入数组的一个副本。

```go
//下面用一个例子来说明这一特点
package main
import "fmt"
func modify(array [10]int){
  array[0] = 10		//试图修改数组的第一个元素
  fmt.Println("In modify(),array values:",array)
}

func main(){
  array := [5]int{1,2,3,4,5}	//定义初始化数组
  modify(array)		//传递给一个函数，并试图在函数体内修改这个数组内容
  fmt.Println("In main(),array values:",array)
}

//该程序的执行结果：
In modify(),array values: [10 2 3 4 5]
In main(),array values:[1 2 3 4 5]
```

#### 数组切片(slice)

我们已经提过数组的特点：数组的长度在定义之后无法再次修改；数组是值类型，每次传递都将产生一份副本。显然这种数据结构无法完全满足开发者的真实需求。

初看起来，数组切片就像一个指向数组的指针，实际上它拥有自己的数据结构，而不仅仅是个指针。数组切片的数据结构可以抽象为以下3个变量：

- 一个指向原生数组的指针；
- 数组切片中的元素个数；
- 数组切片已分配的存储空间

##### 创建数组切片

创建数组切片的方法主要有两种——基于数组和直接创建

- 基于数组

数组切片可以基于一个已存在的数组创建。数组切片可以只使用数组的一部分元素或者整个数组来创建，甚至可以创建一个比所基于的数组还要大的数组切片。

```go
package main
import "fmt"
func main() {
  //先定义一个数组
  var myArray [10]int = [10]int{1,2,3,4,5,6,7,8,9,10}
  //基于数组创建一个数组切片
  var mySlice []int = myArray[:5]
  fmt.Println("Elements of myArray: ")
  for _, v := range myArray{
  		fmt.Print(v," ")
  }
  
  fmt.Println("\nElements of mySlice: ")
  for _, v := range mySlice {
  		fmt.Print(v," ")
  }
  fmt.Println()
}
//运行结果：
Elements of myArray:
1 2 3 4 5 6 7 8 9 10
Elements of mySlice:
1 2 3 4 5
//Go语言支持用myArray[first:last]这样的方式来基于数组生成一个数组切片，而且这个用法还很灵活，比如下面几种都是合法的
//基于myArray的所有火元素创建数组切片:
mySlice = myArray[:]
//基于myArray的前5个元素创建数组切片:
mySlice = myArray[:5]
//基于从第5个元素开始的所有元素创建数组切片：
mySlice = myArray[5:]
```

- 直接创建

并非一定要事先准备一个数组才能创建数组切片。Go语言提供的内置函数make()可以用于灵活地创建数组切片。

```go
//创建一个初始元素个数为5的数组切片，元素初始值为0，
mySlice1 := make([]int,5)
//创建一个初始元素个数为5的数组切片，元素初始值为0，并预留10个元素的存储空间：
mySlice2 := make([]int,5,10)
//直接创建并初始化包含5个元素的数组切片：
mySlice3 := []int{1,2,3,4,5}
```

##### 元素遍历

操作数组元素的所有方法都适用于数组切片，比如数组切片也可以按下标读写元素，用len()函数获取元素个数，并支持使用range关键字来快速遍历所有元素。

##### 动态增减元素

可动态增减元素是数组切片比数组更为强大的功能。与数组相比，数组切片多了一个存储能力（capacity）的概念，即元素个数和分配的空间可以是两个不同的值。合理地设置存储能力的值，可以大幅降低数组切片内部重新分配内存和搬送内存块的频率，从而大大提高程序性能。

数组切片支持Go语言内置的cap()函数和len()函数，可以看出， cap()函数返回的是数组切片分配的空间大小，而len()函数返回的是数组切片中当前所存储的元素个数。

```go
package main
import "fmt"
func main() {
  mySlice := make([]int, 5, 10)
  
  fmt.Println("len(mySlice):", len(mySlice))
  fmt.Println("cap(mySlice):", cap(mySlice))
}

//len(mySlice):5
//len(mySlice):10
//如果需要向上例mySlice已包含的5个元素后面继续新增元素，可以使用append()函数。从下面的代码可以从尾端给mySlice加上3个元素，从而生成一个新的数组切片：
mySlice = append(mySlice, 1, 2, 3)
//函数append()的第二个参数其实是一个不定参数，我们可以按自己需求添加若干个元素，甚至直接将一个数组切片追加到另一个数组切片的末尾
mySlice2 := []int{8, 9, 10}
//给mySlice后面添加一个数组切片
mySlice = append(mySlice,mySlice2...)
//需要注意的是，我们在第二个参数mySlice2后面加了三个点，即一个省略号，如果没有这个省略号的话，会有编译错误，因为按append()的语义，从第二个参数起的所有参数都是待附加的元素。因为mySlice中的元素类型为int，所以直接传递mySlice2是行不通的。加上省略号相当于把mySlice2包含的所有元素打散后传入。
```

##### 基于数组切片创建数组切片

```go
oldSlice := []int{1, 2, 3, 4, 5}
newSlice := oldSlice[:3] //基于oldSlice的前3个元素构建新数组切片
```

有意思的是，选择的oldSlicef元素范围甚至可以超过所包含的元素个数，比如newSlice可以基于oldSlice的前6个元素创建，虽然oldSlice只包含5个元素。只要这个选择的范围不超过oldSlice存储能力（即cap()返回的值），那么这个创建程序就是合法的。 newSlice中超出oldSlice元素的部分都会填上0。

##### 内容复制

数组切片支持Go语言的另一个内置函数copy()，用于将内容从一个数组切片复制到另一个数组切片。如果加入的两个数组切片不一样大，就会按其中较小的那个数组切片的元素个数进行复制。下面的示例展示了copy()函数的行为：

```go
slice1 := []int{1, 2, 3, 4, 5}
slice2 := []int{5, 4, 3}

copy(slice2, slice1) //只复制slice1的前3个元素到slice2中
copy(slice1, slice2) //只复制slice2的前3个元素到slice1的前3个位置
```

#### map

map是一堆键值对的未排序集合.

```go
//以身份证号作为唯一键来标识一个人的信息
package main
import "fmt"
//PersonInfo是一个包含个人详细信息的类型
type PersonInfo struct {
  ID string
  Name string
  Address string
}

func main(){
  var PersonDB map[string] PersonInfo
  	  PersonDB = make(map[string] PersonInfo)
  //往这个map里插入几条数据
  PersonDB["12345"] = PersonInfo{"12345","Tom","Room 203,..."}
  PersonDB["1"] = PersonInfo{"1","Jack","Room 101,..."}
  //从这个map查找键为"1234"的信息
  person, ok := PersonDB["1234"]
  //ok是一个返回bool型，返回true表示找到了对应的数据
  if ok {
  		fmt.Println("Found person",person.Name,"with ID 1234.")
  } else {
  		fmt.Println("Did not find person with ID 1234.")
  }
}
```

##### 创建

```go
//变量声明
var myMap map[string] PersonInfo
//创建
myMap = make(map[string] PersonInfo)
//也可以选择是否在创建时指定该map的初始存储能力，下面的例子创建了一个初始存储能力为100的map
myMap = make(map[string] PersonInfo, 100)
//创建并初始化
myMap = map[string] PersonInfo{
  "1234": PersonInfo{"1","Jack","Room 101,..."}
}
//元素赋值
myMap["1234"] = PersonInfo{"1","Jack","Room 101,..."}
//元素删除 GO语言内置函数delete(),用于删除容器内的元素
delete(myMap,"1234")
//上面的代码将从myMap中删除键为“1234”的键值对。如果“1234”这个键不存在，那么这个调用将什么都不发生，也不会有什么副作用。但是如果传入的map变量的值是nil，该调用将导致程序抛出异常（panic）。
//元素查找，在map中查找一个特定的键
value, ok := myMap["1234"]
if ok{//找到了
  //处理找到的value
}

```

### 流程控制

Go语言支持如下的几种流程控制语句

- 条件语句： if ,else 和else if;
- 选择语句：switch, case 和select
- 循环语句：for range
- 跳转语句：goto

在具体的应用场景中，为了满足更丰富的控制需求，Go语言还添加如下关键字：break,continue和fallthrough

#### 条件语句

```c
if a < 5 {
  return 0
}else{
  return 1
}
```

关于条件语句，需要注意以下几点

- 条件语句不需要使用括号将条件语句包含起来();
- 无论语句体内有几条语句，华括号必须存在
- 左花括号必须和if 或者else在同一行
- 在if之后，条件语句之前，可以添加变量初始化语句，使用；间隔
- 在有返回值的函数中，不允许将“最终的”return语句包含在if...else...结构中，否则会编译失败，失败的原因是因为Go编译器无法找到终止函数的return语句，失败案例如下：

```go
func example(x int) int {
  if x==0 {
  	return 5
  }else {
  	return x
  }
}
```

#### 选择语句

```go
switch i {
  case 0:
  	fmt.Printf("0")
  case 1:
  	fmt.Printf("1")
  case 2:
  	fallthrough
  case 3:
  	fmt.Printf("3")
  case 4, 5, 6:
  	fmt.Printf("4, 5, 6")
  default:
  	fmt.Printf("Default")
}

/*运行上面的案例，会得到如下结果：
i = 0,输出 0；i = 1,输出 1； i =2 时，输出3；i = 3时，输出3；
i = 4，输出 4，5，6 ； i = 5，输出4，5，6；i =6时，输出4，5，6；i=其他任意值，输出Default.*/
//switch 后面的表达式不是必需的
```

在使用switch结构时，我们需要注意以下几点

- 左花括号必需和switch处于同一行
- 条件表达式不限制是常量或者整数
- 单个case中，可以出现多个结果选项
- Go 语言不用break来明确退出一个case
- 只有case中明确添加fallthrough关键字，才会继续执行紧跟下一个case
- 可以不设定switch之后的条件表达式，在此种情况下，整个switch结构与多个if...else...的逻辑作用等同

#### 循环语句

Go语言中的循环语句只支持for关键字

```go
sum := 0
for i := 0;i < 10; i++ {
  	sum += i
}
//for后面的条件表达式不需要用圆括号包含起来。
//Go语言的无限循环
sum := 0
for {
  sum++
  if sum > 100{
  		break
  }
}
//在条件表达式中也支持多重赋值
a := []int{1, 2, 3, 4, 5, 6}
for i, j := 0, len(a)-1; i<j;i, j = i+1, j-1 {
  	a[i],a[j] = a[j],a[i]
}
//数组切片的逆序
```

使用循环语句时，需要注意的有以下几点：

- 左花括号必须与for处于同一行
- Go语言中的for循环与C语言一样，都允许在循环条件中定义和初始化变量，唯一的区别是，Go语言不支持以逗号为间隔的多个赋值语句，必须使用平行赋值的方式来初始化多个变量
- Go语言的for 循环支持continue和break来控制循环，但它的break可以选择中断哪一个循环

```go
for j := 0; j < 5; j++ {
  for i := 0; i < 10; i++ {
  	if i > 5 {
  		break JLoop
	}
  fmt.Println(i)
  }
}
JLoop:
//...
//break语句终止的是JLoop标签处的外层循环
```

#### 跳转语句

```go
func myfunc() {
  i := 0
  HERE:
  fmt.Println(i)
  i++
  if i < 10 {
  	goto HERE
  }
}
```

### 函数

函数构成代码执行的逻辑结构。在GO语言中，函数的基本组成为：关键字func,函数名，参数列表，返回值，函数体和返回语句。

#### 函数定义

```go
//一个简单的加法函数
package mymath
import "errors"

func Add(a int, b int) (ret int, err error) {
	if a < 0 || b < 0 {	//假设这个函数只支持两个非负数字的加法
  		err = errors.New("Should be non-negative numbers!")			return
	}
  
  	return a + b, nil //支持多重返回值
}
//如果参数列表中若干相邻的参数类型的相同，可以将参数列表中省略前面变量的类型声明
func Add(a, b int)(ret int, err error)
//如果只有一个返回值，可以用
func Add(a, b int) int
```

#### 函数调用

函数调用非常方便，只要事先导入该函数所在的包，就可以直接按照如下所示的方式调用函数：

```go
import "mymath" // 假设Add被放在一个叫mymath的包中
//...
c := mymath.Add(1, 2)
```

函数调用的规则：小写字母开头的函数只在本包内可见，大写字母开头的函数才能被其他包使用。

这个规则也适用于类型和变量的可见性

#### 不定参数

##### 不定参数类型

不定参数是指函数传入参数个数为不定数量。为了做到这点，首先需要将函数定义为接受不定参数类型：

```go
func myfunc(args ...int) {
  for _, arg := range args {
  	fmt.Println(arg)
  }  	
}
//这段代码是函数myfunc()接受不定数量参数，这些参数的类型全部是int
myfunc(2, 3, 4)
myfunc(1, 3, 7, 13)
```

形如...type格式的类型只能作为函数的参数类型存在，并且必须是最后一个参数。它是一个语法糖（syntactic sugar），即这种语法对语言的功能并没有影响，但是更方便程序员使用。通常来说，使用语法糖能够增加程序的可读性，从而减少程序出错的机会。

##### 不定参数的传递

假设有另一个变参函数叫做myfunc3(args ...int),下面的例子演示了如何向其传递变参：

```go
func myfunc(args ...int) {
  //按原样传递
  myfunc3(args...)
  //传递片段，实际上任意的int slice都可以传进去
  myfunc3(args[1:]...)
}
```

##### 任意类型的不定参数

之前的例子中将不定参数类型约束为int,如果你希望传任意类型，可以指定类型为interface{ }。下面是Go语言标准库中fmt.Printf( )的函数原型：

```go
func Printf(format string, args  ...interface{}) {
  //...
}
```

##### 多返回值

Go语言的函数或者成员的方法可以有多个返回值， 比如File.Read()函数就可以同时返回读取的字节数和错误信息。如果读取文件成功，则返回值中的n为读取字节数，err为nil，否则err为具体的出错信息

```go
func (file *File) Read(b []byte)(n int, err Error)
```

同样，从上面的方法原型可以看到，我们还可以给返回值命名，就像函数的输入参数一样。返回值被命名之后，它们的值在函数开始的时候就被自动初始化为空。在函数中执行不带任何参数的return语句时，会返回对应的返回值变量的值。

如果调用方调用了一个具有多返回值的方法，但是却不想关心其中的某个返回值，可以简单地用一个下划线"_"来跳过这个返回值，比如下面的代码表示调用者在读文件的时候不想关心Read( )函数返回的错误码：

n, _ := f.Read(buf)

##### 匿名函数与闭包

匿名函数是只不需要定义函数名的一种函数实现方式

1.匿名函数

在Go里面，函数可以像普通变量一样被传递或使用，这与C语言的回调函数比较类似，不同的是，GO语言支持随时在代码里定义匿名函数。

匿名函数由一个不带函数名的函数声明和函数体组成，如下所示：

```go
func(a, b int, z float64) bool {
  	return a*b < int(z)
}
//匿名函数可以直接赋值给一个变量或直接执行：
f := func(x, y int) int {
  	return x + y
}
func(ch chan int) {
  	ch <- ACK
} (reply_chan)	//花括号后直接跟参数列表表示函数调用 
```

2.闭包

Go的匿名函数是一个闭包，下面我们先来了解一下闭包的概念，价值和应用场景。

- 基本概念

闭包是可以包含自由(未绑定到特定对象)变量的代码块,这些变量不在这个代码块内或者任何全局上下文中定义，而是在定义代码块的环境中定义。要执行的代码块(由于自由变量包含在代码块中，所以这些自由变量以及它们引用的对象没有被释放)为自由变量提供绑定的计算环境(作用域)。

- 闭包的价值

闭包的价值在于可以作为函数对象或者匿名函数，对于类型系统而言，这意味着不仅要表示数据还要表示代码。支持闭包的多数语言都将函数作为第一级对象，就是说这些函数可以存储到变量中作为参数传递给其他函数，最重要的是被函数动态创建和返回。

- Go语言中的闭包

Go语言中的闭包同样也会引用到函数外的变量。闭包的实现确保只要闭包还被使用，那么被闭包引用的变量会一直存在。

```go
package main
import(
	"fmt"
)
func main() {
  var j int = 5
  a := func()(func()) {
  	var i int = 10
    return func() {
      fmt.Printf("i, j: %d, %d\n",i, j)
	}
  }()
  a()
  j *= 2
  a()
}
//i, j: 10, 5
//i, j: 10, 10
```

在变量a指向闭包函数中，只有内部的匿名函数才能访问变量i，而无法通过其他途径访问到，保证了i 的安全性

#### 错误处理

##### error接口

Go语言引入了一个关于错误处理的标准模式，即erro接口，该接口的定义如下：

```go
type error interface {
  Error() string
}
//对于大多数函数，返回错误的模式
func Foo(param int)(n int, err error){
  //....
}
//调用的代码的出错情况处理
n, err := Foo(0)
if err != nil {
  	//错误处理
}else {
  	//使用返回值n 
}
```

```go
//Go库中的实际代码来示范如何使用自定义的error类型
type PathError struct {
  Op string
  Path string
  Err error
}
//编译器如何做到PathError可以当做一个error来传递
func (e *PathError) Error() string {
  return e.op + " " + e.Path + ": " + e.Err.Error()
}
//之后直接返回PathError变量了，比如在下面的代码中，当syscall.Stat()失败返回err时，将该err报装到一个PathError对象中返回:
func Stat(name string) (fi FileInfo, err error) {
  var stat syscall.Stat_t
  err = syscall.Stat(name, &stat)
  if err != nil {
  	return nil, &PathError{"stat",name, err}
  }
  return fileInfoFromStat(&stat, name), nil
}
//如果在处理错误时获取详细信息，而不仅仅满足域打印一句错误信息，那就要用到类型转换的知识了：
fi, err := os.Stat("a.txt")

if err != nil {
  if e, ok := err.(*os.PathError); ok && e.Err != nil {
  	// 获取PathError类型变量e中的其他信息处理
  }
}
```

##### defer 

关键字defer是Go语言引入的一个非常有意思的特性

```c++
//下面是一段c++代码
class file_closer {
  FILE _f;
public:
  file_closer(FILE f) : _f(f) {}
  ~file_closer() { if (f) fclose(f); }
};
//然后再需要使用的地方这么写：
void f() {
  FILE f = open_file("file.txt");
  file_closer _closer(f);
}
```

为什么需要file_closer这么个包装类呢？因为如果没有这个类，代码中所有退出函数的环节，比如每一个可能抛出异常的地方，每一个return的位置，都需要关掉之前打开的文件句柄。

开发者可以将需要释放的资源变量都声明在函数的开头部分，并在函数的末尾部分统一释放资源。函数需要退出时，就必须使用goto语句跳转到指定位置先完成资源清理工作，而不能调用return语句直接返回

```go
//在go语言中我们使用defer
func CopyFile(dst, src string) (w int64, err error) {
  srcFile, err := os.Open(src)
  if err != nil {
  	return
  }
  defer srcFile.Close()
  dstFile, err := os.Create(dstName)
  if err != nil {
  	return
  }
  defer dstFile.Close()
  
  return io.Copy(dstFile,srcFile)
}
//即使其中的Copy()函数抛出异常，Go仍然会保证dstFile和srcFile会被正常关闭，如果觉得一处化干不完清理的工作，也可以使用在deferh后加一个匿名函数的做法：
defer func(){
  //清理工作
} ()
```

一个函数可以存在多个defer语句，因此需要注意的是，defer语句的调用是遵照先进后出的原则，即最后一个defer语句将被最先执行。

##### panic()和recover()

Go语言引入两个内置函数panic()和recover()来报告和处理运行时错误和程序中的错误场景:

```go
func panic(interface{})
func recover() interface{}
```

当在一个函数执行过程中调用panic()函数时，正常的函数执行流程将立即终止，但函数中之前使用defer关键字延迟执行的语句将正常展开执行，之后该函数将返回到调用函数，并导致逐层向上执行panic流程，直至所属的goroutine中所有正在执行的函数被终止。错误信息将被报告，包括在调用panic()函数时传入的参数，这个过程称为错误处理流程。

从panic()的参数类型interface{}我们可以得知，该函数接收任意类型的数据，比如整型、字符串、对象等。调用方法很简单，下面为几个例子：

```go
panic(404)
panic("network broken")
panic(Error("file not exists"))
```

recover( )函数用于终止错误处理流程。一般情况下，recover( )应该在一个使用defer关键字的函数中执行以有效截取错误处理流程，如果没有在发生异常的goroutine中明确调用恢复过程(使用recover关键字)，会导致该goroutine所属的进程打印异常信息后直接退出。

```go
//一个常见的场景
//我们对于foo()函数的执行可能会触发错误处理，或资金在其中加入了特定条件的错误处理，那么可以用如下方式在调用代码中截取recover():
defer func() {
  if r := recover(); r != nil {
    log.Printf("Runtime error caught: %v", r)
  }
}()
foo()
```

无论foo( )中是否触发了错误处理流程，该匿名defer函数都将在函数退出时得到执行。假如foo( )中触发了错误处理流程，recover( )函数执行将使得该错误处理过程终止。如果错误处理流程被触发时，程序传给panic函数的参数不为nil，则该函数还会打印详细的错误信息

## 面向对象编程

### 类型系统(type system) 

类型系统是指一个语言的类型体系结构。一个典型的类型系统通常包含如下基本内容：

- 基础类型，如byte,int ,bool,float
- 复合类型，如数组，结构体，指针等
- 可以指向任意对象的类型(Any类型)
- 值语义和引用语义
- 面向对象，即所有具备面向对象特征(比如成员方法)的类型
- 接口

类型系统描述的是这些内容在一个语言中如何被关联

Go语言中的大多数类型都是值语义，并且都可以包含对应的操作方法。在需要的时候，你可以给任何类型（包括内置类型）“增加”新方法。而在实现某个接口时，无需从该接口继承（事实上， Go语言根本就不支持面向对象思想中的继承语法），只需要实现该接口要求的所有方法即可。任何类型都可以被Any类型引用。Any类型就是空接口，即interface{}。

#### 未类型添加方法

在Go语言中，你可以给任意类型(包括内置类型，但不包括指针类型)添加相应的方法

```go
type Integer int
func (a Integer) Less(b Integer) bool {
  	return a < b
}
//在这个例子中，我们定义了一个新类型Integer,它和int没有本质不同，只是它为内置的int类型增加了个新方法Less()。
//这样实现了Integer后，就可以让整型像一个普通的类一样使用：
func main() {
  var a Integer = 1
  if a.Less(2) {
  		fmt.Println(a, "Less 2")
  }
}
```

Go语言中的面向对象最为直观，也无需支付额外的成本。如果要求对象必须以指针传递，这有时会是个额外成本，因为对象有时很小（比如4字节），用指针传递并不划算。只有在你需要修改对象的时候，才必须用指针。它不是Go语言的约束，而是一种自然约束。举个例子

```go
func (a *Integer) Add(b Integer) {
	*a += b
}
//这里为Interger类型增加了Add( )方法。由于Add( )方法需要修改对象的值，所以需要用指针引用。调用如下：
func main() {
  var a Integer = 1
  a.Add(2)
  		fmt.Println("a =", a)
}
//运行该程序，a=3.如果传入的是值而不是指针
func (a Interger) Add(b Interger) {
   a += b
}
//a=1
```

究其原因，是因为Go语言和C语言一样，类型都是基于值传递的。要想修改变量的值，只能传递指针。

#### 值语义和引用语义

值语义和引用语义的差别在于赋值，比如下面的例子：

```go
b = a
b.Modify()
```

如果修改b不会影响a的值，那么此类型属于值类型。如果影响a的值，那么是引用类型

Go语言中的大多数类型都基于值语义，包括：

- 基本类型，如byte,int,bool,float32,float64和string
- 复合类型，如数组(array),结构体(struct)和指针(pointer)等


Go语言有4个类型比较特别，看起来像引用类型

- 数组切片:指向数组(array) 的一个区间
- map:及其常见的数组结构，提供键值查询能力
- channel: 执行体(goroutine)间的通信设施
- 接口(interface): 对一组满足某个契约的类型的抽象

但是这并不影响我们将Go语言类型看做值语义。下面我们来看看这4个类型。

```go
//数组切片本质上是一个区别，你可以大致将[]T表示为：
type slice struct {
  first *T
  len int
  cap int
}
//因为数组切片内部是指向数组的指针，所以可以改变锁指向的数组元素。数组切片本身的赋值仍然是值语义。
//map本质上是一个字典指针，你可以大致将map[K]V表示为：
type Map_K_V struct {
  	// ...
}
type map[K]V struct {
  	impl *Map_K_V
}
//基于指针，我们完全可以自定义一个引用类型，如：
type IntegerRef struct {
	impl *int
}
//channel和map类似，本质上是一个指针。将它们设计为引用类型而不是统一的值类型的原因是，完整赋值一个channel或map并不是常规需求
//接口的引用语义，是因为内部维持了两个指针
type interface struct {
  	data *void
  	itab *Itab
}
```

#### 结构体

Go语言的结构体(struct)和其他语言的类(class)有同等地位，但Go语言放弃了包括继承在内的大量面向对象特性，只保留了组合(composition)这个最基础的特性。组合只是形成复合类型的基础。

面我们说到，所有的Go语言类型（指针类型除外）都可以有自己的方法。在这个背景下，Go语言的结构体只是很普通的复合类型，平淡无奇。例如，我们要定义一个矩形类型：

```go
type Rect struct {
  x,y float64
  width, height float64
}
//然后我们定义成员方法Area()来计算矩形的面积：
func (r *Rec) Area() float64 {
  	return r.width * r.height
}
```

```go
//初始化,定义完Rect类型后，该如何创建并初始化Rect
rect1 := new(Rect)
rect2 := &Rect{}
rect3 := &Rect{0, 0, 100, 200}
rect4 := &Rect{width: 100, height: 200}
//在Go语言中，未进行显示初始化的变量都会被初始化为该类型的零值，bool的零值为flase,int类型的零值为0,string类型的零值为空字符串
```

```go
//在GO语言中没有构造函数的概念，对象的创建通常交由一个全局的创建函数来完成，以NewXXX来命名，表示为""构造函数"
func NewRect(x,y,width,height float64) *Rect {
 		return &Rect{x, y, width,height}
}
```

##### 匿名组合

确切的说，Go语言也提供了继承，但是采用了组合的文法，所以我们将其称为匿名组合：

```go
type Base struct {
  Name string
}

func (base *Base) Foo() { ... }
func (base *Base) Bar() { ... }
type Foo struct {
  Base
  ...
}

func (foo *Foo) Bar() {
  foo.Base.Bar()
  ...
}
```

以上代码定义了一个Base类（实现了Foo()和Bar()两个成员方法），然后定义了一个Foo类，该类从Base类“继承”并改写了Bar()方法（该方法实现时先调用了基类的Bar()方法）

在“派生类” Foo没有改写“基类” Base的成员方法时，相应的方法就被“继承”，例如在上面的例子中，调用foo.Foo()和调用foo.Base.Foo()效果一致。

与其他语言不同， Go语言很清晰地告诉你类的内存布局是怎样的。此外，在Go语言中你还可以随心所欲地修改内存布局，如

```go
type Foo struct {
   ... //其他成员
   Base
}
//这段代码从语义上来说，和上面给的例子并无不同，但内存布局发生了改变。“基类” Base的数据放在了“派生类” Foo的最后。
//另外，在Go语言中，你还可以以指针方式从一个类型“派生”：
type Foo struct {
  	*Base
  	...
}
//这段Go代码任然有""派生"的效果，只是Foo创建实例的时候，需要外部提供一个Base类实例的指针
```

在Go语言官方网站提供的Effective Go中曾提到匿名组合的一个小价值，值得在这里再提一下。首先我们可以定义如下的类型，它匿名组合了一个log.Logger指针：

```go
type Job struct {
  Command string 
  *log.Logger
}
//在合适的赋值后，我们在job类的所有成员方法都可以很舒适的使用所有log.Logger提供的方法
func (job *Job)Start() {
  job.Log("starting now...")
  ....//做一些事情
  job.Log("started.")
}
//需要注意的是不管是非匿名的类型组合还是匿名组合，被组合的类型所包含的方法虽然都升级成了外部这个组合类型的方法，但其实它们被组合方法调用时接收者并没有改变。比如上面的例子，即使调用的方式变成了job.Log(...)，但Log函数的接受者仍然是log.Logger这个指针，在Log中我们访问不了job的其他成员方法和变量
```

另外，我们必须关注一下接口组合中的名字冲突问题，比如如下的组合： 

```go
type X struct {
  Name string
}
type Y struct {
  X
  Name string
}
//组合的类型和被组合的类型都包含一个Name成员。会不会有问题呢，答案是否定的，所有Y类型的Name成员的访问都只会访问到最外层的Name变量，X.Name变量相当于被隐藏起来了
//另一种情况
type Logger struct {
  Level int
}
type Y struct {
  *Logger
  Name string
  *log.Logger
}
//显然这里会有问题，因为之前提到，匿名组合类型相当于以其类型名称(去掉包名部分)作为成员变量的名字，按此规则，Y类型中就相当于存在两个名为Logger的成员，虽然类型不同，因此我们会收到编译报错
```

##### 可见性

Go语言对关键字的增加非常吝啬，其中没有private、 protected、 public这样的关键字。要使某个符号对其他包（package）可见（即可以访问），需要将该符号定义为以大写字母开头，如：

```go
type Rect struct {
  x, y float64
  Width, Height float64
}
//这样， Rect类型的成员变量就全部被导出了，可以被所有其他引用了Rect所在包的代码访问到
//成员方法的可访问性遵循同样的规则，例如
func (r *Rect) area() float64 {
   return r.Width * r.Height
}
```

### 接口

接口在Go语言有着至关重要的地位。如果说goroutine和channel 是支撑起Go语言的并发模型的基石，让Go语言在如今集群化与多核化的时代成为一道极为亮丽的风景，那么接口是Go语言整个类型系统的基石，让Go语言在基础编程哲学的探索上达到前所未有的高度。

#### 其他语言的接口

在Go语言出现之前，接口主要作为不同组件之间的契约存在。对契约的实现是强制的，你必须声明你的确实现了该接口。为了实现一个接口，你需要从该接口继承：

```c++
//c++的接口
interface IFoo {
  void Bar();
}

class Foo : public IFoo {
  //....
}

IFoo* foo = new Foo;
```

即使另外有一个接口IFoo2实现了与IFoo完全一样的接口方法甚至名字也叫IFoo只不过位于不同的名字空间下，编译器也会认为上面的类Foo只实现了IFoo而没有实现IFoo2接口。

这类接口我们称为侵入式接口。“侵入式”的主要表现在于实现类需要明确声明自己实现了某个接口。这种强制性的接口继承是面向对象编程思想发展过程中一个遭受相当多置疑的特性。我们接下来讨论一下为什么这是个问题，以及为何Go语言的接口设计是一个更合适的选择。

设想我们现在要实现一个简单搜索引擎（SE），它需要依赖两个模块，一个是哈希表（HT），一个是HTML分析器（HtmlParser）。

搜索引擎的实现者认为， SE对HT的依赖是确定性的，所以不需要在SE和HT之间定义接口，而是直接通过import（或者include）的方式使用HT；而模块SE对HtmlParser的依赖是不确定的，未来可能需要有WordParser、 PdfParser等模块来替代HtmlParser，以达到不同的业务要求。为此，他定义了SE和HtmlParser之间的接口，在模块SE中通过接口调用方式间接引用模块HtmlParser。

应当注意到，接口的需求方是SE，只有SE才知道接口应该定义成什么样子，但是接口的实现方是HtmlParser。基于模块设计的单向依赖原则，模块HtmlParser实现自身的业务时，不应该关心某个具体使用方的要求。 HtmlParser在实现的时候，甚至还不知道未来有一天SE会用上它。

期望模块HtmlParser能够知道需求方需要的所有接口，并提前声明实现这些接口是不合理的。同样的道理发生在SE自己身上。 SE并不能够预计未来会有哪些需求方会用到自己，并且实现它们所要求的接口。

#### 非入侵式接口

在Go语言中，一个类只需要实现了接口要求的所有函数，我们就说这个类实现了该接口

```go
type File struct {
  	//....
}
func (f *File) Read(buf []byte) (n int, err error)
func (f *File) Write(buf []byte) (n int, err error)
func (f *File) Seek(off int64, whence int) (pos int64, err error)
func (f *File) Close() error
//这里我们定义了一个File类，并实现由Read(),Write(),Seek(),Close()等方法。设想我们有如下几个接口
type IFile interface {
  Read(buf []byte) (n int, err error)
  Write(buf []byte) (n int, err error)
  Seek(off int64,whence int) (pos int64,err error)
  Close() error
}

type IReader interface {
  Read(buf []byte) 
}

type IWriter interface {
  Write(buf []byte) (n int, err error)
}

type ICloser interface {
  Close() error
}
//尽管File类并没有从这些接口继承，甚至不知道这些接口的存在，但File类实习了这些接口，可以进行赋值
var file1 IFile = new(File)
var file2 IReader = new(File)
var file3 IWriter = new(File)
var file4 ICloser = new(File)

```

Go语言的非侵入式接口，看似只是做了很小的文法调整，实则影响深远

- Go语言的标准库，再也不需要绘制类库的继承数图，你只需要知道类实现了那些方法和每个方法的含义
- 实现类的时候，只需要关心自己应该提供那些方法不需要考虑接口的拆分细致问题
- 不用为了实现一个接口而导入一个包，因为多引用一个外部的包，就意味着更多的耦合。接口由使用方按自身需求来定义，使用方无需关心是否有其他模块定义过类似的接口。

#### 接口赋值

接口赋值在Go语言中分为如下两种情况

- 将对象实例赋值给接口
- 将一个接口赋值给另一个接口

如果是某种类型的对象实例赋值给接口，这要求该对象实例实现了接口要求的所有方法。

```go
type Integer int
func (a Integer)Less(b Integer) bool {
  return a < b
}
func (a *Integer)Add(b Integer) {
  *a += b
}
//我们定义的接口LessAdder 
type LessAdder interface {
  Less(b Integer) bool
  Add(b Integer)
}
//赋值
var a Integer = 1
var b LessAdder = &a //right
var b LessAdder = a //wrong
/*这里我们只能用&a,因为Go可以通过
func (a Integer) Less (b Integer)bool
自动生成一个系的less()方法
func (a *Integer) Less (b Integer)bool {
  	return (*a).Less(b)
}*/
```

将一个接口赋值给另一个接口。在Go语言中，只要两个接口拥有相同的方法列表（次序不同不要紧），那么它们就是等同的，可以相互赋值。

```go
//第一个接口
package one
type ReadWrite interface {
  Read(buf []byte) (n int, err error)
  Write(buf []byte) (n int,err error)
}
//第二个接口在另外的包中
package two
type IStream interface {
  Write(buf []byte) (n int, err error)
  Read(buf []byte) (n int, err error)
}
//这里我们定义了两个接口，一个叫one.ReadWriter，一个叫two.Istream，两者都定义了Read()、 Write()方法，只是定义次序相反。 one.ReadWriter先定义了Read()再定义了Write()，而two.IStream反之
//在Go语言中，这两个接口实际上并无区别
var file1 two.IStream = new(File)
var file2 one.ReadWrite = file1
var file3 two.Istream = file2
```

接口赋值并不要求两个接口必须等价。如果接口A的方法列表是接口B的方法列表的子集，那么接口B可以赋值给接口A。但是反过来并不会成立

#### 接口查询

有办法让上面的Writer接口转换为two.IStream接口么？有。那就是我们即将讨论的接口查询语法，代码如下： 

```go
var file1 Write = ...
if file5, ok := file1.(two.IStream); ok {
  ...
}
//这个if语句检查file1接口指向的对象实例是否实现了two.IStream接口，如果实现了，则执行特定的代码
```

接口查询是否成功，要在运行期才能够确定。它不像接口赋值，编译器只需要通过静态类型检查即可判断赋值是否可行。 

```go
//在GO语言中，你可以查询接口它指向的对象是否是某个类型
var file1 Write = ...
if file6, ok := file1.(*File); ok {
  ...
}
//这个if语句判断file1接口指向的对象实例是否是*File类型，如果是则执行特定代码。
```

#### 类型查询

在Go语言中，还可以更加直截了当的查询接口指向的对象实例的类型

```go
var v1 interface{} = ...
switch v := v1.(type) {
  case int:
  case string:
  ...
}
```

就像现实生活中物种多得数不清一样，语言中的类型也多得数不清，所以类型查询并不经常使用。它更多是个补充，需要配合接口查询使用，例如： 

```go
type Stringer interface {
  String() string
}

func Println(args ...interface{}) {
  for _, arg := range args {
    switch v := v1.(type){
   		case int:		
    	case string:
      	default:
      	if v,ok := arg.(Stringer); ok{
          val	:= v.String()
          ....
		}else{
  			//....
		}	 
    }
  }
}
```

#### 接口组合

像之前介绍的类型组合一样，Go语言同样支持接口组合。我们已经介绍过Go语言包中io.Reader接口和io.Writer接口，接下来我们再介绍同样来自于io包的另一个接口io.ReadWriter：

```go
//ReadWriterjiek哦将基本的Read和Write组合起来
type ReadWriter interface {
  Reader
  Writer
}
//这个接口组合了Reader和Writer两个接口，它完全等同于如下写法：
type ReadWriter interface {
  Read(p []byte) (n int,err error)
  Write(p []byte) (n int,err error)
}
```

可以认为接口组合是类型匿名组合的一个特定场景，只不过接口只包含方法，而不包含任何成员变量。

#### Any类型

由于Go语言中任何对象实例都满足空接口interface{}，所以interface{}看起来像是可以指向任何对象的Any类型，如下 

```go
var v1 interface{} = 1 
var v2 interface{} = "abc"
var v3 interface{} = &v2    //把*interface{}类型赋值给interface{}
var v4 interface{} = strcut{ X int }{1}
var v5 interface{} = &strcut{ X int }{1}
```

当函数可以接受任意的对象实例时，我们会将其声明为interface{}，最典型的例子是标准库fmt中PrintXXX系列的函数，例如： 

```go
func Printf(fmt string,args ...interface{})
func Println(args ...interface{})
```

总体来说， interface{}类似于COM中的IUnknown，我们刚开始对其一无所知，但可以通过接口查询和类型查询逐步了解它。 

## 并发编程

并发包含以下几种主流的实现模型

- 多进程：多进程是在操作系统层面进行并发的基本模式，同时也是开销最大的模式。在Linux平台上，很多工具链正是采用这种模式在工作。比如某个web服务器，它会有专门的进程负责网络端口的监听和链接管理，还会有专门的进程负责事务和运算。这种方法的好处在于简单，进程间互不影响，坏处在域系统开销大，因为所有的进程都是由内核管理的
- 多线程：多线程在大部分操作系统上都属于系统层面的并发模式，也是我们使用最多的最有效的一种模式。目前，我们所见的几乎所有工具链都会使用这种模式，它比多进程的开销小很多，但是其开销依旧比较大，且在高并发模式下，效率会有影响
- 基于回调的非阻塞/异步IO。这种架构的诞生实际上来源于多线程模式的危机。在很多高并发服务器开发实践中，使用多线程模式会很快耗尽服务器的内存和CPU资源。而这种模式通过事件驱动的方式使用异步IO，使服务器持续运转，且尽可能地少用线程，降低开销，它目前在Node.js中得到了很好的实践。但是使用这种模式，编程比多线程要复杂，因为它把流程做了分割，对于问题本身的反应不够自然
- 协程。协程(Coroutine) 本质上是一种用户态线程，不需要操作系统来进行抢占式调度，且在真正的实现中寄存于线程中，因此，系统开销极小，可以有效提高线程的任务并发性，而避免多线程的缺点，使用协程的优点是编程简单，结构清晰，缺点是需要语言的支持，如果不支持，则需要用户在程序中自行实现调度器。目前，原生支持协程的语言还很少

### 协程

执行体是个抽象的概念，在操作系统层面有多个概念与之对应，比如操作系统自己掌管的进程(process),进程内的线程(thread)以及进程内的协程(coroutine,也叫轻量级线程)。与传统的系统级线程和进程相比，协程的最大优势在于其"轻量级",可以轻松创建上上百万个而不会导致系统资源衰竭，而线程和进程最多也不会超过1万个。

多数语言不直接支持协程，而是通过库的方式支持，但是库的方式支持的功能也不完整，比如仅仅提供轻量级线程的创建，销毁与切换等能力。如果在这样的轻量级线程中调用一个同步IO操作，比如网络通信，本地文件读写，都会阻塞其他的并发执行轻量级线程。

GO语言在语言级别支持轻量级线程，叫goroutine。Go语言标准库提供的所有系统调用操作，都会出让CPU给其他goroutine,这让事情变得非常简单，让轻量级线程的切换管理不依赖于系统的线程和进程，也不依赖于CPU的核心数量

### goroutine

goroutine是Go语言中的轻量级线程实现，由Go运行时(runtime)管理，

假设我们需要实现一个函数Add( )，他把两个参数相加，并将结果打印到屏幕上没具体代码如下

```go
func Add(x, y int) {
  z := x + y
  fmt.Println(z)
}
//让这个函数并发执行
go Add(1,1)
```

在一个函数调用前加上go关键字，这次调用就会在一个新的goroutine中并发执行。当被调用的函数返回时，这个goroutine也自动结束了。需要注意的是，如果这个函数有返回值，那么这个返回值会被丢弃

```go
package main 
import "fmt"
func Add(x, y int) {
  z := x + y
  fmt.Println(z)
}
func main() {
  for i := 0; i < 10; i++ {
  	go Add(i, i)
  }
}
//我们在一个for循环中调用了10次Add( )函数，它们是并发执行的。我们在屏幕上看不到输出
```

Go程序从初始化main package并执行main()函数开始，当main()函数返回时，程序退出，且程序并不等待其他goroutine（非主goroutine）结束。

对于上面的例子，主函数启动了10个goroutine，然后返回，这时程序就退出了，而被启动的执行Add(i, i)的goroutine没有来得及执行，所以程序没有任何输出。

要让主函数等待所有goroutine退出后再返回，如何知道goroutine都退出了呢?这就引出了多个

要让主函数等待所有goroutine退出后再返回，如何知道goroutine都退出了呢?这就引出了多个goroutine之间通信的问题。下一节我们将主要解决这个问题。 

### 并发通信

并发编程的难度在于协调，而协调就要通过交流。从这个角度看来 ，并发单元间的通信是最大的问题。

在工程上，有两种最常见的并发通信模型：共享数据和消息

共享数据是指多个并发单元分别保持对同一个数据的引用，实现对该数据的共享。被共享的数据可能有多种形式，比如内存数据块，磁盘文件，网络数据等。在实际工程应用中最常见的无疑是内存了，也就是常说的共享内存

C语言中通常是怎么处理线程间数据共享的

```C
//thread.c C语言的线程数据共享处理
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *count();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

main()
{
  int rc1, rc2;
  pthread_t thread1,thread2;
  //创建线程，没个线程独立运行函数functionC
  if((rc1 = pthread_create(&thread1,NULL,&add,NULL)))
  {
  	printf("Thread creation failed: %d\n",rc1);
  }
  if((rc2 = pthread_create(&thread2,NULL,&add,NULL)))
  {
  	printf("Thread creation failed: %d\n",rc2);
  }
  //等待所有线程执行完毕
  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  
  exit(0);
}
void *count()
{
  pthread_mutex_lock(&mutex1);
  counter++;
  printf("Counter value: %d\n",counter);
  pthread_mutex_unlock(&mutex1);
}
```

```go
//我们把上面的C翻译成go
package main
import "fmt"
import "sync"
import "runtime"

var counter int = 0

func Count(lock *sync.Mutex) {
  lock.Lock()
  counter++
  fmt.Println(z)
  lock.Unlock()
}
func main() {
  lock := &sync.Mutex{}
  
  for i := 0; i < 10; i++ {
  	go Count(lock)
  }
  for {
    lock.Lock()
    c := counter
    lock.Unlock()
    runtime.Gosched()
    if c >= 10 {
  		break
	}
  }
}
```

Go语言提供的是另一种通信模型，即以消息机制而非共享内存作为通信方式。

消息机制认为每个并发单元是自包含的，独立的个体，并且都有自己的变量，但在不同并发单元间这些变量不共享。每个并发单元的输入和输出只有一种，那就是消息。真有点类似于进程的概念，每个进程不会被其他进程打扰，它只做好自己的工作就可以了。不同进程间靠消息来通信，它们不会共享内存。

Go语言提供的消息通信机制被称为channel。

不要通过共享内存来通信，而应该通过通信来共享内存。

### channel

channel是Go语言在语言级别提供的goroutine的通信方式，我们可以使用channel在两个或多个goroutine之间传递消息。channel是进程间的通信方式，因此通过channel传递对象的过程和调用函数时的参数传递行为比较一致，比如也可以传递指针等，如果需要跨进程通信，我们建议用分布式系统的方法来解决，比如使用Socket或者HTTP等通信协议。

channel是类型相关的，也就是说，一个channel只能传递一种类型的值。这个类型需要在声明channel时指定。如果对Unix管道有所了解的话，就不难理解channel,可以将其认为是一种类型安全的管道

我们用channel重写上面的例子

```go
package main
import "fmt"
func Count (ch chan int) {
  ch < -1
  fmt.Println("Counting")
}
func main() {
  chs := make([]chan int, 10)
  for i := 0; i<10 ;i++ {
  	chs[i] = make(chan int)
    go Count(chs[i])
  }
  for _, ch := range(chs) {
  	<-ch
  }
}
```

在这个例子中，我们定义了一个包含10个channel的数组（名为chs），并把数组中的每个channel分配给10个不同的goroutine。在每个goroutine的Add()函数完成后，我们通过ch <- 1语句向对应的channel中写入一个数据。在所有的goroutine启动完成后，我们通过<-ch语句从10个channel中依次读取数据，在对应的channel写入数据前，这个操作也是阻塞的。这样，我们就用channel实现了类似锁的功能，进而保证了所有goroutine完成后主函数才返回。

我们在使用Go语言开发时，经常会遇到需要实现条件等待的场景，这也是channel可以发挥作用的地方。对channel的熟练使用，才能真正理解和掌握Go语言并发编程。 

#### 基本语法

```go
//一般channel的声明形式为
var chanName chan ElementType
//于一般的变量声明不同的地方仅仅是在类型之前加chan关键字。ElementType指定这个channel所能传递的元素类型
var ch chan int //传递类型为int的channel
var m map[string] chan bool //声明一个map，元素是bool型的channel
//定义一个channel也很简单，直接使用内置的函数make()
ch := make(chan int) //声明并初始化了一个int型的名为ch的channel

//在channel的用法中，最常见的包括写入和读出，将一个数据写入(发送)至channel的语法很直观
ch <- value
//向channel写入数据通常会导致程序阻塞，直到有其他goroutine从这个channel中读取数据。从channel中读取数据的语法是：
value := <-ch
//如果channel之前没有写入数据，那么从channel中读取数据也会导致程序阻塞，直到channel中被写入数据为止
```

我们也可以控制channel只接受写或者只允许读取，即单向channel

#### select

早在Unix时代，select机制就已经被引入。通过调用select( )函数来监控一系列的文件句柄，一旦其中一个文件句柄发送了IO动作，该select()调用就会被返回。后来该机制也被用于实现高并发的Socket服务器程序。go语音直接在语言级别支持select关键字，用于处理异步IO问题。

select的用法与switch语言非常类似，由select开始一个新的选择块，每个选择条件由case语句来描述。与switch语句可以选择任何可以使用相等比较的条件相比，select有很多的限制，其中最大的一条限制就是每个case语句必须必须是一个IO操作

```go
//select 的大致结构
select {
  case <-chan1:
  	//如果chan1成功读到数据，则进行该case处理语句
  case chan2 < -1:
  	//如果成功向chan2写入数据，则进行该case处理语句
  default:
  	// 如果上面都没有成功，则进入default处理流程
}


```

可以看出， select不像switch，后面并不带判断条件，而是直接去查看case语句。每个case语句都必须是一个面向channel的操作。比如上面的例子中，第一个case试图从chan1读取一个数据并直接忽略读到的数据，而第二个case则是试图向chan2中写入一个整型数1，如果这两者都没有成功，则到达default语句。

```go
//基于此功能，我们可以实现一个有趣的程序

ch := make(chan int, 1)
for {
  select {
  	case ch <- 0;
    case ch <- 1;
  }
  i := <-ch
  fmt.Println("Value received:",i)
}
//这个程序实现了一个随机向ch中写入一个0或者1的过程
```

#### 缓冲机制

之前我们示范创建的都是不带缓冲的channel，这种做法对于传递单个数据的场景可以接受，但对于需要持续传输大量数据的场景就有些不合适了。接下来我们介绍如何给channel带上缓冲，从而达到消息队列的效果。

要创建一个带缓冲的channel，其实也非常容易： 

```go
c := make(chan int, 1024)
//在调用make()时将缓冲区大小作为第二个参数传入即可，比如上面这个例子就创建了一个大小为1024的int类型channel，即使没有读取方，写入方也可以一直往channel里写入，在缓冲区被填完之前都不会阻塞。
//从带缓冲的channel中读取数据可以使用与常规非缓冲channel完全一致的方法，但我们也可以使用range关键来实现更为简便的循环读取：
for i := range c {
  fmt.Println("Received:",i)  
}
```

#### 超时机制

在并发编程的通信过程中，最需要处理的就是超时问题，即向channel写数据时发现channel已满，或者从channel试图读取数据时发现channel为空。如果不正确处理这些情况，很可能会导致整个goroutine锁死。

Go语言没有提供直接的超时处理机制，但我们可以利用select机制。虽然select机制不是专为超时而设计的，却能很方便地解决超时问题。因为select的特点是只要其中一个case已经完成，程序就会继续往下执行，而不会考虑其他case的情况。

```go
//实现channel的超时机制
//首先，我们实现并执行一个匿名的超时等待函数
timeout := make(chan bool,1)
go func() {
  time.Sleep(le9) //等待1秒
  timeout <- true
}()

//然后我们把timeout这个channel利用起来
select {
  case <-ch:
  		//从ch中读取到数据
  case <-timeout
  		//一直没从ch中读取数据，但从timeout中读取到了数据
}
```

这样使用select机制可以避免永久等待的问题，因为程序会在timeout中获取到一个数据后继续执行，无论对ch的读取是否还处于等待状态，从而达成1秒超时的效果。
这种写法看起来是一个小技巧，但却是在Go语言开发中避免channel通信超时的最有效方法。在实际的开发过程中，这种写法也需要被合理利用起来，从而有效地提高代码质量。

#### channel的传递

需要注意的是，在Go语言中channel本身也是一个原生类型，与map之类的类型地位一样，因此channel本身在定义后也可以通过channel来传递

我们可以使用这个特性来实现Linux上非常常见的管道特性。管道也是使用非常广泛的一种设计模式，比如在处理数据时，我们可以采用管道设计，这样可以比较容易以插件的方式增加数据的处理流程

下面我们利用channel可被传递的特性来实现我们的管道。为了简化表达，我们假设在管道中传递的数据只是一个整型数，在实际的应用场景中这通常会是一个数据块。

```go
//定义限定基本的数据结构：
type PipeData struct {
  value int 
  handler func(int) int
  next chan int
//然后我们写一个常规的处理函数，我们只要定义一系列pipeDate的数据结构并一起传递给这个函数，就可以达到流式处理数据的目的
func handle(queue chan *PipeData) {
  for data := range queue {
  	data.next <- data.handler(data.value)
  }
}
```

利用channel的这个可传递特性，我们可以实现非常强大、灵活的系统架构。

#### 单向channel

顾名思义，单向channel只能用于发送或者接收数据。 channel本身必然是同时支持读写的，否则根本没法用。假如一个channel真的只能读，那么肯定只会是空的，因为你没机会往里面写数据。同理，如果一个channel只允许写，即使写进去了，也没有丝毫意义，因为没有机会读取里面的数据。所谓的单向channel概念，其实只是对channel的一种使用限制

我们在将一个channel变量传递到一个函数时，可以通过将其指定为单向channel变量，从限制 该函数中可 以对此 channel的操作， 比如只能往 这个 channel写，或者只 能从这个channel读。

```go
//单向channel变量的声明非常简单
var ch1 chan int 	//normal
var ch2 chan<- float64	// 单向，只用于写入float64数据
var ch3 <-chan int 	//单向channel，只用于读取int数据
//初始化channel.channel是以个原生类型，支持被传递和类型转化。即我们可以再单向channel和双向channel之间进行转换
ch4 := make(chan int)
ch5 := <-chan int(ch4) 	// 一个单向的读取channel
ch6 := chan<- int(ch4)  // 一个单向的写入channel
```

为什么要做这样的限制呢？从设计的角度考虑，所有的代码应该都遵循“最小权限原则”，从而避免没必要地使用泛滥问题，进而导致程序失控。写过C++程序的读者肯定就会联想起const指针的用法。非const指针具备const指针的所有功能，将一个指针设定为const就是明确告诉函数实现者不要试图对该指针进行修改。单向channel也是起到这样的一种契约作用。

```go
func Parse(ch <-chan int) {
  for value := range ch {
  	fmt.Println("Parsing value", value)
  }
}
```

#### 关闭channel

```go
close(ch)
//判断channel是否关闭
x, ok := <-ch
//这个用法和map中的按键获取value的过程类似，只需要看第二个bool返回值即可，如果是false则表示ch被关闭
```