#include <iostream>
#include <tuple>

using namespace std;

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r);
int64_t powMod(int64_t x, int64_t y, int64_t n);

int main() {
    int64_t n, y, p;
    cin >> n >> y >> p;

    // Использование теоремы Ферма для проверки
    if (powMod(n, p-1, p) != 1) {
        cout << "Теорема Ферма не выполняется для данных n и p." << endl;
        cout << "a^x mod p = " << powMod(n, y, p);
    }

    else{
        cout << "Теорема Ферма выполняется для данных n и p = " << powMod(n, y, p - 1);
    }

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