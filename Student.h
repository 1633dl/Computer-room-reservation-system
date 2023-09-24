#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include"Indentity.h"
#include"globafile.h"
//学生只能预约一次，除非手动取消或被老师取消，否则不能再次申请
//存放顺序为：姓名、学号、日期、时间、机房号、预约状态(1、预约成功 2、未成功 3、还在批阅)
/*
class myclass
{
public:
void operator()(const Apply&apply)
{
cout << apply.name << " " << apply.number << " " << apply.day << " " << apply.time << " " << apply.room << endl;
}
};
*/

class Student:public Indentity
{
public:
	Student(string name, int number, string password);
	virtual void operator_menu();//操作菜单
	void apply();//申请预约
	void find_mine();//查看自身预约
	void find_all_order();//查看所有人的预约
	void cancle_order();//取消预约
	virtual void read_message();//读取申请的文件

	bool is_apply;//判断是否预约过
	string name;
};