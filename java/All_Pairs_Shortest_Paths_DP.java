import java.util.*;
public class All_Pairs_Shortest_Paths_DP {
  private static void extend_shortest_paths(int[][] L, int[][] w) {
    int n = L.length;
    // this creates a copy of arrays.
    int[][] temp = Arrays.stream(L).map(int[]::clone).toArray(int[][]::new);
    int[][] W = Arrays.stream(w).map(int[]::clone).toArray(int[][]::new);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        L[i][j] = 1000;
        for (int k = 0; k < n; k++)
          L[i][j] = Math.min(L[i][j], temp[i][k] + W[k][j]);
      }
  }

  private static void print_paths(int[][] L) {
    int n = L.length;
    System.out.println("Final Matrix");
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        System.out.print(L[i][j] + "\t");
      System.out.println();
    }
  }

  private static void fast_all_pairs_shortest_paths(int[][] w) {
    int n = w.length;
    int[][] L = Arrays.stream(w).map(int[]::clone).toArray(int[][]::new);
    for (int m = 1; m < n - 1; m++)
      extend_shortest_paths(L, L);
    print_paths(L);
  }

  private static void slow_all_pairs_shortest_paths(int[][] w) {
    int n = w.length;
    int[][] L = Arrays.stream(w).map(int[]::clone).toArray(int[][]::new);
    for (int m = 1; m < n - 1; m++)
      extend_shortest_paths(L, w);
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
