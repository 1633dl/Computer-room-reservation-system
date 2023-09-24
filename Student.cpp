#include"Student.h"
Student::Student(string name, int number, string password)
{
	this->name = name;
	this->number = number;
	this->password = password;
	this->read_message();//��ȡ��������
	this->initilize_map();//��ʼ��map����
	//�鿴�Ƿ�ԤԼ��
	//��ʱ����һ�����������ڲ�������
	Apply temp(this->name, this->number, 0, 0, 'c', 0);
	vector<Apply>::iterator it = find(this->txt_apply_ok.begin(), this->txt_apply_ok.end(),temp);
	vector<Apply>::iterator its = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
	if (it != this->txt_apply_ok.end() || its != this->txt_apply_waiting.end())
	{
		this->is_apply = true;//ԤԼ��
	}
	else
		this->is_apply = false;//û��ԤԼ��
}
//����ԤԼ,��ѧ������������ļ���
void Student::apply()
{
	if (this->is_apply)
	{
		cout << "���Ѿ�ԤԼ��һ�Σ������ٴ�ԤԼ" << endl;
		return;
	}
	int day;//����
	int time;//����
	char room;//����
	while (1)
	{
		cout << "��������ҪԤԼ������:" << endl;
		cout << "1������һ 2�����ڶ� 3�������� 4�������� 5��������" << endl;
		cin >> day;
		for (int i = 1; i < 6; i++)
		{
			if (day == i)
				goto A;
		}
	}
A:
	while (1)
	{
		cout << "��������Ҫѡ���ʱ��" << endl << "1������ 2������" << endl;
		cin >> time;
		if (time == 1 || time == 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}
	while (1)
	{
		cout << "��������Ҫѡ��Ļ���" << endl << "A���� B���� C����" << endl;
		cin >> room;
		if (room == 'A'||room == 'B'||room == 'C')
			break;
		cout << "������������������" << endl;
	}	
	//����Ϣ���뵽�ļ�
	//���˳��Ϊ��������ѧ�š����ڡ�ʱ�䡢�����š�ԤԼ״̬(1��ԤԼ�ɹ� 2��δ�ɹ� 3����������)
	ofstream ofs;
	ofs.open(ORDER_WAITING_FILE, ios::app);
	ofs << this->name << " " << this->number << " " << day << " " << time << " " <<
		room << " " << 3 << endl;
	ofs.close();
	//����Ϣ�����vector������
	this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, 3));
	this->is_apply = true;//ԤԼ��һ��
	cout << "ԤԼ�ɹ���" << endl;
}

//ȡ��ԤԼ
void Student::cancle_order()
{
	if (!this->is_apply)
	{
		cout << "����û��ԤԼ!" << endl;
		return;
	}
	cout << "��ȷ��Ҫȡ����" << endl;
	cout << "1��ȡ�� 2����ȡ��" << endl;
	cin >> select;
	if (this->select == 1)
	{	//��ʱ����һ�����������ڲ�������
		Apply temp(this->name, this->number, 0, 0, 'c', 0);
		vector<Apply>::iterator it = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
		this->txt_apply_waiting.erase(it);//ɾ������
		//д�ļ�
		ofstream ofs;
		ofs.open(ORDER_WAITING_FILE, ios::trunc);
		for (vector<Apply>::iterator it = this->txt_apply_waiting.begin(); it !=this->txt_apply_waiting.end(); it++)
		{
			ofs << it->name << " " << it->number << " " << it->day << " " 
				<< it->time << " " << it->room << " " << it->state << endl;
		}
		ofs.close();
		cout << "ɾ���ɹ�!" << endl;
	}
	else
		return;
}

//���������˵�ԤԼ(ֻ������ԤԼ�ɹ�����,��ֻ�ܿ������������ڣ�ʱ�䣬������)
void Student::find_all_order()
{
	if (this->txt_apply_ok.empty())
	{
		cout << "ԤԼ����Ϊ0" << endl;
	}
	//for_each(this->txt_apply_ok.begin(), this->txt_apply_ok.end(),myclass());
	for (vector<Apply>::iterator it = this->txt_apply_ok.begin(); it != this->txt_apply_ok.end(); it++)
	{
		cout << it->name << " ";
		map<int,string>::iterator its=this->day.find(it->day);
		cout << its->second << " ";
		its = this->time
			.find(it->time);
		cout << its->second << " " << it->room << "�Ż���" << endl;
	}
}

//�������������״̬
void Student::find_mine()
{
	if (!this->is_apply)
	{
		cout << "�㻹û��ԤԼ" << endl;
	}
	else
	{
		Apply temp(this->name, this->number, 0, 0, 'c', 0);
		vector<Apply>::iterator it = find(this->txt_apply_ok.begin(), this->txt_apply_ok.end(), temp);
		if (it != this->txt_apply_ok.end())
		{
			cout << "����ԤԼͨ����" << endl;
			return;
		}
		vector<Apply>::iterator its = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
		if (its != this->txt_apply_waiting.end())
		{
			cout << "����ԤԼ��������С���" << endl;
			return;
		}
		else
		{
			cout << "����ԤԼû�б�ͨ��" << endl;
		}
	}
}

//��ȡ��������(������״̬�µ�ԤԼ�������ֲ�ͬ��������)
void Student::read_message()
{
	int time, day, number, state;//����,���ڣ��˺ţ�ԤԼ״̬
	char room;//����
	string name;
	ifstream ifs;
	//ԤԼͨ��
	ifs.open(ORDER_OK_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_ok.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//�ȴ�����
	ifs.open(ORDER_WAITING_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//������ͨ��
	ifs.open(ORDER_REFUSE_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_refuse.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
}

//�����˵�
void Student::operator_menu()
{
	while (1)
	{
		cout << "��ѡ��һ�����" << endl;
		cout << "***************************" << endl;
		cout << "***1������ԤԼ*************" << endl;
		cout << "***2���������ҵ�ԤԼ״̬***" << endl;
		cout << "***3���鿴�����˵�ԤԼ*****" << endl;
		cout << "***4��ȡ��ԤԼ*************" << endl;
		cout << "***5��ע����¼*************" << endl;
		cout << "***************************" << endl;
		cin >> this->select;
		switch (this->select)
		{
		case 1://����ԤԼ
			this->apply(); break;
		case 2://���������ԤԼ״̬
			this->find_mine(); break;
		case 3://�鿴�����˵�ԤԼ
			this->find_all_order(); break;
		case 4://ȡ��ԤԼ
			this->cancle_order(); break;
		case 5://ע����¼
			return;
		default:
			cout << "�������" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}