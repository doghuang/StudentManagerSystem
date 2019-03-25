/*  学生成绩管理系统
系统以菜单方式工作
学生信息录入功能（学生信息用文件保存）—输入
学生信息浏览功能——输出
查询、排序功能——算法 
1、按学号查询 
2、按姓名查询
学生信息的删除与修改
界面简单明了；
有一定的容错能力，比如输入的成绩不在0～100之间，就提示不合法，要求重新输入；
用链表的方式实现。
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "defineFunction.h"


Node* head;													//开辟链表头结点,头结点本身不存储信息
char ch[10];												//用于查删改学生信息输入姓名
Node* find;													//用于返回查找学生信息节点

int main() 
{
	system("color f9");
	initialList(head);
	menu();
	return 0;
}

//欢迎界面
void welcome()
{
	printf("\t\t*************************************************\n");
	printf("\t\t*\t ==欢迎使用高校学生成绩管理系统==\t*\n");
	printf("\t\t*\t      ****请选择功能列表****\t\t*\n");
	printf("\t\t*\t         1.输入学生信息\t\t\t*\n");
	printf("\t\t*\t         2.修改学生信息\t\t\t*\n");
	printf("\t\t*\t         3.删除学生信息\t\t\t*\n");
	printf("\t\t*\t         4.查找学生信息\t\t\t*\n");
	printf("\t\t*\t         5.打印所有学生信息\t\t*\n");
	printf("\t\t*\t         6.统计所有学生人数\t\t*\n");
	printf("\t\t*\t         7.读取学生信息\t\t\t*\n");
	printf("\t\t*\t         8.保存学生信息\t\t\t*\n");
	printf("\t\t*\t         9.按成绩降序排序\t\t*\n");
	printf("\t\t*\t         0.退出系统\t\t\t*\n");
	printf("\t\t*************************************************\n");
}

//功能选择菜单
void menu()
{
	while(1)
	{
		welcome();
		char input = getch();
		switch(input)
		{
			case '1':										//输入学生信息
				inputStuInfo(head);
				break;
			case '2':										//修改学生信息
				printf("请输入要修改的学生姓名：");
				scanf("%s",ch);
				if(reviseStuInfo(ch))
					printf("修改成功！\n");
				break;
			case '3':										//删除学生信息
				printf("请输入要删除的学生姓名：");
				scanf("%s",ch);
				if(deleteStuInfo(head,ch))
					printf("删除成功！\n");
				else
					printf("没有查询到此学生信息！\n");
				break;
			case '4':										//查找学生信息
				printf("请输入学生姓名:");
				scanf("%s",ch);
				find = findStuInfo(ch);
				if(find == NULL)
					printf("无此学生信息！\n");
				else
				{
					printf("\t\t---------------------------------------------\n");

					printf("\t\t|学生姓名：%s|性别：%s|年龄:%d|学号:%d|分数:%d|\n",
					find->stuInfo.name,find->stuInfo.gender,
					find->stuInfo.age,find->stuInfo.stuID,
					find->stuInfo.score);

					printf("\t\t---------------------------------------------\n\n");
				}
				break;
			case '5':										//打印所有学生信息
				system("cls");
				if(head->next == NULL)
					{
						printf("当前学生数据信息为空！\n");
						menu();
					}
				else
					printStuInfo();
				break;
			case '6':										//统计所有学生人数
				printf("当前学生信息总数:%d\n",countStuInfo(head));
				break;
			case '7':										//读取学生信息
				readStuInfo();
				break;
			case '8':										//保存学生信息
				if(saveStuInfo())
					printf("保存成功！\n");
				else
					printf("保存失败，请输入学生数据。");
				break;
			case '9':										//按成绩降序排序
				sortByScore();
				break;
			case '0':										//退出系统
				printf("欢迎再次使用!\n");
				exit(0);
				break;
			default:
				printf("输入错误，请重新输入！\n");
				break;
		}
	}
}

void initialList(Node *&L)
{
	L = (Node*)malloc(sizeof(Node));
	L->next = NULL;
}

//输入学生信息，每次将学生信息插入表尾
void inputStuInfo(Node *&L)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	printf("请输入学生姓名:");
	scanf("%s",newNode->stuInfo.name);
	printf("请输入学生性别:");
	scanf("%s",newNode->stuInfo.gender);
	printf("请输入学生年龄:");
	scanf("%d",&newNode->stuInfo.age);
	printf("请输入学生学号:");
	scanf("%d",&newNode->stuInfo.stuID);
	printf("请输入学生分数:");
	scanf("%d",&newNode->stuInfo.score);
	Node* p = L;												//当前遍历节点
	if(L->next == NULL)
		L->next = newNode;
	else
	{
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = newNode;
	}
	system("cls");
	printf("学生数据添加成功！\n");
}

//修改学生信息
bool reviseStuInfo(char name[10])
{
	char name_new[10],gender_new[2];
	int age_new,stuID_new,score_new;
	Node *found = findStuInfo(name);
	if(found == NULL)
	{
		printf("没有查询到该学生信息。\n");
		return false;
	}else
	{
		printf("请输入修改后的姓名:");
		scanf("%s",name_new);
		printf("请输入修改后的性别:");
		scanf("%s",gender_new);
		printf("请输入修改后的年龄:");
		scanf("%d",&age_new);
		printf("请输入修改后的学号:");
		scanf("%d",&stuID_new);
		printf("请输入修改后的成绩:");
		scanf("%d",&score_new);

		strcpy(found->stuInfo.name,name_new);						//对字符串进行操作
		strcpy(found->stuInfo.gender,gender_new);
		found->stuInfo.age = age_new;
		found->stuInfo.stuID = stuID_new;
		found->stuInfo.score = score_new;

		return true;
	}
}

//删除学生信息
bool deleteStuInfo(Node *L,char name[10])
{
	Node* search = L;
	Node* tmp;
	while(search->next !=NULL && strcmp(search->next->stuInfo.name, name) != 0)
	{
		search = search->next;
	}
	if(search->next == NULL)
		return false;
	tmp = search->next;
	search->next = search->next->next;
	free(tmp);
	return true;
}

//打印所有学生信息
void printStuInfo()
{
	printf("\t\t---------------------------------------------\n");
	Node* temp = head->next;
	if(temp == NULL)
	{
		printf("无学生信息，请录入！\n");
		menu();
	}
	else
	{
		while(temp != NULL)
		{
			printf("\t\t|学生姓名：%s|性别：%s|年龄:%d|学号:%d|分数:%d|\n",
				temp->stuInfo.name,temp->stuInfo.gender,
				temp->stuInfo.age,temp->stuInfo.stuID,
				temp->stuInfo.score);
			temp = temp->next;
		}
	}
	printf("\t\t---------------------------------------------\n\n");
}

//按姓名查找学生信息
Node *findStuInfo(char name[10])
{
	Node* seek = head->next;
	while(seek !=NULL && strcmp(seek->stuInfo.name, name) != 0)				//字符串的比较不能直接用 ==
	{
		seek = seek->next;
	}
	return seek;
}

//统计学生人数
int countStuInfo(Node *L)
{
	int cnt = 0;
	L = head->next;
	while(L != NULL)
	{
		++cnt;
		L = L->next;
	}
	return cnt;
}

//结点信息交换，用于排序
void swap(Node *p,Node *q)
{
	Node *tmp;
	initialList(tmp);

	strcpy(tmp->stuInfo.name,p->stuInfo.name);
	strcpy(tmp->stuInfo.gender,p->stuInfo.gender);
	tmp->stuInfo.age = p->stuInfo.age;
	tmp->stuInfo.stuID = p->stuInfo.stuID;
	tmp->stuInfo.score = p->stuInfo.score;

	strcpy(p->stuInfo.name,q->stuInfo.name);
	strcpy(p->stuInfo.gender,q->stuInfo.gender);
	p->stuInfo.age = q->stuInfo.age;
	p->stuInfo.stuID = q->stuInfo.stuID;
	p->stuInfo.score = q->stuInfo.score;

	strcpy(q->stuInfo.name,tmp->stuInfo.name);
	strcpy(q->stuInfo.gender,tmp->stuInfo.gender);
	q->stuInfo.age = tmp->stuInfo.age;
	q->stuInfo.stuID = tmp->stuInfo.stuID;
	q->stuInfo.score = tmp->stuInfo.score;
}

//按照成绩降序排序
void sortByScore()
{
	Node *p,*q,*r;
	if(head->next == NULL)
	{
		printf("请录入学生信息！\n");
		return;
	}
	r = head->next;
	while(r != NULL)
	{
		p = r;
		q = r->next;
		while(q != NULL)
		{
			if(q->stuInfo.score > p->stuInfo.score)
			{
				swap(p,q);
			}
			q = q->next;
		}
		r = r->next;
	}
	printf("排序后的结果为：\n");
	printStuInfo();
}

//添加节点到链表
void addNode(Node *L,Node *add)
{
	Node* p = L;												//当前遍历节点
	if(L->next == NULL)
		L->next = add;
	else
	{
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->next = add;
	}
}
//从文件中读取学生信息
void readStuInfo()
{
	Student in;
	FILE *fp = fopen("record.txt","r");
	if(fp == NULL)
	{
		printf("打开失败！\n");
		return;
	}
	int n;
	while(1)
	{
		n = fread(&in,1,sizeof(in),fp);
		if(n <= 0)
			break;
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->next = NULL;
		strcpy(newNode->stuInfo.name,in.name);
		strcpy(newNode->stuInfo.gender,in.gender);
		newNode->stuInfo.age = in.age;
		newNode->stuInfo.stuID = in.stuID;
		newNode->stuInfo.score = in.score;
		addNode(head,newNode);
	}
	fclose(fp);
	printf("读取成功！\n");
}

//将已经输入的学生信息保存到磁盘
bool saveStuInfo()
{
	FILE *fp = fopen("record.txt","w");
	Node *tmp = head->next;
	if(fp == NULL)
		return false;
	while(tmp != NULL)
	{
		fwrite(&tmp->stuInfo,1,sizeof(Student),fp);
		tmp = tmp->next;
	}
	fclose(fp);
	return true;
}
