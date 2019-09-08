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
void StartWithMenu();//+
string* UserInputLoginPass(string*);//+
int CheckBaseLoginPassword(string, string);//+
int CheckLoginNew(string);//+

struct LoginPass
{
	string login;
	string password;
}lp;

vector<LoginPass> dataLoginPass;

enum button { registration = 1, autorization, showAll, exitProg };

string pathToFile = { "login-pass.txt" };

void main()
{
	SetConsoleTitle("FILESTREAM");
	system("mode con cols=80 lines=25");
	system("color 0f");
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	//SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	srand(time(NULL));

	//write your code HERE!
	//Start();
	StartWithMenu();

	//_getch();
	//system("pause");

	//cout << "\n";
	//system("cls");
	//system("pause");
	//Sleep(1000);
}

//старт обычного меню
void Start()
{

	int number;
	bool whileKey = false;
	string* str;
	bool(*operation[])(string, string) = { Registration, Authorization };
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
//извлечь всю базу из txt в vector
void ExtractDataFromFile()
{
	ifstream ifstr(pathToFile, ios::in);
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
//Дозаписать строку в конец текстового файла
bool AppendDataToFile(string login, string password)
{
	ofstream ofstr(pathToFile, ios::app);
	if (ofstr.is_open())
	{
		ofstr << login << ':' << password << '\n';
		ofstr.close();
		return true;
	}
	else
		return false;
}
//вывести всю базу на экран
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
//регисртация пользователя
bool Registration(string login, string password)
{
	int resultCheck = CheckLoginInDataBase(login);
	if (0 <= resultCheck)
		return false;
	else if (resultCheck == -1)
		return AppendDataToFile(login, password) ? true : false;
}
//проверка логина из внутреннего хранилища vector'а
int CheckLoginInDataBase(string login)
{
	ExtractDataFromFile();
	for (int i = 0; i < dataLoginPass.size(); i++)
		if (dataLoginPass[i].login == login)
			return i;
	return -1;
}
//проверка пороля из внутреннего хранилища vector'а
bool CheckPasswordInDataBase(int position, string password)
{
	return dataLoginPass[position].password == password ? true : false;
}
//Авторизация пользователя
bool Authorization(string login, string password)
{
	int resultCheck = CheckLoginInDataBase(login);
	if (0 <= resultCheck)
		return CheckPasswordInDataBase(resultCheck, password) ? true : false;
	else if (resultCheck == -1)
		return false;
}




//Новые функции

//Регистрация
bool RegistrationNew(string login, string password)
{
	int result = CheckLoginNew(login);
	if (result >= 0)
		return false;
	else if (result == -1)
		return AppendDataToFile(login, password) ? true : false;
}
//новая авторизация(в отличии от старой авторизации, не требует загрузки всей базы в vector, а проверяет логин в потоке построчно. Тем самым дойдя до нужной позиции, не проверяет оставшуюся часть базы)
bool AuthorizationNew(string login, string password)
{
	int result = CheckBaseLoginPassword(login, password);
	if (result == 1)
		return true;
	else if (result == 0)
		return false;//TODO: return 0 - логина не существует(для вывода сообщений)
	else if (result == -1)
		return false;//TODO: return -1 - логин найден, но пароль не подходит(для вывода сообщений)
}
//Проверяет логин в потоке построчно
int CheckLoginNew(string login)
{
	ifstream ifstr(pathToFile, ios::in);
	string data;
	int iterator = 0;
	if (ifstr.is_open())
	{
		while (getline(ifstr, data))
		{
			if (login == data.substr(0 < data.find(':')))
				return iterator;
			iterator++;
		}
	}
	ifstr.close();
	return -1;
}
//Ввод логина и пароля пользователем в консоль
string* UserInputLoginPass(string* loginPassword)
{
	string login;
	string password;
	system("cls");
	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";
	cin >> password;
	loginPassword[0] = login;
	loginPassword[1] = password;
	return loginPassword;
}
//старт графического меню
void StartWithMenu()
{
	string menuTitle[3] = { "Регистрация", "Авторизация", "Весь список" };
	int target = 1;
	int xCoord = 0;
	int yCoord = 0;
	int button = 0;
	bool isInTheCycle = false;
	bool(*operation[])(string, string) = { RegistrationNew, AuthorizationNew };
	string* ptrLoginPassword;
	string loginPasArray[2];
	do
	{
		system("cls");
		for (int i = 0; i < 3; i++)
		{
			if (target - 1 == i)
				color(Green, Black);
			cursor(xCoord, yCoord + i);
			cout << menuTitle[i];
			color(White, Black);
		}
		button = _getch();
		switch (button)
		{
		case Enter:
			if (target == 3)
			{
				ShowAll();
				_getch();
				break;
			}
			ptrLoginPassword = UserInputLoginPass(loginPasArray);
			if (operation[target - 1](loginPasArray[0], loginPasArray[1]))//вызов соответствующей функции на которую указывает курсор(через указатель на функцию)
			{
				//system("cls");
				color(Green, Black);
				cout << "Успешно!";
				color(White, Black);
				_getch();
			}
			else
			{
				//system("cls");
				color(Red, Black);
				cout << "Что-то пошло не так!";
				color(White, Black);
				_getch();
			}
			break;
		case Esc:
			isInTheCycle = true;
			break;
		case Up:
			if (target == 1)
				break;
			target--;
			break;
		case Down:
			if (target == 3)
				break;
			target++;
			break;
		}
	} while (!isInTheCycle);
}
//Проверяет наличие логина и после сравнивает пароли(возврат: 1 - логин и пароль верны / 0 - такого логина не существует / -1 - логин найден, но пароль не подходит)
int CheckBaseLoginPassword(string login, string password)
{
	ifstream ifstr(pathToFile, ios::in);
	string data;
	if (ifstr.is_open())
	{
		while (getline(ifstr, data))
		{
			if (login == data.substr(0, data.find(':')))
			{
				if (password != data.substr(data.find(':') + 1, data.length()))
					return -1;//неверный пароль(при этом логин подошёл)
				else
					return 1;//логин и пароль совпали
			}
		}
	}
	ifstr.close();
	return 0;//такого логина не существует(пароль даже не стал проверяться)
}