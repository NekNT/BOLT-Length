#include "pch.h"
#include <iostream>
#include <conio.h>
#include <clocale>
#include <math.h>
#include <string>
using namespace std;

int boltLengthVerification(int boltDiam, int boltLength, int t1, int t2, int countNuts, int countWashers) {

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
	double threadInDetails = (countWashers - 1) * tWasher + t1 + t2 - notThreadLength;

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
	else { result = 0; };
	
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
	
	return result;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "ТЕСТ ФУНКЦИИ" << endl << endl;

	boltLengthVerification(16, 100, 25, 30, 2, 2);
	
	cout << endl;
	system("pause");
	return 0;
}