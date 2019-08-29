// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<malloc.h>
#include<string>
#include<stdio.h>
#include <iostream>
using namespace std;
typedef struct{
	string pid;
	int priority;
	int running_time;
	char state='R';
}ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode* next;//指向后继节点
}LinkNode;//声明单链表节点类型

//根据输入进程id，优先级和运行时间设置单链表节点信息，并将节点依次连接进表中，传入参数：新增加的单链表节点，单链表头结点
void createPCB(LinkNode *&pcb,LinkNode *&L)
{
//	pcb = (LinkNode*)malloc(sizeof(LinkNode));
	pcb = new LinkNode;
	//获取进程id
	cout << "Please input your pid: ";
//	long int pid;
	string pid;
	cin >> pid;
	pcb->data.pid=pid;
	//获取进程优先级（必须为正整数）
	cout << "Please input the priority of this process( it must be a positive integer!): ";
	int priority;
	cin >> priority;
	if (priority <= 0) {
		cout << "Invalid! " << endl;
		cout << "Please input the priority of this process( it must be a positive integer!): ";
	}
	pcb->data.priority=priority;
	//获取进程运行时间必须为正整数
	cout << "Please input the running time you want to set to this process:( it must be positive!): ";
	int runningtime;
	cin >> runningtime;
	if (runningtime <= 0) {
		cout << "Invalid!" << endl;
		cout << "Please input the running time you want to set to this process:( it must be positive!): ";
	}
	pcb->data.running_time=runningtime;
	//提示进程创建成功
	cout << "Process " << pcb->data.pid<< " has been successfully created!" << endl << endl;
	//将节点用头插法插入单链表中
	pcb->next = L->next;
	L->next = pcb;
}

//初始化单链表
void InitList(LinkNode*& L)
{
//	L = (LinkNode*)malloc(sizeof(LinkNode));
	L = new LinkNode;
	L->next = NULL;	
}

//得到就绪队列，（在已有单链表基础上进行冒泡排序）
void getReadyQueue(LinkNode*& L)
{
	LinkNode* pre, * p, * tail, * temp;
	tail = NULL;
	pre = L;
	while ((L->next->next) != tail)
	{
		p = L->next;
		pre = L;
		while (p->next != tail)
		{
			if ((p->data.priority) < (p->next->data.priority))
			{
				pre->next = p->next;
				temp = p->next->next;
				p->next->next = p;
				p->next = temp;
				p = pre->next;
			}
			p = p->next;
			pre = pre->next;
		}
		tail = p;
	}
}

//打印就绪队列信息
void showReadyQueue(LinkNode* L)
{
	LinkNode* s = L->next;
	if (s != NULL)
	{
		cout << "Ready Process Queue: " << endl;
		cout << "-----------------------------" << endl;
		cout << "  Pid	    Priority	   Running_time" << endl;
	}
	while (s != NULL)
	{
		cout <<"  "<< s->data.pid<< "		" << s->data.priority << "		" << s->data.running_time << endl;
		s = s->next;
	}
	cout << "-----------------------------" << endl;
}

//执行进程
void doPCB(LinkNode*& L)
{
	//先输出刚才执行的进程信息，包括进程id，优先级和运行时间
	LinkNode* s = L->next;
	cout << "The executing process: " << s->data.pid << "; "<< "Its current priority: " << s->data.priority << "; "<< "Remaining time: " << s->data.running_time << endl;
	//优先级减一
	if (s->data.priority > 0)
		s->data.priority -= 1;
	//运行时间减一
	s->data.running_time -= 1;
	
	if (s->data.running_time > 0)//如果运行时间仍旧大于0，表明时间片用完，但进程还没执行结束，将该进程重新进就绪队列
	{
		getReadyQueue(L);
	}
	else//如果以运行完，则将状态设为F，并删掉就绪队列单链表中这个结点
	{
		s->data.state = 'F';
		cout << "Process " << s->data.pid<< " has completed execution successfully!" << endl;
		L->next = s->next;
		s = s->next;
	}
}

int main()
{
	LinkNode *p1, *p2,*p3,*p4,*p5;//新建单链表节点
	LinkNode* queue;//头结点
	InitList(queue);//初始化单链表
	createPCB(p1,queue);//将用户输入的信息导入结点，并将节点插入单链表
	createPCB(p2,queue);
	createPCB(p3,queue);
	createPCB(p4,queue);
	createPCB(p5,queue);
	getReadyQueue(queue);//得到就绪队列
	showReadyQueue(queue);//打印此时就绪队列信息
	cout << endl;
	while (queue->next != NULL)//如果就绪队列不为空，依次从队列中去队首进程执行，并打印执行进程的信息和更新后的就绪队列情况
	{		
		cout << "After executing----"<<endl;
		doPCB(queue);
		showReadyQueue(queue);
		cout << endl;
	}
	cout << "Process executing completed!" << endl;
	return 0;
}
