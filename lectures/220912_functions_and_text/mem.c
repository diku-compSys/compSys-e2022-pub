#include <stdlib.h>

int memeq(const unsigned char *p1, const unsigned char *p2, int n) {
  for (int i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return 0;
    }
  }
  return 1;
}

const unsigned char* memfind(const unsigned char *haystack, int haystacklen,
                             const unsigned char *needle, int needlelen) {
  for (int i = 0; i < haystacklen-needlelen; i++) {
    if (memeq(haystack+i,needle,needlelen)) {
      return haystack+i;
    }
  }
  return NULL;
}
