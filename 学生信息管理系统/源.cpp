#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

class Student {
public:
	string id;
	string name;
	string sex;
	int age;
	string province;
	string major;
	Student(string _id, string _name, string _sex, int _age, string _province, string _major) {
		this->id = _id;
		this->name = _name;
		this->sex = _sex;
		this->age = _age;
		this->province = _province;
		this->major = _major;
	}
	void showInfo() {
		cout << id << "    " << name << "    " << sex << "    " << age << "    " << province << "    " << major << endl;
	}
};

class StudentManager {
public:
	bool DataNotExist;
	int m_count;
	Student** StuArray;//员工数组指针

	int GetCount() {
		ifstream ifs;
		ifs.open("stu1.txt", ios::in);

		int num = 0;

		string id;
		string name;
		string sex;
		int age;
		string province;
		string major;

		while (ifs >> id && ifs >> name && ifs >> sex && ifs >> age && ifs >> province && ifs >> major) {
			num++;
		}
		return num;
	}

	StudentManager() {
		ifstream ifs;
		ifs.open("stu1.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "文件不存在" << endl;
			this->m_count = 0;
			this->StuArray = NULL;
			this->DataNotExist = true;
			ifs.close();
			return;
		}
		char ch;
		ifs >> ch;
		if(ifs.eof()){
			cout << "文件为空" << endl;
			this->m_count = 0;
			this->StuArray = NULL;
			ifs.close();
			return;
		}
		int num = this->GetCount();
		this->m_count = num;
		this->StuArray = new Student * [this->m_count];
		this->InitStu();
	}

	void InitStu() {
		ifstream ifs;
		ifs.open("stu1.txt", ios::in);
		int i = 0;
		string id;
		string name;
		string sex;
		int age;
		string province;
		string major;
		while (ifs >> id && ifs >> name && ifs >> sex && ifs >> age && ifs >> province && ifs >> major) {
			Student* student = new Student(id, name, sex, age, province, major);
			this->StuArray[i] = student;
			i++;
		}
		ifs.close();
	}

	void ShowMenu() {
		cout << "*****************************************************************" << endl;
		cout << "**********                                             **********" << endl;
		cout << "**********               学生信息管理系统              **********" << endl;
		cout << "**********                                             **********" << endl;
		cout << "*****************************************************************" << endl;
		cout << "              请选择功能键0-5" << endl << endl;
		cout << "              0:退出" << endl;
		cout << "              1:浏览学生信息" << endl;
		cout << "              2:插入学生信息" << endl;
		cout << "              3:删除学生记录" << endl;
		cout << "              4:查询学生记录" << endl;
		cout << "              5:修改学生记录" << endl;  //显示页面
	}

	void ExitSystem() {
		cout << "欢迎下次使用" << endl;
		system("pause");
		exit(0);
	}

	void CinError() {
		cout << "请输入正确的选项" << endl;
		system("pause");
		system("cls");
	}

	void save() {
		ofstream ofs;
		ofs.open("stu1.txt", ios::out);
		for (int i = 0; i < this->m_count; i++) {
			ofs << this->StuArray[i]->id << "    " << this->StuArray[i]->name << "    " << this->StuArray[i]->sex << "    " << this->StuArray[i]->age
				<< "    " << this->StuArray[i]->province << "    " << this->StuArray[i]->major << endl;
		}
		ofs.close();
	}

	void AddStudent(){
		cout << "请输入增加学生的数量" << endl;
		int addCount;
		cin >> addCount;
		if (addCount > 0) {
			int newCount = this->m_count + addCount;
			Student** newStuArray = new Student * [newCount];
			if (this->StuArray != NULL) {
				for (int i = 0; i < m_count; i++) {
					newStuArray[i] = this->StuArray[i];
				}
			}
			for (int i = 1; i <= addCount; i++) {
				system("pause");
				system("cls");
				string id;
				string name;
				string sex;
				int age;
				string province;
				string major;
				cout << "正在添加第" << i << "个学生，学号" << endl;
				while (true) {
					int ret = 1;
					cin >> id;
					string str = "0000";
					if (id.length() == 12) {
						for (int i = 0; i < id.length(); i++) {
							if (id[i] < 48 || id[i] > 57) {
								ret = 0;
							}
						}
						for (int i = 0; i < this->m_count; i++)
						{
							if (id == StuArray[i]->id) {
								ret = -1;
							}
						}

						if (ret == 1) {
							for (int i = 0; i < 4; i++) {
								str[i] = id[i];
							}
							int year = atoi(str.c_str());
							if (year > 1970 && year < 2022) {
								break;
							}
							else{
								cout << "请输入正确的年份，请重新输入" << endl;
							}
						}
						else if (ret == 0) {
							cout << "请输入12位数字学号，请重新输入" << endl;
						}
						else if (ret == -1) {
							cout << "学号不唯一，请重新输入" << endl;
						}

					}

					else {
						cout << "请输入12位学号，请重新输入" << endl;
					}
				}
				cout << "正在添加第" << i << "个学生，姓名" << endl;
				cin >> name;
				cout << "正在添加第" << i << "个学生，性别" << endl;
				while (true) {
					cin >> sex;
					if (sex == "男" || sex == "女") {
						break;
					}
					else {
						cout << "请输入正确的性别" << endl;
					}
				}
				cout << "正在添加第" << i << "个学生，年龄" << endl;
				while (true) {
					cin >> age;
					if (0 <= age && age <= 120) {
						break;
					}
					else {
						cout << "请重新输入" << endl;
					}
				}
				cout << "正在添加第" << i << "个学生，籍贯" << endl;
				cin >> province;
				cout << "正在添加第" << i << "个学生，专业" << endl;
				cin >> major;
				Student* student = NULL;
				student = new Student(id, name, sex, age, province, major);
				this->DataNotExist = false;
				newStuArray[this->m_count + i - 1] = student;
			}
			cout << "成功添加" << addCount << "个学生" << endl;
			this->StuArray = newStuArray;
			this->m_count = newCount;
			this->save();
			system("pause");
			system("cls");
		}
			else {
				cout << "输入有误" << endl;
				system("pause");
				system("cls");
			}
	}

	int StuIsExist(string id) {
		int tmp = -1;
		for (int i = 0; i < this->m_count; i++) {
			if (this->StuArray[i]->id == id) {
				tmp = i;
				break;
			}
		}
		return tmp;
	}

	void DelStudent() {
		if (this->DataNotExist) {
			cout<< "文件不存在或无数据" << endl;
		}
		else {
			cout << "请输入学生的学号" << endl;
			string id;
			cin >> id;
			int tmp = this->StuIsExist(id);
			if (tmp != -1) {
				for (int i = tmp; i < this->m_count; i++) {
					this->StuArray[i] = this->StuArray[i + 1];
					this->m_count--;
					this->save();
					cout << "删除成功" << endl;
				}
			}
			else {
				cout << "学生不存在" << endl;
			}
			system("pause");
			system("cls");
		}
	}

	void ShowStu() {
		if (this->DataNotExist) {
			cout << "文件不存在或无数据" << endl;
		}
		else {
			for (int i = 0; i < m_count; i++) {
				this->StuArray[i]->showInfo();
			}
			system("pause");
			system("cls");
		}
	}

	void ModStu() {
		if (this->DataNotExist) {
			cout << "文件不存在或无数据" << endl;
		}
		else {
			string id;
			cout << "请输入所修改的学生学号" << endl;
			cin >> id;
			int tmp = StuIsExist(id);
			if (tmp != -1) {
				this->StuArray[tmp]->showInfo();
				int select = 1;
				string data;
				int age;
				cout << "请输入所要修改的信息" << endl;
				cout << "1.姓名" << endl;
				cout << "2.性别" << endl;
				cout << "3.年龄" << endl;
				cout << "4.籍贯" << endl;
				cout << "5.专业" << endl;
				cout << "若完成请输入0退出修改" << endl << endl;
				while (select) {
					cin >> select;
					switch (select)
					{
					case 1:
						cout << "请输入新的姓名" << endl;
						cin >> data;
						this->StuArray[tmp]->name = data;
						cout << "0.退出修改" << endl;
						break;
					case 2:
						cout << "请输入新的性别" << endl;
						while (true) {
							cin >> data;
							if (data == "男" || data == "女") {
								break;
							}
							else {
								cout << "请输入正确的性别" << endl;
							}
						}
						this->StuArray[tmp]->sex = data;
						cout << "0.退出修改" << endl;
						break;
					case 3:
						cout << "请输入新的年龄" << endl;
						while (true) {
							cin >> age;
							if (0 <= age && age <= 120) {
								break;
							}
							else {
								cout << "请重新输入" << endl;
							}
						}
						this->StuArray[tmp]->age = age;
						cout << "0.退出修改" << endl;
						break;
					case 4:
						cout << "请输入新的籍贯" << endl;
						cin >> data;
						this->StuArray[tmp]->province = data;
						cout << "0.退出修改" << endl;
						break;
					case 5:
						cout << "请输入新的专业" << endl;
						cin >> data;
						this->StuArray[tmp]->major = data;
						cout << "0.退出修改" << endl;
						break;
					case 0:
						this->save();
						system("pause");
						system("cls");
					default:
						cout << "请选择正确的选项" << endl;
						break;
				}
			}
		}
			else {
				cout << "查无此人" << endl;
			}
		}
	}

	void FindStu() {
		if (this->DataNotExist) {
			cout << "文件不存在或无数据" << endl;
		}
		else {
			int select = 1;
			while (select) {
				cout << "请选择查询的方式" << endl;
				cout << "1.姓名" << endl;
				cout << "2.学号" << endl;
				cout << "3.性别" << endl;
				cout << "4.籍贯" << endl;
				cout << "5.专业" << endl;
				cout << "6.年龄" << endl;
				cout << "7.多重信息查询" << endl;
				cout << "8.姓名模糊查询" << endl;
				cout << "9.统计某条件的人数" << endl;
				cout << "0.退出" << endl;
				cin>> select;
				switch (select)
				{
				case 0:
					system("pause");
					system("cls");
					break;
				case 1: {
					int ret = 1;
					string name;
					cout << "请输入姓名" << endl;
					cin >> name;
					for (int i = 0; i < m_count; i++) {
						if (name == StuArray[i]->name) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					int ret = 1;
					string id;
					cout << "请输入学号" << endl;
					cin >> id;
					for (int i = 0; i < m_count; i++) {
						if (id == StuArray[i]->id) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break; 
				}
				case 3: {
					int ret = 1;
					string sex;
					cout << "请输入性别" << endl;
					cin >> sex;
					for (int i = 0; i < m_count; i++) {
						if (sex == StuArray[i]->sex) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 4: {
					int ret = 1;
					string province;
					cout << "请输入籍贯" << endl;
					cin >> province;
					for (int i = 0; i < m_count; i++) {
						if (province == StuArray[i]->province) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 5: {
					int ret = 1;
					string major;
					cout << "请输入专业" << endl;
					cin >> major;
					for (int i = 0; i < m_count; i++) {
						if (major == StuArray[i]->major) {
							this->StuArray[i]->showInfo();
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 6: {
					int ret = 1;
					int age;
					cout << "请输入年龄" << endl;
					cin >> age;
					for (int i = 0; i < m_count; i++) {
						if (age == StuArray[i]->age) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无此人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 7: {
					int ret = 1;
					int age;
					string province;
					string sex;
					cout << "请输入查询的年龄" << endl;
					cin >> age;
					cout << "请输入籍贯" << endl;
					cin >> province;
					cout << "请输入性别" << endl;
					cin >> sex;
					for (int i = 0; i < m_count; i++) {
						if (age == StuArray[i]->age && sex == StuArray[i]->sex && province == StuArray[i]->province) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "查无符合此条件的人" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 8: {
					string str;
					int ret = 1;
					cout << "请输入查询的模糊字" << endl;
					cin >> str;
					if (str.length() != 2) {
						cout << "请输入一个字" << endl;
					}
					else {
						for (int i = 0; i < m_count; i++) {
							for (int j = 0; j < StuArray[i]->name.length() / 2; j++) {
								if (str[0] == StuArray[i]->name[2 * j] && str[1] == StuArray[i]->name[2 * j + 1]) {
									this->StuArray[i]->showInfo();
									ret = 0;
								}
							}
						}
					}
					if (ret) {
						cout << "没有找到相关信息的学生" << endl;
					}
					str = "";
					system("pause");
					system("cls");
					break;
				}
				case 9: {
					int age;
					string province;
					string major;
					string temp;
					int num = 0;
					cout << "请选择查询的条件" << endl;
					cout << "1.性别" << endl;
					cout << "2.籍贯" << endl;
					cout << "3.专业" << endl;
					cout << "4.年龄" << endl;
					cin >> select;
					cout << "请输入查询的条件" << endl;
					switch (select)
					{
					case 1:
						cin >> temp;
						for (int i = 0; i < m_count; i++) {
							if (temp == StuArray[i]->sex) {
								num++;
							}
						}
						cout << temp << "性有" << num << "人" <<endl;
						system("pause");
						system("cls");
						break;
					case 2:
						cin >> temp;
						for (int i = 0; i < m_count; i++) {
							if (temp == StuArray[i]->province) {
								num++;
							}
						}
						cout << temp << "的学生有" << num << "人" << endl;
						system("pause");
						system("cls");
						break;
					case 3:
						cin >> temp;
						for (int i = 0; i < m_count; i++) {
							if (temp == StuArray[i]->major) {
								num++;
							}
						}
						cout << temp << "的学生有" << num << "人" << endl;
						system("pause");
						system("cls");
						break;
					case 4: {
						cin >> age;
						for (int i = 0; i < m_count; i++) {
							if (age == StuArray[i]->age) {
								num++;
							}
						}
						cout << age << "岁的学生有" << num << "人" << endl;
						system("pause");
						system("cls");
						break;
					}
					default:
						cout << "请选择正确的选项" << endl;
						break;
					}
				}
				default:
					cout << "请选择正确的选项" << endl;
					break;
				}
			}
		}
	}

	~StudentManager() {
		delete[] this->StuArray;
		this->StuArray = NULL;
	}
};

int main() {
	StudentManager sm;
	int select;
	while (true) {
		sm.ShowMenu();
		cin >> select;
		switch (select)
		{
		case 1: 
			sm.ShowStu();
			break;//浏览
		case 2:
			sm.AddStudent();
			break;//插入
		case 3:
			sm.DelStudent();
			break;//删除
		case 4:
			sm.FindStu();
			break;//查询
		case 5:
			sm.ModStu();
			break;//修改
		case 0: 
			sm.ExitSystem();
			break;//退出
		default:
			sm.CinError();
			break;
		}
	}
}