#include <iostream>
#include <windows.h>


using namespace std;

struct student {
	char surname[20];
	char name[20];
	char otchestvo[20];
	char dateOfBirth[10];
	char adress[20];
	int rang;
};
student* newStudent() {						//заполняем структуру
	student* st = new student();
	cout << "Введите данные студента:\n";
	cout << "  Введите имя: ";
	cin >> st->name;
	cout << "  Введите фамилию: ";
	cin >> st->surname;
	cout << "  Введите отчество: ";
	cin >> st->otchestvo;
	cout << "  Введите дату рождения: ";
	cin >> st->dateOfBirth;
	cout << "  Введите адрес: ";
	cin >> st->adress;
	cout << "  Введите рейтинг: ";
	cin >> st->rang;
	return st;
}
void printStudent(student* st) {			//выводим структуру
	cout << st->surname << " " << st->name << " " << st->otchestvo << " Дата рождения: " << st->dateOfBirth << " Адрес: " << st->adress << " Рейтинг: " << st->rang << "\n";
}
void printFile(char* str) {
	FILE* f;
	if ((f = fopen(str, "rb")) == NULL) {
		cout << "Файл невозоможно открыть на чтение\n";
		system("pause");
		return;
	}
	int col = 0;
	fread(&col, sizeof(int), 1, f);
	cout << "Кол-во студентов: " << col << "\n";
	int i = 0;
	while (!feof(f) && i < col) {
		student* st = new student();
		fread(st, sizeof(student), 1, f);
		printStudent(st);
		i++;
	}
	fclose(f);
}
void addStudentToFile(FILE* f, student* st) {
	student s = *st;
	fwrite(st, sizeof(student), 1, f);
}

void deleteStuden(FILE* fOld, FILE* f) {
	int col = 0;
	fwrite(&col, sizeof(int), 1, f);
	fread(&col, sizeof(int), 1, fOld);
	int i = 0, j = 0;
	while (!feof(fOld) && i < col) {
		student* st = new student();
		fread(st, sizeof(student), 1, fOld);
		int i2 = 0;
		int pos = ftell(fOld);
		fseek(fOld, sizeof(int), SEEK_SET);
		student* st2 = new student();
		bool povtor = false;
		while (!feof(fOld) && i2 < col) {
			fread(st2, sizeof(student), 1, fOld);
			if (i != i2) {
				if (strcmp(st2->dateOfBirth, st->dateOfBirth) == 0) {
					povtor = true;
					break;
				}
			}
			i2++;
		}
		fseek(fOld, pos, SEEK_SET);
		if (!povtor) {
			fwrite(st, sizeof(student), 1, f);
			j++;
		}
		i++;
	}
	fseek(f, 0, SEEK_SET);
	fwrite(&j, sizeof(int), 1, f);
}
bool addStudent(FILE* fOld, FILE* f, char* family) {
	int col = 0;
	fread(&col, sizeof(int), 1, fOld);
	col++;
	fwrite(&col, sizeof(int), 1, f);
	int i = 0;
	bool okey = false;
	while (!feof(fOld) && i < col - 1) {
		student* st = new student();
		fread(st, sizeof(student), 1, fOld);
		if (!okey && strcmp(st->surname, family) == 0) {
			student* stNew = newStudent();
			fwrite(stNew, sizeof(student), 1, f);
			okey = true;
		}
		fwrite(st, sizeof(student), 1, f);
	}
	return okey;
}
void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* f;
	if ((f = fopen("students.dat", "wb")) == NULL) {
		cout << "Файл невозоможно открыть на запись\n";
		system("pause");
		return;
	}
	int col;
	cout << "Вводите данные нового студента по-английски \n";
	cout << "Введите количество студентов: ";
	cin >> col;
	fwrite(&col, sizeof(int), 1, f);
	for (int i = 0; i < col; i++) {
		student* st = newStudent();
		addStudentToFile(f, st);
	}
	fclose(f);
	printFile("students.dat");

	//УДАЛЕНИЕ 
	FILE* fOld = fopen("students.dat", "rb");
	f = fopen("studentsNew.dat", "wb");
	deleteStudentOfBirth(fOld, f);
	fclose(fOld);
	fclose(f);
	remove("students.dat");
	rename("studentsNew.dat", "students.dat");

	cout << "ПОСЛЕ УДАЛЕНИЯ: ";
	printFile("students.dat");

	//Добавление 
	fOld = fopen("students.dat", "rb");
	f = fopen("studentsNew.dat", "wb");
	cout << "Введите фамилию человека, перед которым вставить студента: ";
	char family[20];
	cin >> family;
	if (addStudentFamily(fOld, f, family)) {
		fclose(fOld);
		fclose(f);

		remove("students.dat");
		rename("studentsNew.dat", "students.dat");
	} else {
		cout << "Студент с фамилией " << family << " не найден!" << "\n";
		fclose(fOld);
		fclose(f);
		remove("studentsNew.dat");
	}
	cout << "ПОСЛЕ ДОБАВЛЕНИЯ: ";
	printFile("students.dat");

	system("pause");
}
