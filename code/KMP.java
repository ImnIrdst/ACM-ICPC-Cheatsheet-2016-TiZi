public class Kmp {

  public static int[] prefixFunction(String s) {
    int[] p = new int[s.length()];
    int k = 0;
    for (int i = 1; i < s.length(); i++) {
      while (k > 0 && s.charAt(k) != s.charAt(i))
        k = p[k - 1];
      if (s.charAt(k) == s.charAt(i))
        ++k;
      p[i] = k;
    }
    return p;
  }

  public static int kmpMatcher(String s, String pattern) {
    int m = pattern.length();
    if (m == 0)
      return 0;
    int[] p = prefixFunction(pattern);
    for (int i = 0, k = 0; i < s.length(); i++)
      for (; ; k = p[k - 1]) {
        if (pattern.charAt(k) == s.charAt(i)) {
          if (++k == m)
            return i + 1 - m;
          break;
        }
        if (k == 0)
          break;
      }
    return -1;
  }
}


// Competitive Programming KMP
#define MAX_N 100010
char T[MAX_N], P[MAX_N]; // T = text, P = pattern
int b[MAX_N], n, m; // b = back table, n = length of T, m = length of P

void kmpPreprocess() {
  int i = 0, j = -1; b[0] = -1; // call this before calling kmpSearch()
  while (i < m) { // starting values
  while (j >= 0 && P[i] != P[j]) j = b[j]; // pre-process the pattern string P
    i++; j++; // if different, reset j using b
    // if same, advance both pointers
    b[i] = j; // observe i = 8, 9, 10, 11, 12 with j = 0, 1, 2, 3, 4
  } 
}

// in the example of P = "SEVENTY SEVEN" above
void kmpSearch() {
  // this is similar as kmpPreprocess(), but on string T
  int i = 0, j = 0;
  // starting values
  while (i < n) { // search through string T
    while (j >= 0 && T[i] != P[j]) j = b[j]; // if different, reset j using b
    i++; j++;
    if (j == m) { // if same, advance both pointers
      printf("P is found at index %d in T\n", i - j); // a match found when j == m
      j = b[j]; // prepare j for the next possible match
      
    } 
  } 
}