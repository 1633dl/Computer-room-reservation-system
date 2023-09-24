#include"Manager.h"
Manager::Manager(int number, string password)
{
	this->number = number;
	this->password = password;
	//��ʼ��������Ϣ
	this->computer.insert(make_pair('A', 60));
	this->computer.insert(make_pair('B', 40));
	this->computer.insert(make_pair('C', 40));
	//��ʼ����ʦ��ѧ����vector����
	vector<Indentity*>student;
	vector<Indentity*>teacher;
	this->v_number.push_back(student);
	this->v_number.push_back(teacher);
	this->read_txt();//��ȡ����
}
//����˺�
void Manager::add_account()
{
	Indentity *person;//����ָ�룬��������˺�
	ofstream ofs;
	string file_name;//���ļ�������
	int number;
	string name, postword1, postword2;
	//ȷ����ӵĶ���
	while (1)
	{
		cout << "��Ҫ��ӵĶ���Ϊ" << "1��ѧ�� 2����ʦ" << endl;
		cin >> this->select;
		if (this->select == 1)
		{
			file_name = STUDENT_FILE;
			break;
		}
		else if (this->select == 2)
		{
			file_name = TEACHER_FILE;
			break;
		}
		cout << "�������" << endl;
	}

	//���ļ�������˺�����
	ofs.open(file_name, ios::out | ios::app);
	while (1)
	{
		cout << "����������" << endl;
		cin >> name;
		cout << "�������˺�" << endl;
		cin >> number;
		//�ж��˺��Ƿ����!!!!!!!!!!!!!!
		if (!this->number_is_true(number))
		{
			cout << "���˺��Ѵ��ڣ�����������" << endl;
			continue;
		}
		cout << "����������" << endl;
		cin >> postword1;
		system("cls");
		cout << "���ٴ�ȷ������";
		cin >> postword2;
		if (postword1 == postword2)
		{
			cout << "��ӳɹ���" << endl;
			//����Ϣ������ĵ���
			ofs << number << " " << name << " " << postword1 << endl;
			ofs.close();
			//�Ѷ�Ӧ�����ݼ���vector����
			if (this->select == 1)
			{
				person = new Student(name, number, postword1);
				this->v_number[0].push_back(person);
			}
			else
			{
				person = new Teacher(name, number, postword1);
				this->v_number[1].push_back(person);
			}
			break;
		}
		else
			cout << "��֮ǰ���벻һ�£�����������" << endl;
		system("cls");
	}

}
//�鿴�����˺�(�ö��ļ��ķ�ʽ�鿴)
//���ڴ�����ʦ��ѧ���������Ǹ����ָ�����ͣ����������޷����ʵ��������޷�ͨ��vector���ж�ȡ
void Manager::check_all_account()
{
	ifstream ifs;
	cout << "Ҫ�鿴�Ķ���Ϊ:" << endl << "1��ѧ��" << endl << "2����ʦ" << endl;
	cin>>this->select;
	char c;
	if (select == 1)
	{
		ifs.open(STUDENT_FILE, ios::in);
	}
	else if (select == 2)
	{
		ifs.open(TEACHER_FILE, ios::in);
	}
	ifs >> c;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		return;
	}
	int number;//�˺�
	string name, pastword;//����������
	while (ifs >> number&&ifs>>name&&ifs >> pastword)
	{
		cout << "�˺ţ�" << number << " ������" << name << " ���룺" << pastword << endl;
	}
	ifs.close();
}
//�鿴����
void Manager::check_computer()
{
	//���û�������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::out);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
	}
	char name;
	int number;
	while (ifs >> name&&ifs >> number)
	{
		cout << "����" << name << " ʣ����λ�� " << number << endl;
	}
	ifs.close();
}
//�������ԤԼ
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_OK_FILE, ios::trunc);
	ofs.open(ORDER_REFUSE_FILE, ios::trunc);
	ofs.open(ORDER_WAITING_FILE, ios::trunc);
	ofs.close();
	cout << "ԤԼ��ճɹ�!" << endl;
}
//�����˵�
void Manager::operator_menu()
{
	system("cls");
	while (1)
	{
		cout << "��ӭ����Աʹ�û���ԤԼϵͳ" << endl;
		cout << "��ѡ��һ�µĲ���" << endl;
		cout << "***********************" << endl;
		cout << "*****1������˺�*******" << endl;
		cout << "*****2���鿴�˺�*******" << endl;
		cout << "*****3���鿴����*******" << endl;
		cout << "*****4�����ԤԼ*******" << endl;
		cout << "*****5��ע����¼*******" << endl;
		cout << "***********************" << endl;
		cin >> this->select;
		switch (select)
		{
		case 1:
			this->add_account(); break;
		case 2:
			this->check_all_account(); break;
		case 3:
			this->check_computer(); break;
		case 4:
			this->cleanFile(); break;
		case 5:
			return;
		default:
			cout << "�������" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
//��ȡ����(��ʵ��)
void Manager::read_message()
{
}

Manager::~Manager()
{
	for (int i = 0; i < 2; i++)
	{
		int temp = this->v_number[i].size();
		for (int j = 0; j < temp; j++)
		{
			delete this->v_number[i].at(j);
			cout << "�������ͷ�" << endl;
		}
	}
}
//�ж��˺��Ƿ����
bool Manager::number_is_true(int m_number)
{
	if (this->v_number[this->select - 1].empty())
	{
		//�����ǰ��������Ϊ�գ�ֱ������
		return true;
	}
	for (vector<Indentity*>::iterator it = this->v_number[this->select - 1].begin(); it != this->v_number[this->select-1].end(); it++)
	{
		if (m_number == (*it)->number)
		{
			return false;
		}
	}
	
	return true;
}
//��ȡ����
void Manager::read_txt()
{
	ifstream ifs;
	int number;
	string name, postword;
	Indentity* person;
	//��ȡѧ������
	ifs.open(STUDENT_FILE, ios::in);
	while (ifs >> number&&ifs >> name&&ifs >> postword)
	{
		person = new Student(name,number,postword);
		this->v_number[0].push_back(person);
	}
	ifs.close();
	//��ȡ��ʦ����
	ifs.open(TEACHER_FILE, ios::in);
	while (ifs >> number&&ifs >> name&&ifs >> postword)
	{
		person = new Teacher(name, number, postword);
		this->v_number[1].push_back(person);
	}
	ifs.close();
}