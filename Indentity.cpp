#include"Indentity.h"
//读取申请信息
void Indentity::read_message()
{
	int time, day, number, state;//房间,日期，账号，预约状态
	char room;//机房
	string name;
	ifstream ifs;
	//预约通过
	ifs.open(ORDER_OK_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_ok.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//等待批阅
	ifs.open(ORDER_WAITING_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//不予与通过
	ifs.open(ORDER_REFUSE_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_refuse.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
}
//初始化map容器
void Indentity::initilize_map()
{
	//初始化日期
	this->day.insert(make_pair(1, "星期一"));
	this->day.insert(make_pair(2, "星期二"));
	this->day.insert(make_pair(3, "星期三"));
	this->day.insert(make_pair(4, "星期四"));
	this->day.insert(make_pair(5, "星期五"));
	//初始化时间
	this->time.insert(make_pair(1,"上午"));
	this->time.insert(make_pair(2,"下午"));
}