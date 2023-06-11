import java.util.Arrays;

public class Floyd_Warshall {
    private static int[][] transitive_closure(int[][] w) {
        int n = w.length;
        int[][] t_p = new int[n][n];
        int[][] t = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                t_p[i][j] = (w[i][j] < 1000) ? 1 : 0;

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    t[i][j] = t_p[i][j] | (t[i][k] & t[k][j]);
                }
            }
            t_p = t;
        }
        return t;
    }

    private static int[][] floyd_warshall(int[][] w) {
        int n = w.length;
        int[][] D_k_p = w;
        int[][] D_k = new int[n][n];
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    D_k[i][j] = Math.min(D_k_p[i][j], D_k_p[i][k] + D_k_p[k][j]);
                }
            }
            D_k_p = D_k;
        }
        return D_k;
    }

    public static void main(String[] args) {
        int n = 5;
        int[][] w = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j)
                    w[i][j] = 1000;
                else
                    w[i][j] = 0;
            }
        }

        w[0][1] = 3;
        w[0][2] = 8;
        w[0][4] = -4;
        w[1][3] = 1;
        w[1][4] = 7;
        w[2][1] = 4;
        w[3][0] = 2;
        w[3][2] = -5;
        w[4][3] = 6;

        int[][] f = floyd_warshall(w);
        System.out.println("Shortest Distances:");
        for (int[] row : f)
            System.out.println(Arrays.toString(row));

        int[][] t = transitive_closure(w);
        System.out.println("\nTransitive Enclosure");
        for (int[] row : t)
            System.out.println(Arrays.toString(row));
    }
}
