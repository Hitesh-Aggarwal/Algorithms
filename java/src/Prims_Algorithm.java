import java.util.*;

public class Prims_Algorithm {
    private static void mst_prims(int[][] graph) {
        int n = graph.length;
        Graph_Adjacency_List G = new Graph_Adjacency_List(n);
        int[] p = new int[n];
        int[] k = new int[n];
        Queue<Integer> pq = new PriorityQueue<>(n, Comparator.comparingInt(a -> k[a]));
        for (int i = 0; i < n; i++) {
            p[i] = -1;
            k[i] = Integer.MAX_VALUE;
        }
        k[0] = 0;
        for (int i = 0; i < n; i++)
            pq.add(i);
        while (!pq.isEmpty()) {
            int u = pq.poll();
            for (int i = 0; i < n; i++) {
                if (u != i && graph[u][i] != Integer.MAX_VALUE && pq.contains(i) && graph[u][i] < k[i]) {
                    p[i] = u;
                    k[i] = graph[u][i];
                    pq.remove(i);
                    pq.add(i);
                }
            }
            if (u > 0) {
                G.insert_edge(p[u], u);
            }
        }
        G.pretty_print();
    }

    public static void main(String[] args) {
        int n = 9;
        int[][] graph = new int[n][n];
        graph[0][1] = 4;
        graph[0][7] = 8;
        graph[1][2] = 8;
        graph[1][7] = 11;
        graph[2][3] = 7;
        graph[2][5] = 4;
        graph[2][8] = 2;
        graph[3][2] = 7;
        graph[3][4] = 9;
        graph[3][5] = 14;
        graph[4][5] = 10;
        graph[5][6] = 2;
        graph[6][7] = 1;
        graph[6][8] = 6;
        graph[7][8] = 7;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i == j)
                    graph[i][j] = 0;
                else if (i > j)
                    graph[i][j] = graph[j][i];
                else if (graph[i][j] == 0)
                    graph[i][j] = Integer.MAX_VALUE;

        mst_prims(graph);
    }
}
