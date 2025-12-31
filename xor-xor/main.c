#include <stdio.h>
#include <string.h>

int main(){
  char a[] = "Baltej Singh";
  int key = 21;
  char b[strlen(a)+1];

  for (int i=0; i<strlen(a); i++){
    int ch = (int) a[i];
    b[i] = ch^key;
  }
  b[strlen(a)] = '\0';

  printf("%s", b);
}
