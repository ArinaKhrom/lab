#include <iostream>
#include <ctime>
using namespace std;
int main() {
    setlocale(LC_ALL, "Rus");
    int a[100];
	int n;

//заполнение массива
	cout << "Введите длину массива n: ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		a[i] = rand() % 100 - 50; //заполнение массива 
	}
	cout << "Исходный массив: ";
	for (int i = 1; i <= n; i++) {
		cout << a[i] << ' ';
	}
	cout << endl << endl;
//поиск миниамльного
	int min = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] < a[min]) {
			min = i;
		}
	}
//удаление минимального элемента
	cout << endl;
	cout << "Удаление " << min << " минимального элемента массива:";
	cout << endl;
	for (int i = min; i <= n; i++) {
		a[i] = a[i + 1];
	}
	n = n - 1;
//вывод измененного массива
	for (int i = 1; i <= n; i++) {
		cout << a[i] << " ";
	}

	cout << '\n';
	//перестановка и вывод обновленного массива
	for (int i = 1; i <= n - N; i = i + 2) {
		int x = a[i];
		a[i] = a[i + 1];
		a[i + 1] = x;
	}
	cout << "обновленный массив: ";
	for (int i = 1; i <= n - N + 1; i++) {
		cout << a[i] << ' ';
	}
	cout << '\n';
	cout << endl;
    return 0;
}