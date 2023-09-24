#include"Student.h"
Student::Student(string name, int number, string password)
{
	this->name = name;
	this->number = number;
	this->password = password;
	this->read_message();//读取所有申请
	this->initilize_map();//初始化map容器
	//查看是否预约过
	//临时创建一个变量，用于查找数据
	Apply temp(this->name, this->number, 0, 0, 'c', 0);
	vector<Apply>::iterator it = find(this->txt_apply_ok.begin(), this->txt_apply_ok.end(),temp);
	vector<Apply>::iterator its = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
	if (it != this->txt_apply_ok.end() || its != this->txt_apply_waiting.end())
	{
		this->is_apply = true;//预约过
	}
	else
		this->is_apply = false;//没有预约过
}
//申请预约,将学生的申请放入文件中
void Student::apply()
{
	if (this->is_apply)
	{
		cout << "您已经预约过一次，不能再次预约" << endl;
		return;
	}
	int day;//日期
	int time;//房间
	char room;//机房
	while (1)
	{
		cout << "请输入你要预约的日期:" << endl;
		cout << "1、星期一 2、星期二 3、星期三 4、星期四 5、星期五" << endl;
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
		cout << "请输入你要选择的时间" << endl << "1、上午 2、下午" << endl;
		cin >> time;
		if (time == 1 || time == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	while (1)
	{
		cout << "请输入你要选择的机房" << endl << "A机房 B机房 C机房" << endl;
		cin >> room;
		if (room == 'A'||room == 'B'||room == 'C')
			break;
		cout << "输入有误，请重新输入" << endl;
	}	
	//将信息输入到文件
	//存放顺序为：姓名、学号、日期、时间、机房号、预约状态(1、预约成功 2、未成功 3、还在批阅)
	ofstream ofs;
	ofs.open(ORDER_WAITING_FILE, ios::app);
	ofs << this->name << " " << this->number << " " << day << " " << time << " " <<
		room << " " << 3 << endl;
	ofs.close();
	//将信息存放入vector容器中
	this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, 3));
	this->is_apply = true;//预约过一次
	cout << "预约成功！" << endl;
}

//取消预约
void Student::cancle_order()
{
	if (!this->is_apply)
	{
		cout << "您还没有预约!" << endl;
		return;
	}
	cout << "您确定要取消吗？" << endl;
	cout << "1、取消 2、不取消" << endl;
	cin >> select;
	if (this->select == 1)
	{	//临时创建一个变量，用于查找数据
		Apply temp(this->name, this->number, 0, 0, 'c', 0);
		vector<Apply>::iterator it = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
		this->txt_apply_waiting.erase(it);//删除数据
		//写文件
		ofstream ofs;
		ofs.open(ORDER_WAITING_FILE, ios::trunc);
		for (vector<Apply>::iterator it = this->txt_apply_waiting.begin(); it !=this->txt_apply_waiting.end(); it++)
		{
			ofs << it->name << " " << it->number << " " << it->day << " " 
				<< it->time << " " << it->room << " " << it->state << endl;
		}
		ofs.close();
		cout << "删除成功!" << endl;
	}
	else
		return;
}

//查找所有人的预约(只允许看到预约成功的人,且只能看到姓名，日期，时间，机房号)
void Student::find_all_order()
{
	if (this->txt_apply_ok.empty())
	{
		cout << "预约人数为0" << endl;
	}
	//for_each(this->txt_apply_ok.begin(), this->txt_apply_ok.end(),myclass());
	for (vector<Apply>::iterator it = this->txt_apply_ok.begin(); it != this->txt_apply_ok.end(); it++)
	{
		cout << it->name << " ";
		map<int,string>::iterator its=this->day.find(it->day);
		cout << its->second << " ";
		its = this->time
			.find(it->time);
		cout << its->second << " " << it->room << "号机房" << endl;
	}
}

//查找自身申请的状态
void Student::find_mine()
{
	if (!this->is_apply)
	{
		cout << "你还没有预约" << endl;
	}
	else
	{
		Apply temp(this->name, this->number, 0, 0, 'c', 0);
		vector<Apply>::iterator it = find(this->txt_apply_ok.begin(), this->txt_apply_ok.end(), temp);
		if (it != this->txt_apply_ok.end())
		{
			cout << "您的预约通过！" << endl;
			return;
		}
		vector<Apply>::iterator its = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
		if (its != this->txt_apply_waiting.end())
		{
			cout << "您的预约还在审核中……" << endl;
			return;
		}
		else
		{
			cout << "您的预约没有被通过" << endl;
		}
	}
}

//读取所有申请(将三种状态下的预约放入三种不同的容器中)
void Student::read_message()
{
	int time, day, number, state;//房间,日期，账号，预约状态
	char room;//机房
	string name;
	ifstream ifs;
	//预约通过
	ifs.open(ORDER_OK_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_ok.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//等待批阅
	ifs.open(ORDER_WAITING_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
	//不予与通过
	ifs.open(ORDER_REFUSE_FILE, ios::in);
	while (ifs >> name&&ifs >> number&&ifs >> day&&ifs >> time&&ifs >> room&&ifs >> state)
	{
		this->txt_apply_refuse.push_back(Apply(name, number, day, time, room, state));
	}
	ifs.close();
}

//操作菜单
void Student::operator_menu()
{
	while (1)
	{
		cout << "请选择一项操作" << endl;
		cout << "***************************" << endl;
		cout << "***1、申请预约*************" << endl;
		cout << "***2、查找自我的预约状态***" << endl;
		cout << "***3、查看所有人的预约*****" << endl;
		cout << "***4、取消预约*************" << endl;
		cout << "***5、注销登录*************" << endl;
		cout << "***************************" << endl;
		cin >> this->select;
		switch (this->select)
		{
		case 1://申请预约
			this->apply(); break;
		case 2://查找自身的预约状态
			this->find_mine(); break;
		case 3://查看所有人的预约
			this->find_all_order(); break;
		case 4://取消预约
			this->cancle_order(); break;
		case 5://注销登录
			return;
		default:
			cout << "输入错误" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}