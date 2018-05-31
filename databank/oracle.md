[TOC]

# oracle

## 基本概念

Oracle数据库适用于多种系统，SQL server数据库只能用于Windows。

数据库的架构：在Oracle数据库中，一个实例只能管理一个数据库。只有数据库在集群的环境下才能实现多个数据库被一个实例管理，而SQL server 数据库是一个实例管理多个数据库

内存分配：Oracle的内存分配大部分是由INIT.ORA来决定的，而SQL内存分配主要有动态内存分配和静态内存分配

数据库模型：层次结构模型，网状结构模型，关系结构模型(常用)

数据库的三级模式：外模式，模式，内模式；二级映像：外模式/模式映像，模式/内模式映像

外模式对应用户级，面向用户或应用程序员是模式的子集；模式对应着概念集，面向建立和维护数据库人员；内模式对应物理级，面向系统程序员；外模式/模式映像保证了数据与程序间的逻辑独立性，模式/内模式映像保证了数据与程序间的物理独立性

### 数据库中的相关术语

视图：视图是数据库中的虚拟表。在视图中存放的是从数据库表中查询出来的记录，使用视图主要是为为了方便信息查询，同时也能够缩短查询数据的时间

存储过程：存储过程是由SQL语句和控制流语句组成的语句块，存储过程存储在数据库内，可由应用程序通过存储过程的名称调用执行；存储过程在开发软件时，可以把大量的数据库操作放在服务器端的存储过程中，而只返回需要的数据，这样就减少了数据的传输量，速度也可以大大的提高

触发器：触发器是特殊的存储过程，也是有SQL语句和程序控制语句组成的，但是，触发器在数据库中是不需要调用而自动执行的。例如：在触发器中可以定义在修改某张表记录后执行触发器中的内容。

约束：约束是在数据库中保证数据库里表中数据完整性的手段。在Oracle 11g中使用约束有主键约束，外键约束，唯一约束，检查约束，非空约束，其中主键约束和唯一约束都被认为是唯一约束，而外键约束被认为是参照约束

### 范式——设计关系型数据库的准则

第一范式：数据库表中的字段都是单一属性的，不可再分

第二范式：数据库表中不存在非关键字段对任一候选关键字段的部分函数依赖；在第二范式中组合主键(A,B)里面的A或者B 与其他字段不能存在组合重复。

第三范式：数据库中不存在非关键字段对任一候选关键字段的传递函数依赖，传递函数依赖是指的是如果存在A决定B,B决定C的关系，则C传递函数依赖于A。

## SQL基础

SQL中的4种类型的语言：DDL,DML,DQL,DCL

DDL:定义要在数据库存储那些信息的数据定义语言；

DML:对数据库中的表进行操作的数据操纵语言

DQL:对数据库中的表进行检索的数据查询语言

DCL:对数据库中对象进行权限管理的数据控制语言

### DDL

使用create语句创建表：

```sql
CREATE TABLE table_name
(
  column_name datatype [null|not null],
  column_name datatype [null|noy null],
  ...
  [constraint]
)
```

使用Alter语句修改表

```sql
ALTER TABLE table_name
ADD column_name | MODIFY column_name|DROP COLUMN column_name;
--ADD: 用于向表中添加列
--MODIFY：用来修改表中已经存在的列的信息
--DROP COLUMN： 删除表中的列，在删除表中的列时经常要加上CASCADE CONSTRAINTS,是要把与该列有关的约束也一并删除掉
--向表里插入remark列,修改，删除
ALTER TABLE scott_tb ADD remark varchar(200);
ALTER TABLE scott_tb MODIFY remark number(2,2);
ALTER TABLE scott_tb DORP COLUMN remark;
--可以同时修改多个字段
```

使用DROP语句删除表：DROP TABLE table_name;

### 约束的使用

主键约束：

```sql
create table categoryinfo
(CategoryId varchar2(10),
 CategoryName varchar2(30),
 primary key(CategoryId)
);
--使用ALTER TABLE
ADD CONSTRAINTS constraint_name PRIMARY KEY (column_name);
--constraint_name:约束名称
ADD CONSTRAINTS pk_category primary key(categoryid);
DROP CONSTRAINT constraint_name; --移除主键约束
```

外键约束：

外键约束可以保证使用外键约束的数据库列与所引用的主键约束的数据列一致，外键约束一个数据表可以有多个

```sql
CONSTRAINT constraint_name FOREIGN KEY (column_name)
REFERENCE table_name (column_name)
ON DELETE CASCADE;
-- constraint_name:创建的约束的名字 
-- REFERENCE：要引用的表明(列名)
-- ON DELETE CASCADE: 设置级联删除，当主键的字段被删除时，外键所对应的字段也被同时删除
ALTER TABLE table_name
ADD CONSTRAINT constraint_name FOREIGN KEY (column_name)
REFERENCE table_name (column_name)
ON DELETE CACADE;
--修改数据库时添加外键约束
ALTER TABLE table_name
DROP CONSTRAINT constraint_name
--删除约束
```

check约束

检查约束能够规定每一个列能输入的值，以保证数据的正确性。

```sql
--创建表时在后面加上
CONSTRAINT constraint_name CHECK(condition);
--修改数据表时
ADD CONSTRAINT constraint_name CHECK(condition);
DROP CONSTRAINT constraint_name --删除
```

UNIQUE约束

唯一约束 操作方式同check约束

NOT NULL约束

创建表时在字段后设置

修改表时：ALTER TABLE table_name

MODIFY column NOT NULL;

删除约束 MODIFY column NULL;

## DML&DQL

insert插入数据

insert into table_name(column_name1,column_name2,...) values(data1,data2...);

insert into table_name1(column_name1,column_name2,...) select column_name1,column_name2... from table_name2;

直接通过源数据表在添加数据的同时创建表也是可以实现的。

create table table_name AS select column_name1,column_name2,...FROM source_table;

update 修改数据

update table_name set column_name=data1,column_name1=data2,...[where condition];

delete 删除数据

delete from table_name [where condition] 删除的数据不是字段

select 查询数据

select column_name1,column_name2,...from table_name where[condition];

### 其他语句：

TRUNCATE 删除全部数据，比delete快，TRUNCATE TABLE table_name;

MERGE 修改表中数据，可以对数据表同时进行增加和修改的操作。

```sql
MERGE [INTO] table_name1
	USING table_name2
	ON ( condition )
	WHEN MATCHED THEN merge_update_clause
	WHEN NOT MATCHED THEN merge_insert_clause;
--table_name1：要修改或添加的表
--table_name2:参照的更新的表
--condition:两表之间的关系，或其他的一些条件
--merge_update_clause:如果和参照表2中的雕件匹配，执行更新操作的SQL语句
--merge_update_clause:如果条件不匹配，就执行增加操作的SQL的语句
--可以删除一个，但不能都删除
```

下面使用MERGE语句完成对LOGIN表的操作

首先查询login和managerinfo表中的全部数据，然后使用on后面的条件编号是否相同，当相同时把login表中的loginname列改写成managerinfo表中的loginname，当不相同时，在login表中增加一条在managerinfo中存在的数据。

```sql
merge into login
using managerinfo
on (login.login_id=managerinfo.managerid)
when matched then update
set login.loginname=managerinfo.loginname
when not matched then insert
values(managerinfo.loginname,managerinfo.password,managerinfo.managerid);
```

## 利用select检索数据

select基本语法

```sql
select
	[DISTINCT|ALL]   --描述列表字段中的数据是否去除重复记录
		select_list	 --需要查询的字段列表，也可以说是占位符。可以是一个也可以是多个字段
	FROM table_list	 
	[where_clause]		--查询条件
	[group_by_clause]	--group by 子句部分
	[HAVING condition]	--HAVING子句部分
	[order_by_clause]  --排序
--其中select_list的具体语法
{
  * |
{[ schema. ] { table | view } .*
 | expr [ [AS] c_alias ]	
}
--schema:模式名称 table|view 表或视图 expr 表达式 c_alias:别名
```

使用别名：

select productid 产品编号， productname AS 产品名称， productprice as 产品价格 from productinfo;

给字段定义别名可以用AS ,如果不用AS而是在查询的列名后加上空格然后输入别名效果相同

使用表达式查询

```sql
SELECT productid,productname,productprice || '*' || 1.25 || '=' || productprice*1.25 AS new_productprice from productinfo;
--* 代表乘号，"||"是连续操作符，用来连接两个字符串
--使用函数 subStr截取字符的函数
select productid 产品编号, subStr(productid,1,6) as 截取后的编号,
			productname AS 产品名称, productprice AS 产品价格
from productinfo;
```

去除检索数据中的重复记录

select distinct(category)  产品类型 from productinfo;distinct 后面如果是多个列名，那么distinct把这些列名看出一个整体，来去除重复记录。

使用排序的语法

```sql
order by
{expr | position | c_alias}	--表达式|列表中列的位置|别名
[ASC | DESC]		--升|降  不写默认升序
[NULLS FIRST | NULLS LAST]	--对空字段的处理方式
	[,{expr | postion | c_alias}
     	[ASC | DESC]
     	[NULLS FIRST | NULLS LAST] --指定空字段的位置，默认NULL是最大值
    ]...
--使用字段位置作为排序字段
SELECT productname, productprice,quantity from productinfo order by 3 desc;
```

### 使用where子句设置检索条件

where 条件子句中可以使用的操作符主要有关系操作符，比较操作符和逻辑操作符。

1.关系操作符包括：<,<=,>,>=,=,!=,<> 不为和!=一样.

2.比较操作符包括：is NULL ；like 模糊比较字符串值 ；between...and... 验证值是否在范围内；in 验证操作数在设定的一系列值中

3.逻辑操作符包括: and 两个条件都必须得到满足；or 只要满足两个条件中的其中一个；not 与某个逻辑值取反

模糊查询数据，like 加上两个通配符：_ 可以替代字符 %可以替代多个字符

查询条件限制在某个列表范围之内：IN(list)

### group by 和having子句

group by 用于归纳汇总相关数据，它不属于where子句，

```sql
group by
{ expr		-- 通常表示数据库列名
| { rollup | cube } ({expr [, expr ]...}) --group by子句的扩展，可以返回小计和总计记录
}

```

having子句通常和group by子句一起使用，限用搜索条件，它和where子句不一样，having子句与组有关，而不是单个的值有关。在group by 子句中，它会作用与group by创建的组

```sql
select category avg(productprice) 平均价格 from productinfo group by category having avg (productprice) > 2000;
```

### 使用子查询

什么是子查询？子查询就是嵌套查询，它是嵌套在另一个语句中的select语句。在很多情况下，where后面的条件不是一个确切的值或表达式，而是另外一个查询语句的查询结构。子查询不仅仅出现在select语句中，也会出现在delete和update语句中，它本质上是where后面的一个条件表达式。

子查询返回单行：

```sql
--查询产品类型为"MP3"的产品名称和产品价格
select productname,productprcie from productinfo
where category = (select categoryid from categoryinfo where categoryname = 'MP3');
--查询出产品价格在最大值和最小值之间的产品，不包含两端的值。脚本如下：
select productname,productprice from productinfo
where productprice > (select min(productprcie) from productinfo) and productprice < (select max(productprice) from productinfo);
```

子查询返回多行：

如果子查询返回值为多行值，那么需要用到IN关键字，此时IN的用法和前面介绍的方式一致，除此之外，也可以使用量化比较关键字SOME,ANY,ALL,这些需要配合<,<=,=,>,>=使用。

ANY:表示满足子查询结构的如何一个 SOME:和ANY含义相同  ALL:查询的所有结果

```sql
--从表productinfo中查询出价格低于知道价格列表中的最大值。指定的价格列表就是指定产品类型编码为""0100030002" 的所有产品价格
select productname,productprice from productinfo
where productprice <
any (select productprice from productinfo where category = '0100030002')and category <> '0100030002'
--some 的用法和any一样，只不过any多用于非""="的环境中
select productname,productprice from productinfo
where productprice =
some (select productprice from productinfo where category = '0100030002')and category <> '0100030002';
--all 找出比指定价格列表还低的产品数据
select productname,productprice from productinfo
where productprice < 
ALL (select productprice from productinfo where category = '0100030002')
```

## 连接查询

连接分为内连接，外链接和全连接，还有一种是自连接

内连接也称为简单连接，它会把两个或多个表进行连接，只能查询出匹配的记录，不匹配的记录将无法查询出来，这种连接查询是平常最常用的查询。内连接中最常用的就是等值连接和不等值连接

等值连接：连接条件中使用"="连接两个条件列表

```sql
--查询出productinfo表和categoryinfo表中产品类型编码一致的数据
select p.productname,p.productprcie,c.categoryname
from productinfo p ,categoryinfo c where p.category = c.categoryid;
--或者
select p.productname,p.productprice,c.categoryname
from productinfo p INNER JOIN categoryinfo c ON p.category = c.categoryid;
```

不等值连接：连接条件不是"=",但这种方式通常需要和其他等值运算一起使用，否则检索出来的数据很可能没有实际意义

```sql
--内连接中的关键字""innner join" 可以直接写成 "join",系统会把""join" 识别成内连接。但是""on" 不能省略
select p.productname,p.productprice,c.categoryname
from productinfo p INNER JOIN categoryinfo c ON p.category IN c.categoryid;
select p.productname,p.productprice,c.categoryname
from productinfo p , categoryinfo c where p.category IN c.catgoryid;
```

自连接

所谓自连接，就是把自身表的一个引用作为另一个表来处理，这样就能获取一些特殊的数据

```sql
--获取表productinfo中数量相等的不同产品
select p.productname,p.productprice,pr.productname,pr.productprice,pr.quantity
from productinfo p,productinfo pr
where p.productid != pr.productid
AND p.quantity = pr.quantity
AND p.rowid < pr.rowid; --去除重复记录，只取rowid比较小的那条

select p.productname,p.productprice,pr.productname,pr.productprice,pr.quantity
from productinfo p join productinfo pr
ON p.productid != pr.productid
AND p.quantity = pr.quantity
AND p.rowid < pr.rowid; --去除重复记录，只取rowid比较小的那条
--语句中省略了""INNER"关键字
```

外连接

外连接分为左外连接，右外连接，全外连接。它们所表示的含义如下：

左外连接：又称为左向外连接。使用左外连接的查询，返回结果不仅仅是符合连接条件的行记录，还包含了左边表中的全部记录。也就是说，如果左表的某行记录在右表中没有匹配项，则在返回结果中右表的所有选择列表均为空。

右外连接：又称为右向外连接。它与左外连接相反，将右边的表中所有的数据与左表进行匹配，返回的结果除了匹配成功的记录，还包含右表中未匹配成功的记录，并在其左表对应的列补空值

全外连接：返回所有匹配成功的记录，并返回左表未匹配成功的记录，也返回右表未匹配成功的记录

```sql
--左连接 要求检索出productinfo表中每个产品对应的产品类型的名称。
select p.productname,p.productprice,p.category,c.categoryid,c.categoryname
from productinfo p LEFT JOIN categoryinfo c ON p.category = c.categoryid;
--右连接 查看那些产品类型还没有对应的产品
select p.productname,p.productprice,p.category,c.categoryid,c.categoryname from productinfo p RIGHT JOIN categoryinfo c ON p.category = c.categoryid;
--全外连接 左右连接的综合
select p.productname,p.productprice,p.category,c.categoryid,c.categoryname from productinfo p FULL JOIN categoryinfo c ON p.category = c.categoryid;
```

(+)的使用

在Oracle使用外连接，可以用“(+)”表示外连接。虽然这种方式可以实现外连接，但开发人员最好还是使用outer join关键字

(+)的使用方法读者可以简单记一下，该操作符总是放在非主表的一方，并且需要使用where子句，不能存在outer join关键字

```sql
--左外连接使用(+)
select p.productname,p.productprice,p.category,c.categoryid,c.categoryname
from productinfo p,categoryinfo c 
where p.category = c.categoryid(+);
--右连接使用(+)
select p.productname,p.productprice,p.category,c.categoryid,c.categoryname from productinfo p, categoryinfo c 
where p.category(+) = c.categoryid;
```

## Oracle内置函数

Oracle中真实存在的一个dual表，任何用户都可以读取，多数情况下可以用在没有目标的select查询语句中。它本身只包含了一个dummy字段。dual表对Oracle很重要，不能删除。

### 数值型函数

- 绝对值，取余，判断数值正负函数

```sql
--ABS(n)函数。用于返回绝对值。该函数输入一个参数，参数类型为整数型，假如参数可以隐式转换成数值类型，那么也可以
select ABS(100),ABS(-100),ABS('100') FROM DUAL;
--MOD(n2,n1)函数。该函数表示返回n2除以n1的余数。如果n1为0，将返回n2
select MOD(5,2),MOD(8/3,5),MOD('10',5),MOD(-10,6),MOD(1,0) FROM DUAL;
--SIGN(n)函数。返回参数n的符号。正数返回1，0返回0，负数返回-1。但如果n为BINARY_FLOAT 或 BINARY_DOUBLE类型时，n>=0或者n=NaN函数会返回1。
select sign('9'),sign(-9),sign(0.00),sign(-2*'9') from dual;
```

- 三角函数

COS(n)函数：用于返回参数n的余弦，n为弧度表示的角度

ACOS(n)函数：反余弦值；COSH(n)函数：双曲余弦值；

SIN(n)函数：正弦值；SINH(n)函数：双曲正弦值；

ASIN(n)函数：反正弦值；TAN(n)函数：正切值；

TANH(n)函数：双曲正切值；ATAH(n)函数：反正切值；

- 返回以指定数值为准整数的函数

CEIL(n)函数。其返回结果是大于等于输入参数的最小整数，该输入参数要求是十进制数值类型，或可以隐式的转换数值的类型，可以是非整数。

SELECT CEIL(10),CEIL('10,5'),CEIL(-10.2) FROM DUAL; 10，11，-10

FLOOR(n)函数。其返回结果是小于或等于参数的最大整数，该函数输入参数要求是十进制数值类型，或可以隐式地转换为数值的类型。可以是非整数。同CEIL函数相反。

SELECT FLOOR(10),FLOOR('10.5'),FLOOR(-10.2) FROM DUAL; 10，10，-11

- 指数，对数函数

SQRT(n)函数。该函数返回n的平方根。n为数字类型的时候不能为负数，将返回一个实数，当n为BINARY_FLOAT 或 BINARY_DOUBIE类型时，n<0将返回Nan。

SELECT SQRT(100),SQRT('53.9') FROM DUAL;

POWER(n2,n1)函数。利用该函数可以得到n2的n1次幂的结果。这两个参数为任意数值，但如果n2为负数，那么n1必须为整数。

SELECT POWER(5,2),POWER('5',2),POWER(5.5,2.5),POWER(-5,2),5*5 FROM DUAL

EXP(n)函数，表示返回e的n次幂，e为数学常量，e = 2.71828183...

LOG(n1,n2)函数。该函数可以返回以n1为底n2的对数，n1是除1和0以外的任意正数。n2为正数。

SELECT LOG(10,100),LOG(10.5,'100'),POWER(10,2)  FROM DUAL;

LN(n)函数，表示返回n的自然对数。n要求大于0。

- 四舍五入截取函数

ROUND(for number) 函数。该函数的具体原型是ROUND(n,integer)。它将数值n四舍五入成第二个参数指定的形式的十进制数。参数integer要求是整数，如果不是整数，那么它将被自动截取为整数部分。当integer为正整数时，表示n被四舍五入为integer为小数。如果该参数为负数，则n被四舍五入到小数点向左integer位。

SELECT ROUND(100.23456,4),ROUND(100.23456,2.56),ROUND(155.23456,-2) FROM DUAL;    100.2346   100.23    200

TRUNC(for number) 函数。该函数原型TRUNC(n,integer)。它把数值n根据integer的值进行截取，截取时和integer的正负有关。参数integer要求是整数，如果不是整数，那么n将截取到integer位小数；如果integer为负数，则截取到小数点左第integer位，被截取部分用0代替。

SELECT TRUNC(100.23456,4),TRUNC(100.23456,2.56),TRUNC(155.23456,-2),TRUNC(155.23456) FROM DUAL;  100.2346   100.23    100  155 

### 字符型函数

CHR(n[USING NCHAR_CS])函数。根据相应的字符集，把给定的ASCII码转换为字符。USING NCHAR_CS指明字符集

SELECT CHR(65) || CHR(66) || CHR(67)  ABC, CHR(54678) FROM DUAL;

ASCII(char)函数，返回首字母的ASCII码值。

length函数，返回字符串长度

SUBSTR函数，该函数提供截取字符串的功能，而且该函数有很多的扩展形式，其具体语句结构是

```sql
{[SUBSTR]|[SUBSTRB]|[SUBSTRC]|[SUBSTR2]|[SUBSTR4]}(char,position[,substring_length]).
--position 要截取字符串的开始位置，初始为1，如果该值为负数，则表示从char的右边算起  substring_length 截取的长度
```

字符串连接函数：CONCAT(char1,char2) 效果连接符"||" 相似

字符串搜索函数：INSTR(string,substring[,position[,occurrence]])。

substring:要搜索的字符串,position:搜索的开始位置，默认为1，负数从右开始，occurrence：substring第几次出现，默认为1

字母大小写转换函数：

UPPER(char):装换成大写字母 LOWER(char):转换成小写字母

带排序参数的字母大小写转换函数：

NLS_INITCAP(char[,nlsparam])函数。将指定参数的第一个字母转换成大写。

nlsparam参数为可选参数，其设置可以到NSL_DATABASE_PARAMETERS表中查询。如果该函数没有nlsparam参数，则它和INITCAP函数一样。

```sql
select NLS_INITCAP('a test'), NLS_INITCAP('my test','NLS_SORT = SCHINESE_STROKE_M') FROM DUAL;
--参数中'NLS_SORT=SCHINESE_PINYIN_M'表示按拼音排序。
```

NLS_LOWER(char[,nlsparam])函数。将指定参数转换成小写。nlsparam参数同NLS_INITCAP函数设置

```sql
SELECT NLS_LOWER('ABC','NLS_SORT= XGerman'),
NLS_LOWER('THIS IS A TEST','NLS_SORT= XGerman')
FROM DUAL;
```

为指定参数排序函数

NLSSORT(char[,nlsparam])函数。根据nlsparam指定的方式对char进行排序。

```sql
SELECT * FROM PRODUCTINFO
ORDER BY NLSSORT(PRODUCTNAME,'NLS_SORT=SCHINESE_PINYIN_M')
```

替换字符串函数

```sql
REPLACE(char,search_string[,replacement_string]),
--char 搜索的目标字符串 search_string: 在目标字符串中搜索的字符串  replacement_string 可选参数，用来代替被搜索到的字符串，如果不用删除搜索到的字符
```

字符串填充函数

RPAD(expr1,n[,expr2]) :在字符串expr1的右边用字符expr2填充，直到字符串长度到n为止。如果expr2不存在，则以空格填充，

LRAD(expr1,n[,expr2]) 在左边填充

删除字符串首尾指定字符的函数

```sql
TRIM([LEADING|TRAILING|BOTH][time_character FROM] trim_source)
--LEADING 删除前缀
--TRAILING 删除后缀
--BOTH  删除time_source 的前缀和后缀字符
--trim_charater 删除的指定字符，默认删除空格
--trim_source 被操作的字符数
```

RTRIM(char[,set]) 删除char右边出现在set中的字符

LTRIM(char[,set]),删除左边的字符

字符集名称和ID互换函数

NLS_CHARSET_ID(string)函数。该函数可以得到字符集名称对应ID

NLS_CHARSET-NAME(number)函数。根据ID得到名称

### 日期型函数

系统日期，时间函数

SYSDATE函数。该函数没有参数，可以得到系统日期，下面示例将得到的时间格式化：

SELECT TO_CHAR(SYSDATE,'YYYY-MM-DD HH24:MI:SS') FROM DUAL;

SYSTIMESTAMP函数。该函数没有参数，返回系统时间，该时间包含时区信息，精确到微秒。返回类型为带时区的TIMESTAMP类型

得到数据库时区函数： DBTIMEZONE

为日期加上指定月份函数： ADD_MONTHS(date,integer)函数

返回当前会话的时区： SESSIONTIMEZONE函数

返回指定月份最后一天：LAST_DAY(date)

返回指定日期后一周的日期函数：NEXT_DAY(date,char) char表示星期几

返回会话所在时区当前的日期：CURRENT_DATE

提取指定日期特定部分的函数：EXTRACT(datetime)

```sql
SELECT 
EXTRACT(YEAR FROM SYSDATE) YEAR,
EXTRACT(MINUTE FROM TIMESTAMP '2010-6-18 12:23:10') MIN,
EXTRACT(SECOND FROM TIMESTAMP '2010-6-18 12:23:10') SEC,
FROM DUAL;
```

得到两个日期之间的月份数：MONTHS_BETWEEN(date1,date2),函数两个参数都是日期型数据，当date1>date2，如果两个参数表示日期是某月的同一天，或它们都是某月中的最后一天，则该函数返回一整函数，否则返回小数。当date1<date2时，返回一个负值

时区时间转化函数 NEW_TIME(date,timezone1,timezone2)函数，该函数将返回时间date在时区timezone1转化到时区timezone2

日期四舍五入，截取函数：ROUND(date[,fmt]) 将date舍入到fmt指定的形式，如果fmt被省略，则date将被处理到最近的一天

TRUNC(date[,fmt]) 将date舍入到fmt指定的形式，如果fmt被省略，则date将被处理到最近的一天

```sql
select TO_CHAR(ROUND(TO_DATE('2010-5-1 09:00:00','YYYY-MM-DD HH 24:MI:SS'),'YYYY-MM-DD HH 24:MI:SS')) FROM DUAL;
select TO_CHAR(TRUNC(TO_DATE('2010-5-1 09:00:00','YYYY-MM-DD HH 24:MI:SS'),'YYYY-MM-DD HH 24:MI:SS')) FROM DUAL;
```

## 转换函数

字符串转ASCII类型字符串 ASCIISTR(char)

二进制转换为十进制 BIN_TO_NUM(data[,data...]) 用，分开位数

数据类型转换 CAST(expr as type_name) 把expr参数转化为type_name类型 基本上用于数字和字符之间和字符与日期类型之间的转换

字符串和ROWID(伪列)相互转换 ROWID格式必须长度为18，每一条记录都由一个rowid，rowid在数据库中唯一，可以利用select查询该字段

把字符串转为ROWID类型:CHARTOROWID(char)

把ROWID类型转换为字符类型 ROWIDTOCHAR(rowid)

把字符集转到另一个字符集 CONVERT(char,dest_char_sest[,source_char_set]),

char 等待转换的字符  dest_char_sest 转变后的字符集  source_char_set  原字符集，如果没有该参数，则默认数据库实例字符集

十六进制字符串转换为RAW类型 HEXTORAW(char)

RAW类型转换为十六进制字符串 RAWTOHEX(raw)

数值到字符串 TO_CHAR(number)  TO_CHAR(n[,fmt[,nlsqaram]])

日期类型到字符串 TO_CHAR(date) TO_CHAR(n,[,fmt[,nlsparam]])

字符转日期型函数 TO_DATE(char[,fmt[,nlsparam]])

字符串转数字函数 TO_NUMBER(expr[,fmt[,nlsparam]])

全角转半角函数 TO_SINGLE_BYTE(char) 

### NULL函数

返回列表第一个不为NULL的表达式，如果都是NULL，则返回一个NULL: COALESCE(expr)

排除指定条件 LNNVL(condition) ,包含NULL的条件

```sql
SELECT* FROM PRODUCTINFO WHERE LNNVL(QUANTITY>=70);
--数量低于70的产品，包括为NULL的
```

替换NULL值函数

NVL(expr1,expr2)函数，替换NULL值，表示如果expr1为NULL值，则返回expr2的值，否则返回expr1的值。该函数要求两个参数类型一致，至少相互间能进行隐式的转换，否则会提示出错

NVL2(expr1,expr2,expr3),expr1为NULL时，返回expr3，当不为空时，则返回expr2的值

### 集合函数

AVG([distinct|all]expr) 求某组的平均值，返回数值类型

distinct 去重 all 所有值 expr 表达式

```sql
select avg(all productprice) from productinfo group by category
--查询各类产品的平均价格
```

求记录数量函数：

```sql
COUNT(*|[distinct][all]expr) 
--查询productinfo表中的productprice字段低于3000的不重复的记录数
SELECT COUNT(DISTINCT PRODUCTPRICE) FROM PRODUCTINFO WHERE PRODUCTPRICE < 3000;
```

返回最大最小值函数

```sql
MAX([distinct|all]expr) --返回指定列的最大值
MIN([distinct|all]expr)
```

求和函数

```sql
SUM([distinct|all]expr) 
```

### 其他函数

返回登录名 ： USER

返回会话以及上下文信息函数：

```sql
USERENV(parameter)  --返回当前会话信息
SELECT USERENV('ISDBA') FROM DUAL;
SYS_CONTEXT(namespace,parameter) --可以得到Oracle已经创建的context，名为userenv的属性对应值
SELECT SYS_CONTEXT('USERENV','SESSION_USER') SESSION_USER FROM DUAL;--得到当前会话对应的用户名
```

表达式匹配函数

```sql
DECODE(expr,search,result[,search1,result1][,default])
--改函数的执行结果是，当expr符合条件search时就返回result的值，该过程可以重复多个，如果最后没有匹配结果，可以返回默认值default，注意它是一对一的匹配过程
--下面的事例将演示PRODUCTINFO中产品数量大于100显示充足，少于或等于100则显示不足
SELECT PRODUCTNAME,QUANTITY,DECODE(SIGN(QUANTITY-100),1，'充足',0,'不足') FROM PRODUCTINFO
```

## PL/SQL基础

### 什么是PL/SQL

结构化查询语言(structured query language,SQL)是用来访问和操作关系型数据库的一种标准通用语言，它属于第四代语言(4GL)，简单易学，特点是方便，非过程化。使用的时候不用明确指明执行的具体方法和途径，不用关注任何实现的细节。但这种语言也有一个问题，就是满足不了复杂的流程需求。

Oracle中的PL/SQL语言正是为了解决这一问题，它属于第三代的语言，也是过程化的语言，同Java,C#一样可以关注细节，用它可以实现复杂的业务逻辑，是数据库开发人员的利器

PL/SQL(Procedural Language/Structured Query Language)是Oracle公司在标准SQL语言基础上进行扩展而形成的一种可以再数据库上进行设计编程的语言，通过Oracle的PL/SQL引擎执行，可以实现逻辑判断，条件循环等与语句。

PL/SQL的特点：

- 支持事务控制和SQL数据操作命令
- 它支持SQL的所有数据类型，并且在此基础上扩展了新的数据类型，也支持SQL的函数和运算符
- PL/SQL可以存储在oracle服务器中
- 服务器上的PL/SQL程序可以使用权限进行控制
- Oracle有自己的DBMS包，可以处理数据的控制和定义命令

PL/SQL优点：

- 可以提高程序的运行性能，语句块中可以包含多条SQL语句，只用连接一次数据库
- 可以使用程序模块化：可以包装一个功能
- 可以采用逻辑控制语句来控制程序结构
- 利用处理运行时的错误信息
- 良好的可移植性

### PL/SQL的结构

PL/SQL程序的基本单位是块(block),而PL/SQL块很明确地分三部分，其中包括声明部分，执行部分和异常处理部分

```plsql
[DECLARE]  --声明开始的关键字
			/*这里是声明部分，包括了变量，常量和类型等*/
BEGIN	--执行部分开始的标志
			/*这里是执行部分，是整个plsql的主题部分，该部分必须存在，可以是SQL语句或者是程序流程控制语句等*/
[EXCEPTION]	--异常开始部分的关键字
			/*这里是异常处理部分，当出现异常时程序流程可以进入此处*/
END;	--执行结束标志
```

```plsql
DECLARE
v_categoryid VARCHAR2(12);
BEGIN
	SELECT CATEGORYID
		INTO V_CATEGORYID
			FROM CATEGORYINFO
		WHERE CATEGORYINFO.CATEGORYNAME = '雨具'；
	DBMS_OUTPUT.PUT_LINE('雨具对应的编码是：'|| v_categoryid);

EXCEPTION
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('没有对应的编码! ');
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('对应数据过多，请确认！ ');

END;

--select...into 是PL/SQL特有赋值语句，该类型语句一次只能返回一条记录，超过一条会报错

```

### PL/SQL的基本规则

- 标识符不分大小写，所有的名称在存储时都被修改成大写
- 标识符中能有字母，数字，下划线，并且以字母开头
- 标识符最多30个字符
- 不能用保留字，如果与保留字需要用双引号括住
- 语句使用分号结束
- 语句中的关键字，标识符，字段的名称以及表名等都需要空格的分隔
- 字符类型和日期类型需要使用单引号括起

### PL/SQL 变量的使用

```plsql
variable_name datetype
[
  [ NOT NULL ]
  {:= | DEFAULT} expression --当使用not NULL 属性是，赋值和默认值选一
];
```

#### 数值类型：

- NUMBER类型可以表示整数和浮点数，十进制。格式NUMBER(precision,scale).precision表示精度，也就是位数，最多38位，scale表示小数点后的位数，例如NUMBER(3,1)可以储存-99.9~99.9之间的数
- float 用来存储126位数据(二进制)
- PLS_INTEGER和BINARY_INTENER类型通常可以认为是一样的类型，表示的是-2147483628~2147483647之间。不同是BINARY_INTENER 发生溢出时指派一个NUMBER类型而不发生异常，而PLS_INTEGER会发生异常
- SIMPLE_INTEGER属于PLS_INTEGER的子类型，取值范围一样，只是改类型不允许为空。如果数据本身不需要溢出检查而且也不可能是空，可以选择该类型

字符类型

- CHAR类型，用来描述固定长度的字符串，最长为32 767个字节，默认为1，如果长度达不到会以空格补齐长度，CHAR(maximum_size).
- VARCHAR2类型 作为变量为32 767字节，但存储时最大4000个字节，该类型表示可以变的长度字符串，当没到定义的最大长度的时候不会补齐
- NCHAR,NVARCHAR2 与国家的字符集有关
- LONG类型 可以变的方式存储数据，PL/SQL中该类型作为变量最长为32760字节的字符串，如果作为存储字段则可达2GB

BOOL类型，不能定义表中的存储数据，可以用来存储逻辑上的值，它有3个值可以选：TRUE FALSE NULL

日期类型

- DATE类型可以存储月，年，日，世纪，时，分，秒
- TIMESTAMP类型由DATE演变，可以存储月，年，日，世纪，时，分，秒以及小数的秒

#### 使用%TYPE方式定义变量类型。

它利用以及存在的数据类型来定义数据的数据类型。例如，当定义多个变量时，只要使用过的数据类型，后面的变量就可以用%TYPE引用。 productinfo.productid%TYPE;

#### 复合类型的变量

- PL/SQL '记录类型'

该类型可以包括一个或多个成员，每个成员的类型可以不同。该类型比较适合处理 查询语句中有多个列的情况。最常见的就是在调用某张表中的记录时，利用该类型存储这行记录

```plsql
TYPE type_name IS RECORD
(
  field_name datetype
  [
  [ NOT NULL ]
  { := | DEFAULT } expression
  ]
  	[, field_name datatype [[ NOT NULL ] { := | DEFAULT } expression]]...
);
```

- %ROWTYPE声明记录类型数据

这种声明方式可以直接引用表中的行作为变量类型。可以避免因表中字段的数据改变而导致PL/SQL块出错的问题

v_product productinfo%ROWTYPE;

- PL/SQL索引表类型(关联数组)

该类型和数组相似，它利用键值查找对应值。这里键值同真正数组的下标不同，索引表中下标允许字符串。数组的长度不是固定值，它可以根据需要自动增长。其中键值是整数或字符串。而其中的值就是普通的标量类型，也可以是记录类型。可以利用“变量名称（键值）”为其赋值或取值，如果某个键值的指向已经有数据了，那么该操作就是更改已有的数据。

```plsql
TYPE type_name IS TABLE OF
{
column_type |
variable_name%TYPE |
table_name.column_name%TYPE|
table_name%ROWTYPE
}
[NOT NULL]
INDEX BY { PLS_INTEGER | BINARY_INTEGER | VARCHAR2 ( v_size ) }

```

以上的语法只是索引表类型本身的定义语法，并没有包含变量的定义。如果想把某个变量声明成索引表类型：

variable_name  type_name;

```plsql
DECLARE
TYPE prodt_tab_fst IS TABLE OF productinfo%ROWTYPE
	INDEX BY BINARY_INTEGER;
TYPE prodt_tab_sec IS TABLE OF VARCHAR2(8)
	INDEX BY PLS_INTEGER;
	v_ptr_row	prodt_tab_fst;
		v_ptr	prodt_tab_sec;

BEGIN 
	v_prt(1) := '正数';
	v_prt(-1) := '负数';
	
	SELECT * INTO v_prt_row(1);
	FROM productinfo
	WHERE productid = '0240040001';
	
	DBMS_OUTPUT.PUT_LINE('行数据-v_prt_row(1) = ' || v_prt_row(1).productid || '---' || v_ptr_row(1).productname);
	DBMS_OUTPUT.PUT_LINE('v_prt(1)= '			|| v_prt(1));
	DBMS_OUTPUT.PUT_LINE('v_prt(-1) = '			||v_prt('-1'));
END;
/
```

```plsql
DECLARE
TYPE prodt_tab_thd IS TABLE OF NUMBER(8)
	INDEX BY VARCHAR2(20);
	v_ptr_chr  prodt_tab_thd;
BEGIN
	v_ptr_chr('test') := 123;
	v_ptr_chr('test1') := 0;
	DBMS_OUTPUT.PUT_LINE('v_prt_chr(123) = ' || v_ptr_chr('test')); --123
    DBMS_OUTPUT.PUT_LINE('v_prt_chr(000) = ' || v_ptr_chr('test1')); --0
    DBMS_OUTPUT.PUT_LINE('v_prt_chr(000) = ' || v_ptr_chr.first); --test
    DBMS_OUTPUT.PUT_LINE('v_prt_chr(000) = ' || v_ptr_chr(v_prt_chr.first)); --123
END;
/
```

- VARRAY变长数组

该类型的元素个数是需要限制的，它是一个存储有序元素的集合。集合下标从1开始，比较适合较少的数据使用。声明语法如下：

```plsql
TYPE type_name IS { VARRAY | VARYING ARRAY} (size_limit)
OF element_type [ NOT NULL ]
```
```plsql
DECLARE
	TYPE varr IS VARRAY(100) OF VARCHAR2(20);
	v_product varr := varr('1','2');
BEGIN
	v_product(1) := 'THIS IS A';
	v_product(2) := 'TEST';
	DBMS_OUTPUT.PUT_LINE('productid = ' || v_product(1));
    DBMS_OUTPUT.PUT_LINE('productid = ' || v_product(2));
END;
/
```

### 表达式

- 数值表达式

乘方**

```plsql
--计算根号的58+25*3+(19-9)^2
DECLARE
	v_result NUMBER(10,4);
BEGIN
	v_result := SQRT(58+25*3+(19-9)**2);
	DBMS_OUTPUT.PUT_LINE('v_result = ' || v_result);
END;
```

- 关系表达式

不等号 !=  和 <>

- 逻辑表达式

NOT OR AND

### PL/SQL结构控制

- IF条件控制语句

```plsql
IF condition1 THEN
	statements;
ELSIF condition2 THEN
		statements;
...
[ElSE statements;]
END IF;
```

- CASE条件控制语句

```plsql
--简单CASE语句
[ <<lable_name>> ] --标签，选择性添加
CASE case_operand
WHEN when_operand THEN
statement ;
[
WHEN when_operand THEN
  statement ;
]...
[ ELSE statement [ statement ]]... ;
END CASE [ label_name ];
--搜索式的CASE语句
[ <<lable_name>> ]
CASE
WHEN boolean_expression THEN statement ;
[WHEN boolean_expression THEN statement ;]...
[ELSE statement [statement]... ;
 END CASE [label_name];
 --搜索的CASE语句会依次检查波尔值是否为true，一旦为true，那么它虽在的when子句会立即执行而且它后面的表达式将不被考虑，如果所有表达式都不为true，那么程序转到else语句，如果没有else语句，系统会给出CASE_NOT_FOUND异常
```

- LOOP循环控制语句

```plsql
--基本的LOOP
[ <<lable_name>> ]
LOOP
	statement...
END LOOP [label_name]
------------------------------------
DECLARE
	v_num NUMBER(8) := 1;
BEGIN
	 <<basic_loop>> 
	LOOP 
	DBMS_OUTPUT.putline('当前v_num变量的值是： ' || v_num)；
	v_num := v_num + 1;
	IF v_num > 5 THEN 
	--EXIT basic_loop WHEN v_num > 5;
		DBMS_OUTPUT.PUT_LINE('退出！ 当前v_num的值是 ' || v_num);
		EXIT basic_loop;
	END IF;
END LOOP;
DBMS_OUTPUT.put_line('LOOP循环已经结束；');
END;
/
--EXIT 默认表示退出当前的循环，后面加标签可以终止并退出指定的LOOP循环
```

```plsql
--WHILE...LOOP
[ <<lable_name>> ]
WHILE boolean_expression
LOOP
	statement...
END LOOP [label_name] ;
--FOR...LOOP
[ <<lable_name>> ]
FOR index_name IN --循环计数器，该变量可以得到当前的循环次数，但是不能对其赋值
[REVERSE]	--循环方式，默认从下到上如果有REVERSE,那么从上到下
lower_bound .. upper_bound --下标界和上标界，中间用..连接
LOOP
statement...
END LOOP [label_name] ;
```

### PL/SQL中的异常

- 预定异常

|      Exception      | ORA ERROR | SQL CODE |           Condition           |
| :-----------------: | :-------: | :------: | :---------------------------: |
|   CASE_NOT_FOUND    | ORA-06592 |  -6592   | case语句中，when子句没有匹配条件且没有else语句 |
|   NOT_DATA_FOUND    | ORA-01403 |   +100   |     select...into语句没有返回记录     |
|    TOO_MANY_ROWS    | ORA-01422 |  -1422   |    select...into语句返回多于一条记录    |
|  DUP_VAL_ON_INDEX   | ORA-00001 |    -1    |       表中唯一索引所对应的列上出现重复值       |
|     VALUE_ERROR     | ORA-06502 |  -06502  |          赋值时，变量长度不够           |
|     ZERO_DIVIDE     | ORA-01476 |  -1476   |             除数为0              |
|    STORAGE_ERROR    | ORA-06500 |  -6500   |            内存溢出或破坏            |
| TIMEOUT_ON_RESOURCE | ORA-00051 |   -51    |            等待资源超时             |
| CURSOR_ALREADY_OPEN | ORA-06511 |  -6511   |          打开一个已经打开的游标          |

利用下面的语句可以查询Oracle所有预定异常

SELECT * FROM DBA_SOURCE WHERE NAME='STANDARD' AND TEXT LIKE '%EXCEPTION_INIT%';

- 非预定异常

Oracle中的异常更多都是非预定义异常，也就是说，它们只有错误的编号和相关的错误描述，而没有名称的异常是不能捕捉的。

为一个非预定义异常定义名称需要如下两步：

1) 声明一个异常的名称

2) 把这个名称和异常的编号相互关联

```plsql
--由于产品表PRODUCTINFO中的产品类型引用了产品类型表CATEGROYINFO的编码，所以当修改产品类型编码时有可能造成PRODUCTINFO产生垃圾数据。为了避免这种情况，表PRODUCTINFO中可以使用外键约束，这时候如果直接修改PRODUCTINFO表中的产品类型编码，就有可能导致ORA-02291错误

DECLARE
v_ctgy VARCHAR2(10);

my_2291_exp EXCEPTION; --声明异常名称
PRAGMA EXCEPTION_INIT(my_2291_exp,-2291); --把异常名称和数据库错误号关联

BEGIN
	v_ctgy := '1111111111';
	UPDATE PRODUCTINFO SET PRODUCTINFO.CATEGORY = v_ctgy；
EXCEPTION 
	WHEN my_2291_exp THEN
	DBMS_OUTPUT.PUT_LINE('违反完整约束条件，未找到父项关键字
                         ！');
	DBMS_OUTPUT.PUT_LINE('SQLERRM: ' || SQLERRM);--错误信息
	DBMS_OUTPUT.PUT_LINE('SQLCODE: ' || SQLCODE);--错误代码
	ROLLBACK; --回滚，SQL语句未commit之前恢复数据

END;
/
```

- 自定义异常

如果开发中遇到与实际业务相关的错误，例如产品数量不允许为负数，生产日期必须在保质日期之前等，这些与业务相关的问题并不能算是系统错误，也不能使用预定义和非预定义异常来捕捉。如果想用异常的方式处理这些问题，那么这样的异常需要开发人员自己编写，而且在调用时也需要显示的触发。

```plsql
--根据输入的产品ID得到产品数量，如果产品数量小于0，则抛出异常，并作出提示
DECLARE
v_prcid PRODUCTINFO.Productid%TYPE := '&产品ID'; --替换变量，利用替换变量可以达到创建通用脚本的目的，当执行程序时会提示输入替换数据，最后运行到脚本的是替换后的数据。
v_qunty PRODUCTINFO.Quantity%TYPE;
	
quantity_exp EXCEPTION;
PRAGMA EXCEPTION_INIT(quantity_exp,-20001); --关联一个错误号，范围是-20999~-20000

BEGIN
	SELECT quantity INTO v_qunty
	FROM PRODUCTINFO
	WHERE productid = v_prcid;
	
	IF v_qunty < 0 THEN 
		RAISE quantity_exp; --抛出异常
	END IF;
		
	DBMS_OUTPUT.PUT_LINE('该产品的数量是：  ' || v_qunty);
	
EXCEPTION
	WHEN quantity_exp THEN
		DBMS_OUTPUT.PUT_LINE('该产品的数量为空数据，请核查！');
		ROLLBACK; --回滚 
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('没有对应的数据！');
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('对应数据过多，请确认！ ');
	
END;
/
```

###	PL/SQL函数编写

#### 函数创建语法

```plsql
CREATE [OR REPLACE] FUNCTION [ schema.] function_name
[
  (parameter_declaration [, parameter_declaration] ) 
]
RETURN datatype
{ IS | AS }
[ declare_section ]
BEGIN
	statement [ statement | pragma ]...
	[ EXCEPTION exception_handler [ exception_handler ]... ]
END [ name ];
--[OR REPLACE]: 覆盖同名函数 FUNCTION：关键字，表示创建的是函数 schema.：模式名称 parameter_declaration :函数参数，有IN，OUT，IN OUT三种类型 
--RETURN datatype：表示函数的返回类型 
--{ IS | AS } ： 二选一。该项之后是PL/SQL块
```

函数利用RETURN可以返回一个参数，某种情况下需要得到函数内的多个数据，那么可以采用OUT类型参数的方法。

```plsql
--函数使用IN OUT 类型的参数，函数有两个参数，产品类型编码和价格，求出该产品类型下比指定价格高的产品的平均价格，并返回范围内最少的产品数量
CREATE FUNCTION AVG_PRIC(V_CTGRY IN VARCHAR2,--产品类型和指定价格
                        V_PRIC IN OUT VARCHAR2) 
RETURN NUMBER IS V_QNTY NUMBER; --利用min函数得到的产品数量

BEGIN
	IF V_PRIC IS NULL THEN
		V_PRIC := 0;
	END IF;
	
	SELECT AVG(PRODUCTPRICE),MIN(QUANTITY)
	INTO V_PRIC,V_QNTY
	FROM PRODUCTINFO
	WHERE CATEGORY = V_CTGRY
		AND PRODUCTPRICE>V_PRIC;
	RETURN V_QNTY;

EXCEPTION
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('没有对应的数据！');
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('对应数据过多，请确认！');
END;
/
--调用函数，在pl/sql块内调用，只有这样才能获取out类型参数的值，否则只能得到return的值

DECLARE
V_CTGRY VARCHAR2(10) := '0100030002';
v_PRIC 	VARCHAR2(20) := 1500;
V_QUNT	vARCHAR2(20);			

BEGIN 
	V_QNTY := AVG_PRIC(V_CTGRY, V_PRIC);  
	DBMS_OUTPUT.PUT_LINE('平均价格 ' || V_PRIC);
	DBMS_OUTPUT.PUT_LINE('最低的产品数量是 ' || V_QNTY);
END;
```

#### 查看函数

函数一旦创建成功，就会存储在Oracle服务器中，随时可以调用，也可以查看具体脚本。对于当前用户所在模式，用户可以再数据字典USER_PROCEDURES中查看其属性，在数据字典USER_SOURCE中查看其源脚本。这两个数据字典属于视图，利用这两个视图不仅可以查看函数的相关信息。也可以查看存储过程的相关信息。除了这两个视图外，也可以再数据字典视图DBA_PROCEDURES和数据字典视图DBA_SOURCE查看同样的信息。

```plsql
--在SQL*Plus下执行查询脚本，查看已有的函数名称
COL OBJECT_NAME FROMAT A60
--格式化字段长度，避免出现自动换行的情况
SELECT OBJECT_NAME,OBJECT_ID,OBJECT_TYPE
FROM USER_PROCEDURES
ORDER BY OBJECT_TYPE;
--查看已有函数的源脚本
COL NAME FORMAT A15
COL TEXT FORMAT A80
SELECT NAME,LINE,TEXT FROM USER_SOURCE WHERE NAME='AVG-PRIC';
```

修改函数，利用REPLACE关键词，从而完成修改

删除函数：DROP FUNCTION [schema.] function_name

## 游标——数据的缓存区

### 什么是游标

游标的使用可以让用户想操作数组一样操作查询出来的数据集，实际上，它提供了一种从集合性质的结果中提取单挑记录的手段。

游标(Cursor)形象地看出一个变动的光标。它实际上是一个指针，它在一段Oracle存放数据查询结果集的内存中，它可以指向结果集中的任意记录，初始是指向首记录。想数组的结构。

#### 游标的种类：

Oracle游标分静态游标和REF游标两种，其中静态游标像一个数据快照，打开游标后的结构集是对数据库数据的一个备份，数据不随着对表执行DML操作改变。

静态游标分成两种：

- 显示游标：是指在使用之前有明确的游标声明和定义，这样游标定义会关联数据查询语句，通常会返回一行或多行。打开游标后，用户可以利用游标的位置对结果集进行任何操作，显示游标有用户控制。
- 隐式游标：它被PL/SQL自动关联，也叫SQL游标，由Oracle管理，用户无法控制但可以得到它的属性信息

### 显示游标

```plsql
--创建语法
CURSOR cursor_name
	[(parameter_name datatype,...)]
		IS select_statement;
--声明游标
DECLARE CURSOR cursor_name
IS SELECT_STATEMENT
--打开游标
OPEN cursor_name
--读取数据
FETCH cursor_name INTO Record_name
--关闭游标
CLOSE cursor_name
```

```plsql
--创建一个游标并使用它
DECLARE
	CURSOR pdct_cur
	IS SELECT * FROM PRODUCTINFO ;
	cur_prodrcd productinfo%ROWTYPE;
	
BEGIN
	OPEN pdct_cur;
		FETCH pdct_cur INTO cur_prodrcd;
		DBMS_OUTPUT.PUT_LINE(cur_prodrcd.productid || '-' || cur_prodrcd.productname || '-' || cur_prodrcd.productprice);
	CLOSE pdct_cur;
END;
```

#### 游标中的LOOP语句

通常显示游标的数据不止一条，而是多条记录。这样就需要一个遍历结果集的方式，而LOOP语句就能实现该功能。

```plsql
DECLARE
CURSOR pdct_loop_cur
IS SELECT PRODUCTID,PRODUCTNAME,PRODUCTPRICE FROM PRODUCTINFO WHERE PRODUCTPRICE > 2500;

cur_productid prodcuctinfo.Productid%TYPE;
cur_productname prodcuctinfo.Productname%TYPE;
cur_productprice prodcuctinfo.Productprice%TYPE;

BEGIN
	OPEN pdct_loop_cur;
	LOOP
		FETCH proct_loop_cur INTO cur_productid,cur_productname,cur_productprice;
		EXIT WHEN pdct_loop_cur%NOTFOUND;
		DBMS_OUTPUT.PUT_LINE('产品ID：' || cur_productid ||' 产品名称： ' || cur_productname ||' 产品价格：' || cur_productprice);
	END LOOP;
	CLOSE pdct_loop_cur;
END;
```

#### 使用BULK COLLECT和FOR语句的游标

游标中通常使用FETCH...INTO...语句提取数据，这种方式是单条数据提取，而FETCH...BULK COLLECT INTO 语句可以批量提取数据

```plsql
DECLARE 
CURSOR pdct_collect_cur
IS SELECT * FROM PRODUCTINFO;

TYPE PDCT_TAB IS TABLE OF PRODUCTINFO%ROWTYPE;
pdct_rd PDCT_TAB;

BEGIN
	OPEN pdct_collect_cur;
	LOOP
		FETCH pdct_collect_cur BULK COLLECT INTO pdct_rd LIMIT 2;
		FOR i in 1..pdct_rd.count LOOP
			DBMS_OUTPUT.PUT_LINE('产品ID：' || 		pdct_rd(i).productid || ' 产品名称：' ||prct_rd(i).productname|| ' 产品价格：' || pdct_id(i).productprice);

		END LOOP;
		EXIT WHEN pdct_collect_cur%NOTFOUND;

	END LOOP;
CLOSE pdct_collect_cur;
END;
```

#### 使用CURSOR FOR LOOP

游标很多机会都是迭代结果集，我们可以使用更简单的方式实现，CURSOR FOR LOOP不需要特别的声明变量，它可以提出行对象类型的数据。

```plsql
DECLARE
 CURSOR cfl IS SELECT productname,productprice FROM PRODUCTINFO WHERE  productprice > 1200;
BEGIN 
	FOR  curcfl IN cfl
	LOOP 
		DBMS_OUTPUT.PUT_LINE('名称： ' || curcfl.productname || ' 产品价格： ' || curcfl.prodycrprice);
END LOOP;
END;
```

显示游标的属性

- %ISOPEN 判断是否打开，打开返回TRUE
- %FOUND 检测行数据是否有效，有效返回TRUE
- %NOTFOUND 如果没有提取返回TRUE
- %ROWCOUNT  累计到当前为止使用FETCH提取数据的行数

#### 带参数的游标

使用显示游标时是可以指定参数的，指定的参数包括参数的顺序和参数的类型。参数可以传递给游标在查询中使用，这样就方便了用户根据不同的查询条件进行查询，也方便了游标在存储过程中的使用。

```plsql
DECLARE
	cur_productid productinfo.Productid%TYPE := '0240';
	cur_productprice productinfo.Productprice%TYPE := '1200';
	cur_prodrcd productinfo%TYPE;

	CURSOR pdct_parameter_cur (id VARCHAR,price NUMBER)
	IS SELECT * FROM PRODUCTINFO
	WHERE productid like id ||'%' 
	AND productprice > price;
BEGIN 
	OPEN pdct_parameter_cur(cur_productid,cur_productprice);
		LOOP 
			FETCH pdct_parameter_cur INTO cur_prodrcd;
			EXIT WHEN pdct_parameter_cur%NOTFOUND;
			DBMS_OUTPUT.PUT_LINE('产品ID：' || cur_prodrcd.productid || '产品名称： ' || cur_prodrcd.productname || ' 产品价格：' || cur_prodrcd.productprice);
		END LOOP;
	CLOSE pdct_parameter_cur;
END;
```

### 隐式游标

每当运行SELECT或DML语句时，PL/SQL会打开一个隐式的游标。隐式游标不受用户的控制，这一点和显示游标有明显的不同。

- 隐式游标由PL/SQL自动管理
- 隐式游标的默认名称是SQL
- SELECT或DML操作产生隐式游标；
- 隐式游标的属性值始终是最新执行的SQL语句

```plsql
DECLARE
	cur_productname productinfo.Productname%TYPE;
	cur_productprice productinfo.Productprice%TYPE;
BEGIN 
	SELECT productname,productprice INTO cur_productname,cur_productprice
	FROM PRODUCTINFO
	WHERE productid = '0240040001';
	IF SQL%FOUND THEN
		DBMS_OUTPUT.PUT_LINE('产品名称： ' || cur_productname || ' 产品价格： ' || cur_productprice);
	END IF ;
END;
```

隐式游标的属性

- %ISOPEN 判断是否打开，永远返回FALSE
- %FOUND 检测DML操作是否有效，有效返回TRUE
- %NOTFOUND 如果没有提取返回TRUE
- %ROWCOUNT  DML操作对数据影响的数量

## 视图——数据库中虚拟的表

### 什么是视图

视图是一个基于一个表或多个表的逻辑表，视图本身不包含任何数据。当基表中的数据发生变化时，视图里的数据同样发生变化。通常视图的数据源有：单一表的子集，多表操作结果集，视图的子集

视图的作用：使数据简化，使数据更加独立，增加安全性

视图的语法

```plsql
CREATE [ OR REPLACE ] [[ NO ] FORCE ] VIEW --FROCE 强制创建视图
	[ schema. ]view
	[(alias,...) inline_constraint(s)] --别名和内联约束
		[out_of_line_constraint(s)]
AS subquery
[
  	WITH { READ ONLY | CHECK OPTION [ CONSTRAINT constraint ]} --read only只读视图 
  --CHECK OPTION [ CONSTRAINT constraint ] 一旦使用，当对视图增加或者修改数据时必须满足子查询的条件。
];

```
#### 创建视图

```plsql
--单表视图
CREATE OR REPLACE VIEW SIMPLE_PRODUCTINFO_VIEW
AS
	SELECT PRODUCTID,PRODUCTNAME,PRODUCTPRICE,CATEGORY,ORIGIN
	FROM PRODUCTINFO
	WHERE ORIGIN = 'CHINA'
	AND ROWNUM < 6;
--多表视图
CREATE OR REPLACE VIEW MULTI_PRODUCTINFO_VIEW 
AS 
	SELECT PT.PRODUCTID,PT.PRODUCTNAME,PT.PRODUCTPRICE,PT.CATEGORY,CG.CATEGROYNAME,PT.ORIGIN
	FROM PRODUCTINFO PT,CATEGROYINFO CG
	WHERE PT.CATEGORY = CG.CATEGROYID
	AND PT.ORIGIN = '中国'
	AND ROWNUM < 10;
--视图中的视图
CREATE OR REPLACE VIEW VI_PRODUCTINFO_VIEW
AS
	SELECT PRODUCTID,PRODUCTNAME,PRODUCTPRICE,CATEGROYNAME,ORIGIN
	FROM MULTI_PRODUCTINFO_VIEW;
--没有源表的视图
CREATE OR REPLACE FORCE VIEW NOTABLE_PRODUCTINFO_VIEW 
AS
	SELECT PRODUCTID,PRODUCTNAME,PRODUCTPRICE,CATEGROYNAME,ORIGIN
	FROM NOTABLE
```

#### 创建带约束的视图

```plsql
CREATE OR REPLACE VIEW CONST_PRODUCTINFO_VIEW
(
  PRODUCTID,
  PRODUCTNAME CONSTRAINT PRODUCTNAME_UNQ UNIQUE RELY DISABLE NOVALIDATE, --使用inline方式对productname创建UNIQUE约束
  PRODUCTPRICE,
  QUANTITY,
  CATEGORY,
  ORIGIN,
  CONSTRAINT VI_PRODUCTID_PRK PRIMARY KEY (PRODUCTID) RELY DISABLE NOVALIDATE --用out_of_line方式对视图设置主键约束
  --RELY DISABLE NOVALIDATE 表示约束对此前此后的数据都不进行检查，并告知Oracle此视图现在符合这两种约束
)
AS
	SELECT PRODUCTID,PRODUCTNAME,PRODUCTPRICE,QUANTITY,CATEGORY,ORIGIN
	FROM PRODUCTINFO
	WHERE ORIGIN = 'CHINA'
	WITH CHECK OPTION;
```

#### 对操作视图数据的限制

视图允许我们进行DML操作，但视图的增加和更新实际上是在源表中进行的，所以我们可以对视图进行设置更新限制条件。

视图的只读属性：在最后加上WITH READ ONLY

视图的检查约束： WITH CHECK OPTION 

该选项表示视图启动了和子查询条件一样的约束，也就是说，如果对视图修改或插入的数据和查询条件不一致，那么该操作就会被终止。

如果你想要一个可以更新的视图，源表尽量是单表，否则限制比较多，下面的情况一旦出现在视图中，视图就不允许更新

- DISTINCT关键字
- 集合运算或分组函数，如INTERSECT,SUM,MAX,COUNT
- 出现GROUP BY,ORDER BY,MODEL,START WITH等语句
- 出现伪列关键字，如ROWNUM

#### 对视图约束的修改

```plsql
ALTER VIEW [schema.] view
ADD [CONSTRAINT constraint_name] 
{UNIQUE (column [,column ]...)
| PRIMARY KEY (column [,column ]...)
| FOREIGN KEY (column [,column ]...)
	references_clause
| CHECK (condition) 
}
[constraint_state]  --约束声明

--增加约束
ALTER VIEW SIMPLE_PRODUCTINFO_VIEW
ADD CONSTRAINT PUTPRIC_UNQ UNIQUE (PRODUCTPRICE)
DISABLE NOVALIDATE;
--查看约束
SELECT CONSTRAINT_NAME,TABLE_NAME,R_OWNER,R_CONSTRAINT_NAME
FROM USER_CONSTRAINTS
WHERE TABLE_NAME = 'SIMPLE_PRODUCTINFO_VIEW';
--删除约束
ALTER VIEW SIMPE_PRODUCTINFO_VIEW
DORP CONSTRAINT PUTPRIC_UNQ;
```

#### 删除视图

```plsql
DROP VIEW [.shcema.] view [CASCADE CONSTRAINTS] --删除视图时删除约束
```

## 存储过程——提高程序执行的效率

### 什么是存储过程

存储过程是一段存储在数据库中执行某种功能的程序，其中包含一条或多条SQL语句，它的定义港式和块，包等有所区别。存储过程可以投诉的理解为存储在数据库服务器中的封装了一段或多段SQL语句中的代码块。

存储过程的优点：

- 简化复杂的操作
- 增加数据独立性
- 提高安全性
- 提高性能

存储过程的语法

```plsql
CREATE [ OR REPLACE ] PROCEDURE [ schema. ] procedure_name
	[parameter_name [ [ IN ] datatype [ { := | DEFAULT} expression ] | { OUT | IN OUT }[ NOCOPY ] datatype ][,....]
     {IS | AS }
     BODY ;
 -- [ IN ] datatype [ { := | DEFAULT} expression ] ：整个这段语法表示传入参数的数据类型以及默认值。其中，OUT表示输出参数，IN OUT表示既可输入也可输出的参数，datatype依旧表示参数类型
 --BODY:表示函数体，是存储过程的具体操作部分
```

### 存储过程

#### 创建存储过程

```plsql
CREATE PROCEDURE TEST
AS
BEGIN
	DBMS_OUTPUT.PUT_LINE('我的第一个过程！');
END;
--执行
--SERVEROUTPUT设置，想让DBMS_OUTPUT.PUT_LINE成功输出，需要把SERVEROUTPUT选项设置为ON的状态
SHOW SERVEROUTPUT
SET SERVEROUTPUT ON 
BEGIN 
	TEST;
END;
--还具体在关键词EXEC后面加上存储过程名来执行以及存在的存储过程
```

#### 查看存储过程

```plsql
SELECT * FROM USER_SOURCE WHERE NAME= 'TEST' ORDER BY LINE ;
--从视图USER_SOURCE中查询过程或函数时需要把名称大写

--查看存储过程TEST_ERR的错误
SHOW ERRORS PROCEDURE TEST_ERR;
```

#### 无参存储过程

无参存储过程就是创建的存储过程不带任何参数，通常这种存储过程用做数据转换的几率比较大。

```plsql
--把表productinfo中价格最低的3件产品的desperation字段设置为’促销商品‘
CREATE PROCEDURE PRODUCT_UPDATE_PRC
AS
BEGIN 
UPDATE PRODUCTINFO SET DESPERATION = '促销产品'
WHERE PRODUCTID IN
(
  SELECT PRODUCTID FROM
  ( SELECT * FROM PRODUCTINFO ORDER BY PRODUCTPRICE ASC )
  WHERE ROWNUM < 4
);
COMMIT;
END;
```

#### 存储过程中使用游标

```plsql
--要求把productinfo表中数据根据不同的产品类型分类把数据输出到屏幕
CREATE PROCEDURE PRODUCT_CUR_PRC
AS
cur_ctgy productinfo.category%TYPE;
cur_ctgyname categroyinfo.categroyname%TYPE;
cur_prtifo productinfo%ROWTYPE;

CURSOR cur_category
IS 
SELECT CATEGORY FROM PRODUCTINFO GROUP BY CATEGORY;

BEGIN 
	OPEN cur_category;
	LOOP
		FETCH cur_category;
		EXIT WHEN cur_category%NOTFOUND;
			SELECT CATEGORYINFO.CATEGROYNAME INTO cur_ctgyname
			FROM CATEGROYINFO
			WHERE CATEGROYID = cur_ctgy;
				IF SQL%FOUND THEN
					DBMS_OUTPUT.PUT_LINE('---------------');
					DBMS_OUTPUT.PUT_LINE(cur_ctgyname || ':');
				END IF;
			
			FOR my_prdinfo_rec IN
			(
              	SELECT * FROM PRODUCTINFO WHERE CATEGORY = cur_ctgy
            )
				LOOP
				 DBMS_OUTPUT.PUT_LINE(
                   					'产品名称: ' || my_prdinfo_rec.PRODUCTNAME|| '产品价格: ' || my_prdinfo_rec.PRODUCTPRICE|| '产品数量：' || my_prdinfo_rec.QUANTITY
                 					  );
				END LOOP;
		END LOOP;
	CLOSE cur_category;
END ;
```

#### 存储过程中的DDL语句

有时候我们会在操作数据的时候使用临时表，而为了让存储过程根据有通用性，可以选择把创建临时表的步骤一并放到过程里。这样的操作会和前面介绍的两种示例写法有所不同，它会用到EXECUTE IMMEDIATE语句，存储过程中会使用它来执行DDL语句和动态SQL语句

```plsql
--要求把各种不同类型的产品中价格最低的输入到临时表PRODUCTINFO_TMP(此表需要创建)中，并在其中DESPERATION字段注明“热销商品“，如果记录中价格低于20则表示数据有问题，需要输出到屏幕

CREATE PROCEDURE PRODUCT_TMEP_UPDATE_PRC
AS

pc_delestr 	VARCHAR2(50);
pc_createstr	VARCHAR2(500);
pc_insrtstr	VARCHAR2(500);
tabext VARCHAR2(10); --判断临时表是否存在中间变量

cur_ctgy productinfo.Category%TYPE;
cur_prtifo productinfo%ROWTYPE;

CURSOR cur_category
IS
SELECT CATEGORY FROM PRODICTINFO GROUP BY CATEGORY;

CURSOR cur_proinfo(ctgy varchar)
IS
SELECT * FROM 
(SELECT * FROM PRODUCTINFO WHERE CATEGORY = ctgy ORDER BY PRODUCTPRICE ASC)
WHERE ROWNUM < 2;

BEGIN 
	SELECT COUNT(1)INTO tabext
	FROM ALL_TABLES
	WHERE TABLE_NAME = 'PRODUCTINFO_TMP'
	
	pc_delestr:= 'DELECTE FROM PRODUCTINFO_TMP'
	
	pc_createstr := 'CREATE GLOBAL TEMPORARY TABLE PRODUCTINFO_TMP
	(
      	PRODUCTID VARCHAR2(10) NOT NULL,
      	PRODUCTNAME VARCHAR2(20),
      	PRODUCTPRICE NUMBER(8，2),
      	QUANTITY NUMBER(10),
      	CATEGORY VARCHAR2(10),
      	DESPERATION VARCHAR2(1000),
      	ORIGIN	BARCHAR2(10)
    )On Commit Preserve Rows';
      
     if tabext=0 then  --不存在就创建一个
      	EXECUTE IMMEDIATE pc_createrstr;
      	DBMS_OUTPUT.PUT_LINE('创建临时表成功');
      else
      	EXECUTE IMMEDIATE pc_delestr;
      	DBMS_OUTPUT.PUT_LINE('删除记录完成');
      end if;
      
	OPEN cur_category;
    LOOP
      FETCH cur_category INTO cur_ctgy;
      EXIT WHEN cur_category%NOTFOUND;
      		OPEN cur_proinfo(cur_ctgy);
      			FETCH cur_proinfo INTO cur_prtifo;
      			IF cur_proinfo%FOUND THEN
      				IF cur_prtifo.PRODUCTPRICE < 20 THEN --产品价格低于20的打印出来
      					DBMS_OUTPUT.PUT_LINE('产品ID：'||cur_prtifo.PRODUCTID||'产品名称：' ||cur_prtifo.PRODUCTNAME||' 产品价格：' || cur_prtifo.PRODUCTPRICE
    				);
      				ELSE    --非低于20价格的产品输入到临时表 
     		    	EXECUTE IMMEDIATE 'INSERT INTO PRODUCTINFO_TMP(PRODUCTID,PRODUCTNAME.PRODUCTPRICE,QUANTITY,CATEGORY,DESPERATION,ORIGIN) VALUES (...||cur_prtifo.PRODUCTID||...,...||cur_prtifo.PRODUCTNAME||...,...||cur_prtifo.PRODUCTPRUCE||...,...||cur_prtifo.QUANTITY||...,...||cur_prtifo.CATEGORY||...,...||cur_prtifo.DESPERATION||...,...||cur_prtifo.ORIGIN||...)';
      				END IF;
      			END IF;
      		CLOSE cur_proinfo;
      	END LOOP;
      		COMMIT;
      	CLOSE cur_category;
      	EXECUTE IMMEDIATE 'UPDATE PRODUCTINFO_TMP SET DESPERATION = ''热销商品''',
     END;
```

#### 有参存储过程

存储过程允许带有参数，参数的使用将增加存储过程的灵活性。存储过程中如果使用了参数，在执行存储过程时必须为其指定的参数。

```plsql
--使用输入参数的存储过程
--根据输入的产品类型从表PRODUCTINFO中搜索符合要求的数据，并将其打印到屏幕
CREATE PROCEDURE PRODUCT_INTYPE_PRC (parm_ctgyname IN VARCHAR2)
AS
cur_ctgyid categroyinfo.categroyid%TYPE;
cur_prtifo productinfo%ROWTYPE;

BEGIN
	SELECT CATEGROYINFO.CATEGROYID INTO cur_ctgyid
	FROM CATEGROYINFO
	WHERE CATEGROYINFO.CATEGROYNAME = parm_ctgyname;
	--根据类型编码得到产品类型名称
		IF SQL%FOUND THEN 
			DBMS_OUTPUT.PUT_LINE('----------------');
			DBMS_OUTPUT.PUT_LINE(parm_ctgyname || ':');
		END IF;
		FOR my_prdinfo_rec IN
		(
          SELECT * FROM PRODUCTINFO WHERE CATEGORY = cur_ctgyid
        )
		LOOP
			DBMS_OUTPUT.PUT_LINE(
              					'产品名称： ' || my_prdinfo_rec.PRODUCTNAME || '产品价格： '|| my_prdinfo_rec.PRODUCTPRICE || '产品数量： ' || my_prdinfo_rec.QUANTITY
            					);
		END LOOP;
		EXCEPTION
		WHEN NO_DATA_FOUND THEN
			DBMS_OUTPUT.PUT_LINE('没有数据： ');
		WHEN TOO_MANY_ROWS THEN
			DBMS_OUTPUT.PUT_LINE('数据过多： ');
END;
```

```plsql
--使用参数的默认值
--根据输入的产品类型查询对应产品类型编码的功能，有默认值

--step 1 穿件函数，函数将返回”雨具“字符串
CREATE OR REPLACE FUNCTION DEFT RETURN VARCHAR2
IS 
BEGIN 
	DBMS_OUTPUT.PUT_LINE("---已进入函数----");
	DBMS_OUTPUT.PUT_LINE("默认类型是雨具");
	RETURN '雨具'
END DEFT;
--STEP2 创建存储过程
CREATE PROCEDURE PRODUCT_INTYPE_DEFT_PRC(parm_ctgyname IN VARCHAR2 DEFAULT DEFT() )
AS
cur_ctgyid categroyinfo.categroyid%TYPE;

BEGIN 
	SELECT CATEGROYINFO.CATEGROYID INTO cur_ctgyid;
	FROM CATEGROYINFO
	WHERE CATEGROYINFO.CATEGROYNAME = parm_ctgyname;

	IF SQL%FOUND THEN
		DBMS_OUTPUT.PUT_LINE('---------------');
        DBMS_OUTPUT.PUT_LINE(parm_ctgyname || ':');        		END IF;        
	FOR my_prdinfo_rec IN        
	(          
      SELECT * FROM PRODUCTINFO WHERE CATEGORY = cur_ctgyid     )        
	LOOP            
		DBMS_OUTPUT.PUT_LINE(                                								'产品名称： ' || my_prdinfo_rec.PRODUCTNAME || '产品价格： '|| my_prdinfo_rec.PRODUCTPRICE || '产品数量： ' || my_prdinfo_rec.QUANTITY                                
                            );        
	END LOOP;        
	EXCEPTION        
	WHEN NO_DATA_FOUND THEN            			 					DBMS_OUTPUT.PUT_LINE('没有数据： ');        
	WHEN TOO_MANY_ROWS THEN            								DBMS_OUTPUT.PUT_LINE('数据过多： ');
	END;
```

```plsql
--输出类型参数的使用
--step1 创建被调用的存储过程，该过程根据输入的产品类型查询出对应的产品类型编码功能，并将编码放到输出参数中

CREATE PROCEDURE PRODUCT_OUTTYPE_PRC(parm_ctgyname IN VARCHAR2, parm_ctgyid OUT VARCHAR2)
AS
BEGIN 
	SELECT CATEGROYINFO.CATEGROYID INTO parm_ctgyid
	FROM CATEGROYINFO
	WHERE CATEGROYINFO.CATEGROYNAME = parm_ctgyname;
		IF SQL%FOUND THEN
			DBMS_OUTPUT.PUT_LINE('传出参数是： ' || parm_ctgyid);
		END IF;
	EXCEPTION
	WHEN NO_DATA_FOUND THEN            			 					DBMS_OUTPUT.PUT_LINE('没有数据： ');        
	WHEN TOO_MANY_ROWS THEN            								DBMS_OUTPUT.PUT_LINE('数据过多： ');
	END;

--STEP2创建调用存储过程，该过程根据输入的产品类型以及价格从表PRODUCTINFO中查询符合要求的数据并输出
CREATE PROCEDURE PRODUCT_CLOUTTYPE_PRC(parm_ctgyname IN VARCHAR2,parm_pric NUMBER)
AS
cur_ctgyid categroyinfo.categoryid%TYPE;
cur_prtifo productinfo%ROWTYPE;

BEGIN
		PRODUCT_OUTTYPE_PRC(parm_ctgyname,cur_ctgyid);
		IF SQL%FOUND THEN
			DBMS_OUTPUT.PUT_LINE('--------')；
			DBMS_OUTPUT.PUT_LINE(parm_ctgyname || '对应的编码是:' || cur_ctgyid); 
		END IF;
		 FOR my_prdinfo_rec IN 
			(
              SELECT * FROM PRODUCTINFO
              WHERE CATEGORY = cur_ctgyid
              AND PRODUCTINFO.PRODUCTPRICE < parm_pric
            )
			LOOP
				DBMS_OUTPUT.PUT_LINE(
                				'产品名称： ' || my_prdinfo_rec.PRODUCTNAME || '产品价格： '|| my_prdinfo_rec.PRODUCTPRICE || '产品数量： ' || my_prdinfo_rec.QUANTITY                                
                            );  	
			END LOOP;
END;
```

```plsql
--使用输入输出类型的参数
--step1 创建被调用的存储过程，该过程提供根据输入的产品类型编号和降价比例对表PRODUCTINFO的数据进行降价修改，并返回修改的记录数
CREATE PROCEDURE PRODUCT_INOUTTYPE_PRC(parm_ctgyid IN VARCHAR2, parmparm_pric  IN OUT NUMBER)
AS
BEGIN 
	UPDATE PRODUCTINFO
	SET PRODUCTPRICE = PRODUCTINFO.PRODUCTPRICE*(1-parmparm_pric)
	WHERE PRODUCTINFO.CATEGORY = parm_ctgyid;
	IF SQL%FOUND THEN 
		parmparm_pric := SQL%ROWCOUNT;
	END IF;
END PRODUCT_INOUTTYPE_PRC;
--parmparm_pric 输入时表示降价比例输出时表示修改语句修改的记录数
--step2 创建调用存储构成，该过程输入产品类型名称，根据产品类型名称查询出产品类型编码并调用PRODUCT_INOUTTYPE_PRC存储过程，最终输出修改的记录数
CREATE PROCEDURE PRODUCT_CLINOUTTYPE_PRC(parm_ctgyname IN VARCHAR2)
AS
cur_ctgyid categroyinfo.categroyid%TYPE;
cur_pric number;

BEGIN 
	SELECT CATEGROYINFO.CATEGROYID INTO cur_ctgyid
	FROM CATEGROYINFO
	WHERE CATEGROYINFO.CATEGROYNAME = parm_ctgyname;
	
	PRODUCT_INOUTTYPE_PRC(cur_ctgyid,cur_pric);
	IF cur_pric > 0 THEN
		DBMS_OUTPUT.PUT_LINE('共修改' || cur_pric || '条记录。');
	END IF;
	
	EXCEPTION
	WHEN NO_DATA_FOUND THEN            			 					DBMS_OUTPUT.PUT_LINE('没有数据： ');        
	WHEN TOO_MANY_ROWS THEN            								DBMS_OUTPUT.PUT_LINE('数据过多： ');
	END;
```

## 触发器——保证数据的正确性

### 什么是触发器

触发器和存储过程比较类似，它由PL/SQL编写并存储在数据库中，它可以调用存储过程，但触发器的调用和存储过程的不一样，它只能由数据库的特定事件来触发

特定事件主要有：

- 用户在指定的表或视图做DML操作
  - INSERT
  - UPDATE
  - DELECTE
- 用户做DDL操作
  - CREATE
  - ALTER
  - DROP
- 数据库事件
  - LOGON/LOGOFF 用户的登录注销
  - STARTUP/SHUTDOWN 数据库的打开关闭
  - ERRORS 特定错误消息

触发器的作用

- 自动生成自增长字段
- 执行更复杂的业务逻辑
- 防止无意义的数据操作
- 提供审计
- 允许或限制修改某些表
- 实现完整性规则
- 保证数据的同步复制

触发器的类型

- 数据操纵语言(DML)触发器。
- 数据定义语言(DDL)触发器


- 符合触发器
- INSTEAD OF触发器。
- 用户和系统事件触发器

### 触发器的语法

```plsql
--DML触发器的主要语法
CREATE [ OR REPLACE ] TRIGGER [schema.] trigger
{BEFORE | AFTER | INSTEAD OF} --触发类型，前触发，后触发，替换类型 
	{DELETE | INSERT | UPDATE --表示触发的事件
		[OF column [, column ]...] --触发条件具体到的某列
	}
	[ OR {DELETE | INSERT | UPDATE 
     	  [OF column [, column ]...]		
     	 }
  	]...
{ON [schema. ]table | [schema. ] view}
	[FOR EACH ROW ] --表示行级触发器，省略则为语句级触发器
	[FOLLOWS [ schema.] trigger [,[ schema. ] trigger ]...]--触发器执行的顺序
	[ENABLE | DISABLE] --设置触发器是否为可用状态
	[WHEN (condition)]
	trigger_body
```

```plsql
--DDL和数据库事件触发器语法如下：
CREATE [ OR REPLACE ] TRIGGER [schema.] trigger
{ BEFOR | AFTER}
{ ddl_event [OR ddl_event]... --DDL事件，用or连接
| database_event [OR database_event]...
}
ON { [schema.] SCHEMA
  | DATABASE
}
	[FOLLOWS [ schema.] trigger [,[ schema. ] trigger ]...]--触发器执行的顺序
	[ENABLE | DISABLE] --设置触发器是否为可用状态
	[WHEN (condition)]
	trigger_body
```

|     DDL事件     |    简介    |
| :-----------: | :------: |
|     ALTER     |   修改对象   |
|    ANALYSE    |  分析统计信息  |
| AUDIT/NOAUDIT | 启用或取消审计  |
|    COMMENT    | 注解列或表的含义 |
|    CREATE     |   创建对象   |
|     DROP      |   删除对象   |
|     GRANT     |   授权操作   |
|    RENAME     |  修改对象名称  |
|    REVOKE     |   取消权限   |
|   TRUNCATE    |  删除行记录   |

触发器由三部分组成。它们分别是触发事件或语句，触发器限制，触发器动作。

### 使用SQL*PLUS操作触发器

#### 创建触发器

创建触发器的首要条件是要有相关的权限。用户模式下如果想在自己的对象上创建触发器，则必须具有CREATE TRIGGER系统权限，如果想在其他用户上创建触发器，则需要有CREATE ANY TRIGGER权限，如果在数据库上创建触发器。则需要有ADMINISTER DATABASE TRIGGER系统权限。

```plsql
--一个简单的触发器
CREATE TRIGGER FIRST_TGR
	AFTER DELETE
	ON PRODUCTINFO  --触发器作用的表
		BEGIN
	IF DELETING THEN 
		DBMS_OUTPUT.put_line('删除数据操作！ ');
	END IF;
		END;
```

#### 查看触发器

```plsql
--查看触发器的名称。执行如下脚本：
SELECT OBJECT_NAME FROM USER_OBJECTS
WHERE OBJECT_TYPE = 'TRIGGER'
--查看触发器内容，有了触发器名称就可以查看其具体内容
SELECT * FROM USER_SOURCE WHERE NAME = 'FIRST_TGR' ORDER BY LINE;
```

#### DML类型触发器

```plsql
--创建行级触发器，当在productinfo表中增加数据时将激发该触发器
--step1 创建操作事件记录表
CREATE TABLE LOG_TAB
(
  ID	VARCHAR2(10) NOT NULL,
  OPER_TABLE	VARCHAR2(20),
  OPER_KD		VARCHAR2(10),
  OPER_TABLE_PRK	VARCHAR2(50),
  OPER_DATE		DATE,
  constraint 	LOG_TAB_PRK primary key (ID)
)
--step2创建用做LOG_TAB表主键的自增长序列
CREATE SEQUENCE LOG_TAB_ID
MINVALUE	1000000000
MAXVALUE   	9999999999
START WITH  1000000000
INCREMENT BY 1
--step3 创建触发器
CREATE TRIGGER PRODUCTINFO_OPER_TGR
	BEFORE	INSERT
	ON	PRODUCTINFO
		FOR	EACH ROW --每增加一行就会触发一次
		BEGIN
			IF INSERTING THEN
				INSERT INTO LOG_TAB
				VALUES
				(LOG_TAB_ID.NEXTVAL,
                	'PRODUCTINFO',
                 	'INSERT',
                 	:NEW.PRODUCTID,
            		SYSDATE);
			DBMS_OUTPUT.PUT_LINE('插入数据主键是 ' || :new.PRODUCTID);
--在事件记录表中增加数据，LOG_TAB_ID.NEXTVAL表示得到序列的下一个值,SYSDATE系统时间
			END IF;
		END
--行级触发器使用:new或:old来访问变更前和变更后的数据
```

```plsql
--在触发器中使用多种触发事件
CREATE TRIGGER PRODUCTINFO_OPER_DML_TGR
	AFTER INSERT OR UPDATE OR DELETE
	ON PRODUCTINFO
	FOR	EACH ROW
BEGIN
	CASE
		WHEN INSERTING THEN
		INSERT INTO LOG_TAB
		VALUES
			(LOG_TAB_ID.NEXTVAL,
                  'PRODUCTINFO',
                 	'INSERT',
                 	:NEW.PRODUCTID,
            		SYSDATE);
            DBMS_OUTPUT.PUT_LINE('插入数据主键是 ' || :new.PRODUCTID);
		WHEN UPDATEING THEN
		INSERT INTO LOG_TAB
		VALUES
			(LOG_TAB_ID.NEXTVAL,
                  'PRODUCTINFO',
                 	'INSERT',
                 	:NEW.PRODUCTID,
            		SYSDATE);
            DBMS_OUTPUT.PUT_LINE('修改数据主键是 ' || :OLD.PRODUCTID);
		WHEN DELETEING THEN
				INSERT INTO LOG_TAB
		VALUES
			(LOG_TAB_ID.NEXTVAL,
                  'PRODUCTINFO',
                 	'INSERT',
                 	:NEW.PRODUCTID,
            		SYSDATE);
            DBMS_OUTPUT.PUT_LINE('修改数据主键是 ' || :OLD.PRODUCTID);
			END CASE;
		END;
```

```plsql
--在触发器中使用if
CREATE TRIGGER PRODUCTINFO_OPER_CHK_TGR
	BEFORE UPDATE OF PRODUCTPRICE ON PRODUCTINFO
	FOR EACH ROW
BEGIN
	IF (TO_CHAR(SYSDATE,'dd') = 25 AND :OLD.PRODUCTPRICE >3000) THEN RAISE_APPLICATION_ERROR(-20000，'今天是25号，不允许修改价格高于3000的数据！');
--if的判断条件是系统日期是25号而且修改前的价格大于3000
--RAISE_APPLICATION_ERROR，它把应用程序错误传递到客户端，包含两个参数-20999--20000之间的错误代码和错误提示
	INSERT INTO LOG_TAB
	VALUES
			(LOG_TAB_ID.NEXTVAL,
                  'PRODUCTINFO',
                 	'INSERT',
                 	:NEW.PRODUCTID,
            		SYSDATE);
            DBMS_OUTPUT.PUT_LINE('修改数据主键是 ' || :NEW.PRODUCTID);

END;
--在触发器中使用when
CREATE TRIGGER PRODUCTINFO_WHEN_OPER_CHK_TGR
	BEFORE INSERT ON PRODUCTINFO
	FOR EACH ROW
	WHEN (NEW.CATEGORY = '0100050001')
BEGIN
	DBMS_OUTPUT.PUT_LINE('原价格： ' || :NEW.PRODUCTPRICE);
	:NEW.PRODUCTPRICE := :NEW.PRODUCTPRICE * 0.9;
	DBMS_OUTPUT.PUT_LINE('打折后价格： ' || :NEW.PRODUCTPRICE);
END;
--如果要修改:NEW引用的数据(类似脚本第7行的操作)，那么该触发器应为前触发的方式，因为后触发方式中:NEW数据是不允许被修改的，只能被调用，即使能修改也没有任何意义
```

```plsql
--为保证数据的完整性，在某种情况下开发人员会利用触发器实现级联操作功能
--实现级联修改的触发器
--实例为提供级联修改产品类型编码的功能，并把原来的编码存放到CATEGROYINFO_BAK 表中。具体来说就是当表CATEGROYINFO的编码发生变化时，PRODUCTINFO表中CATEGORY字段与之对应的编码同样要变化。

--step1创建备份表
CREATE TABLE CATEGROYINFO_BAK AS SELECT * FROM CATEGROYINFO WHERE 1<>1
--该语句表示复制表结构但不复表数据
--step2 创建触发器
CREATE TRIGGER MUTLI_OPER_CHK_TGR
	AFTER UPDATE OF CATEGROYID ON CATEGROYINFO
	FOR EACH ROW
BEGIN
	UPDATE PRODUCTINFO
	SET CATEGORY = :NEW.CATEGROYID
	WHERE CATEGORY = :OLD.CATEGROYID;
	INSERT INTO CATEGROYINFO_BAK VALUES (:OLD.CATEGROYID, :OLD.CATEGROYNAME);
	
	DBMS_OUTPUT.PUT_LINE('数据已存入 CATEGROYINFO_BAK表中');
END;
```

#### 触发器执行顺序

在同一个对象上可以作用多个触发器，因此触发器被激活是有先后顺序的：

- 首先触发的是前语句级触发器(before statement trigger),该触发器执行一次
- 如果有行级的触发器则接下来执行前行级触发器(before row trigger)该触发器域SQL修改的记录次数一致
- 当SQL修改记录完成后会触发行级触发器，这是的行级触发器为后触发(after statement trigger),该类型触发的次数同SQL修改记录的次数一致
- 执行一次语句级的触发器，此时的语句级的出嘎旗为后与狙击触发器(after statement trigger)

如果相同类型，相同事件触发器作用在同一个对象上，如果在Oracle 11g之前，那么最终被执行的会有一定的随机性，在Oracle 11g中利用FOLLOWS可以控制其顺序

```plsql
CREATE TRIGGER PRODUCTINFO_OPER_ORD_TGR
	BEFORE INSERT
	ON PRODUCTINFO
	FOR EACH ROW 
	FOLLOWS PRODUCTINFO_OPER_TGR
BEGIN
	DBMS_OUTPUT.PUT_LINE('触发器顺序测试');
END;

```

#### 符合类型触发器

复合类型触发器是Oracle 11g 的新特性，属于触发器的增强部分。复合类型的触发器相当于在一个触发器中包含了4种不同类型的触发器，分别是语句之前(before statement),行之前(before row),语句之后(after statement).这么做可以很轻松地把变量在各状态之间传递

利用该类型的触发器还可以很方便地解决ORA-04091错误，这里涉及一个变异表的概念，读者可以理解变异表是正在被DML操作修改的表，也是触发器的作用表，而触发器通常不能对变异表进行操作，下面一个示例将利用复合类型的触发器，解决ORA-04091错误

```plsql
--当productinfo表中的数据提高价格时，触发器判断新旧价格差是否高于价格在2000以下的所有产品价格的平均值的20%，如果高于此值，则提示数据有问题
CREATE OR REPLACE TRIGGER COMPOUND_TGR
	FOR UPDATE ON PRODUCTINFO COMPOUND TRIGGER

V_PRO_AVG NUMBER(10，2) := 0.0;

	BEFORE STATEMENT IS
	BEGIN
		SELECT AVG(PRODUCTPRICE)
		INTO V_PRO_AVG
		FROM PRODUCTINFO
		WHERE PRODUCTINFO.PRODUCTPRICE < 2000;
	END BEFORE STATEMENT;
	
	AFRER EACH ROW IS 
	BEGIN 
		IF :NEW.PRODUCTPRICE - :OLD.PRODUCTPRICE > V_PRO_AVG * 0.20 THEN
			RAISE_APPLICATION_ERROR(-20011，'数据修改错误！');
		END IF;
		END AFTER EACH ROW;
END;
```

#### INSTEAD OF 类型触发器

在该类型的触发器作用下，如果对作用对象执行DML操作，那么该操作会被触发器的内部操作所取代。触发器作用在视图当中，用于解决视图不可更新的问题。至于什么样的视图不可更新

```plsql
--利用INSTEAD OF触发器的使用
--step1,创建视图
	CREATE VIEW PRODUCTINFO_VIEW AS 	--视图
	SELECT DISTINCT PRODUCTNAME,PRODUCTPRICE,QUANTITY,CATEGORY,ORIGIN
	FROM PRODUCTINFO;
--STEP2 创建触发器
	CREATE TRIGGER INSTEAD_OF_TGR
		INSTEAD OF INSERT ON  PRODUCTINFO_VIEW
	DECLARE
		CATEGID VARCHAR2(10);
	BEGIN 
		SELECT CATEGROYID
		INTO	CATEGID
		FROM	CATEGROYINFO
		WHERE	CATEGROYINFO.CATEGROYNAME = :NEW.CATEGORY;
		DBMS_OUTPUT.PUT_LINE('------' || CATEGID);
		INSERT INTO PRODUCTINFO
		VALUES
		('0240090001',
         :NEW.PRODUCTNAME,
         :NEW.PRODUCTPRICE,
         :NEW.QUANTITY,
         CATEGID,
         '测试',
         :NEW,ORIGIN
        	);
END;
```

#### DDL类型触发器

```plsql
--该触发器将提示create创建操作，如果有人执行test表的删除操作，提示错误，也不允许对表使用alter操作和rename操作
CREATE TRIGGER DDL_TGR
	BEFORE CREATE OR ALTER OR DROP OR RENAME ON SCHEMA
BEGIN
	IF SYSEVENT = 'CREATE' THEN
--SYSEVENT 事件属性，当前操作
		DBMS_OUTPUT.PUT_LINE(DICTIONARY_OBJ_NAME || '创建中...');
	ELSEIF SYSEVENT = 'DROP' THEN
		IF DICTIONARY_OBJ_NAME = 'TEST' THEN
--DICTIONARY_OBJ_NAME ，操作的对象名称
			RASIE_APPLICATION_ERROR(-20000,'');
		END IF;
	ELSEIF SYSEVENT = 'ALTER' THEN
		RASIE_APPLICATION_ERROR(-20000,'不允许修改表！');
	ELSEIF SYSEVENT = 'RENAME' THEN
		RASIE_APPLICATION_ERROR(-20000,'不允许修改表名称！');
	END IF;
END;
```

#### 用户和系统事件触发器

所谓的系统触发器，就是基于Oracle系统事件而建立的触发器，该类型的触发器可以审计数据库的登录，注销以及关闭和启动

```plsql
--step1 创建用户登录日志表
CREATE TABLE LOG_USER (
	LOGONID	VARCHAR2(50),
  	LOGONNAME	VARCHAR2(50),
  	LOGONTIME	DATE,
  	CONSTRAINT LOG_USER_PRK	PRIMARY KEY	(LOGONID)
);
--STEP2 创建触发器，该触发器是数据库级，记录每个用户的登录时间
CREATE TRIGGER	LOGON_TGR
AFTER
LOGON
ON	DATABASE
BEGIN
	INSERT INTO	LOG_USER
	VALUES(LOG_TAB_ID.NEXTVAL,SYS.LOGIN_USER,SYSDATE);
END;
```

#### 删除触发器

```plsql
DROP TRIGGER DEV_TGR
```

## 事务和锁——确保数据安全

事务和锁是两个联系非常紧密的概念，它们保证了数据库的一致性。由于数据库是一个可以由多个用户共享的资源，因此当多个用户并发的存取数据时，就要保证数据的准确性。事务和锁就完成了这项功能。

### 什么是事务

事务在数据库中主要用于保证数据的一致性，防止出现错误数据。在事务内的语句都会被看成一个单元，一旦有一个失败，所有的都会失败。

事务就是一组包含一条或多条语句的逻辑单元，每个事务都是一个原子单位，在事务中的语句被作为一个整体，要么一起被提交，作用在数据上，使数据库数据永久的修改，要么一起被撤销，对数据库不做任何修改。

对于这个问题比较经典的例子就是银行账户间的回馈操作。

- 源账户减少存储金额，例如减少1000
- 目标账户增加存储金额，增加1000
- 在事务日志中记录该事务

整个交易过程，我们看做一个事务，如果操作失败，那么事务就会回滚，所有操作就会撤销。

事务在没有提交之前可以回滚，而且在提交前用户可以查看已经修稿的数据，但其他用户查看不到该数据，一旦数据提交就不能再撤销修改了。Oracle的事务基本控制语句有如下几个：

- SET TRANSACTION: 设置事务的属性
- COMMIT  提交事务
- SAVEPOINT  设置保存点
- ROLLBACK   回滚事务
- ROLLBACK TO SAVEPOINT  回滚至保存点

#### 事务的类型

显示方式：利用命令去完成

```plsql
新事务的开始
sql statement
...
COMMIT | ROLLBACK;
```

隐式方式：该类型没有明确的开始和结束，它由数据库自动开启，当一个程序正常结束或使用DDL语言时会自动提交，而操作失败时也会自动回滚，如果设置AUTOCOMMIT为打开状态，每次DML操作都会自动提交。

```plsql
SET AUTOCOMMIT ON/OFF
```

#### 事务的保存点

在事务中可以根据自己的需要设置保存点，保存点可以设置在事务中的如何地方，也可以设置多个点，这样就可以把比较长的事务根据需要分成较小的段。一旦把事务回滚到某个保存点后，Oracle将把保存点之后 持有的锁释放掉，这时先前等待被锁资源的事务就可以继续了。而使事务回滚到保存点，有几点需要了解

- 事务只回滚保存点之后的操作
- 回滚到某保存点时，它一行的保存点将被删除，但保存点会被保留
- 保存点之后的锁将被释放，但之前的会被保留

```plsql
INSERT INTO PRODUCTINFO VALUES('1','保存点测试1',1000,0,00000000,NULL,'测试');

SAVEPOINT FST;

INSERT INTO PRODUCTINGO VALUES('1','保存点测试2',1000,0,00000000,NULL,'测试');

ROLLBACK FST;
```

#### 事务的ACID特性

- 原子性：不可分割，是一个整体，同时成功和撤销
- 一致性：事务执行前后数据库都必须处于一致性状态，只有在事务完成后才能被所有使用者看见
- 分离性：事务之间不能互相的干扰
- 持久性：持久性是指一旦事务提交完成，对数据库就是永久的修改

tips:事务提交很重要，但不建议频繁的提交事务，因为每次提交事务都需要时间。

### 什么是锁

数据库是一个庞大的多用户数据管理系统，由于在多用户系统中，同一时刻多个用户同时操作某相同资源的情况时有发生，而在逻辑上这些用户想同时操作资源是不可能的，而数据库利用锁消除了多用户操作同一资源可能产生的隐患

锁出现在数据共享的环境中，它是一种机制，在访问相同资源时，可以防止事务之间破坏性交互。

锁的分类，Oracle分为两种模式的锁

- 排他锁(X锁)，也叫写锁，防止资源共享，用于数据的修改，加入有事务对数据A加上该锁，那其他事务不能对A加任何锁，所以此时只允许T对该数据进行读取和修改，直到事务完成释放锁为止
- 共享锁(S锁)，也叫读锁，这种模式下数据只能读取，不能修改，如果事务对数据A加了该锁，那么其他事务不能对其加上排他锁，只能加共享锁。加了该锁的数据可以被并发的读取。

锁的类型

- DML锁：该类型的锁被称为数据锁，用于保护数据
  - 行级锁(TX) 也可以称为事务锁。当修改表中某行记录时，需要对将要修改的记录加上行级锁，属于排他锁
  - 表级锁(TM)主要作用是防止在修改表的数据时，表的结构发生变化。会话S在修改表A的数据时它会得到表A的TM锁，而此时将不允许其他会话对该表进行变更或删除操作
- DDL锁：可以保护模式中对象的结构
- 内部闩锁： 保护数据库的内部结构，完全自动调用

在执行DML操作时，数据库会先申请数据对象上的共享锁，防止其他的会话对该对象执行DDL操作，一旦申请成功，会对将要修改的记录申请排他锁，如果此时其他会话正在修改该记录，那么等待期事务结束后再为修改的记录加上排他锁

表级锁报含如下几种模式：

- ROW SHARE 行级共享锁(RS)。该模式下不允许其他的并行会话对同一张表使用排他锁，但允许其利用DML语句或lock命令所得同一张表中的其他记录。select ... from for update 语句就是给记录加上了RS锁
- ROW EXCLUSIVE 行级排他锁(RX)。该模式允许并行会话对同一张表的其他数据进行修改，但不允许并行会话对同一张表使用排他锁
- SHARE，共享锁(s),不允许会话更新表，但允许对表添加RS锁
- SHARE ROW EXCLUSIVE，共享行级排他锁(SRX).该模式下，不能对同一张表进行DML操作，也不能添加S锁
- EXCLUSIVE，排他锁(X)，该模式下，不能对表进行DML和DDL操作，该表只能读

  ​			

|      |  RS  |  S   |  RX  | SRX  |  X   |
| :--: | :--: | :--: | :--: | :--: | :--: |
|  RS  |  y   |  y   |  y   |  y   |  x   |
|  S   |  y   |  y   |  x   |  x   |  x   |
|  RX  |  y   |  x   |  y   |  y   |  x   |
| SRX  |  y   |  x   |  x   |  x   |  x   |
|  X   |  x   |  x   |  x   |  x   |  x   |

```plsql
--主动添加TM锁
LOCK TABLE [SCHEMA.] TABLE IN 
	[EXCLUSIVE]
	[SHARE]
	[ROW EXCLUSIVE]
	[SHARE ROW EXCLUSIVE]
	[ROW SHARE* | SHARE UPDATE*]
	MODE [NOWAIT]
--r如果要释放他们，只需要使用rowback命令
```

#### 锁等待和死锁

在某些情况下有域占用的资源不能及时释放，而造成锁等待，也可以叫锁冲突，锁等待会严重影响数据库性能和日常工作。

死锁和等待不同，它是锁等待的一个特例，通常发生在空格或多个会话之间。假设一个会话想修改两个资源对象，修改这个两个对象在一个事务当中。当它修改第一个对象时需要对其锁定，然后等待第二个对象，这时如果另外一个会话也需要修改这两个资源对象，并且已经获得并锁定了第二个对象，那么就会出现死锁，因为当前会话锁定了第一个对象等待第二个对象，另一个相反，两个会话都不能得到向要的对象，就会出现死锁。

此时oracle自动做出处理，并重新回到锁等待的情况。出现锁等待的情况时应尽快找出错误并对其处理。主要原因有：

- 用户没有良好的编程习惯，偶尔忘记提交事务，导致长时间占用资源
- 操作的记录过多，而且操作过程没有很好的对其分组。前面介绍过，对于数据量很大的操作，可以将其分成几组提交事务。这样可以避免长时间地占用资源
- 逻辑错误，两个会话都想得到已占有的资源


## 常用工具介绍

### 什么是SQL *plus

SQL *Plus是操作Oracle数据库的工具，它是与Oracle数据库一起安装的。主要可以完成对数据的操作有：

-  对数据库的数据进行增加，删除，修改，查询的操作
-  可以对查询出的结果进行格式化的显示
-  对数据库对象进行管理，如用户，表空间，角色等对象

#### 连接数据库

进入命令页面，输入sqlplus,输入用户名和密码。成功出现SQL>

连接指定的数据库：

SQL>connect username/password	@Oralce net名称

#### 使用SQL *Plus

1.运行上一次输入的语句："/"

2.追加文本：Append text;

3.替换文本：Change	/old text/new text

4.删除指定行： DEL n

5.删除缓冲区的全部语句： CLEAR BUFFER

6.添加行：INPUT text

7.显示缓冲区内容： LIST [n/LAST/]，last代表最后一行

8.保存缓冲区内容： SAVE filename;

9.运行缓冲区的内容：RUN;

10.运行文件中的语句：START filename

11.设置别名：COLUMN oldname HEADING newname

12.设置每页的行数：SET PAGESIZE n

13.显示查询数据所用的时间： SET TIMING ON/OFF

14.查询结果保存在文件中：

SPOOL filename

SPOOL OFF(当执行完这个后，结果才真正写入到文件中)

15.设置报表标题：TTITLE title

## 控制文件和日志文件

控制文件和日志文件是数据库中两个主要的文件，没有控制文件数据库就无法启动，没有日志文件数据库的信息就无法完全恢复。

#### 控制文件

控制文件是数据库中的一个二进制文件，它主要用来记录数据库的名字，数据库的数据文件存放的位置等信息。控制文件不能手动修改。只能由数据库本身来进行修改。

查看控制文件的信息：desc v$controlfile

或者：select name,status from  v$controlfile;

#### 控制文件的多路复用

Oracle的多路复用的特性就可以帮助数据库管理员保护好控制文件，多路复用的特性可以把控制文件的副本创建到不同的磁盘上。

```plsql
--使用SPFILE多路复用控制文件
--step1 修改control_files参数
Alter system set control_files='文件的路径1',
								'文件的路径2'....,
							'文件的路径n' scope=spfile;
--step2 关闭数据库
shutdown immediate;
--step3 在DOS下复制文件到指定位置
copy old_filename, new_filename
--step4 启动数据库实例并验证
startup
```

```plsql
--创建控制文件
--step1 关闭数据库
shutdown immediate;
--step2 创建新的控制文件
create controlfile
reuse database "数据库实例名" noresetlogs//是否重做日志或重命名数据库 noarchivelog //归档状态
maxlogfiles		//最大日志文件大小
maxlogmembers	//日志文件组的成员数
maxinstances	//最大实例的个数
maxloghistory	//最大历史日志文件个数
logfile			//日志文件
group1   '日志文件路径1 '	size 日志文件大小,
....
Groupn	 '日志文件路径n '	size 日志文件大小
datafile		//数据文件
'路径1',
...
'路径n'
Character set we8dec
```















































