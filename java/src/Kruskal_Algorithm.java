public class Kruskal_Algorithm {

    private static void kruskal(int[][] graph) {
        Graph_Adjacency_List final_graph = new Graph_Adjacency_List(graph.length);
        Disjoint_Set set = new Disjoint_Set(graph.length);
        for (int i = 0; i < graph.length; i++)
            set.make_set(i);
        int u = 0, v = 1, min, edge_count = 0;
        while (edge_count < graph.length - 1) {
            min = Integer.MAX_VALUE;
            for (int i = 0; i < graph.length; i++) {
                for (int j = 0; j < graph.length; j++) {
                    if (set.find_set(i) != set.find_set(j) && graph[i][j] < min) {
                        min = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
            set.Union(u, v);
            edge_count = edge_count + 1;
            final_graph.insert_edge(u, v);
            final_graph.insert_edge(v, u);
        }
        final_graph.pretty_print();
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

        kruskal(graph);
    }
}
