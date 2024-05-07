import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter three numbers (a, b, c) to compute a^(b^c): ");
        int a = scanner.nextInt();
        int b = scanner.nextInt();
        int c = scanner.nextInt();

        int temp = powMod(b, c, 10);  // Compute b^c modulo 10
        int result = powMod(a, temp, 10);  // Compute a^(b^c) modulo 10

        System.out.println("The last digit of " + a + "^(" + b + "^" + c + ") = " + result);
    }

    public static int f(int x, int y, int n, int r) {
        if (y == 0) return r;
        if ((y & 0x01) == 1) return f((x * x) % n, y >> 1, n, (r * x) % n);
        return f((x * x) % n, y >> 1, n, r);
    }

    public static int powMod(int x, int y, int n) {
        return f(x, y, n, 1);
    }
}
