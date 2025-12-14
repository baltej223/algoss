#include "bisection.h"

float MathFunction(float x){
  return x*x*x - 3 * x*x - 43 * x +32;
}

int main(){
  float root = Bisection(&MathFunction, -1000, 1000, 0.0000001);
  printf("root=%f", root);
}
