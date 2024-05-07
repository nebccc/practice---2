import java.util.Scanner;
import java.util.Vector;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long y = scanner.nextLong();
        long p = scanner.nextLong();

        // Using Fermat's theorem for checking
        if (powMod(n, p - 1, p) != 1) {
            System.out.println("Fermat's theorem does not hold for the given n and p.");
            System.out.println("a^x mod p = " + powMod(n, y, p));
        } else {
            System.out.println("Fermat's theorem holds for the given n and p = " + powMod(n, y, p));
            System.out.println("Fermat's theorem holds for the given n and p = " + powModLog(n, y, p));
        }
    }

    public static long f(long x, long y, long n, long r) {
        if (y == 0) return r;
        if ((y & 0x01) == 1) return f((x * x) % n, y >> 1, n, (r * x) % n);
        return f((x * x) % n, y >> 1, n, r);
    }

    public static long powMod(long x, long y, long n) {
        return f(x, y, n, 1);
    }

    public static long powModLog(long a, long x, long p) {
        long t = (long) (Math.log(x) / Math.log(2));

        long result = 1;
        Vector<Long> xi = new Vector<>();

        for (long i = 0; i <= t; i++) {
            xi.add(x % 2);
            x /= 2;
        }

        a %= p;
        for (long i = 0; i <= t; i++) {
            if (xi.get((int) i) != 0) {
                for (long j = 0; j < Math.pow(2, i); j++) {
                    result *= a;
                    result %= p;
                }
            }
        }
        return result;
    }
}
