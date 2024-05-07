import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the message:");
        String message = scanner.nextLine();

        long a, p;
        Pair<Long, Long> pair = init();
        a = pair.getFirst();
        p = pair.getSecond();

        long x = rn(p);
        long y;

        while (true) {
            y = rn(p);
            if (gcd(y, p - 1) == 1) {
                break;
            }
        }

        System.out.println("Participant A chooses a random large integer x: " + x);

        long k = powMod(a, x, p);
        System.out.println("Participant A generates the private key k: " + k);

        String encrypted = caesarCipher(message, k);
        System.out.println("Participant A encrypts the message: " + encrypted);
        System.out.println("Participant B chooses a random large integer y (coprime with p - 1): " + y);

        long Y = powMod(a, y, p);
        System.out.println("Participant B sends to participant A: " + Y);

        long X = powMod(Y, x, p);
        System.out.println("Participant A sends to participant B: " + X);

        long z = findModularInverse(y, p - 1);
        System.out.println("Participant B computes z: " + z);

        long k_prime = powMod(X, z, p);
        System.out.println("Participant B computes k': " + k_prime);

        if (k == k_prime) {
            System.out.println("Private key k = k'");
            String decrypted = caesarDecipher(encrypted, k_prime);
            System.out.println("Decrypted message: " + decrypted);
        } else {
            System.out.println("Private key k != k'");
        }
    }

    public static Pair<Long, Long> init() {
        long a, p;
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter values (a) and modulus (p): ");

        while (true) {
            a = scanner.nextLong();
            p = scanner.nextLong();

            if (a < p && p < Math.pow(2, 1024)) {
                if (isPrime((int) p)) {
                    break;
                } else {
                    System.out.println("Does not fit the parameters for algorithm execution");
                }
            } else {
                System.out.println("Does not fit the parameters for algorithm execution");
            }
        }

        return new Pair<>(a, p);
    }

    public static boolean isPrime(int n) {
        if (n <= 1) return false;

        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }

    public static long rn(long p) {
        long num = (long) (Math.random() * (p - 1)) + 1;
        return num;
    }

    public static long gcd(long a, long b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    public static long f(long x, long y, long n, long r) {
        if (y == 0) return r;
        if ((y & 0x01) == 1) return f((x * x) % n, y >> 1, n, (r * x) % n);
        return f((x * x) % n, y >> 1, n, r);
    }

    public static long powMod(long x, long y, long n) {
        return f(x, y, n, 1);
    }

    public static long extendedEuclidean(long a, long b, long[] x, long[] y) {
        if (b == 0) {
            x[0] = 1;
            y[0] = 0;
            return a;
        }

        long[] x1 = new long[1];
        long[] y1 = new long[1];
        long gcd = extendedEuclidean(b, a % b, x1, y1);

        x[0] = y1[0];
        y[0] = x1[0] - (a / b) * y1[0];

        return gcd;
    }

    public static long findModularInverse(long a, long m) {
        long[] x = new long[1];
        long[] y = new long[1];
        long gcd = extendedEuclidean(a, m, x, y);

        x[0] = (x[0] % m + m) % m;

        return x[0];
    }

    public static String caesarCipher(String message, long k) {
        StringBuilder result = new StringBuilder();

        for (char c : message.toCharArray()) {
            result.append((char) ((c + k) % 256));
        }


        return result.toString();
    }

    public static String caesarDecipher(String message, long k_prime) {
        StringBuilder result = new StringBuilder();

        for (char c : message.toCharArray()) {
            result.append((char) ((c - k_prime + 256) % 256));
        }

        return result.toString();
    }
}

class Pair<T, U> {
    private final T first;
    private final U second;

    public Pair(T first, U second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public U getSecond() {
        return second;
    }
}