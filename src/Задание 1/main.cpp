#include <iostream>
#include <cmath>

#include <tuple>
#include <vector>
using namespace std;

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r);
int64_t powMod(int64_t x, int64_t y, int64_t n);
int64_t PowModLog(int64_t a, int64_t x, int64_t p);

int main() {
    int64_t n, y, p;
    cin >> n >> y >> p;

    // Использование теоремы Ферма для проверки
    if (powMod(n, p-1, p) != 1) {
        cout << "Теорема Ферма не выполняется для данных n и p." << endl;
        cout << "a^x mod p = " << powMod(n, y, p);
    }

    else{
        cout << "Теорема Ферма выполняется для данных n и p = " << powMod(n, y, p);
        cout << "Теорема Ферма выполняется для данных n и p = " << PowModLog(n, y, p);

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

int64_t PowModLog(int64_t a, int64_t x, int64_t p) {
    int64_t t = log2(x);

    int64_t result = 1;
    vector<int64_t> xi;

    for (int64_t i = 0; i <= t; i++) {
        xi.push_back(x % 2);
        x /= 2;
    }

    a %= p;
    for (int64_t i = 0; i <= t; i++) {
        if (xi[i]) {
            for (int64_t j = 0; j < pow(2, i); j++) {
                result *= a;
                result %= p;
            }
        }
    }
    return result;
}