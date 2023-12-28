#include "lib.h"

int _min(int a, int b) {
  return (a < b) ? a : b;
}

int _max(int a, int b) {
  return (a > b) ? a : b;
}

void swap(void* a, void* b, size_t size) {
  void* t = (void*)malloc(size);
  memcpy(t, a, size);
  memcpy(a, b, size);
  memcpy(b, t, size);
  free(t);
}

void bprint(bool b) {
  printf(b ? "True" : "False");
}

bool strIsUnique(char* str) {
  int len = strlen(str);
  // brute force approach
  for (int i = 0; i < len; i++) {
    for (int j = i; j < len; j++) {
      if (str[i] == str[j]) {
        return false;
      }
    }
  }
  return true;
}

bool isPermutation(char* org, char* str) {
  // return true if org == str;
  int len_a = strlen(org);
  int len_b = strlen(str);

  if (len_a != len_b) {
    return false;
  }
  long long hash_a = 1;
  long long hash_b = 1;
  for (int i = 0; i < len_a; i++) {
    hash_a += org[i] + ((org[i] * 3) / 2);
    hash_b += str[i] + ((str[i] * 3) / 2);
  }
  return hash_a == hash_b;
}

char* URLify(char* str) { 
  // replace spaces with %20
  // length => (length + 2) * number of spaces
  int* arr = (int*)calloc(strlen(str), sizeof(int));
  int idx = 0;
  int ptr = 0;
  int len = strlen(str);
  int actlen = 0;
  // mumber of spaces in the string, with offset
  // because of the increase in characters by a factor of 2
  // " " => "%20"
  for (int i = 0; i < len; i++) {
    if (str[i] == ' ') {
      arr[idx] = i + (idx * 2);
      idx++;
    }
  }

  // assign the actual length after URLifying
  actlen = len + (idx * 2);
  char* newstr = (char*)calloc(actlen + 1, sizeof(char));
  idx = 0;

  for (int i = 0; i < actlen; i++) {
    if (arr[idx] == i) {
      newstr[i] = '%';
      newstr[i + 1] = '2';
      newstr[i + 2] = '0';
      i += 2;
      idx++;
      ptr++; 
      // we gotta increment ptr, because at this index,
      // original string had a space
      continue;
    } 
    newstr[i] = str[ptr++];
  }
  free(arr);
  return newstr;
}


bool checkIfStringIsPalindromic(char* str) {
  // check if string can form palindromes
  // there should be only one or zero odd number of characters

  int arr[26] = { 0 };
  int ARR[26] = { 0 };
  int odd = 0;
  int len = strlen(str);
  
  for (int i = 0; i < len; i++) {
    if ('A' <= str[i] && str[i] <= 'Z') {
      ARR[str[i] - 'A'] += 1;
    } else if ('a' <= str[i] && str[i] <= 'z') {
      arr[str[i] - 'a'] += 1;
    } else if (str[i] == ' ') {
      continue;
    } else {
      return false;
    }
  }

  for (int i = 0; i < 26; i++) {
    if ((arr[i] == 1) || (ARR[i] == 1)) {
      odd++;
    }
    if (odd > 1) {
      return false;
    }
  }
  return true;
}

bool oneAway(char* p, char* q) {
  int lp = strlen(p);
  int lq = strlen(q);
  if (abs(lp - lq) > 1) {
    return false;
  }

  int arr[26] = { 0 };
  int minL = _min(lp, lq);
  int matching = 0;

  for (int i = 0; i < minL; i++) {
    arr[p[i] - 'a'] += 1;
    arr[q[i] - 'a'] += 1;
  }

  for (int i = 0; i < 26; i++) {
    if (arr[i] % 2 == 0 && arr[i] > 0) {
      matching += 1;
    }
  }
  return _max(abs(lp - lq), (minL - matching)) <= 1;
}

char* stringCompression(char* str) {
  char* nStr = (char*)calloc(1025, sizeof(char)); // we'll just assume a max string size of 1024
  char buf[64];

  int len = strlen(str);
  int ptr = 0;
  char last = str[0];
  int count = 1;

  for (int i = 1; i < len + 1; i++) {
    if (str[i] != last) {
      nStr[ptr++] = last;
      sprintf(buf, "%d", count);
      strcpy(&nStr[ptr], buf);
      count = 1;
      ptr++;
      last = str[i];
    } else {
      count++;
    }
  }
  nStr[ptr] = '\0';
  return (ptr < len) ? nStr : str;
}

void transpose(int** img, int w, int h) {
  size_t size = sizeof(img[0][0]);
  for (int i = 0; i < w; i++) {
    for (int j = i; j < h; j++) {
      swap(&img[i][j], &img[j][i], size);
    }
  }
}

void zeroMat(int** mat, int w, int h) {
  int row = -1;
  int col = -1;

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (mat[i][j] == 0) {
        mat[i][j] = -1;
      }
    }
  }

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (mat[i][j] == -1) {
        mat[i][j] = 0;
        row = 0;
        col = 0;
        while (row < w) {
          if (mat[row][j] != -1) {
            mat[row][j] = 0;
          }
          row++;
        }
        while (col < h) {
          if (mat[i][col] != -1) {
            mat[i][col] = 0;
          }
          col++;
        }
      }
    }
  }
}

bool isSubString(char* p, char* q) {
  int lp = strlen(p);
  int lq = strlen(q);
  int lr = 2 * lq;

  int matching = 0;
  char* r = (char*)calloc(lr, sizeof(char));
  sprintf(r, "%s%s", q, q);

  int pt = 0;
  int rt = 0;
  
  while (pt < lp && rt < lr) {
    if (p[pt] == r[rt] && p[pt] != ' ') {
      pt++;
      matching = _max(pt, matching);
    } else {
      pt = 0;
    }
    rt++;
  }

  free(r);
  return matching > 0;
}