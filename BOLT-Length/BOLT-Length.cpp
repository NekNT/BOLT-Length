
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <clocale>
#include <math.h>
#include <string>
using namespace std;

int calcPreBoltLength(int boltDiam, int t1, int t2) {
	
	// Эта функция определяет предварительную длину болта из условия, что хвостик должен быть не меньше минимального

	// Определение толщин гаек и шайб, а так же размера минимального хвостика
	double tNut, tWasher;
	int tailMin;

	switch (boltDiam) {
	case 12:	tNut = 10.8;		tWasher = 2.5;		tailMin = 3;	break;
	case 16:	tNut = 14.8;		tWasher = 3;		tailMin = 3;	break;
	case 20:	tNut = 18;			tWasher = 3;		tailMin = 3;	break;
	case 24:	tNut = 21.5;		tWasher = 4;		tailMin = 4;	break;
	case 30:	tNut = 25.6;		tWasher = 4;		tailMin = 4;	break;
	};

	//Вычисляем предварительную длину болта
	int COUNT_NUTS = 2, COUNT_WASHERS = 2;
	double preBoltLength = COUNT_WASHERS * tWasher + COUNT_NUTS * tNut + t1 + t2 + tailMin;
	preBoltLength = ceil(preBoltLength /= 5) * 5;
	return preBoltLength;
}

int boltLengthVerification(int boltDiam, int boltLength, int t1, int t2, int countNuts, int countWashers) {	
	
	// Эта функция проверяет болтовое соединение с заданными параметрами

	// Определение толщин гаек и шайб, а так же размера минимального хвостика
	double tNut, tWasher;
	int tailMin;

	switch (boltDiam) {
	case 12:	tNut = 10.8;		tWasher = 2.5;		tailMin = 3;	break;
	case 16:	tNut = 14.8;		tWasher = 3;		tailMin = 3;	break;
	case 20:	tNut = 18;			tWasher = 3;		tailMin = 3;	break;
	case 24:	tNut = 21.5;		tWasher = 4;		tailMin = 4;	break;
	case 30:	tNut = 25.6;		tWasher = 4;		tailMin = 4;	break;
	};

	// Находим длину нарезки резьбы болта
	int threadLength;
	if (boltDiam == 12 && boltLength <= 120) { threadLength = 30; };
	if (boltDiam == 12 && boltLength > 120 && boltLength <= 200) { threadLength = 36; };
	if (boltDiam == 12 && boltLength > 200) { threadLength = 49; };

	if (boltDiam == 16 && boltLength <= 40) { threadLength = boltLength; };
	if (boltDiam == 16 && boltLength > 40 && boltLength <= 120) { threadLength = 38; };
	if (boltDiam == 16 && boltLength > 120 && boltLength <= 200) { threadLength = 44; };
	if (boltDiam == 16 && boltLength > 200) { threadLength = 57; };

	if (boltDiam == 20 && boltLength <= 50) { threadLength = boltLength; };
	if (boltDiam == 20 && boltLength > 50 && boltLength <= 120) { threadLength = 46; };
	if (boltDiam == 20 && boltLength > 120 && boltLength <= 200) { threadLength = 52; };
	if (boltDiam == 20 && boltLength > 200) { threadLength = 65; };

	if (boltDiam == 24 && boltLength <= 60) { threadLength = boltLength; };
	if (boltDiam == 24 && boltLength > 60 && boltLength <= 120) { threadLength = 54; };
	if (boltDiam == 24 && boltLength > 120 && boltLength <= 200) { threadLength = 60; };
	if (boltDiam == 24 && boltLength > 200) { threadLength = 73; };

	if (boltDiam == 30 && boltLength <= 70) { threadLength = boltLength; };
	if (boltDiam == 30 && boltLength > 70 && boltLength <= 120) { threadLength = 66; };
	if (boltDiam == 30 && boltLength > 120 && boltLength <= 200) { threadLength = 72; };
	if (boltDiam == 30 && boltLength > 200) { threadLength = 85; };

	// Вычисляем длину ненарезанной части болта
	int notThreadLength = boltLength - threadLength;

	// Вычисляем хвостик
	double tail = boltLength - t1 - t2 - countWashers * tWasher - countNuts * tNut;

	// Вычисляем резьбу в пакете
	double threadInDetails = (countWashers-1) * tWasher + t1 + t2 - notThreadLength;

	// Вычисляем толщину самой тонкой детали
	double tMin = fmin(t1, t2);
	
	// Вычисляем допустимую резьбу в пакете
	double maxThreadInDetails;
	if (tMin <= 8) { maxThreadInDetails = 0; }
	else {
		if (tMin / 2 < 5) { maxThreadInDetails = tMin; }
		else { maxThreadInDetails = 5; };
	};

	/* Проверки:
		1. Проверка хвостика
		2. Проверка резьбы в пакете
		3. Проверка закручиваемости
	*/
	int result, result1, result2, result3;

	if (tail >= tailMin) { result1 = 1; }
	else { result1 = 0; };

	if (threadInDetails <= maxThreadInDetails) { result2 = 1; }
	else { result2 = 0; };

	if (t1 + t2 + countWashers * tWasher >= notThreadLength) { result3 = 1; }
	else { result3 = 0; };

	if (result1 + result2 + result3 == 3) { result = 1; }
	else{result = 0;};

	/*
	cout << "Диаметр болта: " << boltDiam << endl;
	cout << "Длина болта: " << boltLength << endl;
	cout << "Толщина t1: " << t1 << endl;
	cout << "Толщина t2: " << t2 << endl;
	cout << "Толщина гайки: "<< tNut << endl;
	cout << "Толщина шайбы: " << tWasher << endl;
	cout << "Длина нарезки резьбы: " << threadLength << endl;
	cout << "Резьба в пакете: "<< threadInDetails<<endl;
	cout << "Половина tMin: " << tMin/2<<endl;

	cout << "Результат проверки хвостика - " << result1 << " ( " << tail << "мм >= " << tailMin << "мм )" << endl;
	cout << "Результат проверки резьбы в пакете - " << result2 << " ( " << threadInDetails << "мм <= " << maxThreadInDetails << "мм )" << endl;
	cout << "Результат проверки закручиваемости - " << result3 << endl;
	cout << "Итоговый результат - " << result << endl;
	*/
	return result;
}

void coutVariant(int boltDiam, int boltLength, int countNuts, int countWashers){
	
	// Эта функция выводин на экран подобраный вариант 

	cout << "Болт М " << boltDiam << " х " << boltLength;
	if (countNuts == 1) { cout << " с 1-й гайкой и "; };
	if (countNuts == 2) { cout << " с 2-мя гайками и "; };
	if (countWashers == 1) { cout << "1-й шайбой (со стороны гайки)."; };
	if (countWashers == 2) { cout << "2-мя шайбами."; };
	if (countWashers == 3) { cout << "3-мя шайбами."; };
	if (boltLength == 85 || 
		boltLength == 95 ||
		boltLength == 105 ||
		boltLength == 115 ||
		boltLength == 125 ||
		boltLength == 135 ||
		boltLength == 145 ||
		boltLength == 155 ||
		boltLength == 165 ||
		boltLength == 175 ||
		boltLength == 185 ||
		boltLength == 195) {
		cout << " ВНИМАНИЕ! Длина со знаком *, уточнить возможность закупа." << endl;
	}
	else { cout << endl; };
}

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "РАСЧЕТ ДЛИНЫ БОЛТА" << endl << endl;

	//Секция ввода исходных данных для расчета
	cout << "Введите диаметр болта:";
	int boltDiam;
	cin >> boltDiam;
	while (	boltDiam != 12 &&
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

	//Вычисляем предварительную длину болта
	int preBoltLength = calcPreBoltLength(boltDiam, t1, t2);
	
	//Проверяем предварительную длину болта 
	int countNuts = 2, countWashers = 2;
	int result = boltLengthVerification(boltDiam, preBoltLength, t1, t2, countNuts, countWashers);
	
	cout << endl << "ПОДОБРАННЫЕ ВАРИАНТЫ:" << endl << endl;

	//Подбираем и выводим на экран варианты с 2-мя гайками и с 2-мя шайбами
	int boltLength;
	for (int i = -10; i <= 10; i += 5) {
		boltLength = preBoltLength + i;
		result = boltLengthVerification(boltDiam, boltLength, t1, t2, countNuts, countWashers);
		if (result == 1) {
			coutVariant(boltDiam, boltLength, countNuts, countWashers);
		};
	};

	//Подбираем и выводим на экран варианты с 2-мя гайками и с 3-мя шайбами
	countWashers = 3;
	for (int i = -10; i <= 10; i += 5) {
		boltLength = preBoltLength + i;
		result = boltLengthVerification(boltDiam, boltLength, t1, t2, countNuts, countWashers);
		if (result == 1) {
			coutVariant(boltDiam, boltLength, countNuts, countWashers);
		}; 
	};

	//Подбираем и выводим на экран варианты с 2-мя гайками и с 1-й шайбой
	countWashers = 1;
	for (int i = -10; i <= 10; i += 5) {
		boltLength = preBoltLength + i;
		result = boltLengthVerification(boltDiam, boltLength, t1, t2, countNuts, countWashers);
		if (result == 1) {
			coutVariant(boltDiam, boltLength, countNuts, countWashers);
		};
	};
	
	cout << endl;
	system("pause");
	return 0;
}
