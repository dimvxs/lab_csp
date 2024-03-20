#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;


void readDate() {
	ifstream file("file.txt"); // ��������� ����
	if (!file.is_open()) {
		cout << "������ �������� �����!" << endl;
		return;
	}

	string line;
	while (getline(file, line)) { // ��������� ���� ���������
		const char* cstr = line.c_str(); // ����������� ������ � ������ ��������

		const char* exchangedate_pos = strstr(cstr, "\"exchangedate\":\"");

		// ���� ������� ���������
		if (exchangedate_pos) {
			// ��������� ��������
			char exchangedate[20];
			if (sscanf_s(exchangedate_pos + 16, "%[^\"]", exchangedate, _countof(exchangedate)) == 1) {
				// ������� ��������
				cout << "����: " << exchangedate << endl;
			}
			else {
				cout << "������ ��� ���������� ����!" << endl;
			}

			break; // ������� �� �����, ���� ����� ������ ����������
		}
	}

	file.close();

}

void readCurrency() {

	ifstream file("file.txt"); // ��������� ����
	if (!file.is_open()) {
		cout << "������ �������� �����!" << endl;
	}

	string line;
	while (getline(file, line)) { // ��������� ���� ���������
		const char* cstr = line.c_str(); // ����������� ������ � ������ ��������

		// ���� ������ ��� ���������
		const char* rate_pos = strstr(cstr, "\"rate\":");


		if (rate_pos) {
			// ��������� ��������
			float rate;
			sscanf_s(rate_pos + 7, "%f", &rate); // ��������� ����� ����� ":"

			// ������� ��������
			cout << rate;

			break; // ������� �� �����, ���� ����� ������ ����������
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
	1. � ���������� ������ ��������� ������:
	  ����
	  ������
	  ������� ���������� ����������!
	  ������ ������ - ����: 19.03.2024�, ������ - USD, 1$ = 38.9744 ���.

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

