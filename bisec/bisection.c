#include "bisection.h"

float Bisection(float (*eq)(float x), float left, float right, float tol){
  
  // printf("%d\n", eq(21));

   if (eq(left)*eq(right) > 0){
     return -1;
   }
   if (eq(left)*eq(right) == 0){
     if (eq(left) == 0){
       return left;
     }
     else if (eq(right) == 0){
       return right;
     }
   }

  float root = (right+left)/2;
  float prev_root = root;
  float err = FLT_MAX;
  // printf("The error is %f\n", err);

  while (err > tol){
    if (eq(root) * eq(left) < 0){
      right = root;
    } else if (eq(root) * eq(left) > 0){
      left = root;
    } else {
      if (eq(root) == 0){
        return root;
      } 
    }

    prev_root = root;
    root = (left+right)/2;

    err = fabs(root-prev_root);
  }
  return root;
}
