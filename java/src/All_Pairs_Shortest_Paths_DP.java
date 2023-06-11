import java.util.*;

public class All_Pairs_Shortest_Paths_DP {
    private static int[][] extend_shortest_paths(int[][] L, int[][] w) {
        int n = L.length;
        int[][] temp = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                temp[i][j] = 1000;
                for (int k = 0; k < n; k++)
                    temp[i][j] = Math.min(temp[i][j], L[i][k] + w[k][j]);
            }
        return temp;
    }

    private static void print_paths(int[][] L) {
        System.out.println("Final Matrix");
        for (int[] row : L)
            System.out.println(Arrays.toString(row));
    }

    private static void fast_all_pairs_shortest_paths(int[][] w) {
        int n = w.length;
        int[][] L = w;
        for (int m = 1; m < n - 1; m++)
            L = extend_shortest_paths(L, L);
        print_paths(L);
    }

    private static void slow_all_pairs_shortest_paths(int[][] w) {
        int n = w.length;
        int[][] L = w;
        for (int m = 1; m < n - 1; m++)
            L = extend_shortest_paths(L, w);
        print_paths(L);
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

        System.out.println("Runs in O(n^4)");
        slow_all_pairs_shortest_paths(w);
        System.out.println("\nRuns in O((n^3)log(n))");
        fast_all_pairs_shortest_paths(w);
    }
}
