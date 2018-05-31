//qsort.go 快速排序
package qsort

func quickSort(values []int, left, right int){
	temp := values[left]  //临时变量temp保存左值
	p := left			//p保存左下标
	i, j := left, right
	for i <= j {				
		for j >= p && values[j] >= temp {	//找到小于最左值的最大的下标j
			j--
		}
		if j >= p {
			values[p] = values[j]  
			p = j					
		}

		for values[i] <= temp && i <= p{		//小于等于最左值且坐标小于（小于最左值的最大下标）		  		
			i++						//i加一
		}
		if i <= p {
			values[p] = values[i]	
			p = i
		}
	}
	values[p] = temp //把初始的最左值付给我们找到的节点
	if p -left > 1{  //判断节点与最左边节点的位置关系
		quickSort(values,left,p-1)
	}
	if right - p > 1 {	//判断节点与最右边的位置关系
		quickSort(values,p + 1,right)
	}
}

func QuickSort(values []int){ 
	quickSort(values, 0, len(values)-1)
}
