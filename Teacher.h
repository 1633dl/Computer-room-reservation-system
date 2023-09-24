#pragma once
#include<iostream>
#include<string>
#include<queue>
#include"Indentity.h"
class Teacher:public Indentity
{
public:
	Teacher(string name, int number, string password);
	virtual void operator_menu();//操作菜单
	virtual void read_message();//读取申请的数据
	void seek_all_order();//查找所有预约
	void check_order();//审核预约
	void delete_apply(int select);//将预约移除
	void show_apply(const vector<Apply>&v,int select);//展示每种预约

	//这里的vector容器(继承过来的)用于老师查看所有有人的预约，queue容器用于审核预约(先进先出)
	queue<Apply>txt_apply_wait;//用队列存放等待申请的数据
	string name;//姓名
};