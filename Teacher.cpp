#include"Teacher.h"
Teacher::Teacher(string name, int number, string password)
{
	this->name = name;
	this->password = password;
	this->number = number;
	this->read_message();//��ȡ��Ϣ(����Ϣ�ֱ�����3��������
	this->initilize_map();//��ʼ��map����
}
//��ȡԤԼ��Ϣ
void Teacher::read_message()
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
		//�����vector����������ʦ�鿴�������˵�ԤԼ��queue�����������ԤԼ(�Ƚ��ȳ�)
		this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, state));
		this->txt_apply_wait.push(Apply(name, number, day, time, room, state));
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
//���ԤԼ
void Teacher::check_order()
{
	if (this->txt_apply_wait.empty())
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	else
	{
		while (!this->txt_apply_wait.empty())
		{
			//��ʾ������Ϣ
			cout << this->txt_apply_wait.front().name << " " << this->txt_apply_wait.front().number << " ";
			map<int, string>::iterator its = this->day.find(this->txt_apply_wait.front().day);
			cout << its->second << " ";
			its = this->time.find(this->txt_apply_wait.front().time);
			cout << its->second << " " << this->txt_apply_wait.front().room << "�Ż���" << endl;
			//��ʼ����
	
			int choice;
			cout << "�Ƿ�ͬ��" << endl << "1��ͬ��" << " 2����ͬ��" << endl;
			cin >> choice;
			cout << "choice==" << choice << endl;
			if (choice == 1)
			{
				this->delete_apply(1);
			}
			else if (choice == 2)
			{
				this->delete_apply(2);
			}
			/*if (select != 1 || select != 2)
			{
				cout << "�������" << endl;
				goto A;
			}*/
		}
	}
	ofstream ofs;
	ofs.open(ORDER_WAITING_FILE, ios::out);
	ofs.clear();//���ȴ�����ļ��е��������
	ofs.close();
}

//�����˵�
void Teacher::operator_menu()
{
	while (1)
	{
		cout << "��ѡ��һ�����" << endl;
		cout << "***************************" << endl;
		cout << "***1���鿴����ԤԼ*********" << endl;
		cout << "***2�����ԤԼ*************" << endl;
		cout << "***3��ע����¼*************" << endl;
		cout << "***************************" << endl;
		cin >> this->select;
		switch (this->select)
		{
		case 1://�鿴����ԤԼ
			this->seek_all_order(); break;
		case 2://���ԤԼ
			this->check_order(); break;
		case 3:
			return;
		default:
			cout << "�������" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//�鿴����ԤԼ,���ǲ������κβ���
void Teacher::seek_all_order()
{
A:
	//ѡ��鿴��ԤԼ
	cout << "��ѡ����Ҫ�鿴��ԤԼ" << endl;
	cout << "1���Ѿ�ͬ���ԤԼ" << endl;
	cout << "2����δ��˵�ԤԼ" << endl;
	cout << "3���Ѿ����ܾ���ԤԼ" << endl;
	cin >> this->select;
	switch (this->select)
	{
	case 1:
		this->show_apply(this->txt_apply_ok, 1); break;
	case 2:
		this->show_apply(this->txt_apply_waiting, 1); break;
	case 3:
		this->show_apply(this->txt_apply_refuse, 1); break;
	default:
		cout << "�������" << endl;
		system("cls");
		system("pause");
		goto A;
		break;
	}
}

//չʾÿ��ԤԼ
void Teacher::show_apply(const vector<Apply>&v, int select)
{
	if (v.empty())
	{
		cout << "ԤԼΪ��" << endl;
	}
	for (vector<Apply>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->name << " "<<it->number<<" ";
		map<int, string>::iterator its = this->day.find(it->day);
		cout << its->second << " ";
		its = this->time.find(it->time);
		cout << its->second << " " << it->room << "�Ż���" << endl;
	}
}

//��ԤԼ�Ƴ�
void Teacher::delete_apply(int select)
{
	//�����ݴ�vector������ɾ��
	//��㴴��һ�����������ѯ
	Apply temp(this->txt_apply_wait.front().name, this->txt_apply_wait.front().number, 0, 0, 'c', 0);
	vector<Apply>::iterator it = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
	this->txt_apply_waiting.erase(it);

	//����һ�������������������vector������
	Apply apply(this->txt_apply_wait.front().name, this->txt_apply_wait.front().number,
		this->txt_apply_wait.front().day, this->txt_apply_wait.front().time, this->txt_apply_wait.front().room, 1);
	
	ofstream ofs;
	if (select == 1)//���ȴ����������Ƶ��ɹ���
	{
		ofs.open(ORDER_OK_FILE, ios::out | ios::app);
		this->txt_apply_ok.push_back(apply);
	}
	else//���ȴ����������Ƶ��ܾ���
	{
		ofs.open(ORDER_REFUSE_FILE, ios::out | ios::app);
		this->txt_apply_refuse.push_back(apply);
	}
	//�����ݷ����ļ���
	ofs << this->txt_apply_wait.front().name << " " << this->txt_apply_wait.front().number << " " <<
		this->txt_apply_wait.front().day << " " << this->txt_apply_wait.front().time << " " <<
		this->txt_apply_wait.front().room << " " << 1 << endl;
	ofs.close();
	//�����ݴ�queue������ɾ��
	this->txt_apply_wait.pop();
}