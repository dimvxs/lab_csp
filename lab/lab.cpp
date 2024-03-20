#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;


void readDate() {
	ifstream file("file.txt"); // Открываем файл
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}

	string line;
	while (getline(file, line)) { // Считываем файл построчно
		const char* cstr = line.c_str(); // Преобразуем строку в массив символов

		const char* exchangedate_pos = strstr(cstr, "\"exchangedate\":\"");

		// Если найдена подстрока
		if (exchangedate_pos) {
			// Извлекаем значение
			char exchangedate[20];
			if (sscanf_s(exchangedate_pos + 16, "%[^\"]", exchangedate, _countof(exchangedate)) == 1) {
				// Выводим значение
				cout << "Дата: " << exchangedate << endl;
			}
			else {
				cout << "Ошибка при считывании даты!" << endl;
			}

			break; // Выходим из цикла, если нашли первое совпадение
		}
	}

	file.close();

}

void readCurrency() {

	ifstream file("file.txt"); // Открываем файл
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}

	string line;
	while (getline(file, line)) { // Считываем файл построчно
		const char* cstr = line.c_str(); // Преобразуем строку в массив символов

		// Ищем нужные нам подстроки
		const char* rate_pos = strstr(cstr, "\"rate\":");


		if (rate_pos) {
			// Извлекаем значение
			float rate;
			sscanf_s(rate_pos + 7, "%f", &rate); // Извлекаем число после ":"

			// Выводим значение
			cout << rate;

			break; // Выходим из цикла, если нашли первое совпадение
		}
	}

	file.close();
}

int main()
{
	setlocale(0, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// the URL to download from 
	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";

	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=USD&date=20240320&json"; // 
	// the destination file 
	//string destFile = "file.txt";
	//// URLDownloadToFile returns S_OK on success 
	//if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
	//{
	//	cout << "Saved to " << destFile << "\n";
	//}
	//else cout << "Fail!\n";
	/*
	1. С клавиатуры вводим следующие данные:
	  дата
	  Валюта
	  Вывести актуальную информацию!
	  формат вывода - Дата: 19.03.2024г, Валюта - USD, 1$ = 38.9744 грн.

	*/

	string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=USD&date=20240320&json";
	string currency;
	string year, month, day;

	cout << "enter the day: ";
	cin >> day;

	cout << "enter the month: ";
	cin >> month;

	cout << "enter the year: ";
	cin >> year;


	cout << "enter the currency: ";
	cin >> currency;
	string date = (year += month += day);
	srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=" + currency + "&date=" + date + "&json";

	// the destination file 
string destFile = "file.txt";
// URLDownloadToFile returns S_OK on success 
if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
{
	cout << "Saved to " << destFile << "\n";
}
else cout << "Fail!\n";



cout << "current currency: 1$ = ";
readCurrency();
cout << endl;

cout << "current date: ";
readDate();
cout << endl;

}

