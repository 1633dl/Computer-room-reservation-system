#include"Indentity.h"
//��ȡ������Ϣ
void Indentity::read_message()
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
//��ʼ��map����
void Indentity::initilize_map()
{
	//��ʼ������
	this->day.insert(make_pair(1, "����һ"));
	this->day.insert(make_pair(2, "���ڶ�"));
	this->day.insert(make_pair(3, "������"));
	this->day.insert(make_pair(4, "������"));
	this->day.insert(make_pair(5, "������"));
	//��ʼ��ʱ��
	this->time.insert(make_pair(1,"����"));
	this->time.insert(make_pair(2,"����"));
}