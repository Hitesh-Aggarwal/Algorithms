public class Disjoint_Set {
  private int[] parent;
  private int[] rank;

  public Disjoint_Set(int n) {
    parent = new int[n];
    rank = new int[n];
  }

  private void link(int x, int y) {
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;
    if (rank[x] == rank[y])
      rank[y] = rank[y] + 1;
  }

  public void make_set(int x) {
    parent[x] = x;
    rank[x] = 0;
  }

  public int find_set(int x) {
    if (parent[x] != x)
      parent[x] = find_set(parent[x]);
    return parent[x];
  }

  public void Union(int x, int y) {
    link(find_set(x), find_set(y));
  }
}
