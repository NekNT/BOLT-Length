
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <clocale>
using namespace std;

int preBoltLength(int boltDia, int t1, int t2) {

}

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "РАСЧЕТ ДЛИНЫ БОЛТА" << endl << endl;

	//Секция ввода исходных данных для расчета
	cout << "Введите диаметр болта:";
	int boltDiam;
	cin >> boltDiam;
	while (boltDiam != 12 &&
		boltDiam != 16 &&
		boltDiam != 20 &&
		boltDiam != 24 &&
		boltDiam != 30) {
		cout << "Нет такого диаметра! Попробуйте ещё раз:"; cin >> boltDiam;
	};

	cout << "Введите толщину первой соединяемой детали:";
	int  t1, t2;
	cin >> t1;

	cout << "Введите толщину второй соединяемой детали:";
	cin >> t2;

	//Расчет предварительной длины болта
	double tNut, tWasher, tailMin;
	const int countNuts = 2, countWashers = 2;
	switch (boltDiam) {
	case 12:	tNut = 10.8;		tWasher = 2.5;		tailMin = 3;	break;
	case 16:	tNut = 14.8;		tWasher = 3;		tailMin = 3;	break;
	case 20:	tNut = 18;			tWasher = 3;		tailMin = 3;	break;
	case 24:	tNut = 21.5;		tWasher = 4;		tailMin = 4;	break;
	case 30:	tNut = 25.6;		tWasher = 4;		tailMin = 4;	break;
	};
	double preBoltLength = countWashers * tWasher + countNuts * tNut + t1 + t2 + tailMin;
	preBoltLength = ceil(preBoltLength /= 5) * 5;

	//Вывод на экран
	cout << preBoltLength << endl;


	system("pause");
	return 0;
}
