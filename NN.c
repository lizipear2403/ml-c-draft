#define NN_IM
#include "NN.h"
#include <stdio.h>
#include <stdlib.h>

float addOne(float v) { return v + 1.0f; }

int main(void) {
  // srand(time(0));
  Mat X1 = allocMat(1, 2);
  // setX;
  Mat W = allocMat(2, 2);
  Mat B = allocMat(1, 2);

  Mat fstLayer = allocMat(1, 2);
  Mat AfstLayer = allocMat(1, 2);
  printf("Hello, Machine Learning World !\n");
  return EXIT_SUCCESS;
}
