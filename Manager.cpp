#include"Manager.h"
Manager::Manager(int number, string password)
{
	this->number = number;
	this->password = password;
	//初始化机房信息
	this->computer.insert(make_pair('A', 60));
	this->computer.insert(make_pair('B', 40));
	this->computer.insert(make_pair('C', 40));
	//初始化老师和学生的vector容器
	vector<Indentity*>student;
	vector<Indentity*>teacher;
	this->v_number.push_back(student);
	this->v_number.push_back(teacher);
	this->read_txt();//读取数据
}
//添加账号
void Manager::add_account()
{
	Indentity *person;//父类指针，用于添加账号
	ofstream ofs;
	string file_name;//打开文件的名称
	int number;
	string name, postword1, postword2;
	//确认添加的对象
	while (1)
	{
		cout << "你要添加的对象为" << "1、学生 2、老师" << endl;
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
		cout << "输入错误！" << endl;
	}

	//往文件中添加账号密码
	ofs.open(file_name, ios::out | ios::app);
	while (1)
	{
		cout << "请输入姓名" << endl;
		cin >> name;
		cout << "请输入账号" << endl;
		cin >> number;
		//判断账号是否存在!!!!!!!!!!!!!!
		if (!this->number_is_true(number))
		{
			cout << "此账号已存在，请重新输入" << endl;
			continue;
		}
		cout << "请输入密码" << endl;
		cin >> postword1;
		system("cls");
		cout << "请再次确认密码";
		cin >> postword2;
		if (postword1 == postword2)
		{
			cout << "添加成功！" << endl;
			//将信息添加入文档中
			ofs << number << " " << name << " " << postword1 << endl;
			ofs.close();
			//把对应的数据加入vector容器
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
			cout << "与之前密码不一致，请重新输入" << endl;
		system("cls");
	}

}
//查看所有账号(用读文件的方式查看)
//由于储存老师和学生的容器是父类的指针类型，所以姓名无法访问到，所以无法通过vector进行读取
void Manager::check_all_account()
{
	ifstream ifs;
	cout << "要查看的对象为:" << endl << "1、学生" << endl << "2、老师" << endl;
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
		cout << "文件为空" << endl;
		return;
	}
	int number;//账号
	string name, pastword;//姓名，密码
	while (ifs >> number&&ifs>>name&&ifs >> pastword)
	{
		cout << "账号：" << number << " 姓名：" << name << " 密码：" << pastword << endl;
	}
	ifs.close();
}
//查看机房
void Manager::check_computer()
{
	//设置机房的信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::out);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
	}
	char name;
	int number;
	while (ifs >> name&&ifs >> number)
	{
		cout << "机房" << name << " 剩余座位数 " << number << endl;
	}
	ifs.close();
}
//清除所有预约
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_OK_FILE, ios::trunc);
	ofs.open(ORDER_REFUSE_FILE, ios::trunc);
	ofs.open(ORDER_WAITING_FILE, ios::trunc);
	ofs.close();
	cout << "预约清空成功!" << endl;
}
//操作菜单
void Manager::operator_menu()
{
	system("cls");
	while (1)
	{
		cout << "欢迎管理员使用机房预约系统" << endl;
		cout << "请选择一下的操作" << endl;
		cout << "***********************" << endl;
		cout << "*****1、添加账号*******" << endl;
		cout << "*****2、查看账号*******" << endl;
		cout << "*****3、查看机房*******" << endl;
		cout << "*****4、清空预约*******" << endl;
		cout << "*****5、注销登录*******" << endl;
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
			cout << "输入错误" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
//读取申请(空实现)
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
			cout << "数据已释放" << endl;
		}
	}
}
//判断账号是否存在
bool Manager::number_is_true(int m_number)
{
	if (this->v_number[this->select - 1].empty())
	{
		//如果当前的容器中为空，直接跳过
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
//读取数据
void Manager::read_txt()
{
	ifstream ifs;
	int number;
	string name, postword;
	Indentity* person;
	//读取学生数据
	ifs.open(STUDENT_FILE, ios::in);
	while (ifs >> number&&ifs >> name&&ifs >> postword)
	{
		person = new Student(name,number,postword);
		this->v_number[0].push_back(person);
	}
	ifs.close();
	//读取老师数据
	ifs.open(TEACHER_FILE, ios::in);
	while (ifs >> number&&ifs >> name&&ifs >> postword)
	{
		person = new Teacher(name, number, postword);
		this->v_number[1].push_back(person);
	}
	ifs.close();
}