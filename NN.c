#include <assert.h>
#include <stddef.h>
#include <time.h>
#define NN_IM
#include "NN.h"
#include <stdio.h>
#include <stdlib.h>

float trainData[] = {0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0};

typedef struct {
  size_t n;
  Mat *m;
} Model;

// Model .n = 3 k + 1
// fst x
// snd w1 b1 a1

float forward(Model m, float x1, float x2) {
  MAT_AT(m.m[0], 0, 0) = x1;
  MAT_AT(m.m[0], 0, 1) = x2;
  matDot(m.m[3], m.m[0], m.m[1]);
  matSum(m.m[3], m.m[3], m.m[2]);
  mapMat(m.m[3], sigmoid);

  matDot(m.m[6], m.m[3], m.m[4]);
  matSum(m.m[6], m.m[6], m.m[5]);
  mapMat(m.m[6], sigmoid);

  return MAT_AT(m.m[6], 0, 0);
}

float loss(Model m, Mat data) {
  float res = 0.0f;
  for (size_t i = 0; i < data.row; i++) {
    float c =
        forward(m, MAT_AT(data, i, 0), MAT_AT(data, i, 1)) - MAT_AT(data, i, 2);
    res += c * c;
  }
  return res;
}

Model diff(Model m, Mat data) {

  Mat x = allocMat(1, 2);
  Mat dw1 = allocMat(2, 2);
  Mat dw2 = allocMat(2, 1);
  Mat db1 = allocMat(1, 2);
  Mat db2 = allocMat(1, 1);
  Mat dl1 = allocMat(1, 2);
  Mat dl2 = allocMat(1, 1);
  Mat m1[] = {x, dw1, db1, dl1, dw2, db2, dl2};
  Model dm = {.m = m1, .n = 7};

  float eps = 1e-3;

  float cost = loss(m, data);

  for (size_t t = 0; t < 7; t++) {

    for (size_t i = 0; i < m.m[t].row; i++) {
      for (size_t j = 0; j < m.m[t].col; j++) {
        MAT_AT(m.m[t], i, j) -= eps;
        MAT_AT(dm.m[t], i, j) = (loss(m, data) - cost) / (-eps);
        MAT_AT(m.m[t], i, j) += eps;
      }
    }
  }
  return dm;
}

void train(Model m, Mat data) {
  float rate = 1e-3;

  Model dm = diff(m, data);

  for (size_t t = 0; t < 7; t++) {
    for (size_t i = 0; i < m.m[t].row; i++) {
      for (size_t j = 0; j < m.m[t].col; j++) {
        MAT_AT(m.m[t], i, j) -= rate * MAT_AT(dm.m[t], i, j);
      }
    }
  }
}

int main(void) {

  Mat data = allocMat(4, 3);
  data.es = trainData;

  Mat x = allocMat(1, 2);

  Mat w1 = allocMat(2, 2);
  Mat w2 = allocMat(2, 1);
  Mat b1 = allocMat(1, 2);
  Mat b2 = allocMat(1, 1);
  Mat l1 = allocMat(1, 2);
  Mat l2 = allocMat(1, 1);

  randMat(w1);
  randMat(w2);
  randMat(b1);
  randMat(b2);

  PRINT_MAT(w1);

  Mat m1[] = {x, w1, b1, l1, w2, b2, l2};
  Model m = {.n = 7, .m = m1};
  // Mat W = allocMat(size_t row, size_t col);
  PRINT_MAT(data);

  printf("loss = %f \n ", loss(m, data));

  line();

  for (size_t i = 0; i < 1000000; i++) {
    train(m, data);
  }

  printf("loss = %f \n ", loss(m, data));

  line();
  for (size_t i = 0; i < 2; i++) {

    for (size_t j = 0; j < 2; j++) {
      printf("%zu xor %zu = %f \n", i, j, forward(m, i, j));
    }
  }

  //
  //
  // PRINT_MAT(diff(m, data).b1);
  printf("Hello, Machine Learning World !\n");

  return EXIT_SUCCESS;
}
