//НИК:		Miracle
//ГРУППА:	Подкидыши
//ТЕМА:		FileStream
//ДАТА:		01.09.2019

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <vector>
//#include <map>
#include<fstream>
#include <typeinfo.h>

//#define yes 1
//#define no 0
//#define std_error "Sorry, its not work\n"

//typedef int int0;

using namespace std;

enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
enum Direction { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };

void color(int text, int background)//через цифры
{
	//0 - ченрый			0
	//1 - синий				1
	//2 - зеленый			2
	//3 - голубой			3
	//4 - красный			4
	//5 - лиловый			5
	//6 - жёлтый			6
	//7 - белый				7
	//8 - серый				8
	//9 - светло-синий		9
	//10 - светло-зеленый	A
	//11 - светло-голубой	B
	//12 - светло-красный	C
	//13 - светло-лиловый	D
	//14 - светло-жёлтый	E
	//15 - ярко-белый		F
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void SetColor(Color text, Color background)//через enum
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void cursor(int x, int y)//курсор
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

//Осуществить регистрацию и авторизацию пользователей.
//При регистрации осуществлять проверку на наличие пользователя с таким именем.
//Если пользователь уже есть - зарегистрироваться нельзя.
//
//При авторизации - сначала проверяем наличие пользователя с таким именем.
//Если пользователь есть - вводим пароль.Если пароли совпадают - мы авторизировались.
//
//
//Данные о каждом пользователе храним в отдельной строке.
//
//Проверка наличия пользователя в файле должна происходить построчно, а не проверкой после считывания всего файла


bool Registration(string, string);//+
int CheckLoginInDataBase(string);//+
bool CheckPasswordInDataBase(int, string);//+
bool Authorization(string, string);//+
void Start();//+
void ExtractDataFromFile();//+
bool AppendDataToFile(string, string);//+
void ShowAll();//+

struct LoginPass
{
	string login;
	string password;
}lp;

vector<LoginPass> dataLoginPass;

enum button { registration = 1, autorization, showAll, exitProg };

void main()
{
	SetConsoleTitle("FILESTREAM");
	system("mode con cols=80 lines=25");
	system("color 0f");
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	//SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_ALL, "rus");

	srand(time(NULL));

	//write your code HERE!

	Start();

	//_getch();
	//system("pause");

	//cout << "\n";
	//system("cls");
	//system("pause");
	//Sleep(1000);
}

void Start()
{
	
	int number;
	bool whileKey = false;
	string* str;
	bool (*operation[])(string, string) = { Registration, Authorization };
	string login;
	string password;
	do
	{
		cout << "Для регистрации введите 1\n" << "Для авторизации введите 2\n" << "Показать весь список введите 3\n" << "Для выхода введите 4\n->";
		cin >> number;
		if (typeid(number) == typeid(int))
		{
			if ((0 < number) & (number < 3))//количество пунктов меню, кроме "Показать весь список"
			{
				system("cls");
				cout << "Логин: ";
				cin >> login;
				cout << "Пароль: ";
				cin >> password;
				if (operation[number - 1](login, password))
				{
					color(2, 0);
					cout << "\nУспешно!";
					color(7, 0);
					_getch();
					system("cls");
				}
				else
				{
					color(4, 0);
					cout << "\nЧто-то пошло не так!";
					color(7, 0);
					_getch();
					system("cls");
				}
			}
			else if (number == showAll)
			{
				ShowAll();
				_getch();
				system("cls");
			}
			else if (number == exitProg)
			{
				system("exit");
				break;
			}
		}
		whileKey = true;
	} while (whileKey);
}

void ExtractDataFromFile()
{
	ifstream ifstr("login-Pass.txt", ios::in);
	string data;
	string login;
	string password;
	dataLoginPass.clear();
	if (ifstr.is_open())
	{
		while (getline(ifstr, data))
		{
			lp.login = data.substr(0, data.find(':'));
			lp.password = data.substr(data.find(':') + 1, data.length());
			dataLoginPass.push_back(lp);
		}
	}
	ifstr.close();
}

bool AppendDataToFile(string login, string password)
{
	ofstream ofstr("login-Pass.txt", ios::app);
	if (ofstr.is_open())
	{
		ofstr << login << ':' << password << '\n';
		ofstr.close();
		return true;
	}
	else
		return false;
}

void ShowAll()
{
	ExtractDataFromFile();
	system("cls");
	color(6, 0);
	cout << "LOGIN : PASSWORD\n";	
	color(7, 0);
	for (int i = 0; i < dataLoginPass.size(); i++)
	{
		cout << dataLoginPass[i].login << " : " << dataLoginPass[i].password << '\n';
	}
}

bool Registration(string login, string password)
{
	int resultCheck = CheckLoginInDataBase(login);
	if (0 <= resultCheck )
		return false;
	else if (resultCheck == -1)
		return AppendDataToFile(login, password) ? true : false;
}

int CheckLoginInDataBase(string login)
{
	ExtractDataFromFile();
	for (int i = 0; i < dataLoginPass.size(); i++)
		if (dataLoginPass[i].login == login)
			return i;
	return -1;
}

bool CheckPasswordInDataBase(int position, string password) 
{ 
	return dataLoginPass[position].password == password ? true : false; 
}

bool Authorization(string login, string password)
{
	int resultCheck = CheckLoginInDataBase(login);
	if (0 <= resultCheck)
		return CheckPasswordInDataBase(resultCheck, password) ? true : false;
	else if (resultCheck == -1)
		return false;
}
