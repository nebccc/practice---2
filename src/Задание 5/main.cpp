#include <iostream>
using namespace std;

int modPow(int a, int x, int p) {
    int result = 1;
    for (int i = 1; i <= x; i++) {
        result = (result * a) % p;
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "ru");

    int a, b, c;
    cout << "Введите три числа (a, b, c) для вычисления a^(b^c): ";
    cin >> a >> b >> c;

    int temp = modPow(b, c, 10);  // Вычисляем b^c по модулю 10
    int result = modPow(a, temp, 10);  // Вычисляем a^(b^c) по модулю 10

    cout << "Последняя цифра числа " << a << "^(" << b << "^" << c << ") = " << result << endl;

    return 0;
}
