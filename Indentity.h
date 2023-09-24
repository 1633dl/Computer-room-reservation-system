#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<queue>
#include"globafile.h"
using namespace std;
//存放申请的类
class Apply
{
public:
	//存放顺序为：姓名、学号、日期、时间、机房号、预约状态
	Apply()
	{

	}
	Apply(string name, int number, int day, int time, char room, int state)
	{
		this->name = name;
		this->number = number;
		this->day = day;
		this->time = time;
		this->room = room;
		this->state = state;
	}
	bool operator==(const Apply& apply)
	{
		if (this->number == apply.number)
		{
			return true;
		}
		else
			return false;
	}
	int state;//预约的状态
	string name;//星期一到星期五,预约者的姓名
	int number, time,day;//上午或者下午,预约者的账号
	char room;//机房
};
//总的父类，被老师，学生，管理员继承
class Indentity
{
public:
	vector<Apply>txt_apply_ok;//存放所有通过的预约
	vector<Apply>txt_apply_waiting;//存放所有待处理的预约
	vector<Apply>txt_apply_refuse;//存放所有不予通过的预约
	map<int, string>day;//用于对应星期几
	map<int, string>time;//用于对应上下午

	int select;//用于每个用户选择对应身份的列表中的信息
	int number;//账号
	virtual void read_message()=0;//读取各种申请信息
	virtual void operator_menu() = 0;//操作菜单
	void initilize_map();//初始化
protected:
	string password;
};