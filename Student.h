#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include"Indentity.h"
#include"globafile.h"
//ѧ��ֻ��ԤԼһ�Σ������ֶ�ȡ������ʦȡ�����������ٴ�����
//���˳��Ϊ��������ѧ�š����ڡ�ʱ�䡢�����š�ԤԼ״̬(1��ԤԼ�ɹ� 2��δ�ɹ� 3����������)
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
	virtual void operator_menu();//�����˵�
	void apply();//����ԤԼ
	void find_mine();//�鿴����ԤԼ
	void find_all_order();//�鿴�����˵�ԤԼ
	void cancle_order();//ȡ��ԤԼ
	virtual void read_message();//��ȡ������ļ�

	bool is_apply;//�ж��Ƿ�ԤԼ��
	string name;
};