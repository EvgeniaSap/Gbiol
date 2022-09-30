// игровая прогр по биологии.cpp: определяет точку входа для консольного приложения.
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

class СntrlQuest {
public:
	СntrlQuest() {};
	virtual void enter_ans(int i) = 0; //Чистая виртуальная функция;
	~СntrlQuest() {};
};

class Test : public СntrlQuest {
protected:
	string quest; //Контрольный вопрос;
	string r_answer; //Верный ответ;
	int point; //Ценность вопроса;
public:
	Test() {};
	Test(string q, string r_a, int p) : СntrlQuest() {
		quest = q;
		r_answer = r_a;
		point = p;
	};
	string get_quest() { return quest; }; //Возвращение во внешнюю среду вопроса;
	string get_r_answer() { return r_answer; }; //Возвращение во внешнюю среду верного ответа;
	int get_point() { return point; }; //Возвращение во внешнюю среду ценности вопроса;
	void enter_ans(int i) { cout << "Класс Test" << endl; }; //Переопределение виртуальной функции;
	~Test() { };
};

class Test1 :public Test {
protected:
	string answer; //Ответ, данный пользователем;
public:
	Test1() {};
	Test1(string q, string r_a, int p) : Test(q, r_a, p) {
	};
	string get_answer() { return answer; }; //Возвращение во внешнюю среду ответа пользователя;
	void enter_ans(int i) {					//Переопределение виртуальной функции;
		cout << endl;
		cout << "ВОПРОС. " << endl << quest << endl;
		cout << "Ответ: " << endl;
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
	string answer; //Ответ, данный пользователем;
	int maxh; //Максимальная сложность, заданная пользователем;
public:
	Test2() {};
	Test2(string q, string r_a, int p) : Test(q, r_a, p) {
	};
	void set_maxh(int m) { maxh = m; }; //Заполнение значения поля максимальной сложности;
	string get_answer() { return answer; }; //Возвращение во внешнюю среду ответа пользователя;
	int get_maxh() { return maxh; }; //Возвращение во внешнюю среду максимальной сложности;
	void enter_ans(int i) {					//Переопределение виртуальной функции;
		if (point <= maxh)
		{
			cout << endl;
			cout << "ВОПРОС. " << endl << quest << endl;
			cout << "Ответ: " << endl;
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

int main_menu(); //Основное меню;
int control_key(int a, int b); //Проверка ввода ключа меню;
void theor_mat(); //Теория для теста;
int menu_passing(); //Меню выбора условий прохождения теста;
void proceed_test(vector<Test1> issues1, vector<Test2> issues2); //Приступить к тесту;
template <class T> vector<T> enter_que(vector<T> &qq, int n); //Считывание вопросов из файла при работе с вектором;
template <class T> void passing(vector<T> &qq); //Прохождение теста с объектами второго производного типа при работе с вектором;
template <class T> void output(vector<T> qq); //Вывод результатов теста при работе с вектором;
void case_all(vector<Test1> issues, int n); //Прохождения теста без условий;
void case_choiсe(vector<Test2> issues, int n); //Прохождение теста с вопросами определённой сложности;
void case_sort(vector<Test1> issues, int n); //Прохождение теста с отсортированными вопросами, используя вектор;
void inform(); //Вывод сведений об авторе;

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

			theor_mat(); //Теория для теста;
			break;

		case 2:

			proceed_test(issues1, issues2); //Приступить к тесту;
			break;

		case 3:

			inform(); //Вывод сведений об авторе;
			break;

		case 4:

			cout << "Выход из программы...\n" << endl;
			cout << endl;
			exit(EXIT_SUCCESS);
			break;
		}
		cout << "Для продолжения нажмите любую клавишу." << endl;
		_getch();
		system("cls");
	}

    return 0;
}

int main_menu() //Основное меню;
{
	cout << "\t ~ Меню ~ \t" << endl;
	cout << endl;
	cout << "1. Ознакомиться с теорией по биологии для подготовки к тесту" << endl;
	cout << "2. Пройти тест" << endl;
	cout << "3. Сведения об авторе" << endl;
	cout << "4. Выход" << endl;
	
	int variant = control_key(1, 4);
	system("cls");
	return variant;
}

int control_key(int a, int b) //Проверка ввода значения, которое должно входить в диапазон от a до b;
{
	int variant = 0;
	string buff;

	while (variant > b || variant < a)
	{
		cin >> buff;
		if (buff.length() != 1)
		{
			cout << "Вместо цифр введены другие символы. Попробуйте ещё раз:" << endl;
			continue;
		}
		else if (isdigit(buff[0]))
		{
			variant = stoi(buff);
			if (variant > b || variant < a)
			{
				cout << "Попробуйте ещё раз:" << endl;
				continue;
			}
		}
		else
		{
			cout << "Вместо цифр введены другие символы. Попробуйте ещё раз:" << endl;
			continue;
		}
	}

	return variant;
}

void theor_mat() //Теория для теста;
{
	string temp1, temp2;
	ifstream fin("теория.txt");

	if (!fin.is_open() || fin.eof())
		cout << "Проблемы с файлом.";
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

int menu_passing() //Меню выбора условий прохождения теста;
{
	cout << "\t ~ Условия прохождения теста ~ \t" << endl;
	cout << endl;
	cout << "1. Пройти тест полностью" << endl;
	cout << "2. Пройти тест с определённой сложностью вопросов" << endl;
	cout << "3. Отсортировать вопросы по сложности" << endl;
	cout << "4. Вернуться в главное меню" << endl;
	
	int variant = control_key(1, 4);

	system("cls");
	return variant;
}

void proceed_test(vector<Test1> issues1, vector<Test2> issues2) //Приступить к тесту;
{
	int n = 10;
	while (true)
	{
		switch (menu_passing())
		{
		case 1:

			case_all(issues1, n); //Прохождения теста без условий, используя очередь;
			break;


		case 2:

			case_choiсe(issues2, n); //Прохождение теста с вопросами определённой сложности, используя стек;
			break;

		case 3:

			case_sort(issues1, n); //Прохождение теста с отсортированными вопросами, используя вектор;
			break;

		case 4:
			
			main();
			break;
		}
		cout << "Для продолжения нажмите любую клавишу." << endl;
		_getch();
		system("cls");
	}
}

template <class T>
vector<T> enter_que(vector<T> &qq, int n) //Считывание вопросов из файла при работе с вектором;
{
	string temp1, temp2;
	int p; 
	int i = 0;
	ifstream fin("вопросы.txt");

	if (!fin.is_open() || fin.eof())
		cout << "Проблемы с файлом.";
	else
	{
		for (int i = 0; i < n; i++)
		{
			do {						//Считывание вопроса;
				fin >> temp1;
				temp2 += temp1 + " ";
			} while (temp1 != ":");

			fin >> temp1; //Считывание верного ответа;
			fin >> p; //Считывание ценности вопроса;

			T exep(temp2, temp1, p);
			qq.push_back(exep);

			temp2 = "";
		}
	}
	fin.close();

	return qq;
}

template <class T>
void passing(vector<T> &qq) //Прохождение теста с объектами второго производного типа при работе с вектором;
{
	cout << "Пройдите тест." << endl;
	cout << "(Ответ записывать с маленькой буквы, согласовывая падеж с тем, который в вопросе)" << endl;
	ofstream fout("ответы.txt", ios_base::out);

	if (!fout.is_open())
		cout << "Проблемы с файлом.";
	else
	{
		for (int i = 0; i != qq.size(); i++)
		{
			qq.at(i).enter_ans(i); //Заполняется значение поля "ответ, данный пользователем";

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
void output(vector<T> qq) //Вывод результатов теста при работе с вектором;
{
	int k = 0; //Количество верных ответов;
	int ball = 0; //Общий бал за тест;

	cout << "\t ~ Итоги теста ~ " << endl;

	for (int i = 0; i != qq.size(); i++)
	{
		cout << endl;
		cout << "_____________________________________________" << endl;
		cout << i + 1 << "-й вопрос: " << qq.at(i).get_quest() << endl;
		cout << "Ценность вопроса: " << qq.at(i).get_point() << endl;
		cout << "Верный ответ: " << qq.at(i).get_r_answer() << endl;
		cout << "Ваш ответ: " << qq.at(i).get_answer() << endl;

		if (qq.at(i).check())
		{
			cout << "-ВЕРНО-" << endl;
			k++;
			ball += qq.at(i).get_point();
		}
		else
			cout << "-НЕВЕРНО-" << endl;
	}
		

	cout << endl;
	cout << "Количество верных ответов: " << k << endl;
	cout << "Общий балл: " << ball << endl;
}

void case_all(vector<Test1> issues, int n) //Прохождения теста без условий;
{
	enter_que(issues, n);
	passing(issues);
}

void case_choiсe(vector<Test2> issues, int n) //Прохождение теста с вопросами определённой сложности;
{
	cout << "Введите максимальную сложность (от 1 до 5): " << endl;
	int k = control_key(1, 5);
	
	enter_que(issues, n);

	for (int i = 0; i != issues.size(); i++)
	{
		issues[i].set_maxh(k);
	}

	passing(issues);
}

void case_sort(vector<Test1> issues, int n) //Прохождение теста с отсортированными вопросами, используя вектор;
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

void inform() //Вывод сведений об авторе;
{
	cout << "\t Сведения об авторе: \n" << endl;
	cout << "Сапунова Евгения Сергеевна" << endl;
	cout << "Курс 2, группа 3-Т3О-205Б-16." << endl;
	cout << "Курсовая работа по дисциплине «Объектно-ориентированное программирование»:" << endl;
	cout << "«Игровая программа для школьников по биологии»;" << endl;
	cout << "реализовано на языке С++ " << endl;
	cout << endl;
}
