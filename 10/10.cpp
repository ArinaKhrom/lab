
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

const int N = 5;

int main() {
    cout << "Enter strings: " << endl; //зполнение массива
    string* strmas = new string[N];
    for (int i = 0; i < N; i++)
        getline(cin, strmas[i]);

    int num;
    cout << "Enter string number:" << endl;
    cin >> num;
    string* strmass = new string[N+1];
    for (int i = 0; i < N; i++)
        strmass[i] = strmas[i];

    strmass[N+1] = strmass[num];

    for (int i = 0; i < N+1 ; i++) //вывод готового массива
        cout << strmass[i] << endl;
}
