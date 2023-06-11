import java.util.*;

public class Dijkstra_Algorithm {

    private static void relax(int u, int v, int w, int[] d, int[] p, PriorityQueue<Integer> q) {
        if (d[u] == Integer.MAX_VALUE)
            return;
        if (d[v] > d[u] + w) {
            d[v] = d[u] + w;
            q.remove(v);
            q.add(v);
            p[v] = u;
        }
    }

    private static void dijkstra(Graph_Adjacency_List G, int s) {
        int n = G.list.length;
        int[] d = new int[n];
        int[] p = new int[n];
        Graph_Adjacency_List finalG = new Graph_Adjacency_List(n);
        for (int i = 0; i < n; i++) {
            d[i] = Integer.MAX_VALUE;
            p[i] = -1;
        }
        d[s] = 0;
        PriorityQueue<Integer> pq = new PriorityQueue<>(n, Comparator.comparingInt(a -> d[a]));
        for (int i = 0; i < n; i++)
            pq.add(i);
        while (!pq.isEmpty()) {
            int u = pq.poll();
            Graph_Adjacency_List.vertex v = G.list[u];
            while (v != null) {
                relax(u, v.i, v.w, d, p, pq);
                v = v.next;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i == s)
                continue;
            finalG.insert_edge(p[i], i);
        }
        finalG.pretty_print();
    }

    public static void main(String[] args) {
        int n = 5;
        Graph_Adjacency_List G = new Graph_Adjacency_List(n);
        G.insert_edge(0, 4, 5);
        G.insert_edge(0, 1, 10);
        G.insert_edge(1, 4, 2);
        G.insert_edge(1, 2, 1);
        G.insert_edge(2, 3, 4);
        G.insert_edge(3, 2, 6);
        G.insert_edge(3, 0, 7);
        G.insert_edge(4, 3, 2);
        G.insert_edge(4, 2, 9);
        G.insert_edge(4, 1, 3);
        dijkstra(G, 0);
    }
}
