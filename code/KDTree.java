import java.util.*;

public class KdTreePointQuery {

  public static class Point {
    int x, y;

    public Point(int x, int y) {
      this.x = x;
      this.y = y;
    }
  }

  int[] tx;
  int[] ty;

  public KdTreePointQuery(Point[] points) {
    int n = points.length;
    tx = new int[n];
    ty = new int[n];
    build(0, n, true, points);
  }

  void build(int low, int high, boolean divX, Point[] points) {
    if (low >= high)
      return;
    int mid = (low + high) >> > 1;
    nth_element(points, low, high, mid, divX);

    tx[mid] = points[mid].x;
    ty[mid] = points[mid].y;

    build(low, mid, !divX, points);
    build(mid + 1, high, !divX, points);
  }

  static void nth_element(Point[] a, int low, int high, int n, boolean divX) {
    while (true) {
      int k = randomizedPartition(a, low, high, divX);
      if (n < k)
        high = k;
      else if (n > k)
        low = k + 1;
      else
        return;
    }
  }

  static final Random rnd = new Random();

  static int randomizedPartition(Point[] a, int low, int high, boolean divX) {
    swap(a, low + rnd.nextInt(high - low), high - 1);
    int v = divX ? a[high - 1].x : a[high - 1].y;
    int i = low - 1;
    for (int j = low; j < high; j++)
      if (divX ? a[j].x <= v : a[j].y <= v)
        swap(a, ++i, j);
    return i;
  }

  static void swap(Point[] a, int i, int j) {
    Point t = a[i];
    a[i] = a[j];
    a[j] = t;
  }

  long bestDist;
  int bestNode;

  public int findNearestNeighbour(int x, int y) {
    bestDist = Long.MAX_VALUE;
    findNearestNeighbour(0, tx.length, x, y, true);
    return bestNode;
  }

  void findNearestNeighbour(int low, int high, int x, int y, boolean divX) {
    if (low >= high)
      return;
    int mid = (low + high) >> > 1;
    long dx = x - tx[mid];
    long dy = y - ty[mid];
    long dist = dx * dx + dy * dy;
    if (bestDist > dist) {
      bestDist = dist;
      bestNode = mid;
    }
    long delta = divX ? dx : dy;
    long delta2 = delta * delta;

    if (delta <= 0) {
      findNearestNeighbour(low, mid, x, y, !divX);
      if (delta2 < bestDist)
        findNearestNeighbour(mid + 1, high, x, y, !divX);
    }
    else {
      findNearestNeighbour(mid + 1, high, x, y, !divX);
      if (delta2 < bestDist)
        findNearestNeighbour(low, mid, x, y, !divX);
    }
  }


  public static void main(String[] args) {
    Point[] points = new Point[n];
    //fill points
    //build tree
    KdTreePointQuery kdTree = new KdTreePointQuery(points);

    int index = kdTree.findNearestNeighbour(qx, qy);
    Point p = points[index];
  }
}