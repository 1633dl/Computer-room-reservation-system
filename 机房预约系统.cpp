/*
���⣺����˺�ʱ���ļ��е����û�����⣬����������ȡʱ��������λ
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
//ѡ����ݵ�¼
void enter(string file_name, int type)
{
	Indentity* person = NULL;
	//��¼���ļ�
	ifstream ifs;
	ifs.open(file_name, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		return;
	}
	int m_number;
	string m_post;
begin:
	cout << "����������˺�" << endl;
	cin >> m_number;
	cout << "�������������" << endl;
	cin >> m_post;
	//��ʼ�����ļ�������֮ƥ�����Ϣ
	int number;
	string name, pastword;
	if (type == 1 || type == 2)//ѧ������ʦ�����
	{
		while (ifs >> number&&ifs >> name&&ifs >> pastword)
		{
			if (number == m_number&&m_post == pastword)
			{
				system("cls");
				cout << "���!" << name << endl;
				cout << "��ӭʹ�û���ԤԼϵͳ!" << endl;
				if (type == 1)//ѧ����¼
				{
					person = new Student(name, number, pastword);
					person->operator_menu();
				}
				else//��ʦ��¼
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
	else//����Ա�����
	{
		while (ifs >> number&&ifs >> pastword)
		{
			if (number == m_number&&m_post == pastword)
			{
				cout << "��ӭʹ�û���ԤԼϵͳ!" << endl;
				person = new Manager(number, pastword);
				person->operator_menu();
				ifs.close();
				delete person;
				return;
			}
		}
	}
	cout << "�˺Ż��������!" << endl;

	cout << "�Ƿ񷵻���һ��"<<"1���� 2����" << endl;
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
	cout << "��ӭ��������ԤԼϵͳ " << endl;
	cout << "*********************" << endl;
	cout << "*******1��ѧ��*******" << endl;
	cout << "*******2����ʦ*******" << endl;
	cout << "*******3������Ա*****" << endl;
	cout << "*******4���˳�*******" << endl;
	cout << "*********************" << endl;
	cout << "���������ѡ��" << endl;
}
int main()
{
	int select;
	while (1)
	{
		show_menu();
		cin >> select;//�������ѡ��
		switch (select)
		{
		case 1://ѧ��ģʽ
			enter(STUDENT_FILE, 1);
			break;
		case 2://��ʦģʽ
			enter(TEACHER_FILE, 2);
			break;
		case 3://����Աģʽ
			enter(ADMIN_FILE, 3);
			break;
		case 4:
			exit(0);break;
		default:
			cout << "�����������������" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}