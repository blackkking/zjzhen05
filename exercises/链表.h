//链表
Stu* creat_node(int data)//创建节点
{
	Stu* newNode = (Stu*)calloc(1,sizeof(Stu));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insert_after(Stu* head, int data) //后插
{
	Stu* newNode = creat_node(data);
	while(head->next != NULL)
	{
		head = head->next;
	}
	head->next = newNode;
}

void delet_stu_node(Stu* head, int data)//删除
{
	Stu* pre = find_stu_node_front(head,data);
	if(pre == NULL)
	{
		return;
	}
	Stu* del = pre->next;
	pre->next = del->next;
	free(del);
	del = NULL;
}

void reserve(Stu* head)//倒置
{
	Stu* p,q;
	p=head->next;
	head->next = NULL;
	while(p)
	{
		q=p;
		p=p->next;
		q->next = head->next;
		head->next = q;
	}
}