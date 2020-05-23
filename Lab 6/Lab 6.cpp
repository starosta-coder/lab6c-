#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

FILE* f_out,* f_in;

struct firm
{
    char surname[56];
    char position[56];
    double salary;
	int year;
};

void medium_1()
{
	firm* arr;
	int size;	

	do
	{
		cout << "Введите количество сотрудников, данные которых вы будете вводить: ";
		cin >> size;
		cout << endl;
	} while (size < 1);

	double sum = 0;
	int year = 2020;
	arr = new firm[size];

    //вводим данные о сотрудниках;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите фамилию сотрудника номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].surname, 56);
		cout << endl;

		cout << "Введите должность: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].position, 56);
		cout << endl;

		do {
			cout << "Введите зарплату: ";
			cin >> arr[i].salary;
			cout << endl;
		} while (arr[i].salary <= 0);

		do {
			cout << "Введите год рождения: ";
			cin >> arr[i].year;
			cout << endl;
		} while (arr[i].year < 1900);

		sum += arr[i].salary;
		cout << endl;
	}

	sum /= size;

	//говорим программе что запись будет происходить в бин. виде;
	ofstream input("medium1_bin_File.bin", ios::binary | ios::out);

	for (int i = 0; i < size; i++)
	{
		if (year - arr[i].year < 30 && arr[i].salary > sum)
		{
			//преобразуем информацию в тип char для записи в файл;
			input << "Сотрудник номер " << i + 1 << ":" << endl;
			input.write((char*)&arr[i], sizeof arr[i]) << endl << endl;
		}
	}

	//закрываем файл;
	input.close();

	cout << "Данные записаны в файл" << endl << endl;
}

void medium_2()
{
	const int row = 5, col = 6;
	int arr[row][col];

	//говорим программе что запись будет идти в бин. виде;
	f_out = fopen("medium2_numbers_before.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				//считываем в файл элементы массива;
				arr[i][j] = rand() % 10;
				fwrite(&arr[i][j], sizeof(int), 1, f_out);
			}
			else
			{
				//элемент перехода на новую строку в файле занимает 6-ю колонку массива - ее мы не будем выводить в консоль;
				fwrite(&"\n", sizeof(int), 1, f_out);
			}
		}
	}

	fclose(f_out);

	int new_arr[row][col];

	//считываем с файла данные в новый массив;
	f_in = fopen("medium2_numbers_before.bin", "rb");
	fread(&new_arr, sizeof(int), row * col, f_in);
	fclose(f_in);

	cout << "Массив до изменений: " << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				cout << new_arr[i][j] << "\t";
				new_arr[i][j] *= 2;
			}
		}
		cout << endl;
	}

	cout << endl;

	//записываем в новый файл уже измененный массив;
	f_out = fopen("medium2_numbers_after.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				fwrite(&new_arr[i][j], sizeof(int), 1, f_out);
			}
			else
			{
				fwrite(&"\n", sizeof(int), 1, f_out);
			}
		}
	}

	fclose(f_out);

	//выводим новый массив в консоль;
	f_in = fopen("medium2_numbers_after.bin", "rb");
	fread(&new_arr, sizeof(int), row * col, f_in);
	fclose(f_in);

	cout << "Массив после изменений:" << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				cout << new_arr[i][j] << "\t";
			}
		}
		cout << endl;
	}

	cout << endl << endl;
}

struct trip
{
	char trip_name[56];
	double price;
	int human_quantity;
};

void medium_3()
{
	trip* arr;
	int group_quantity;

	do
	{
		cout << "Введите количество поездок, данные которых вы будете вводить: ";
		cin >> group_quantity;
	} while (group_quantity < 1);

	arr = new trip[group_quantity];

	for (int i = 0; i < group_quantity; i++)
	{
		cout << "Введите название турпоездки номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].trip_name, 56);
		cout << endl;

		do {
			cout << "Стоимость путевки: ";
			cin >> arr[i].price;
			cout << endl;
		} while (arr[i].price <= 0);

		do {
			cout << "Кол-во человек в группе: ";
			cin >> arr[i].human_quantity;
			cout << endl;
		} while (arr[i].human_quantity <= 0);

		cout << endl;
	}

	//после записи открываем файл и считываем данные в новый массив;
	f_out = fopen("medium3_trip_before.bin", "wb");
	fwrite(arr, sizeof(trip), group_quantity, f_out);
	fclose(f_out);

	trip* new_arr = new trip[group_quantity];

	f_in = fopen("medium3_trip_before.bin", "rb");
	fread(new_arr, sizeof(trip), group_quantity, f_in);
	fclose(f_in);

	cout << "Данные из файла перед изменением:" << endl << endl;

	for (int i = 0; i < group_quantity; i++)
	{
		cout << "Поездка номер : " << i + 1 << endl;
		cout << "Название : " << new_arr[i].trip_name << endl;
		cout << "Стоимость путевки : " << new_arr[i].price << endl;
		cout << "Кол-во человек : " << new_arr[i].human_quantity << endl << endl;
	}

	//снижаем цену если кол-во человек равно 10-ти;
	for (int i = 0; i < group_quantity; i++)
	{
		if (new_arr[i].human_quantity == 10)
		{
			new_arr[i].price = new_arr[i].price / 100 * 95;
		}
	}

	//перезаписываем данные;
	f_out = fopen("medium3_trip_after.bin", "wb");
	fwrite(new_arr, sizeof(trip), group_quantity, f_out);
	fclose(f_out);

	f_in = fopen("medium3_trip_after.bin", "rb");
	fread(new_arr, sizeof(trip), group_quantity, f_in);
	fclose(f_in);

	cout << "Данные из файла после изменения:" << endl << endl;

	for (int i = 0; i < group_quantity; i++)
	{
		cout << "Поездка номер : " << i + 1 << endl;
		cout << "Название : " << new_arr[i].trip_name << endl;
		cout << "Стоимость путевки : " << new_arr[i].price << endl;
		cout << "Кол-во человек : " << new_arr[i].human_quantity << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	int a;
	int count = 0;

	do
	{
		cout << "Введите номер задания(medium_1 - 1, medium_2 - 2, medium_3 - 3): ";

		cin >> a;

		cout << endl;

		if (a == 1)
		{
			medium_1();
			count++;
		}

		if (a == 2)
		{
			medium_2();
			count++;
		}

		if (a == 3)
		{
			medium_3();
			count++;
		}

	} while (count == 0);

	int b;

	do
	{

		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}