#include <iostream>
using namespace std;

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r);
int64_t powMod(int64_t x, int64_t y, int64_t n);

int main() {
    setlocale(LC_ALL, "ru");

    int a, b, c;
    cout << "Введите три числа (a, b, c) для вычисления a^(b^c): ";
    cin >> a >> b >> c;

    int temp = powMod(b, c, 10);  // Вычисляем b^c по модулю 10
    int result = powMod(a, temp, 10);  // Вычисляем a^(b^c) по модулю 10

    cout << "Последняя цифра числа " << a << "^(" << b << "^" << c << ") = " << result << endl;

    return 0;
}

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r) {
    if (y == 0) return r;
    if (y & 0x01) return f((x * x) % n, y >> 1, n, (r * x) % n);
    return f((x * x) % n, y >> 1, n, r);
}

int64_t powMod(int64_t x, int64_t y, int64_t n) {
    return f(x, y, n, 1);
}