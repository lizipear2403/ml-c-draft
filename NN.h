
#ifndef NN_H
#define NN_H

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
// 矩阵库
//
typedef struct {
  size_t col;
  size_t row;
  float *es;
} Mat;

Mat allocMat(size_t row, size_t col);
void matDot(Mat dst, Mat a, Mat b);
void matSum(Mat dst, Mat a, Mat b);
void print_mat(Mat s);
void randMat(Mat s);
void fillMat(Mat s, float x);
void mapMat(Mat s, float (*func)(float v));

float sigmoid(float x);

float randf();
#endif

#define NN_IM
#ifdef NN_IM

#define MAT_AT(m, i, j) (m).es[(i) * (m).col + (j)]

float randf() { return (rand() / (float)RAND_MAX); }
Mat allocMat(size_t row, size_t col) {
  Mat res = {.col = col, .row = row};
  float *e = (float *)malloc(row * col * (sizeof(*(res.es))));
  res.es = e;
  return res;
}

float sigmoid(float v) { return (1.0f) / (1 + expf(-v)); }

void matDot(Mat dst, Mat a, Mat b) {

  assert(a.col == b.row && a.row == dst.row && b.col == dst.col);

  for (size_t i = 0; i < dst.row; i++) {
    for (size_t j = 0; j < dst.col; j++) {
      float sum = 0;
      for (size_t aj = 0; aj < a.col; aj++) {
        sum += MAT_AT(a, i, aj) * MAT_AT(b, aj, j);
      }
      MAT_AT(dst, i, j) = sum;
    }
  }
}

// map Function to Mat
void mapMat(Mat s, float (*func)(float v)) {
  for (size_t i = 0; i < s.row; i++) {
    for (size_t j = 0; j < s.col; j++) {
      MAT_AT(s, i, j) = func(MAT_AT(s, i, j));
    }
  }
}

// fill x to Mat
void fillMat(Mat s, float x) {
  for (size_t i = 0; i < s.row; i++) {
    for (size_t j = 0; j < s.col; j++) {
      MAT_AT(s, i, j) = x;
    }
  }
}

// randamize the Mat
void randMat(Mat s) {
  for (size_t i = 0; i < s.row; i++) {
    for (size_t j = 0; j < s.col; j++) {
      MAT_AT(s, i, j) = randf();
    }
  }
}

void matSum(Mat dst, Mat a, Mat b) {
  assert(dst.col == a.col && a.col == b.col && dst.row == a.row &&
         a.row == b.row);
  for (size_t i = 0; i < a.row; i++) {
    for (size_t j = 0; j < a.col; j++) {
      MAT_AT(dst, i, j) = MAT_AT(b, i, j) + MAT_AT(a, i, j);
    }
  }
}

void print_mat(Mat s) {
  for (size_t i = 0; i < s.row; i++) {
    for (size_t j = 0; j < s.col; j++) {
      printf("Mat[%zu][%zu]=%.2f  ", i, j, MAT_AT(s, i, j));
    }
    putc('\n', stdout);
  }
}

#endif
