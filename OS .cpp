#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<conio.h>
#include<malloc.h>
#include <assert.h>
using namespace std;


typedef struct node {
	int ID;
	int PRIORITY; //����������  
	int CPUTIME;  //����ռ��CPU��ʱ��  
	int ALLTIME;  //��������Ҫʱ��  
	char STATE;   //���̵�ǰ״̬  
	struct node *next;//ָ����һ������  
}PRO;
int CHIP; //ʱ��Ƭ��  
int NUM;  //���̸���  
int A;    // 0���������ȷ����㷨 1ʱ��Ƭ��ת�����㷨  
PRO *head; //���̶��ж�ͷ;  

int num()//�������н����Ƿ񶼵������ ����Ϊ��ɽ��̸���
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
PRO *_sort(PRO *h)//���������Ӻ���
{
	PRO *head, *max;
	max = h;
	head = h;
	while (head->next != NULL) {//��max�Ľڵ�  
		head = head->next;
		if (max->PRIORITY<head->PRIORITY)
			max = head;
	}
	head->next = h;//�γɻ�������  
	while (head->next != max)//�ҳ�min�ڵ�ǰ��Ľڵ㲢����ָ��NULL  
		head = head->next;
	head->next = NULL;
	h = max;
	return h;
}
PRO *sort(PRO *h) {//��������   
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
void show() {//��ʾ��ǰ״̬  
	PRO *t1;
	t1 = head;
	printf("ID  PRIORITY  CPUTIME  ALLTIME  STATE\n");
	while (t1 != NULL) {
		printf("head%-3d%-10d%-9d%-7d  %c\n", t1->ID, t1->PRIORITY, t1->CPUTIME, t1->ALLTIME, t1->STATE);
		t1 = t1->next;
	}
	printf("-------------------------------------\n\n");
}
void queue() {//�����ȷ����㷨  
	int t;
	PRO *t1 = head;
	printf("�����ȷ����㷨����ʼ״̬��ÿһ��ʱ��Ƭ����״̬��\n");
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
void priority() {//���ȼ��㷨  
	int t;
	PRO *t1;
	head = sort(head);
	t1 = head;
	printf("���ȼ��㷨����ʼ״̬��ÿһ��ʱ��Ƭ����״̬��\n");
	show();
	while (t1 != NULL) {
		t = CHIP;
		while (t != 0 && t1 != NULL) {
			t--;
			t1->ALLTIME--;
			t1->CPUTIME++;
			t1->STATE = 'E';
			if (t1->ALLTIME == 0) {//���̵������  
				t1->STATE = 'F';
				t1 = t1->next;
			}
		}
		show();
	}
}
void time() {//ʱ��Ƭ��ת 
	int t;
	int flag = 0;
	PRO *t1 = head;

	printf("ʱ��Ƭ��ת�㷨����ʼ״̬��ÿһ��ʱ��Ƭ����״̬��\n");
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
				{//���̵������  
					t1->STATE = 'F';  //״̬Ϊ���̬
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
//void time() {//ʱ��Ƭ��ת 
//	int t;
//	int flag = 0;
//	PRO *t1 = head;
//
//	printf("ʱ��Ƭ��ת�㷨����ʼ״̬��ÿһ��ʱ��Ƭ����״̬��\n");
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
//				{//���̵������  
//					t1->STATE = 'F';  //״̬Ϊ���̬
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
void create_process() {//��������  
	PRO *t1, *t2;
	int i = 1;
	printf("������ʱ��Ƭ����");
	scanf("%d", &CHIP);
	printf("�������봴�����̸���������1����");
	scanf("%d", &NUM);
	head = (PRO *)malloc(sizeof(PRO));
	t1 = head;
	t1->ID = i;
	t1->STATE = 'R'; //һ��ʼ��Ϊ����̬ready 
	t1->CPUTIME = 0;//��ʼ����ʱ ռ��
	printf("���������%d�����ȼ���", i);
	scanf("%d", &t1->PRIORITY);
	printf("���������%d����Ҫ����ʱ�䣺", i);
	scanf("%d", &t1->ALLTIME);
	while (i++<NUM) {
		t2 = (PRO *)malloc(sizeof(PRO));
		t1->next = t2;
		t2->ID = i;
		t2->STATE = 'R';
		t2->CPUTIME = 0;//��ʼ����ʱ ռ��
		printf("���������head%d�����ȼ���", i);
		scanf("%d", &t2->PRIORITY);
		printf("���������head%d����Ҫ����ʱ�䣺", i);
		scanf("%d", &t2->ALLTIME);
		t1 = t2;
	}
	t1->next = NULL;
}
int main()
{
	int ch;
	printf("��ѡ���㷨��\n0.�����ȷ��� \n1.ʱ��Ƭ��ת \n2���ȼ�����\n");
	cin >> ch;
	
	create_process();//�ٴ�������
	switch (ch)
	{
	case 0:
		printf("�����ȷ���\n");
		queue();
		break;
	case 1:
		printf("ʱ��Ƭ��ת\n");
		time();
		break;
	case 2:
		printf("���ȼ�����\n");
		priority();
		break;
	}
	  
	
	return 0;
}