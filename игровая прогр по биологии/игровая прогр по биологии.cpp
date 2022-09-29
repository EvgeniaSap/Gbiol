// ������� ����� �� ��������.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "string.h"
#include <fstream>
#include <vector>
#include "conio.h"
#include <Windows.h>

using namespace std;

class �ntrlQuest {
public:
	�ntrlQuest() {};
	virtual void enter_ans(int i) = 0; //������ ����������� �������;
	~�ntrlQuest() {};
};

class Test : public �ntrlQuest {
protected:
	string quest; //����������� ������;
	string r_answer; //������ �����;
	int point; //�������� �������;
public:
	Test() {};
	Test(string q, string r_a, int p) : �ntrlQuest() {
		quest = q;
		r_answer = r_a;
		point = p;
	};
	string get_quest() { return quest; }; //����������� �� ������� ����� �������;
	string get_r_answer() { return r_answer; }; //����������� �� ������� ����� ������� ������;
	int get_point() { return point; }; //����������� �� ������� ����� �������� �������;
	void enter_ans(int i) { cout << "����� Test" << endl; }; //��������������� ����������� �������;
	~Test() { };
};

class Test1 :public Test {
protected:
	string answer; //�����, ������ �������������;
public:
	Test1() {};
	Test1(string q, string r_a, int p) : Test(q, r_a, p) {
	};
	string get_answer() { return answer; }; //����������� �� ������� ����� ������ ������������;
	void enter_ans(int i) {					//��������������� ����������� �������;
		cout << endl;
		cout << "������. " << endl << quest << endl;
		cout << "�����: " << endl;
		if (i == 0) {
			cin.get();
		}
		getline(cin, answer);
	};
	bool check() {
		if (r_answer == answer)
			return true;
		else
			return false;
	};
	~Test1() { };
};

class Test2 : public Test {
protected:
	string answer; //�����, ������ �������������;
	int maxh; //������������ ���������, �������� �������������;
public:
	Test2() {};
	Test2(string q, string r_a, int p) : Test(q, r_a, p) {
	};
	void set_maxh(int m) { maxh = m; }; //���������� �������� ���� ������������ ���������;
	string get_answer() { return answer; }; //����������� �� ������� ����� ������ ������������;
	int get_maxh() { return maxh; }; //����������� �� ������� ����� ������������ ���������;
	void enter_ans(int i) {					//��������������� ����������� �������;
		if (point <= maxh)
		{
			cout << endl;
			cout << "������. " << endl << quest << endl;
			cout << "�����: " << endl;
			if (i == 0)
				cin.get();
			getline(cin, answer);
		}
	};
	bool check() {
		if (r_answer == answer)
			return true;
		else
			return false;
	};
	~Test2() { };
};

int main_menu(); //�������� ����;
int control_key(int a, int b); //�������� ����� ����� ����;
void theor_mat(); //������ ��� �����;
int menu_passing(); //���� ������ ������� ����������� �����;
void proceed_test(vector<Test1> issues1, vector<Test2> issues2); //���������� � �����;
template <class T> vector<T> enter_que(vector<T> &qq, int n); //���������� �������� �� ����� ��� ������ � ��������;
template <class T> void passing(vector<T> &qq); //����������� ����� � ��������� ������� ������������ ���� ��� ������ � ��������;
template <class T> void output(vector<T> qq); //����� ����������� ����� ��� ������ � ��������;
void case_all(vector<Test1> issues, int n); //����������� ����� ��� �������;
void case_choi�e(vector<Test2> issues, int n); //����������� ����� � ��������� ����������� ���������;
void case_sort(vector<Test1> issues, int n); //����������� ����� � ���������������� ���������, ��������� ������;
void inform(); //����� �������� �� ������;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	vector <Test1> issues1;
	vector <Test2> issues2;

	while (true)
	{
		switch (main_menu())
		{
		case 1:

			theor_mat(); //������ ��� �����;
			break;

		case 2:

			proceed_test(issues1, issues2); //���������� � �����;
			break;

		case 3:

			inform(); //����� �������� �� ������;
			break;

		case 4:

			cout << "����� �� ���������...\n" << endl;
			cout << endl;
			exit(EXIT_SUCCESS);
			break;
		}
		cout << "��� ����������� ������� ����� �������." << endl;
		_getch();
		system("cls");
	}

    return 0;
}

int main_menu() //�������� ����;
{
	cout << "\t ~ ���� ~ \t" << endl;
	cout << endl;
	cout << "1. ������������ � ������� �� �������� ��� ���������� � �����" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. �������� �� ������" << endl;
	cout << "4. �����" << endl;
	
	int variant = control_key(1, 4);
	system("cls");
	return variant;
}

int control_key(int a, int b) //�������� ����� ��������, ������� ������ ������� � �������� �� a �� b;
{
	int variant = 0;
	string buff;

	while (variant > b || variant < a)
	{
		cin >> buff;
		if (buff.length() != 1)
		{
			cout << "������ ���� ������� ������ �������. ���������� ��� ���:" << endl;
			continue;
		}
		else if (isdigit(buff[0]))
		{
			variant = stoi(buff);
			if (variant > b || variant < a)
			{
				cout << "���������� ��� ���:" << endl;
				continue;
			}
		}
		else
		{
			cout << "������ ���� ������� ������ �������. ���������� ��� ���:" << endl;
			continue;
		}
	}

	return variant;
}

void theor_mat() //������ ��� �����;
{
	string temp1, temp2;
	ifstream fin("������.txt");

	if (!fin.is_open() || fin.eof())
		cout << "�������� � ������.";
	else
	{
		while (!fin.eof())
		{
				fin >> temp1;
				cout << temp1 << " ";
				if (temp1 == "." || temp1 == ";" || temp1==":")
				{
					cout << endl;
				}
			
		}
	}
	fin.close();
}

int menu_passing() //���� ������ ������� ����������� �����;
{
	cout << "\t ~ ������� ����������� ����� ~ \t" << endl;
	cout << endl;
	cout << "1. ������ ���� ���������" << endl;
	cout << "2. ������ ���� � ����������� ���������� ��������" << endl;
	cout << "3. ������������� ������� �� ���������" << endl;
	cout << "4. ��������� � ������� ����" << endl;
	
	int variant = control_key(1, 4);

	system("cls");
	return variant;
}

void proceed_test(vector<Test1> issues1, vector<Test2> issues2) //���������� � �����;
{
	int n = 10;
	while (true)
	{
		switch (menu_passing())
		{
		case 1:

			case_all(issues1, n); //����������� ����� ��� �������, ��������� �������;
			break;


		case 2:

			case_choi�e(issues2, n); //����������� ����� � ��������� ����������� ���������, ��������� ����;
			break;

		case 3:

			case_sort(issues1, n); //����������� ����� � ���������������� ���������, ��������� ������;
			break;

		case 4:
			
			main();
			break;
		}
		cout << "��� ����������� ������� ����� �������." << endl;
		_getch();
		system("cls");
	}
}

template <class T>
vector<T> enter_que(vector<T> &qq, int n) //���������� �������� �� ����� ��� ������ � ��������;
{
	string temp1, temp2;
	int p; 
	int i = 0;
	ifstream fin("�������.txt");

	if (!fin.is_open() || fin.eof())
		cout << "�������� � ������.";
	else
	{
		for (int i = 0; i < n; i++)
		{
			do {						//���������� �������;
				fin >> temp1;
				temp2 += temp1 + " ";
			} while (temp1 != ":");

			fin >> temp1; //���������� ������� ������;
			fin >> p; //���������� �������� �������;

			T exep(temp2, temp1, p);
			qq.push_back(exep);

			temp2 = "";
		}
	}
	fin.close();

	return qq;
}

template <class T>
void passing(vector<T> &qq) //����������� ����� � ��������� ������� ������������ ���� ��� ������ � ��������;
{
	cout << "�������� ����." << endl;
	cout << "(����� ���������� � ��������� �����, ������������ ����� � ���, ������� � �������)" << endl;
	ofstream fout("������.txt", ios_base::out);

	if (!fout.is_open())
		cout << "�������� � ������.";
	else
	{
		for (int i = 0; i != qq.size(); i++)
		{
			qq.at(i).enter_ans(i); //����������� �������� ���� "�����, ������ �������������";

			if (qq.at(i).get_answer() == "")
			{
				qq.erase(qq.begin() + i);
				i--;
			}
			else
			{
				fout << qq.at(i).get_quest() << endl;
				fout << qq.at(i).get_answer() << endl;
				fout << endl;
			}
		}
	}
	fout.close();
	system("cls");

	output(qq);
}

template <class T>
void output(vector<T> qq) //����� ����������� ����� ��� ������ � ��������;
{
	int k = 0; //���������� ������ �������;
	int ball = 0; //����� ��� �� ����;

	cout << "\t ~ ����� ����� ~ " << endl;

	for (int i = 0; i != qq.size(); i++)
	{
		cout << endl;
		cout << "_____________________________________________" << endl;
		cout << i + 1 << "-� ������: " << qq.at(i).get_quest() << endl;
		cout << "�������� �������: " << qq.at(i).get_point() << endl;
		cout << "������ �����: " << qq.at(i).get_r_answer() << endl;
		cout << "��� �����: " << qq.at(i).get_answer() << endl;

		if (qq.at(i).check())
		{
			cout << "-�����-" << endl;
			k++;
			ball += qq.at(i).get_point();
		}
		else
			cout << "-�������-" << endl;
	}
		

	cout << endl;
	cout << "���������� ������ �������: " << k << endl;
	cout << "����� ����: " << ball << endl;
}

void case_all(vector<Test1> issues, int n) //����������� ����� ��� �������;
{
	enter_que(issues, n);
	passing(issues);
}

void case_choi�e(vector<Test2> issues, int n) //����������� ����� � ��������� ����������� ���������;
{
	cout << "������� ������������ ��������� (�� 1 �� 5): " << endl;
	int k = control_key(1, 5);
	
	enter_que(issues, n);

	for (int i = 0; i != issues.size(); i++)
	{
		issues[i].set_maxh(k);
	}

	passing(issues);
}

void case_sort(vector<Test1> issues, int n) //����������� ����� � ���������������� ���������, ��������� ������;
{
	enter_que(issues, n);

	Test1 temp;

	for (int i = 1; i != issues.size(); i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (issues.at(j - 1).get_point() > issues.at(j).get_point())
			{
				temp = issues.at(j - 1);
				issues.at(j - 1) = issues.at(j);
				issues.at(j) = temp;
			}
		}
	}

	passing(issues);
}

void inform() //����� �������� �� ������;
{
	cout << "\t �������� �� ������: \n" << endl;
	cout << "�������� ������� ���������" << endl;
	cout << "���� 2, ������ 3-�3�-205�-16." << endl;
	cout << "�������� ������ �� ���������� ���������-��������������� ����������������:" << endl;
	cout << "�������� ��������� ��� ���������� �� ��������;" << endl;
	cout << "����������� �� ����� �++ " << endl;
	cout << endl;
}