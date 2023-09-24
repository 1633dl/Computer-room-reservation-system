#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<queue>
#include"globafile.h"
using namespace std;
//����������
class Apply
{
public:
	//���˳��Ϊ��������ѧ�š����ڡ�ʱ�䡢�����š�ԤԼ״̬
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
	int state;//ԤԼ��״̬
	string name;//����һ��������,ԤԼ�ߵ�����
	int number, time,day;//�����������,ԤԼ�ߵ��˺�
	char room;//����
};
//�ܵĸ��࣬����ʦ��ѧ��������Ա�̳�
class Indentity
{
public:
	vector<Apply>txt_apply_ok;//�������ͨ����ԤԼ
	vector<Apply>txt_apply_waiting;//������д������ԤԼ
	vector<Apply>txt_apply_refuse;//������в���ͨ����ԤԼ
	map<int, string>day;//���ڶ�Ӧ���ڼ�
	map<int, string>time;//���ڶ�Ӧ������

	int select;//����ÿ���û�ѡ���Ӧ��ݵ��б��е���Ϣ
	int number;//�˺�
	virtual void read_message()=0;//��ȡ����������Ϣ
	virtual void operator_menu() = 0;//�����˵�
	void initilize_map();//��ʼ��
protected:
	string password;
};