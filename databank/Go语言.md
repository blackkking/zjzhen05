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

