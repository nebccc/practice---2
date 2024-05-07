#include <iostream>
using namespace std;

// Расширенный алгоритм Евклида
int extendedEuclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Функция для нахождения обратного элемента
pair<int, int> findModularInverse(int a, int m) {
    int x, y;
    int gcd = extendedEuclidean(a, m, x, y);

    if (gcd != 1) {
        cout << "Обратный элемент не существует!" << endl;
        return make_pair(gcd, x); // Обратного элемента не существует
    }
    else {
        // Нормализация x к положительному значению
        x = (x % m + m) % m;
        return make_pair(gcd, x);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    int a, b;
    cin >> a >> b;
    
    pair<int, int> res = findModularInverse(a, b);

    if (res.first == 1) {
        cout << "Обратный элемент для " << a << " по модулю " << b << " равен " << res.second << endl;
    }

    cout << a << " * " << res.second << " mod" << b << " = " << a * res.second % b << endl;

    return 0;
}