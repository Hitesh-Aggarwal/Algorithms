import java.util.*;

public class Breadth_First_Search {
    private static void BFS(Graph_Adjacency_List graph, int s) {
        int n = graph.list.length;
        char[] color = new char[n];
        int[] dist = new int[n];
        int[] predecessor = new int[n];
        Queue<Integer> Q = new ArrayDeque<>(n);
        for (int i = 0; i < n; i++) {
            color[i] = 'W';
            dist[i] = Integer.MAX_VALUE;
            predecessor[i] = -1;
        }
        color[s] = 'G';
        dist[s] = 0;
        Q.add(s);
        System.out.println("Node\tPredecessor\tDistanceFromSource");
        while (!Q.isEmpty()) {
            int u = Q.poll();
            Graph_Adjacency_List.vertex p = graph.list[u];
            while (p != null) {
                if (color[p.i] == 'W') {
                    color[p.i] = 'G';
                    dist[p.i] = dist[u] + 1;
                    predecessor[p.i] = u;
                    Q.add(p.i);
                }
                p = p.next;
            }
            color[u] = 'B';
            System.out.println(u + "\t" + predecessor[u] + "\t\t" + dist[u]);
        }
    }

    public static void main(String[] args) {
        int n = 8;
        Graph_Adjacency_List graph = new Graph_Adjacency_List(n);
        graph.insert_edge(0, 1);
        graph.insert_edge(0, 4);
        graph.insert_edge(1, 0);
        graph.insert_edge(1, 5);
        graph.insert_edge(2, 3);
        graph.insert_edge(2, 5);
        graph.insert_edge(2, 6);
        graph.insert_edge(3, 2);
        graph.insert_edge(3, 6);
        graph.insert_edge(3, 7);
        graph.insert_edge(4, 0);
        graph.insert_edge(5, 1);
        graph.insert_edge(5, 2);
        graph.insert_edge(5, 6);
        graph.insert_edge(6, 7);
        graph.insert_edge(6, 5);
        graph.insert_edge(6, 2);
        graph.insert_edge(6, 3);
        graph.insert_edge(7, 3);
        graph.insert_edge(7, 6);
        BFS(graph, 0);
    }
}
