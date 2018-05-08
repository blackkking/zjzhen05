[TOC]

# 树及其应用

## 树和二叉树

### 树的概念与定义

#### 什么是树

树是n（n≥0）个结点的有限集合T。当n=0时，称为空树；当n>0时，该集合满足如下条件： 

- 其中必有一个称为根（root）的特定结点，它没有直接前驱，但有零个或多个直接后继。
- 其余n-1个结点可以划分成m（m≥0）个互不相交的有限集T1，T2，T3，…，Tm，其中Ti又是一棵树，称为根root的子树。每棵子树的根结点有且仅有一个直接前驱，但有零个或多个直接后继。

#### 树的基本术语：

- 结点：包含一个数据元素及若干指向其它结点的分支信息。
- 结点的度：一个结点的子树个数称为此结点的度
- 叶结点：度为0的结点，即无后继的结点，也叫终端结点
- 分支结点：度不为0的结点
- 孩子结点：一个结点的直接后继结点是该结点的孩子结点
- 双亲结点：一个结点的直接前驱称为该结点的双亲结点
- 兄弟结点：同一双亲结点的孩子结点之间互称兄弟结点
- 祖先结点：一个结点的祖先结点是指从根结点到该结点的路径上的所有结点
- 堂兄弟结点：其双亲在同一层的结点
- 子孙结点：一个结点的直接后继和间接后继
- 数的度：树种所有结点的度的最大值
- 结点的层次：从根结点开始定义，根结点的层次为1，根的直接后继的层次为2
- 树的高度(深度)：树中所有结点的层次的最大值
- 有序树：在树T中，如果各子树Ti之间是有先后次序的，则叫有序树
- 森林：m(m>=0)棵树互不相交的树的集合

#### 数的抽象数据类型定义

- 数据对象D：一个集合，该集合中所有元素具有相同的特性
- 数据关系R：若D为空集，则为空树。若D中仅含有一个数据元素，则R为空集，否则R={H},H是如下的的二元关系
- 在D中存在唯一的称为根的数据元素root,它在关系H下没有前驱
- 除了root以外，D中每个结点在关系H下都有且仅有一个前驱

#### 树的基本操作

```c
/*InitTree（Tree）： 将Tree初始化为一棵空树。 
DestoryTree（Tree）： 销毁树Tree。 
CreateTree（Tree）： 创建树Tree。 
TreeEmpty（Tree）： 若Tree为空，则返回TRUE，否则返回FALSE。 
Root（Tree）： 返回树Tree的根。 
Parent（Tree，x）： 树Tree存在，x是Tree中的某个结点。若x为非根结点，则返它的双亲，否则返回“空”。 
FirstChild（Tree，x）： 树Tree存在，x是Tree中的某个结点。若x为非叶子结点，则返回它的第一个孩子结点，否则返回“空”。 
NextSibling（Tree，x）： 树Tree存在，x是Tree中的某个结点。若x不是其双亲的最后一个孩子结点，则返回x后面的下一个兄弟结点，否则返回“空”。 
InsertChild（Tree，p，Child）： 树Tree存在，p指向Tree中某个结点，非空树Child与Tree不相交。将Child插入Tree中，做p所指向结点的子树。 
DeleteChild（Tree，p，i）： 树Tree存在，p指向Tree中某个结点，1≤i≤d，d为p所指向结点的度。删除Tree中p所指向结点的第i棵子树。 
TraverseTree（Tree，Visit（））： 树Tree存在，Visit（）是对结点进行访问的函数。按照某种次序对树Tree的每个结点调用Visit（）函数访问一次且最多一次。若Visit（）失败，则操作失败。*/ 

```



### 二叉树

#### 什么是二叉树

我们把满足以下两个条件的树型结构叫做二叉树（Binary Tree）： 

- 每个结点的度都不大于2；


- 每个结点的孩子结点次序不能任意颠倒。

#### 二叉树的基本操作

```c
/*
Initiate（bt）：将bt初始化为空二叉树。 
Create(bt)：创建一棵非空二叉树bt。 
Destory（bt）： 销毁二叉树bt。 
Empty（bt）： 若bt为空，则返回TRUE，否则返回FALSE。 
Root(bt)： 求二叉树bt的根结点。若bt为空二叉树，则函数返回“空”。 
Parent（bt，x）：求双亲函数。求二叉树bt中结点x的双亲结点。若结点x是二叉树的根结点或二叉树bt中无结点x，则返回“空”。 
LeftChild（bt，x）：求左孩子。若结点x为叶子结点或x不在bt中，则返回“空”。RightChild（bt，x）：求右孩子。若结点x为叶子结点或x不在bt中，则返回“空”。Traverse（bt）: 遍历操作。按某个次序依次访问二叉树中每个结点一次且仅一次。Clear（bt）：清除操作。将二叉树bt置为空树。 

*/
```

#### 二叉树的性质

- 在二叉树的第i层上至多有2i-1个结点(i≥1)。 
- 深度为k的二叉树至多有2k-1个结点（k≥1）
- 对任意一棵二叉树T，若终端结点数为n0，而其度数为2的结点数为n2，则n0= n2+1 。
- 具有n个结点的完全二叉树的深度为小于㏒2n+1的最大整数。 
- 对于具有n个结点的完全二叉树，如果按照从上到下和从左到右的顺序对二叉树中的所有结点从1开始顺序编号，则对于任意的序号为i的结点有：
  - 若i = 1, 则 i 无双亲结点，若i >1, 则 i 的双亲结点为小于i /2的最大整数
  - 若2*i > n, 则 i 无左孩子，若2*i≤n, 则 i 结点的左孩子结点为2*i
  - 若 2*i+1 > n ,则i 无右孩子，若 2*i+1≤n, 则i的右孩子结点为2* i+1

#### 两种特殊的二叉树

- 满二叉树(Full Binary Tree) ：深度为k且有2k-1个结点的二叉树。在满二叉树中，每层结点都是满的，即每层结点都具有最大结点数。
- 完全二叉树：若设二叉树的高度为h，则共有h层。除第 h 层外，其它各层 (0  h-1) 的结点数都达到最大个数，第 h 层从右向左连续缺若干结点，这就是完全二叉树。

#### 二叉树的存储结构

二叉树的结构是非线性的，每一结点最多可有两个后继。二叉树的存储结构有两种：顺序存储结构和链式存储结构。

对于一般的二叉树，我们必须按照完全二叉树的形式来存储，就会造成空间的浪费。单支树就是一个极端情况。

```c
//二叉树的二叉链表结点的结构用C语言描述为 ： 
typedef struct Node
{
	DataType data;
  	struct Node *LChild;
  	struct Node *RChild;
}BiTNode,*BiTree;
//有时，为了找到父结点，可以增加一个Parent域，Parent域指向该结点的父结点
```

若一个二叉树含有n个结点，则它的二叉链表中必含有2n个指针域，其中必有n＋1个空的链域。

### 二叉树的遍历与线索化

二叉树的遍历：指按一定规律对二叉树中的每个结点进行访问且仅访问一次。 

用L、D、R分别表示遍历左子树、访问根结点、遍历右子树，那么对二叉树的遍历顺序就可以有：

- 访问根，遍历左子树，遍历右子树(记做DLR)。
- 访问根，遍历右子树，遍历左子树(记做DRL)。
- 遍历左子树，访问根，遍历右子树(记做LDR)。
- 遍历左子树，遍历右子树，访问根 (记做LRD)。
- 遍历右子树，访问根，遍历左子树 (记做RDL)。
- 遍历右子树，遍历左子树，访问根 (记做RLD)。

在以上六种遍历方式中，如果我们规定按先左后右的顺序，那么就只剩有DLR、LDR  和LRD三种。根据对根的访问先后顺序不同，分别称DLR为先序遍历或先根遍历；LDR为中序遍历（对称遍历）；LRD为后序遍历。

#### 三种遍历方法的递归定义

- 先序遍历（DLR）操作过程：若二叉树为空，则空操作，否则依次执行如下操作：（1）访问根结点；（2）按先序遍历左子树；（3）按先序遍历右子树。
- 中序遍历（LDR）操作过程：若二叉树为空，则空操作，否则依次执行如下操作：（1）按中序遍历左子树；（2）访问根结点；（3）按中序遍历右子树。
- 后序遍历（LRD）操作过程：若二叉树为空，则空操作，否则依次执行如下操作：（1）按后序遍历左子树；（2）按后序遍历右子树；（3）访问根结点。

#### 以二叉链表作为存储结构，讨论二叉树的遍历算法

```c
//先序遍历
void PreOrder(BiTree root)
//先序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针
{
  if(root!=NULL)
  {
  	Visit(root->data); 	//访问根结点
    PreOrder(root->LChild); //先序遍历左子树
    PreOrder(root->RChild); //先序遍历右子树
  }  
}

//中序遍历
void  InOrder(BiTree root)  
/*中序遍历二叉树, root为指向二叉树(或某一子树)根结点的指针*/
{	
  	if (root!=NULL)
	{
	    InOrder(root ->LChild);   /*中序遍历左子树*/
	    Visit(root ->data);        /*访问根结点*/
	    InOrder(root ->RChild);   /*中序遍历右子树*/
	}
} 

//后序遍历
void  PostOrder(BiTree root)  
/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
{	
  	if(root!=NULL)
	{
	    PostOrder(root ->LChild); /*后序遍历左子树*/
	    PostOrder(root ->RChild); /*后序遍历右子树*/
	    Visit(root ->data);       /*访问根结点*/
	}
} 
```

#### 基于栈的递归消除

在大量复杂的情况下，递归的问题无法直接转换成循环，需要采用工作栈消除递归。工作栈提供一种控制结构，当递归算法进层时需要将信息保留；当递归算法出层时需要从栈区退出信息。

```c
//中序遍历二叉树的非递归算法(直接实现栈操作)
//s[m]表示栈,top表示栈顶指针
void inorder(BiTree root) //中序遍历二叉树，bt为二叉树的根结点
{
  top=0;p=bt
  do{
  		while(p!=NULL)
        {
  			if(top>m)return('overflow');
          	top=top+1;
          	s[top]=p;
          	p=p->Lchild
		};//遍历左子树
    	if(top!=0)
        {
  			p=s[top];
          	top=top-1;
          	Visit(p->data); //访问根结点
          	p=p->Rchild; //遍历右子树
		}
	}while(p!=NULL||top!=0)
} 

//中序遍历二叉树的非递归算法（调用栈操作的函数）
//首先应用递归进层的三件事与递归退层的三件事的原则,直接先给出中序遍历二叉树的非递归算法基本实现思路。 
void InOrder(BiTree root) //中序遍历二叉树的非递归算法 
{
  InitStack(&S);p=root;
  while(p!=NULL||!IsEmpty(S))
  {
  	if(p!=NULL) //根指针进栈，遍历左子树
    {
  		Push(&S,p);
      	p=p->LChild;
	}
    else
    { //根指针退栈，访问根结点，遍历右子树
      Pop(&S,&p);
      Visit(p->data);
      p=p->RChild;
	}
  }
}

//后序遍历的二叉树的非递归算法
void PostOrder(BiTree root)
{
  BiTNode* p,*q; BiTNode **S;
  int top=0;q=NULL;p=root;
  S=(BiTNode**)malloc(sizeof(BiTNode*)*NUM);
  //NUM为预定义的常数
  while(p!=NULL||top!=0)
  {
  	while(p!=NULL)
    {
  		top++;
      	s[top]=p;
      	p=p->LChild; //左子树遍历
	}
    if(top>0)
    {
  		p=s[top];
      	if((p->RChild==NULL)||(p->RChild==q))
        {
  			visit(p->data); //访问根结点
          	q=p; //保存到q,为下一次已处理结点前驱
          	top--;
          	p=NULL;
		}esle{
  			p=p->RChild;
		}
	}
  }
  free(s);
}
```

#### 遍历算法应用

二叉树的遍历运算是一个重要的基础。在实际应用中，一是重点理解访问根结点操作的含义，二是注意对具体的实现问题是否需要考虑遍历的次序的问题

```c
//先序遍历输出二叉树中的结点
void PreOrder(BiTree root)
{
  if(root!=NULL)
  {
    printf(root->data);
    PreOrder(root->LChild);
    ProOrder(root->Rchild);
  }
}

//输出二叉树中的叶子结点
void PreOrder(BiTree root)
{
  if(root!=NULL)
  {
  	if(root->LChild == NULL && root->RChild == NULL)
    {
  		printf(root->data);
	}
    PreOrder(root->LChild);
    PreOrder(root->RChild);
  }
}
```

#### 建立二叉链表方式存储的二叉树

给定一棵二叉树，可以得到它的遍历序列；反过来，给定一个遍历序列，也可以创建相应的二叉链表。在这里所说的遍历序列是一种“扩展的遍历序列”，通常用特定的元素表示空子树

```c
//利用“扩展先序遍历序列”创建二叉链表的算法
//我们用‘.’来表示空子树
void CreateBiTree(BiTree *bt)
{
  char ch;
  ch = getchar();
  if(ch == '.')
  *bt = NULL;
  else
  {
  	*bt=(BiTree)malloc(sizeof(BiTNode));
    (*bt)->data = ch;
    CreateBiTree(&((*bt)->LChild));
    CreateBiTree(&((*bt)->RChild));
  }
}
```

#### 求二叉树的高度

设函数表示二叉树bt的高度，则递归定义如下：

若bt未空，则高度为0；若bt非空，其高度为其左右子树高度的最大值加1

```c
//后序遍历求二叉树的高度递归算法
int PostTreeDepth(BiTree bt)
{
	int hl,hr,max;
  	if(bt != NULL)
    {
  		hl=PostTreeDepth(bt->LChild);
      	hr=PostTreeDepth(bt->RChild);
      	max = (hl>hr?hl:hr);
      	return max+1;
	}else return 0;
}
```

#### 按树状打印二叉树

二叉树的横向显示问题，横向显示应是竖向显示的900旋转，又由于二叉树的横向显示算法一定是中序遍历算法，所以把横向显示的二叉树算法改为RDL结构

```c
//竖向束装打印二叉树
void PrintTree(TreeNode Root,int nLayer)
{
  if(Root == NULL)
    return;
  PrintTree(Root->RChild,nLayer+1);
  for(int i=0;i<nLayer;i++)
  {
  	prinf(" ");
    printf("%c\n",Root->ch);
    PrintTree(Root->LChild,nLayer+1);
  }
}
```

### 线索二叉树

#### 基本概念

二叉树的遍历运算是将二叉树中结点按一定规律线性化的过程。当以二叉链表作为存储结构时，只能找到结点的左右孩子信息。而不能直接得到结点在遍历序列中的前驱和后继信息，要得到这些信息第一种方法是将二叉树遍历一遍，在遍历过程中便可得到结点的前驱和后继，但这种动态访问浪费时间，第二种方法是充分利用二叉树链表中的空炼域，将遍历过程中结点的前驱，后继信息保存下来。

在有n个结点的二叉链表中共有2n个链域，但只有n-1个有用非空链域，其余n+1个链域是空的。我们可以利用剩下的n+1个空链域来存放遍历过程中结点的前驱和后继信息。先做如下规定：

若结点有左子树，则其LChild域指向其左孩子，否则LChild域指向其前驱结点，若结点有由子树，则RChild域指向其右孩子，否则RChild 域指向其后继结点。

为了区分孩子结点和前驱，后继结点，为结点结构增设两个标志域:Ltag,Rtag。当tag为0的时候指向孩子结点，当tag为1的时候LChild指向遍历前驱，Rchild指向遍历后继

- 线索：在这种存储结构中，指向前驱和后继结点的指针叫做线索
- 线索链表：以这种结构组成的二叉链表作为二叉树的存储结构，叫做线索链表。
- 线索化：对二叉树以某种次序进行遍历并且加上线索的过程叫做线索化。
- 线索二叉树：线索化了的二叉树称为线索二叉树

#### 二叉树的线索化

线索化实质上是将二叉链表中的空指针域填上相应结点的遍历前驱或后继结点的的地址，而前驱和后继的地址只能在动态的遍历过程中才能得到。因此线索化的过程是在遍历过程中修改空指针域的过程。对二叉树按照不同的遍历次序进行线索化，可以得到不同的线索二叉树(先序线索二叉树，中序线索二叉树和后序线索二叉树)。

```c
//中序线索化算法：
void Inthread(BiTree root)
{
  //对root所指的二叉树进行中序线索化，其中pre始终指向刚访问过的结点，其初值为NULL
  if(root != NULL)
  {
  	Inthread(root->LChild); //线索化左子树
    if(root->LChild == NULL)
    {
  		root->Ltag=1;
      	root->LChild = pre; //置前驱线索
      	if(pre!=NULL && pre->RChild == NULL) //置后继线索
        pre->RChild=root;
      pre=root;
      Inthread(root->RChild); //线索化右子树
	}
  }
}
```

#### 在线索二叉树中找前驱，后继结点

##### 找结点的中序前驱结点

根据线索二叉树的基本概念和存储结构可知，对于结点p，当p->Ltag=1时，p->LChild指向p的前驱。

当p->Ltag=0时，p->LChild指向p的左孩子。由中序遍历的规律可知，作为根p的前驱结点，它是中序遍历p的左子树时访问的最后一个结点，即左子树的“最右下端”结点。其查找算法如下：

```c
void InPre(BiTNode *p,BiTNode* pre)
//在中序线索二叉树中查找p的中序前驱，并用pre指针返回结果
{
	if(p->Ltag==1) pre=p->LChild;
  	else
    {	//在p的左子树中查找“最右下端”结点
  		for(q=p->LChild;q->Rtag==0;q=q->RChild);
      	pre=q;
	}
}
```

##### 在中序线索树中找结点后继

对于结点p,若要找其后继结点，当p->Rtag=1时,p->RChild即为p的后继结点；当p->Rtag=0时，说明p有右子树，此时p的中序后继结点即为其右子树的“最左下端”的结点。

```c
void InSucc(BiTNode* p,BiTNode * succ)
{
	//在中序线索二叉树中查找p的后继结点，并用succ指针返回结果
	if(p->Rtag==1) succ = p->RChild; 
  	else{//在p的右子树中查找“最左下端”结点
  		for(q=p->RChild;q->Ltag==0;q=q->LChild);
      succ=q;
	}
}
```

## 树，森林和二叉树的关系

### 树的存储结构

- 双亲表示法
- 孩子表示法
- 孩子兄弟表示法

#### 双亲表示法

用一组连续的空间来存储树中的结点，在保存每个结点的同时附设一个指示器来指示其双亲结点在表中的位置

```c
//双亲表示法的形式
#define MAX 100
typedef struct TNode
{
  DataType data;
  int parent;
}TNode;

//一棵树可以定义为：
typedef struct
{
  TNode tree[MAX];
  int nodenum;//结点数
}ParentTree;
```

#### 孩子表示法

通常是把每个结点的孩子结点排列起来，构成一个单链表，称为孩子链表。n个结点共有n个孩子链表（叶结点的孩子链表为空表），而n个结点的数据和n个孩子链表的头指针又组成一个顺序表。

```c
typedef struct ChildNode //孩子链表结点定义
{
  int Child;  //该孩子结点在线性表中的位置
  struct ChildNode* next; //指向下一个孩子结点的指针
}ChildNode;

typedef struct	//顺序表结点的结构定义
{
  DataType data;	//结点信息
  ChildNode *FirstChild; //指向孩子链表的头指针
}DataNode;

typedef struct
{
  DataNode nodes[MAX]; //顺序表
  int root,num;
  //该树的根结点在线性表中的位置和该树的结点个数
}ChildTree;
```

#### 孩子兄弟表示法(二叉链表表示法)

链表中每个结点设有两个链域，分别指向该结点的第一个孩子结点和下一个兄弟（右兄弟）结点。 

```c
typedef struct CSNode
{
  DataType data;
  Struct CSNode* FirstChild,*Nextsibling;
  //第一个孩子，下一个兄弟
}CSNode,*CSTree;
```

## 哈夫曼树及其应用

### 哈弗曼树

基本概念：

- 路径：指从一个结点到另一个结点之间的分支序列
- 路径长度：指从一个结点到另一个结点所经过的分支数目
- 结点的权：给树的每个结点赋予一个具有某种实际意义的实数，我们称该实数为这个结点的权。
- 带权路径长度：在树形结构中，我们把从树根到某一结点的路径长度与该结点的权的乘积，叫做该结点的带权路径长度
- 树的带权路径长度：为树中所有叶子结点的带权路径长度之和

哈弗曼树又叫最优二叉树，它是由n个带权叶子结点构成的所有二叉树中带权路径长度(WPL)最短的二叉树，直观地看，在哈夫曼树中权越大的叶子离根越近，则其具有最小带权路径长度。

### 哈夫曼编码

哈夫曼树最典型的应用是在编码技术上的应用。利用哈夫曼树，我们可以得到平均长度最短的编码。

such as：

使用频率：

|  指令  | 使用频率(pi) |
| :--: | :------: |
|  I1  |   0.40   |
|  I2  |   0.30   |
|  I3  |   0.15   |
|  I4  |   0.05   |
|  I5  |   0.04   |
|  I6  |   0.03   |
|  I7  |   0.03   |

变长编码：

|  指令  |  编码  |
| :--: | :--: |
|  I1  |  0   |
|  I2  |  1   |
|  I3  |  00  |
|  I4  |  01  |
|  I5  | 000  |
|  I6  | 001  |
|  I7  | 010  |

使用变长编码虽然可以使得程序的总位数达到最小，但机器却无法解码。如对编码串0010110该怎样识别呢？因此，若要设计变长的编码，则这种编码必须满足这样一个条件：任意一个编码不能成为其它任意编码的前缀。我们把满足这个条件的编码叫做前缀编码。 

利用哈夫曼算法，我们可以设计出最优的前缀编码。对于该二叉树，我们可以规定向左的分支标记为1，向右的分支标记为0.这样，从根结点开始，沿线到达各频度指令对应的叶结点，所经过的分支代码序列就构成了相应频度指令的哈夫曼编码。

指令的哈夫曼编码：

|  指令  |  编码   |
| :--: | :---: |
|  I1  |   0   |
|  I2  |  10   |
|  I3  |  110  |
|  I4  | 11100 |
|  I5  | 11101 |
|  I6  | 11110 |
|  I7  | 11111 |

构造满足哈夫曼编码的最短最优性质：

- 若di <>dj (字母不同)，则对应的树叶不同。因此前缀码(任一字符的编码都不送另一个字符编码)不同，一个路径不可能是其他路径的一部分，所以字母之间可以完全区别。
- 将所有字符变成二进制的哈夫曼编码，使带权路径长度最短，相当总的通路长度最短。

### 哈夫曼编码算法的实现

由于哈夫曼树中没有度为1的结点，则一颗有n个叶子的哈夫曼树共有2*n-1个结点，可用一个大小为2*n-1的一维数组来存放各个结点。

因为每个结点同时还包含其双亲信息和孩子结点信息，所以构成一个静态三叉链表。

```c
//静态三叉链表的描述如下
typedef struct 
{
  unsigned int weight; //用来存放各个结点的权值
  unsigned int parent,LChild,Rchild;//指向双亲，孩子结点的指针
}HTNode,*Huffman Tree; //动态分配数组，存储哈弗曼树

typedef char **HuffmanCode; //动态分配数组，存储哈夫曼编码

```

数组ht的前n个分量表示叶子结点，最后一个分量表示根结点。每个叶子结点对应的编码长度不等，但最长不超过n。

## 红黑树

### 二叉查找树(Binary Search Tree)

#### 定义

二叉查找树是在数据结构中比较重要的数据结构之一，从外部看它满足集合性质，具有查找，插入和删除的基本功能，同时还可以求最大值和最小值。由于二叉查找树独特的性质，它特别适合用来存储动态集合。

定义：对于二叉树上所有结点x,如果y是x的左子树，那么y.key<=x.key.如果y是x的右子树，那么y.key>=x.key，这样的二叉树就叫二叉查找树(Binary Search Tree)。

要想二叉树的查找的花费时间小，我们尽可能让二叉树不出现类以于单链形态的二叉树，让树的高度尽量的低。对于高度为h的二叉查找树，从树根对叶子最坏的情况是比较h次。也就是说，对于高度为h的二叉查找树的最坏查找情况的运行时间是O(h)。二叉树的查找效率取决于树的高度。

要想二叉树的查找的花费时间小，我们尽可能让二叉树不出现类以于单链形态的二叉树，让树的高度尽量的低。对于高度为h的二叉查找树，从树根对叶子最坏的情况是比较h次。也就是说，对于高度为h的二叉查找树的最坏查找情况的运行时间是O(h)。二叉树的查找效率取决于树的高度。

要想二叉树的查找的花费时间小，我们尽可能让二叉树不出现类以于单链形态的二叉树，让树的高度尽量的低。对于高度为h的二叉查找树，从树根对叶子最坏的情况是比较h次。也就是说，对于高度为h的二叉查找树的最坏查找情况的运行时间是O(h)。二叉树的查找效率取决于树的高度。

#### 操作

二叉树作为动态集，它有查找，插入，删除，最大值，最小值，前驱和后继这些基本操作。为了后序的方便，我们定义了结点和树，另外我们还用0表示空子树。

```c
typedef struct node_s node_t;
typedef struct tree_s tree_t;
#define NIL 0
#define init(x) x->l=x->r=x->p=NIL

struct node_s{
  int k; //key
  node_t *p; //parent
  node_t *l; //left
  node_t *r; //right
};

struct tree_s{
  node_t *root;
};
```

##### 查找

在二叉查找树中根据给定的key找到该结点。由于二叉树的性质，我们知道，如果目标key比当前结点的key要小，那么目标结点必定在当前结点的左子树上

```c
node_t *search(tree_t *T,int k)
{
  node_t *x;
  x = T->root;
  while(x != NIL){
  	if(k==x->k)
      break;
    if(k < x->k)
      x = x->l;
    esle
      x = x->r;
  }
  return x;
}
```

##### 最小值与最大值

我们来分析一下最小值的位置。我们认为最小值的位置是从根出发一直沿结点的左子树直到某个结点x的左子树为空，那么这个结点x就是整个二叉树中key最小的结点。

```c
node_t * max(node_t *x)
{
  while(x->r != NIL)
  {
  	x = x->r;
  }
  return x;
}

node_t *min(node_t *x)
{
  while(x->l != NIL){
  	x = x->l;
  }
  return x;
}
```

##### 前驱和后继

前驱和后继的定义来源二叉树中序遍历的key序列。我们知道二叉的中序遍历的key序列是一个升序序列。在二叉查找树中，对于结点x,如果有结点y,满足y.key>x.key并且y是这些结点中key最小的，那么y就称之为x的后继。同理，在二叉查找树中，对于结点x，如果有结点y，满足y.key<x.key并且y是这些结点中key最大的，那么y就称之为x的前驱。在二叉查找树中，如果x是y的前驱，那么y就是x的后继。

对于某个结点y它的后继的位置：如果y的右子树存在，那么后继是y的右子树中key最小的结点；如果y的右子树不存在，那么我们只要找到哪个结点的前驱是y，那么那个结点就是y的后继。

```c
node_t *successor(node_t *x)
{
  node_t *y;
  if(x->r != NIL){
  	y=min(x->y);
  }else{
  	y=x->p;
    while((y != NIL)&&(y->r == x))
    {
  		x = y;
      	y = x->p;
    }
  }
  return y;
}

node_t *predecessor(node_t *x)
{
  node_t *y;
  if(x->l != NIL){
  	y = max(x->l);
  }else{
  	y = x->p;
    while(( y != NIL)&&(y->l == x)){
  		x=y;
      	y=x->p;
	}
  }
  return y;
}
```

根据前驱和后继的定义，我们知道通过对树中最小值一直沿着后继直到结束，这样的序列就是中序遍历的序列。下面给出中序遍历的代码：

```c
void inorder(tree_t *T,void (*visit)(node_t *))
{
  node_t *x;
  x = T->root;
  if(x == NIL){
  	x = min(x);
    while(x != NIL){
  		visit(x);
      	x = successor(x);
   }
  }
  return;
}
```

##### 插入

对二叉查找树的插入，不能破坏二叉查找树的性质，那么我们要结点插入到什么地方呢，答案是叶子，新插入的结点，都是成为某个叶子结点的左孩子或者右孩子。

```c
int insert(tree_t *T,node_t *z)
{
  node_t *x,*y;
  x = T->root;
  y = x;
  while(x != NIL){
  	y = x;
    if(z->k == x->k){
  		return 1;
	}
    if(z->k < x->k){
  		x=x->l;
	}else{
  		x=x->r;
	}  
  }
  init(z);
  if(y == NIL){
  	T->root = z;
  }else{
  	if(z->k < y->k){
  		y->l = z;
    }else{
  		y->r = z;
	}
    z->p = y;
  }
  return 0;
}
```

我们发现insert与search方法是一样的，只不过search是查找特定的key，而insert是查找合适的叶子结点的位置，它的运行时间为O(n)。

##### 删除

在介绍删除二叉查找算法之前，我们先来介绍一个辅助函数transplant,这个函数有3个参数，在树T中，将v替换u的位置，即u的双亲变成v的双亲，v替换u成为u双亲的孩子。另外一个辅助函数replace,这个函数有3个参数，在树T中，将v完成代替u，即u的双亲变成v的双亲，v替换u成为u双亲的孩子，另外左右孩子均为u的孩子。

```c
void _transplant(tree_t *T,node_t *u,node_t *v)
{
  if(u->p == NIL)
  {
  	T->root = v;
  }else{
  	if(u->p->l == u){
  		u->p->l = v;
	}else{
  		u->p->r = v;
	}
  }
  if(v != NIL){
 	v->p = u->p; 
  }
  return;
}
```

假设z是待删除的结点，那么z可能有几种情况：

- z没有右孩子——我们只需要将左孩子替换z在树中位置就能完成删除操作，也可以拿z的前驱替换
- z有右孩子：z的右孩子没有左孩子——找到z的后继然后替换z.因为z的key小于右子树所有的key(假设没有重复的key)，那么z的后继就是右子树上的最小key.z的后继是z的右孩子，那么调用transplant(T,z,y).另外，要连接上原来z的左子树；
- z有右孩子：z的右孩子有左孩子——找到z的后继然后替换z.因为z的key小于右子树所有的key(假设没有重复的key)，z的后继也有可能不是z的右孩子，首先我们调用transplant(T,y,y->r)，这时候y已经从树中脱离了，然后我们将y嫁接到z的右孩子的双亲上，这样y就成了z右孩子的双亲了，这和上面一种情况相同

```c
int remove(tree_t *T,node_t *z)
{
  do{
  	node_t *y;
    if(z->r == NIL){
  		_transplant(T,z,z->l);
      	break;
	}
    y=min(z->r);
    if(y != z->r){
  		_transplant(T,y,y->r);
      	y->r = z->r;
      	y->r->p = y;
	}
    _transplant(T,z,y);
    y->l = z->l;
    if(z->l != NIL){
  		z->l->p = y;
	}
  }while(0);
  return 0;
}
```

### 红黑树

在高度为h的二叉查找树上，我们实现的动态集基本操作:min，max，successor，predecessor，search，insert和delete的运行时间都是O(h)。树的高度决定查找效率。如果我们通过某种方法可以将二叉树尽可能的低，那么二叉树的查找效率将会大大的提高。

对于一个含有n结点的最坏情况是这n个结点形成一个单链，那么二叉查找树的树高为n,允许时间为O(n);最好的情况是形成了一颗完全二叉树。那么h介于log2(n) 与log2(n)+1之间，运行时间为O(log2(n))。它的效率可以说是极高的。

#### 基本概念

如果我们把二叉查找树的每个结点都涂上红色或者黑色。如果他满足下面的5个性质，那么我们就称它为红黑树(RED BLACK TREE):

- 每个结点不是红色就是黑色
- 根结点是黑色
- 每个叶子结点(NIL)都是黑色的
- 如果一个结点是红色的，那么它所有的孩子都是黑色的
- 对于每一个结点，从当前结点到后代的叶子的路径上包含黑色结点的数量是相同的。

根据红黑树的性质，我们可以得到下面的结论：具有n内部结点的红黑树的高度最高位2log2(n+1).

在证明这个结论之前，我们来看看红黑树的表示。每个结点到叶子结点（NIL）经过的黑色结点的个数（包括自已）称之为**黑高度**(black-height)。我们把NIL称之为**外部结点**，那些带有key的“合法”的结点称之为**内部结点**。

红黑树的搜索运行时间为O(2log2(n+1))也就是O(log2(n))

为了方便操作，我们引入一个NIL结点，这个NIL结点是跟普通的结点一样，不过我们只使用color这个域，因为NIL结点是黑色的。

```c
typedef struct rbnode_s rbnode_t;
typedef struct rbtree_s rbtree_t;

#define RBT_RED 0
#define RBT_BLACK 1

#define rbt_init(T)
	(T)->root = &((T)->nil);
	(T)->nil.c = RBT_BLACK

struct rbnode_s {
	int	k;	//key
  	int c;	//color
  	rbnode_t *p;	//parent
  	rbnode_t *l;	//left
  	rbnode_t *r;   //right 
};

struct rbtree_s{
  rbnode_t *root;
  rbnode_t nil;
};

//我们定义了结点的颜色，同时每个结点都增加了一个c域来表示结点的颜色。除此之外我们还为树定义了一个nil结点，之前实现的二叉查找树指向NIL都改为指向T->nil.
```

##### 查找

因为红黑树本身就是一颗二叉查找树，所以对红黑树的查找操作跟普通的二叉查找树的操作没什么不一样

```c
rbnode_t * rbt_search(rbtree_t *T,int k)
{
  rbnode_t *x;
  x = T->root;
  while(x != &x->nil){
  	if(k == x->k){
  		break;
	}
    if(k < x->k){
  		x = x->l;
	}else{
  		x = x->r;
	}
  }
  if(x == &T->nil){
  	x = 0;
  }
  return x;
}
```

##### 旋转

在介绍红黑色的插入与删除前，我们介绍一下二叉树的旋转操作：旋转分为左旋(Left-Rotate)和右旋(Right-Rotate)。

```c
//左旋，先用y替换x的位置，再将y的原左子树变成x的右子树，x成y的左子树

void _rbt_left_rotate(rbtree_t *T,rbnode_t *x)
{
  rbnode_t *y;
  y = x->r;
  y->p = x->p;
  if(x->p == &T->nil){
  	x->p->l = y;
  }else{
  	if(x->p->l == x){
  		x->p->l = y;
	}else{
  		x->p->r = y;
  	}
  }
  x->r = y->l;
  if (x->r != &T->nil){
  	x->r->p = x;
  }
  x->p = y;
  y->l = x;
}

```

```c
//右旋 先用y替换x的位置，再将y的原右子树变成x的左子树，x成y的右子树
void _rbt_right_rotate(rbtree_t *T,rbnode_t *x)
{
  rbnode_t *y;
  y = x->l;
  y->p = x->p;
  if(x->p == &T->nil){
  	T->root = y;
  }else{
  	if(x->p->l == x){
  		x->p->l = y;
	}else{
  		x->p->r = y;
	}
  }
  x->l = y->r;
  if(x->l != &T->nil){
  	x->l->p =x;
  }
  x->p = y;
  y->r = x;
}
//区分左旋还是右旋，我们只要看x最终是y的左孩子还是右孩子，如果左孩子那就是左旋，如果右孩子那就是右旋
//二叉查找树的左旋和右旋并不会破坏其二叉查找树的数学性质
```

#### 插入

```c
//红黑树的插入前半部分与普通的二叉查找树的插入大致相同，我们来看一下插入的代码
int rbt_insert(rbtree_t	*T,rbnode_t *z)
{
  rbnode_t *x,*y;
  x = T->root;
  y = x;
  while( x != &T->nil){
  	y = x;
    if(z->k == x->k){
  		return 1;
	}
    if(z->k < x->k){
  		x = x->l;
	}else{
  		x = x->r;
	}
  }
  z->l = z->r = z->p = &T->nil;
  if(y == &T->nil){
  	T->root = z;
  }else{
  	if(z->k < y->k)
      y->l = z;
    else
      y->r = z;
    z->p = y;
  }
  z->c = PBT_RED;
  _rbt_insert_fixup(T,z);
  return 0;
}
```

```c
void _rbt_insert_fixup(rbtree_t *T,rbnode_t *z)
{
  while(z->p->c == RBT_RED){
  	if(z->p == z->p->p->l){
  		if(z->p->p->r->c == RBT_RED){
  			z->p->p->r->c = RBT_BLACK;	//case3
          	z->p->c = RBT_BLACK;	//case3
          	z->p->p->c = RBT_RED;	//case3
          	z = z->p->p;	//case3
		}else{
  			if(z == z->p->r){
  				z = z->p;	//case2
              	_rbt_left_rotate(T,z);	//case2
			}
          	z->p->c = RBT_BLACK;	//case1
          	z->p->p->c = RBT_RED;	//case1
          	_rbt_right_rotate(T,z->p->p);	//case1
		}
	}else{
  		if(z->p->p->l->c == RBT_RED){
  			z->p->p->l->c = RBT_BLACK;	//case3
          	z->p->c = RBT_BLACK;	//case3
          	z->p->p->c = RBT_RED;	//case3
          	z = z->p->p;			//case3
		}else{
  			if(z == z->p->l){
  				z = z->p;					//case2
              	_rbt_right_rotate(T,z);		//case2
			}	
          	z->p->c = RBT_BLACK;			//case1
          	z->p->p->c = RBT_RED;			//case1
          	_rbt_left_rotate(T,z->p->p);  //case1
		}
	}
  }
  T->root->c = RBT_BLACK;
  return;
}

//向红黑树中新插入一个结点着成红色，我们可以通过不超过两次的旋转就可以恢复红黑树的性质。
```

#### 删除

```c
int rbt_remove(rbtree_t *T,rbnode_t *z)
{
  int c;
  rbnode_t *x;
  do{
  	rbnode_t *y;
    c = z->c;
    if(z->r == &T->nil){
  		x = z->l;
      	_rbt_transplant(T,z,z->l);
      	x->p = z->p;  //if x is nil
      	break;
	}
    y = rbt_min(T,z->r);
    c = y->c;
    y->c = z->c;
    x = y->r;
    if(y != z->r){
  		_rbt_transplant(T,y,y->r);
      	x->p = y->p;  //if x is nil
      	y->r = z->r;
      	y->r->p = y;
	}else{
  		x->p = y; //if x is nil
	}
    _rbt_transplant(T,z,y);
    y->l = z->l;
    if(z->l != &T->nil){
  		z->l->p = y;
	}
  }while(0);
  
  if((c == RBT_BLACK )&&(x->c == RBT_BLACK)){
   	_rbt_remove_fixup(T,x);
  }else{
  	x->c = RBT_BLACK;
  }
  return 0;
}
```

```c
int _rbt_remove_fixup(rbtree_t *T,rbnode_t *x)
{
  rbnode_t *w;
  while((x != T->root)&&(x->c == RET_BLACK)){
  	if(x == x->p->l){
  		w = x->p->r;
      	if(w->c == RBT_RED){
  			x->p->c = RBT_RED;
          	w->c = RBT_BLACK;
          	_rbt_left_rotate(T,x->p);	//case4
          	w = x->p->r;	//case4
		}
      	if (w->c == RBT_BLACK){
  			if((w->l->c == RBT_BLACK)&&(w->r->c == RBT_BLACK))
            {
  				w->c = RBT_RED;	//case3
              	x = x->p;		//case3
			}else{
  				if(w->r->c == RBT_BLACK){//case2
  					w->c = RBT_RED;//case2
                  	w->l->c = RBT_BLACK;//case2
                  	_rbt_right_rotate(T,w);//case2
                  	w = x->p->r;//case2
				}
              	w->c = w->p->c;//case1
              	w->p->c = RBT_BLACK;//case1
              	w->r->c = RBT_BLACK;//case1
              	_rbt_left_rotate(T,x->p);//case1
              	x = T->root;
			}
		}
	}else{
      	w = x->p->l;
      	if(w->c == RBT_RED){
  			x->p->c = RBT_RED;
          	w->c = RBT_BLACK;
          	_rbt_right_rotate(T,x->p);//case4
          	w = x->p->r;//case4
		}
      	if (w->c == RBT_BLACK){
  			if((w->l->c == RBT_BLACK)&&(w->r->c == RBT_BLACK))
            {
  				w->c = RBT_RED;//case3
              	x = x->p;	//case3
			}else{
  				if(w->l->c == RBT_BLACK){//case2
  					w->c = RBT_RED;	//case2
                  	w->r->c = RBT_BLACK;	//case2
                  	_rbt_left_rotate(T,w);	//case2
                  	w = x->p->l;//case2
				}
              	w->c = w->p->c;//case1
              	w->p->c = RBT_BLACK;//case1
              	w->l->c = RBT_BLACK;//case1
              	_rbt_right_rotate(T,x->p);//case1
              	x = T->root;
			}
		}
	}
  }
  x->c = RBT_BLACK;
  return 0;
}
```

