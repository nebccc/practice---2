#include <iostream>
#include <cmath>
#include <tuple>

using namespace std;

tuple<int64_t, int64_t, int64_t> init();

bool isPrime(int64_t n);

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r);
int64_t powMod(int64_t x, int64_t y, int64_t n);

int main() {
    int64_t n, y, p;
    tie(n, y, p) = init();

    // Использование теоремы Ферма для проверки
    if (powMod(n, p-1, p) != 1) {
        cout << "Ошибка: теорема Ферма не выполняется для данных n и p." << endl;
    } else {
        cout << powMod(n, y, p) << endl;
    }

    return 0;
}

tuple<int64_t, int64_t, int64_t> init() {
    int64_t x, y, p;

    while (true) {
        cout << "Введите любое натуральное число n: ";
        cin >> x;

        cout << "Введите любое натуральное число y (степень): ";
        cin >> y;

        cout << "Введите любое простое число p: ";
        cin >> p;

        if (isPrime(p) && x % p != 0) break;
        else cout << "Пожалуйста, убедитесь, что p простое и n не делится на p." << endl;
    }

    return make_tuple(x, y, p);
}

bool isPrime(int64_t n) {
    if (n <= 1) return false;

    int64_t limit = sqrt(n);
    for (int64_t i = 2; i <= limit; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r) {
    if (y == 0) return r;
    if (y & 0x01) return f((x * x) % n, y >> 1, n, (r * x) % n);
    return f((x * x) % n, y >> 1, n, r);
}

int64_t powMod(int64_t x, int64_t y, int64_t n) {
    return f(x, y, n, 1);
}