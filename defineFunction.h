#ifndef _SMS_
#define _SMS_

typedef struct tagStudent
{
	char name[10];											//学生名字
	char gender[2];											//学生性别
	int stuID;											    //学生学号
	int age;											      //学生年龄
	int score;											    //学生分数
}Student;

typedef struct pNode
{
	Student stuInfo;										  //学生信息域
	struct pNode* next;										//指针域
}Node;

void initialList(Node *&L);									//初始化链表
void welcome();												      //声明欢迎界面函数
void menu();												        //声明菜单界面函数

void inputStuInfo(Node *&L);								//声明输入信息函数
bool reviseStuInfo(char name[10]);							//声明修改信息函数
bool deleteStuInfo(Node *L,char name[10]);					//声明删除信息函数
Node* findStuInfo(char name[10]);							//声明查找信息函数
void printStuInfo();										      //声明打印信息函数
int countStuInfo(Node *L);									 //声明统计人数函数
void swap(Node *p,Node *q);									 //结点信息交换
void sortByScore();											    //按成绩排序
void readStuInfo();											    //声明读取信息函数
bool saveStuInfo();											  //声明保存信息函数
void exitSystem();											   //声明退出系统函数
void addNode(Node *L,Node *add);							//声明添加节点函数，用于写入文件

#endif
