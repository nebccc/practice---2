#include <iostream>
#include <string>
#include <random>
#include <tuple>
#include <cmath>

using namespace std;

pair<long long, long long> init();
bool isPrime(int n);

long long rn(int p);
long long gcd(long long a, long long b);

long long f(long long x, long long y, long long n, long long r);
long long powMod(long long x, long long y, long long n);


long long extendedEuclidean(long long a, long long b, long long& x, long long& y);
long long findModularInverse(long long a, long long m);

string caesar_cipher(const string& message, long long k);
string caesar_decipher(const string& message, long long k_prime);

int main() {
    setlocale(LC_ALL, "ru");

    string message;
    getline(cin, message);

    long long a, p;
    tie(a, p) = init();

    long long x = rn(p);
    long long y;

    while (true) {
        y = rn(p);
        if (gcd(y, p - 1) == 1) {
            break;
        }

    }

    cout << "Абонент А выбирает случайное большое целое число х: " << x << endl;

    long long k = powMod(a, x, p);
    cout << "Абонент А генерирует закрытый ключ k: " << k << endl;

    // Злоумышленник перехватывает открытый ключ от Абонента B и заменяет его своим
    long long interceptedPublicKey = powMod(a, y, p); // Перехваченный открытый ключ
    long long g = 2; // Основание

    // Злоумышленник генерирует случайное значение для использования в качестве закрытого ключа
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(1, p - 1);
    long long attackerPrivateKey = dist(gen);

    long long interceptedPublicKeyReplaced = powMod(g, attackerPrivateKey, p); // Заменяем открытый ключ своим
    cout << "Абонент B посылает абоненту А (злоумышленнику): " << interceptedPublicKeyReplaced << endl;

    long long X = powMod(interceptedPublicKeyReplaced, x, p);
    cout << "Абонент А посылает абоненту B (злоумышленнику): " << X << endl;

    long long z = findModularInverse(attackerPrivateKey, p - 1);
    cout << "Абонент B вычисляет z: " << z << endl;

    long long k_prime = powMod(X, z, p);
    cout << "Абонент B вычисляет k': " << k_prime << endl;

    // Злоумышленник шифрует сообщение от Абонента А с использованием k'
    string encryptedMessage = caesar_cipher(message, k_prime);
    cout << "Абонент А зашифровывает сообщение: " << encryptedMessage << endl;

    // Злоумышленник дешифрует зашифрованное сообщение с использованием k'
    string decrypted = caesar_decipher(encryptedMessage, k_prime);
    cout << "Расшифрованное сообщение: " << decrypted << endl;

    return 0;
}

pair<long long, long long> init() {
    long long a, p;

    cout << "Введите значения (a) и модуля (p): ";

    while (true) {
        cin >> a >> p;

        if (a < p && p < pow(2, 1024)) {
            if (isPrime(p)) {
                break;
            }

            else {
                cout << "Не подходит под параметры выполнения алгоритма" << endl;
            }
        }

        else {
            cout << "Не подходит под параметры выполнения алгоритма" << endl;
        }
    }

    return make_pair(a, p);
}

bool isPrime(int n) {
    if (n <= 1) return false; // 1 и меньшие числа не являются простыми

    // Проверяем делители от 2 до sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            // Если число делится без остатка, то оно не простое
            return false;
        }
    }

    return true; // Если не нашлось делителей, то число простое
}

long long rn(int p) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(1, p - 1);

    long long num = dist(gen);

    return num;
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long f(long long x, long long y, long long n, long long r) {
    if (y == 0) return r;
    if (y & 0x01) return f((x * x) % n, y >> 1, n, (r * x) % n);
    return f((x * x) % n, y >> 1, n, r);
}

long long powMod(long long x, long long y, long long n) {
    return f(x, y, n, 1);
}

// Расширенный алгоритм Евклида
long long extendedEuclidean(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long gcd = extendedEuclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Функция для нахождения обратного элемента
long long findModularInverse(long long a, long long m) {
    long long x, y;
    long long gcd = extendedEuclidean(a, m, x, y);

    x = (x % m + m) % m;

    return x;
}

string caesar_cipher(const string& message, long long k) {
    string result = "";

    for (char c : message) {
        result += char((c + k) % 256);
    }

    return result;
}

string caesar_decipher(const string& message, long long k_prime) {
    string result = "";

    for (char c : message) {
        result += char((c - k_prime + 256) % 256);
    }

    return result;
}
