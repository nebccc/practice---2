import java.util.Scanner;

public class Main {
    // Extended Euclidean algorithm
    public static int extendedEuclidean(int a, int b, int[] x, int[] y) {
        if (b == 0) {
            x[0] = 1;
            y[0] = 0;
            return a;
        }

        int[] x1 = new int[1];
        int[] y1 = new int[1];
        int gcd = extendedEuclidean(b, a % b, x1, y1);

        x[0] = y1[0];
        y[0] = x1[0] - (a / b) * y1[0];

        return gcd;
    }

    // Function to find the modular inverse
    public static int[] findModularInverse(int a, int m) {
        int[] x = new int[1];
        int[] y = new int[1];
        int gcd = extendedEuclidean(a, m, x, y);
        int[] result = new int[2];

        if (gcd != 1) {
            System.out.println("Modular inverse does not exist!");
            result[0] = gcd;
            result[1] = x[0];
        } else {
            // Normalize x to a positive value
            x[0] = (x[0] % m + m) % m;
            result[0] = gcd;
            result[1] = x[0];
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter two numbers to find the modular inverse:");
        int a = scanner.nextInt();
        int b = scanner.nextInt();

        int[] res = findModularInverse(a, b);

        if (res[0] == 1) {
            System.out.println("Modular inverse for " + a + " modulo " + b + " is " + res[1]);
        }

        System.out.println(a + " * " + res[1] + " mod " + b + " = " + (a * res[1]) % b);
    }
}
