//输入两个字符串，从第一字符串中删除第二个字符串中的所有字符，
//例如，输入'The are students."和"aeiou",则删除之后的第一个字符串变成“They r stdnts"
char* deleSecString(const char* Deskstr,const char* str);
int main(int argc,char** argv)
{
	char* string1,string2;strOut;
	cout<<"please input first strings: ";
	cin>>string1;
	cout<<"please input second string: ";
	cin>>string2;
	strOut=deleSecString(string1,string2);
	cout<<strOut;
}
char* deleSecString(const char* Deskstr,const char* str)
{
	char* p;
	while(str!=NULL)
	{
		while(Deskstr!=NULL)
		{
			if(*Deskstr!=*str)
			{
				*p++=*str;
			}
			Deskstr++;
		}
		str++;
	}	
}

//将一句话的单词进行倒置，标点不倒置。比如 i like bejing.经过函数后变为：beijing. like i

void (const char* Deskstr,char* cOutStr)
{
	int n=strlen(Deskstr);
	cOutStr=Deskstr;
	int i;
	for(i=0;i<n-1/2;i++)
	{
		cOutStr[i]=cOutStr[n-1-i];
	}
}

//输入n个整数，输出出现次数大于等于数组长度一半的数
//输入 3 4 3 2 5 6 7 3 3 3 1 3 3  输出 3

int putNum(int* iArrayNum)
{
	int length,count;
	while(iArrayNum!=NULL)
	{
		length++;
		iArrayNum++;
	}
	int i,j,n；
	for(i=0;i<length/2;i++)
	{
		n=iArrayNum[i];
		for(j=0;j<length;j++)
		{
			if(n=*(iArrayNum+j))
			{
				count++;
			}
			if(count>length/2)
			{
				return n;
			}
		}
	}
	return -999;
}

//给定一个十进制数M，以及需要转换的进制数N。将十进制数M转化为N进制数
//输入为一行，M(32位整数)，N(2<=N<=16),以空格隔开
//输出：为每个测试实例输出转换后的数，每个输出占一行。如果N大于9，则对应的数字规则参考16进制(10用A表示)
//输入7 2   输出111

void beXNum(const int num,const int x)
{
	int iNum=num,flag;
	int iDivisor=1,iRemainder=0;
	int count=0,iOutNum=0;
	while(1)
	{
		iDivisor *= x;
		iRemainder = iNum/iDivisor;
		flag = iNum/iDivisor;
		if(flag==0)
		{
			break;
		}
		iOutNum += iRemainder*10^count;
	}
	return iOutNum;
}

/*正整数A和正整数B的最小公倍数是指能被A和B整除的最小的正整数值，
设计一个算法，求输入A和B的最小公倍数*
输出描述：输入两个正整数A和B。输出最小公倍数
5  7 输出 35*/

int iMinCommult(const int a,const int b)
{
	int imin=a;
	int imax=b;
	if (a>b)
	{
		imin=b;
		imax=a;
	}
	int i=1;
	int iMaxDiv=0;
	for(i=1;i<imin/2;i++)		//求出最小公因数
	{
		if(imin%i==0)
		{
			if(imax%i==0)
			{
				iMaxDiv=i;
			}
		}
	}
	return imin/iMaxDiv*imax;
	
}

/*将一个字符串str的内容颠倒过来，并输出。str的长度不超过100个字符。*/

void strInversion(const char *cStrDesk,char* cStrout)
{
	length = strlen(cStrDesk);
	int i=0;
	for(i=0;i<length;i++)
	{
		*(cStrout+length-1-i)=*(cStrDesk+i);
	}
}

/*功能:等差数列 2，5，8，11，14。。。。
输入:正整数N >0
输出:求等差数列前N项和
返回:转换成功返回 0 ,非法输入与异常返回-1*/

int retNumArith(int n)
{
	if(n<=0)
	{
		return -1;
	}
	int i=0;
	int sum=0;
	for(i=0;i<n;i++)
	{
		sum += 3*i + 2;
	}
	return sum;
}

int retNumArith(int n)
{
	if(n<=0)
	{
		return -1;
	}
	return n(3n+1)/2;
}

int  retNumArith(int n,int a1,int d)
{
	if(n<=0)
	{
		printf("err\n");
		return -1;
	}
	return n(a1+a1+(n-1)d)/2;
}

/*请编写一个函数（允许增加子函数），计算n x m的棋盘格子（n为横向的格子数，
m为竖向的格子数）沿着各自边缘线从左上角走到右下角，总共有多少种走法，
要求不能走回头路，即：只能往右和往下走，不能往左和往上走。*/

int retNumWays(int n,int m)				//worng 
{
	int count=0;
	int i=0,j=0;
	int length=0;
	for(i=0;i<m;i++)
	{
		
	}
	
}



