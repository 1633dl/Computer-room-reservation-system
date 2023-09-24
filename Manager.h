#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Indentity.h"
#include"globafile.h"
#include"Student.h"
#include"Teacher.h"
#include<vector>
#include<map>
#include<queue>
using namespace std;
class Manager:public Indentity
{
public:
	Manager(int number,string password);
	virtual void operator_menu();//操作菜单
	virtual void read_message();//读取申请的信息，但在管理员这里给个空实现就好
	void add_account();//添加账号
	void check_all_account();//查看所有账号
	void check_computer();//查看机房信息
	void cleanFile();//清空预约
	~Manager();
	//以上是操作菜单中的函数，以下是其他的函数

	bool number_is_true(int m_number);//查看账号是否重复
	void read_txt();//读取数据
	map<char, int>computer;//机房的信息
	vector<vector<Indentity*>>v_number;//用来存放所有学生老师账号
};