#pragma once
#include<iostream>
#include<string>
#include<queue>
#include"Indentity.h"
class Teacher:public Indentity
{
public:
	Teacher(string name, int number, string password);
	virtual void operator_menu();//�����˵�
	virtual void read_message();//��ȡ���������
	void seek_all_order();//��������ԤԼ
	void check_order();//���ԤԼ
	void delete_apply(int select);//��ԤԼ�Ƴ�
	void show_apply(const vector<Apply>&v,int select);//չʾÿ��ԤԼ

	//�����vector����(�̳й�����)������ʦ�鿴�������˵�ԤԼ��queue�����������ԤԼ(�Ƚ��ȳ�)
	queue<Apply>txt_apply_wait;//�ö��д�ŵȴ����������
	string name;//����
};