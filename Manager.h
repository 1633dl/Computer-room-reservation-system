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
	virtual void operator_menu();//�����˵�
	virtual void read_message();//��ȡ�������Ϣ�����ڹ���Ա���������ʵ�־ͺ�
	void add_account();//����˺�
	void check_all_account();//�鿴�����˺�
	void check_computer();//�鿴������Ϣ
	void cleanFile();//���ԤԼ
	~Manager();
	//�����ǲ����˵��еĺ����������������ĺ���

	bool number_is_true(int m_number);//�鿴�˺��Ƿ��ظ�
	void read_txt();//��ȡ����
	map<char, int>computer;//��������Ϣ
	vector<vector<Indentity*>>v_number;//�����������ѧ����ʦ�˺�
};