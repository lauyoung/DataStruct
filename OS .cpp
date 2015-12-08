#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<malloc.h>
#include <assert.h>
using namespace std;


typedef struct node {
	int ID;
	int PRIORITY; //进程优先数  
	int CPUTIME;  //进程占用CPU的时间  
	int ALLTIME;  //进程所需要时间  
	char STATE;   //进程当前状态  
	struct node *next;//指向下一个进程  
}PRO;
int CHIP; //时间片数  
int NUM;  //进程个数  
int A;    // 0代表先来先服务算法 1时间片轮转调度算法  
PRO *head; //进程队列队头;  

int num()//计算所有进程是否都调度完毕 返回为完成进程个数
{
	int i = NUM;
	PRO *t1;
	t1 = head;
	while (t1 != NULL) {
		if (t1->ALLTIME == 0)
			i--;
		t1 = t1->next;
	}
	return i;
}
PRO *_sort(PRO *h)//链表排序子函数
{
	PRO *head, *max;
	max = h;
	head = h;
	while (head->next != NULL) {//找max的节点  
		head = head->next;
		if (max->PRIORITY<head->PRIORITY)
			max = head;
	}
	head->next = h;//形成环形链表  
	while (head->next != max)//找出min节点前面的节点并让它指向NULL  
		head = head->next;
	head->next = NULL;
	h = max;
	return h;
}
PRO *sort(PRO *h) {//链表排序   
	PRO *head;
	if (h == NULL)
		return h;
	h = _sort(h);
	head = h;
	while (head->next != NULL) {
		head->next = _sort(head->next);
		head = head->next;
	}
	return h;
}
void show() {//显示当前状态  
	PRO *t1;
	t1 = head;
	printf("ID  PRIORITY  CPUTIME  ALLTIME  STATE\n");
	while (t1 != NULL) {
		printf("head%-3d%-10d%-9d%-7d  %c\n", t1->ID, t1->PRIORITY, t1->CPUTIME, t1->ALLTIME, t1->STATE);
		t1 = t1->next;
	}
	printf("-------------------------------------\n\n");
}
void queue() {//先来先服务算法  
	int t;
	PRO *t1 = head;
	printf("先来先服务算法，初始状态到每一个时间片用完状态：\n");
	show();
	while (t1 != NULL) {
		while (t1 != NULL) {
			t1->CPUTIME = t1->ALLTIME;
			t1->ALLTIME = 0;
			t1->STATE = 'F';
			t1 = t1->next;
		}
		show();
	}
}
void priority() {//优先级算法  
	int t;
	PRO *t1;
	head = sort(head);
	t1 = head;
	printf("优先级算法，初始状态到每一个时间片用完状态：\n");
	show();
	while (t1 != NULL) {
		t = CHIP;
		while (t != 0 && t1 != NULL) {
			t--;
			t1->ALLTIME--;
			t1->CPUTIME++;
			t1->STATE = 'E';
			if (t1->ALLTIME == 0) {//进程调度完毕  
				t1->STATE = 'F';
				t1 = t1->next;
			}
		}
		show();
	}
}
void time() {//时间片轮转 
	int t;
	int flag = 0;
	PRO *t1 = head;

	printf("时间片轮转算法，初始状态到每一个时间片用完状态：\n");
	show();
	while (!flag)
	{
		while (t1 != NULL&&t1->ALLTIME>0) {
			t = CHIP;
			while (t != 0 && t1 != 0) {
				t1->ALLTIME -= t;
				if (t1->ALLTIME < 0)
				{
					t1->ALLTIME = 0;
				}
		
				t1->CPUTIME += t;
				t1->STATE = 'W';
				if (t1->ALLTIME == 0)
				{//进程调度完毕  
					t1->STATE = 'F';  //状态为完成态
				}
				t1 = t1->next;
				t = 0;
			}
			show();
		}
		t1 = head;
		while (t1 && t1->STATE == 'F')
		{
			t1 = t1->next;
		}
		if (t1 == NULL)
		{
			return;
		}
		else
		{
			flag = 0;
		}
	}

}
//void time() {//时间片轮转 
//	int t;
//	int flag = 0;
//	PRO *t1 = head;
//
//	printf("时间片轮转算法，初始状态到每一个时间片用完状态：\n");
//	show();
//	while (!flag)
//	{
//		while (t1 != NULL) {
//			t = CHIP;
//			while (t != 0 && t1 != 0) {
//				t1->ALLTIME -= t;
//				if (t1->ALLTIME < 0)
//				{
//					t1->ALLTIME = 0;
//				}
//				t1->CPUTIME += t;
//				t1->STATE = 'W';
//				if (t1->ALLTIME == 0)
//				{//进程调度完毕  
//					t1->STATE = 'F';  //状态为完成态
//				}
//				t1 = t1->next;
//				t = 0;
//			}
//			show();
//		}
//		t1 = head;
//		while (t1 && t1->STATE=='F')
//		{
//			t1 = t1->next;
//		}
//		if (t1 == NULL)
//		{
//			return;
//		}
//		else
//		{
//			flag = 0;
//		}
//	}
//	
//}
void create_process() {//创建进程  
	PRO *t1, *t2;
	int i = 1;
	printf("请输入时间片数：");
	scanf("%d", &CHIP);
	printf("请输入想创建进程个数（大于1）：");
	scanf("%d", &NUM);
	head = (PRO *)malloc(sizeof(PRO));
	t1 = head;
	t1->ID = i;
	t1->STATE = 'R'; //一开始都为就绪态ready 
	t1->CPUTIME = 0;//开始创建时 占用
	printf("请输入进程%d的优先级：", i);
	scanf("%d", &t1->PRIORITY);
	printf("请输入进程%d的需要运行时间：", i);
	scanf("%d", &t1->ALLTIME);
	while (i++<NUM) {
		t2 = (PRO *)malloc(sizeof(PRO));
		t1->next = t2;
		t2->ID = i;
		t2->STATE = 'R';
		t2->CPUTIME = 0;//开始创建时 占用
		printf("请输入进程head%d的优先级：", i);
		scanf("%d", &t2->PRIORITY);
		printf("请输入进程head%d的需要运行时间：", i);
		scanf("%d", &t2->ALLTIME);
		t1 = t2;
	}
	t1->next = NULL;
}
int main()
{
	int ch;
	printf("请选择算法：\n0.先来先服务 \n1.时间片轮转 \n2优先级服务\n");
	cin >> ch;
	
	create_process();//再创建进程
	switch (ch)
	{
	case 0:
		printf("先来先服务\n");
		queue();
		break;
	case 1:
		printf("时间片轮转\n");
		time();
		break;
	case 2:
		printf("优先级服务\n");
		priority();
		break;
	}
	  
	
	return 0;
}