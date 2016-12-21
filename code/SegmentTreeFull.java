/******************************************************************************
 * Compilation:  javac SegmentTree.java
 * Execution:    java SegmentTree
 * <p/>
 * A segment tree data structure.
 ******************************************************************************/

import java.util.Arrays;

class SegmentTree {

    private Node[] heap;
    private int[] array;
    private int size;

    public SegmentTree(int[] array) {
        this.array = Arrays.copyOf(array, array.length);
        //The max size of this array is about 2 * 2 log2(n) + 1
        size = (int) (2 * Math.pow(2.0, Math.floor((Math.log((double) array.length) / Math.log(2.0)) + 1)));
        heap = new Node[size];
        build(1, 0, array.length);
    }


    public int size() {
        return array.length;
    }

    //Initialize the Nodes of the Segment tree
    private void build(int v, int from, int size) {
        heap[v] = new Node();
        heap[v].from = from;
        heap[v].to = from + size - 1;

        if (size == 1) {
            heap[v].sum = array[from];
            heap[v].min = array[from];
            heap[v].minId = from;
        } else {
            //Build childs
            build(2 * v, from, size / 2);
            build(2 * v + 1, from + size / 2, size - size / 2);

            heap[v].sum = heap[2 * v].sum + heap[2 * v + 1].sum;
            heap[v].min = Math.min(heap[2 * v].min, heap[2 * v + 1].min); //min = min of the children
            heap[v].minId = (heap[2 * v].min < heap[2 * v + 1].min ? heap[2 * v].minId : heap[2 * v + 1].minId);
        }
    }

    public int rsq(int from, int to) {
        return rsq(1, from, to);
    }

    private int rsq(int v, int from, int to) {
        Node n = heap[v];

        //If you did a range update that contained this node, you can infer the Sum without going down the tree
        if (n.pendingVal != null && contains(n.from, n.to, from, to)) {
            return (to - from + 1) * n.pendingVal;
        }

        if (contains(from, to, n.from, n.to)) {
            return heap[v].sum;
        }

        if (intersects(from, to, n.from, n.to)) {
            propagate(v);
            int leftSum = rsq(2 * v, from, to);
            int rightSum = rsq(2 * v + 1, from, to);

            return leftSum + rightSum;
        }

        return 0;
    }

    public int rMinQ(int from, int to) {
        return rMinQ(1, from, to);
    }

    private int rMinQ(int v, int from, int to) {
        Node n = heap[v];


        //If you did a range update that contained this node, you can infer the Min value without going down the tree
        if (n.pendingVal != null && contains(n.from, n.to, from, to)) {
            return n.pendingVal;
        }

        if (contains(from, to, n.from, n.to)) {
            return heap[v].min;
        }

        if (intersects(from, to, n.from, n.to)) {
            propagate(v);
            int leftMin = rMinQ(2 * v, from, to);
            int rightMin = rMinQ(2 * v + 1, from, to);

            return Math.min(leftMin, rightMin);
        }

        return Integer.MAX_VALUE;
    }

    public int rMinIdQ(int from, int to) {
        return rMinIdQ(1, from, to);
    }

    private int rMinIdQ(int v, int from, int to) {
        Node n = heap[v];

        //If you did a range update that contained this node, you can infer the Min value without going down the tree
        if (n.pendingVal != null && contains(n.from, n.to, from, to)) {
            return n.pendingVal;
        }

        if (contains(from, to, n.from, n.to)) {
            return heap[v].minId;
        }

        if (intersects(from, to, n.from, n.to)) {
            propagate(v);
            int leftMinId = rMinIdQ(2 * v, from, to);
            int rightMinId = rMinIdQ(2 * v + 1, from, to);
            if (leftMinId == Integer.MAX_VALUE) return rightMinId;
            if (rightMinId == Integer.MAX_VALUE) return leftMinId;

            return (array[leftMinId] < array[rightMinId] ? leftMinId : rightMinId);
        }

        return Integer.MAX_VALUE;
    }

    public void update(int from, int to, int value) {
        update(1, from, to, value);
    }

    private void update(int v, int from, int to, int value) {
        //The Node of the heap tree represents a range of the array with bounds: [n.from, n.to]
        Node n = heap[v];

        if (contains(from, to, n.from, n.to)) {
            change(n, value);
        }

        if (n.size() == 1) return;

        if (intersects(from, to, n.from, n.to)) {
            propagate(v);

            update(2 * v, from, to, value);
            update(2 * v + 1, from, to, value);

            n.sum = heap[2 * v].sum + heap[2 * v + 1].sum;
            n.min = Math.min(heap[2 * v].min, heap[2 * v + 1].min);
            n.minId = (heap[2 * v].min < heap[2 * v + 1].min ? heap[2 * v].minId : heap[2 * v + 1].minId);
        }
    }

    //Propagate temporal values to children
    private void propagate(int v) {
        Node n = heap[v];

        if (n.pendingVal != null) {
            change(heap[2 * v], n.pendingVal);
            change(heap[2 * v + 1], n.pendingVal);
            n.pendingVal = null; //unset the pending propagation value
        }
    }

    //Save the temporal values that will be propagated lazily
    private void change(Node n, int value) {
        n.pendingVal = value;
        n.sum = n.size() * value;
        n.min = value;
        n.minId = n.from;
        array[n.from] = value;
    }

    //Test if the range1 contains range2
    private boolean contains(int from1, int to1, int from2, int to2) {
        return from2 >= from1 && to2 <= to1;
    }

    //check inclusive intersection, test if range1[from1, to1] intersects range2[from2, to2]
    private boolean intersects(int from1, int to1, int from2, int to2) {
        return from1 <= from2 && to1 >= from2   //  (.[..)..] or (.[...]..)
                || from1 >= from2 && from1 <= to2; // [.(..]..) or [..(..)..
    }

    //The Node class represents a partition range of the array.
    static class Node {
        int sum;
        int min;
        int minId;
        //Here We store the value that will be propagated lazily
        Integer pendingVal = null;
        int from;
        int to;

        int size() {
            return to - from + 1;
        }

    }

}

public class Main {
    public static void main(String[] args) {
        int[] a = new int[]{2, 3, 5, 1, 8, 4, 10};

        SegmentTree segmentTree = new SegmentTree(a);
        System.out.println(segmentTree.rsq(1, 4));
        System.out.println(segmentTree.rMinQ(1, 4));
        System.out.println(segmentTree.rMinIdQ(1, 4));

        segmentTree.update(3,3,4);
        System.out.println(segmentTree.rsq(1, 4));
        System.out.println(segmentTree.rMinQ(1, 4));
        System.out.println(segmentTree.rMinIdQ(1, 4));
    }
}
