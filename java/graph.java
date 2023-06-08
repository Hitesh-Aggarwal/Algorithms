public class graph {
  public class vertex {
    int i;
    int w;
    vertex next;
  }
  public vertex[] list;
  public graph(int n){
    list = new vertex[n];
    for(int i=0; i<n; i++){
      list[i].i = i;
      list[i].w = 0;
      list[i].next = null;
    }
  }
}
