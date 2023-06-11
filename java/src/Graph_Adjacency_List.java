import java.util.Arrays;

public class Graph_Adjacency_List {
    public static class vertex {
        public int i;
        public int w;
        public vertex next;

        public vertex(int i, int w) {
            this.i = i;
            this.w = w;
            this.next = null;
        }

        public vertex(int i) {
            this(i, 1);
        }
    }

    public vertex[] list;

    public Graph_Adjacency_List(int n) {
        list = new vertex[n];
    }

    public void insert_edge(int u, int v) {
        insert_edge(u, v, 1);
    }

    public void insert_edge(int u, int v, int w) {
        vertex x = new vertex(v, w);
        if (list[u] != null)
            x.next = list[u];

        list[u] = x;
    }

    public boolean is_edge(int u, int v) {
        if (list[u] == null)
            return false;
        vertex x = list[u];
        while (x != null) {
            if (x.i == v)
                return true;
            x = x.next;
        }
        return false;
    }

    private void dfs_visit(int u, char[] color, int indent) {
        color[u] = 'G';
        for (int i = 0; i < indent; i++)
            System.out.print("    |");
        System.out.print("----");
        System.out.println(u);
        vertex x = list[u];
        while (x != null) {
            if (color[x.i] == 'W')
                dfs_visit(x.i, color, indent + 1);
            x = x.next;
        }
        color[u] = 'B';
    }

    public void pretty_print() {
        char[] color = new char[list.length];
        Arrays.fill(color, 'W');
        for (int i = 0; i < list.length; i++)
            if (color[i] == 'W')
                dfs_visit(i, color, 0);
    }
}
