import java.util.*;

public class SegmentTree2D {
  public static int max(int[][] t, int x1, int y1, int x2, int y2) {
    int n = t.length >> 1;
    x1 += n;
    x2 += n;
    int m = t[0].length >> 1;
    y1 += m;
    y2 += m;
    int res = Integer.MIN_VALUE;
    for (int lx = x1, rx = x2; lx <= rx; lx = (lx + 1) >> 1, rx = (rx - 1) >> 1)
      for (int ly = y1, ry = y2; ly <= ry; ly = (ly + 1) >> 1, ry = (ry - 1) >> 1) {
        if ((lx & 1) != 0 && (ly & 1) != 0) res = Math.max(res, t[lx][ly]);
        if ((lx & 1) != 0 && (ry & 1) == 0) res = Math.max(res, t[lx][ry]);
        if ((rx & 1) == 0 && (ly & 1) != 0) res = Math.max(res, t[rx][ly]);
        if ((rx & 1) == 0 && (ry & 1) == 0) res = Math.max(res, t[rx][ry]);
      }
    return res;
  }

  public static void add(int[][] t, int x, int y, int value) {
    x += t.length >> 1;
    y += t[0].length >> 1;
    t[x][y] += value;
    for (int tx = x; tx > 0; tx >>= 1)
      for (int ty = y; ty > 0; ty >>= 1) {
        if (tx > 1) t[tx >> 1][ty] = Math.max(t[tx][ty], t[tx ^ 1][ty]);
        if (ty > 1) t[tx][ty >> 1] = Math.max(t[tx][ty], t[tx][ty ^ 1]);
      }
  }

  public static void main(String[] args) {

    int[][] t = new int[sx * 2][sy * 2];
    add(t, x, y, v);//tree-x-y-value
    int res1 = max(t, x1, y1, x2, y2);//t-[x1,y1]*[x2,y2]
  }
}