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
	Student** StuArray;//Ա������ָ��

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
			cout << "�ļ�������" << endl;
			this->m_count = 0;
			this->StuArray = NULL;
			this->DataNotExist = true;
			ifs.close();
			return;
		}
		char ch;
		ifs >> ch;
		if(ifs.eof()){
			cout << "�ļ�Ϊ��" << endl;
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
		cout << "**********               ѧ����Ϣ����ϵͳ              **********" << endl;
		cout << "**********                                             **********" << endl;
		cout << "*****************************************************************" << endl;
		cout << "              ��ѡ���ܼ�0-5" << endl << endl;
		cout << "              0:�˳�" << endl;
		cout << "              1:���ѧ����Ϣ" << endl;
		cout << "              2:����ѧ����Ϣ" << endl;
		cout << "              3:ɾ��ѧ����¼" << endl;
		cout << "              4:��ѯѧ����¼" << endl;
		cout << "              5:�޸�ѧ����¼" << endl;  //��ʾҳ��
	}

	void ExitSystem() {
		cout << "��ӭ�´�ʹ��" << endl;
		system("pause");
		exit(0);
	}

	void CinError() {
		cout << "��������ȷ��ѡ��" << endl;
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
		cout << "����������ѧ��������" << endl;
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
				cout << "������ӵ�" << i << "��ѧ����ѧ��" << endl;
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
								cout << "��������ȷ����ݣ�����������" << endl;
							}
						}
						else if (ret == 0) {
							cout << "������12λ����ѧ�ţ�����������" << endl;
						}
						else if (ret == -1) {
							cout << "ѧ�Ų�Ψһ������������" << endl;
						}

					}

					else {
						cout << "������12λѧ�ţ�����������" << endl;
					}
				}
				cout << "������ӵ�" << i << "��ѧ��������" << endl;
				cin >> name;
				cout << "������ӵ�" << i << "��ѧ�����Ա�" << endl;
				while (true) {
					cin >> sex;
					if (sex == "��" || sex == "Ů") {
						break;
					}
					else {
						cout << "��������ȷ���Ա�" << endl;
					}
				}
				cout << "������ӵ�" << i << "��ѧ��������" << endl;
				while (true) {
					cin >> age;
					if (0 <= age && age <= 120) {
						break;
					}
					else {
						cout << "����������" << endl;
					}
				}
				cout << "������ӵ�" << i << "��ѧ��������" << endl;
				cin >> province;
				cout << "������ӵ�" << i << "��ѧ����רҵ" << endl;
				cin >> major;
				Student* student = NULL;
				student = new Student(id, name, sex, age, province, major);
				this->DataNotExist = false;
				newStuArray[this->m_count + i - 1] = student;
			}
			cout << "�ɹ����" << addCount << "��ѧ��" << endl;
			this->StuArray = newStuArray;
			this->m_count = newCount;
			this->save();
			system("pause");
			system("cls");
		}
			else {
				cout << "��������" << endl;
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
			cout<< "�ļ������ڻ�������" << endl;
		}
		else {
			cout << "������ѧ����ѧ��" << endl;
			string id;
			cin >> id;
			int tmp = this->StuIsExist(id);
			if (tmp != -1) {
				for (int i = tmp; i < this->m_count; i++) {
					this->StuArray[i] = this->StuArray[i + 1];
					this->m_count--;
					this->save();
					cout << "ɾ���ɹ�" << endl;
				}
			}
			else {
				cout << "ѧ��������" << endl;
			}
			system("pause");
			system("cls");
		}
	}

	void ShowStu() {
		if (this->DataNotExist) {
			cout << "�ļ������ڻ�������" << endl;
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
			cout << "�ļ������ڻ�������" << endl;
		}
		else {
			string id;
			cout << "���������޸ĵ�ѧ��ѧ��" << endl;
			cin >> id;
			int tmp = StuIsExist(id);
			if (tmp != -1) {
				this->StuArray[tmp]->showInfo();
				int select = 1;
				string data;
				int age;
				cout << "��������Ҫ�޸ĵ���Ϣ" << endl;
				cout << "1.����" << endl;
				cout << "2.�Ա�" << endl;
				cout << "3.����" << endl;
				cout << "4.����" << endl;
				cout << "5.רҵ" << endl;
				cout << "�����������0�˳��޸�" << endl << endl;
				while (select) {
					cin >> select;
					switch (select)
					{
					case 1:
						cout << "�������µ�����" << endl;
						cin >> data;
						this->StuArray[tmp]->name = data;
						cout << "0.�˳��޸�" << endl;
						break;
					case 2:
						cout << "�������µ��Ա�" << endl;
						while (true) {
							cin >> data;
							if (data == "��" || data == "Ů") {
								break;
							}
							else {
								cout << "��������ȷ���Ա�" << endl;
							}
						}
						this->StuArray[tmp]->sex = data;
						cout << "0.�˳��޸�" << endl;
						break;
					case 3:
						cout << "�������µ�����" << endl;
						while (true) {
							cin >> age;
							if (0 <= age && age <= 120) {
								break;
							}
							else {
								cout << "����������" << endl;
							}
						}
						this->StuArray[tmp]->age = age;
						cout << "0.�˳��޸�" << endl;
						break;
					case 4:
						cout << "�������µļ���" << endl;
						cin >> data;
						this->StuArray[tmp]->province = data;
						cout << "0.�˳��޸�" << endl;
						break;
					case 5:
						cout << "�������µ�רҵ" << endl;
						cin >> data;
						this->StuArray[tmp]->major = data;
						cout << "0.�˳��޸�" << endl;
						break;
					case 0:
						this->save();
						system("pause");
						system("cls");
					default:
						cout << "��ѡ����ȷ��ѡ��" << endl;
						break;
				}
			}
		}
			else {
				cout << "���޴���" << endl;
			}
		}
	}

	void FindStu() {
		if (this->DataNotExist) {
			cout << "�ļ������ڻ�������" << endl;
		}
		else {
			int select = 1;
			while (select) {
				cout << "��ѡ���ѯ�ķ�ʽ" << endl;
				cout << "1.����" << endl;
				cout << "2.ѧ��" << endl;
				cout << "3.�Ա�" << endl;
				cout << "4.����" << endl;
				cout << "5.רҵ" << endl;
				cout << "6.����" << endl;
				cout << "7.������Ϣ��ѯ" << endl;
				cout << "8.����ģ����ѯ" << endl;
				cout << "9.ͳ��ĳ����������" << endl;
				cout << "0.�˳�" << endl;
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
					cout << "����������" << endl;
					cin >> name;
					for (int i = 0; i < m_count; i++) {
						if (name == StuArray[i]->name) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					int ret = 1;
					string id;
					cout << "������ѧ��" << endl;
					cin >> id;
					for (int i = 0; i < m_count; i++) {
						if (id == StuArray[i]->id) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
					}
					system("pause");
					system("cls");
					break; 
				}
				case 3: {
					int ret = 1;
					string sex;
					cout << "�������Ա�" << endl;
					cin >> sex;
					for (int i = 0; i < m_count; i++) {
						if (sex == StuArray[i]->sex) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 4: {
					int ret = 1;
					string province;
					cout << "�����뼮��" << endl;
					cin >> province;
					for (int i = 0; i < m_count; i++) {
						if (province == StuArray[i]->province) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 5: {
					int ret = 1;
					string major;
					cout << "������רҵ" << endl;
					cin >> major;
					for (int i = 0; i < m_count; i++) {
						if (major == StuArray[i]->major) {
							this->StuArray[i]->showInfo();
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 6: {
					int ret = 1;
					int age;
					cout << "����������" << endl;
					cin >> age;
					for (int i = 0; i < m_count; i++) {
						if (age == StuArray[i]->age) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޴���" << endl;
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
					cout << "�������ѯ������" << endl;
					cin >> age;
					cout << "�����뼮��" << endl;
					cin >> province;
					cout << "�������Ա�" << endl;
					cin >> sex;
					for (int i = 0; i < m_count; i++) {
						if (age == StuArray[i]->age && sex == StuArray[i]->sex && province == StuArray[i]->province) {
							this->StuArray[i]->showInfo();
							ret = 0;
						}
					}
					if (ret) {
						cout << "���޷��ϴ���������" << endl;
					}
					system("pause");
					system("cls");
					break;
				}
				case 8: {
					string str;
					int ret = 1;
					cout << "�������ѯ��ģ����" << endl;
					cin >> str;
					if (str.length() != 2) {
						cout << "������һ����" << endl;
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
						cout << "û���ҵ������Ϣ��ѧ��" << endl;
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
					cout << "��ѡ���ѯ������" << endl;
					cout << "1.�Ա�" << endl;
					cout << "2.����" << endl;
					cout << "3.רҵ" << endl;
					cout << "4.����" << endl;
					cin >> select;
					cout << "�������ѯ������" << endl;
					switch (select)
					{
					case 1:
						cin >> temp;
						for (int i = 0; i < m_count; i++) {
							if (temp == StuArray[i]->sex) {
								num++;
							}
						}
						cout << temp << "����" << num << "��" <<endl;
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
						cout << temp << "��ѧ����" << num << "��" << endl;
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
						cout << temp << "��ѧ����" << num << "��" << endl;
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
						cout << age << "���ѧ����" << num << "��" << endl;
						system("pause");
						system("cls");
						break;
					}
					default:
						cout << "��ѡ����ȷ��ѡ��" << endl;
						break;
					}
				}
				default:
					cout << "��ѡ����ȷ��ѡ��" << endl;
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
			break;//���
		case 2:
			sm.AddStudent();
			break;//����
		case 3:
			sm.DelStudent();
			break;//ɾ��
		case 4:
			sm.FindStu();
			break;//��ѯ
		case 5:
			sm.ModStu();
			break;//�޸�
		case 0: 
			sm.ExitSystem();
			break;//�˳�
		default:
			sm.CinError();
			break;
		}
	}
}