/*
问题：添加账号时，文件中的添加没有问题，但是添加完读取时总是少两位
*/
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<fstream>
#include"globafile.h"
#include"Indentity.h"
#include"Student.h"
#include"Manager.h"
#include"Teacher.h"
//选择身份登录
void enter(string file_name, int type)
{
	Indentity* person = NULL;
	//登录读文件
	ifstream ifs;
	ifs.open(file_name, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		return;
	}
	int m_number;
	string m_post;
begin:
	cout << "请输入你的账号" << endl;
	cin >> m_number;
	cout << "请输入你的密码" << endl;
	cin >> m_post;
	//开始遍历文件查找与之匹配的信息
	int number;
	string name, pastword;
	if (type == 1 || type == 2)//学生或老师的情况
	{
		while (ifs >> number&&ifs >> name&&ifs >> pastword)
		{
			if (number == m_number&&m_post == pastword)
			{
				system("cls");
				cout << "你好!" << name << endl;
				cout << "欢迎使用机房预约系统!" << endl;
				if (type == 1)//学生登录
				{
					person = new Student(name, number, pastword);
					person->operator_menu();
				}
				else//老师登录
				{
					person = new Teacher(name, number, pastword);				
					person->operator_menu();
				}
				ifs.close();
				delete person;
				return;
			}
		}
	}
	else//管理员的情况
	{
		while (ifs >> number&&ifs >> pastword)
		{
			if (number == m_number&&m_post == pastword)
			{
				cout << "欢迎使用机房预约系统!" << endl;
				person = new Manager(number, pastword);
				person->operator_menu();
				ifs.close();
				delete person;
				return;
			}
		}
	}
	cout << "账号或密码错误!" << endl;

	cout << "是否返回上一项"<<"1、是 2、否" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		return;
	}
	system("pause");
	system("cls");
	goto begin;
}
void show_menu()
{
	cout << "欢迎来到机房预约系统 " << endl;
	cout << "*********************" << endl;
	cout << "*******1、学生*******" << endl;
	cout << "*******2、老师*******" << endl;
	cout << "*******3、管理员*****" << endl;
	cout << "*******4、退出*******" << endl;
	cout << "*********************" << endl;
	cout << "请输入你的选项" << endl;
}
int main()
{
	int select;
	while (1)
	{
		show_menu();
		cin >> select;//输入你的选项
		switch (select)
		{
		case 1://学生模式
			enter(STUDENT_FILE, 1);
			break;
		case 2://老师模式
			enter(TEACHER_FILE, 2);
			break;
		case 3://管理员模式
			enter(ADMIN_FILE, 3);
			break;
		case 4:
			exit(0);break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}