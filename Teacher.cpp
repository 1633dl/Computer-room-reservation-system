#include"Teacher.h"
Teacher::Teacher(string name, int number, string password)
{
	this->name = name;
	this->password = password;
	this->number = number;
	this->read_message();//读取信息(将信息分别存放入3个容器中
	this->initilize_map();//初始化map容器
}
//读取预约信息
void Teacher::read_message()
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
		//这里的vector容器用于老师查看所有有人的预约，queue容器用于审核预约(先进先出)
		this->txt_apply_waiting.push_back(Apply(name, number, day, time, room, state));
		this->txt_apply_wait.push(Apply(name, number, day, time, room, state));
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
//审核预约
void Teacher::check_order()
{
	if (this->txt_apply_wait.empty())
	{
		cout << "申请为空" << endl;
		return;
	}
	else
	{
		while (!this->txt_apply_wait.empty())
		{
			//显示申请信息
			cout << this->txt_apply_wait.front().name << " " << this->txt_apply_wait.front().number << " ";
			map<int, string>::iterator its = this->day.find(this->txt_apply_wait.front().day);
			cout << its->second << " ";
			its = this->time.find(this->txt_apply_wait.front().time);
			cout << its->second << " " << this->txt_apply_wait.front().room << "号机房" << endl;
			//开始操作
	
			int choice;
			cout << "是否同意" << endl << "1、同意" << " 2、不同意" << endl;
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
				cout << "输入错误" << endl;
				goto A;
			}*/
		}
	}
	ofstream ofs;
	ofs.open(ORDER_WAITING_FILE, ios::out);
	ofs.clear();//将等待审核文件中的数据清空
	ofs.close();
}

//操作菜单
void Teacher::operator_menu()
{
	while (1)
	{
		cout << "请选择一项操作" << endl;
		cout << "***************************" << endl;
		cout << "***1、查看所有预约*********" << endl;
		cout << "***2、审核预约*************" << endl;
		cout << "***3、注销登录*************" << endl;
		cout << "***************************" << endl;
		cin >> this->select;
		switch (this->select)
		{
		case 1://查看所有预约
			this->seek_all_order(); break;
		case 2://审核预约
			this->check_order(); break;
		case 3:
			return;
		default:
			cout << "输入错误" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//查看所有预约,但是不能做任何操作
void Teacher::seek_all_order()
{
A:
	//选择查看的预约
	cout << "请选择你要查看的预约" << endl;
	cout << "1、已经同意的预约" << endl;
	cout << "2、还未审核的预约" << endl;
	cout << "3、已经被拒绝的预约" << endl;
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
		cout << "输入错误" << endl;
		system("cls");
		system("pause");
		goto A;
		break;
	}
}

//展示每种预约
void Teacher::show_apply(const vector<Apply>&v, int select)
{
	if (v.empty())
	{
		cout << "预约为空" << endl;
	}
	for (vector<Apply>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->name << " "<<it->number<<" ";
		map<int, string>::iterator its = this->day.find(it->day);
		cout << its->second << " ";
		its = this->time.find(it->time);
		cout << its->second << " " << it->room << "号机房" << endl;
	}
}

//将预约移除
void Teacher::delete_apply(int select)
{
	//把数据从vector容器中删除
	//随便创建一个变量方便查询
	Apply temp(this->txt_apply_wait.front().name, this->txt_apply_wait.front().number, 0, 0, 'c', 0);
	vector<Apply>::iterator it = find(this->txt_apply_waiting.begin(), this->txt_apply_waiting.end(), temp);
	this->txt_apply_waiting.erase(it);

	//创建一个变量，方便放入其他vector容器中
	Apply apply(this->txt_apply_wait.front().name, this->txt_apply_wait.front().number,
		this->txt_apply_wait.front().day, this->txt_apply_wait.front().time, this->txt_apply_wait.front().room, 1);
	
	ofstream ofs;
	if (select == 1)//将等待区的数据移到成功区
	{
		ofs.open(ORDER_OK_FILE, ios::out | ios::app);
		this->txt_apply_ok.push_back(apply);
	}
	else//将等待区的数据移到拒绝区
	{
		ofs.open(ORDER_REFUSE_FILE, ios::out | ios::app);
		this->txt_apply_refuse.push_back(apply);
	}
	//将数据放入文件中
	ofs << this->txt_apply_wait.front().name << " " << this->txt_apply_wait.front().number << " " <<
		this->txt_apply_wait.front().day << " " << this->txt_apply_wait.front().time << " " <<
		this->txt_apply_wait.front().room << " " << 1 << endl;
	ofs.close();
	//把数据从queue容器中删除
	this->txt_apply_wait.pop();
}