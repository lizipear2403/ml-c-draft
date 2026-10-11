#include <assert.h>
#include <linux/limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN (2 << 10)

// Neuro Network
// 最后需要： 对一个线性的文字序列，给出其中不重要的字符的分布

int table[2 << 29];
// fst Ver : 一个查找表
// 一个hash算法
// BKDR 哈希函数
unsigned int BKDRHash(const char *str) {
  unsigned int seed = 131; // 31, 131, 1313, 13131, 131313 等常数
  unsigned int hash = 0;

  while (*str) {
    hash = hash * seed + (*str++);
  }

  return (hash & 0x7FFFFFFF); // 确保返回非负整数
}

// 词列表
struct StringTable {
  char **items;
  size_t len;
};
typedef struct StringTable StringTable;

char buff[MAX_LEN];
// n 维向量 ->

// 产生检查表
int genCheckTable(StringTable words) {
  if (words.items == NULL)
    return EXIT_FAILURE;

  for (size_t i = 0; i < words.len; i++) {
    table[BKDRHash(words.items[i])] = 1;
  }
  return EXIT_SUCCESS;
}

int printCheck(StringTable words, int *table) {
  assert(table != NULL);

  for (size_t i = 0; i < words.len; i++) {

    printf("table[\"%s\"]=%d\n", words.items[i],
           table[BKDRHash(words.items[i])]);
  }
  return EXIT_SUCCESS;
}

struct KWords {
  const char *word;
  float weight;
};
typedef struct KWords KWords;

KWords *preProcess(const char *str, size_t *len) {
  KWords *res = (KWords *)malloc(sizeof(sizeof(KWords) * (*len)));
  return res;
}

// 包含单词的权重信息
// 设计一个打印结构
// 实现一个泛型动态数组？
//      思路：按照偏移量手动对齐
int printSet(KWords *kw, size_t len) {
  assert(kw != NULL);
  return EXIT_SUCCESS;
}

struct Neuron {
  float w1;
  float w2;
  float b;
};
typedef struct Neuron Neuron;

float test_data[][3] = {{1, 1, 0}, {1, 0, 1}, {0, 1, 1}, {0, 0, 0}};
#define data_len (sizeof(test_data) / sizeof(test_data[0]))
float sigmoid(float v) { return (1.0f) / (1 + expf(-v)); }

float getNeuron(Neuron n, float x1, float x2) {
  return sigmoid(n.w1 * x1 + n.w2 * x2 + n.b);
}
float loss_func(Neuron n) {
  float loss = 0.0f;

  for (int i = 0; i < data_len; i++) {
    float y = getNeuron(n, test_data[i][0], test_data[i][1]);

    float d = y - test_data[i][2];
    loss += d * d;
  }

  return loss;
}

float multiLoss(Neuron neu_1, Neuron neu_2, Neuron neu_3) {
  float loss = 0;
  for (int i = 0; i < data_len; i++) {
    float x1 = test_data[i][0];
    float x2 = test_data[i][1];
    float y =
        getNeuron(neu_3, getNeuron(neu_1, x1, x2), getNeuron(neu_2, x1, x2));
    float d = y - test_data[i][2];
    loss += d * d;
  }
  return loss;
}

float multiLayer() {
  Neuron neu_1 = {rand() % 10 / 10.0f, rand() % 10 / 10.0f,
                  rand() % 10 / 10.0f};
  Neuron neu_2 = {rand() % 10 / 10.0f, rand() % 10 / 10.0f,
                  rand() % 10 / 10.0f};
  Neuron neu_3 = {rand() % 10 / 10.0f, rand() % 10 / 10.0f,
                  rand() % 10 / 10.0f};

  int train_count = 2 << 18;
  float rate = 1e-1;
  float eps = 1e0;

  for (int i = 0; i < train_count; i++) {

    float loss = multiLoss(neu_1, neu_2, neu_3);

    Neuron neu_1_w1 = neu_1;
    neu_1_w1.w1 += eps;
    float dn1w1 = multiLoss(neu_1_w1, neu_2, neu_3) - loss;

    Neuron neu_1_w2 = neu_1;
    neu_1_w1.w1 += eps;
    float dn1w2 = multiLoss(neu_1_w2, neu_2, neu_3) - loss;

    Neuron neu_1_b = neu_1;
    neu_1_w1.w1 += eps;
    float dn1b = multiLoss(neu_1_b, neu_2, neu_3) - loss;

    Neuron neu_2_w1 = neu_2;
    neu_1_w1.w1 += eps;
    float dn2w1 = multiLoss(neu_1, neu_2_w1, neu_3) - loss;

    Neuron neu_2_w2 = neu_2;
    neu_1_w1.w1 += eps;
    float dn2w2 = multiLoss(neu_1, neu_2_w2, neu_3) - loss;

    Neuron neu_2_b = neu_2;
    neu_1_w1.w1 += eps;
    float dn2b = multiLoss(neu_1, neu_2_b, neu_3) - loss;

    Neuron neu_3_w1 = neu_3;
    neu_1_w1.w1 += eps;
    float dn3w1 = multiLoss(neu_1, neu_2, neu_3_w1) - loss;

    Neuron neu_3_w2 = neu_3;
    neu_1_w1.w1 += eps;
    float dn3w2 = multiLoss(neu_1, neu_2, neu_3_w2) - loss;

    Neuron neu_3_b = neu_3;
    neu_1_w1.w1 += eps;
    float dn3b = multiLoss(neu_1, neu_2, neu_3_b) - loss;

    neu_3.w1 -= dn3w1 / eps;
    neu_3.w2 -= dn3w2 / eps;
    neu_3.b -= dn3b / eps;

    neu_1.w1 -= dn1w1 / eps;
    neu_1.w2 -= dn1w2 / eps;
    neu_1.b -= dn1b / eps;

    neu_2.w1 -= dn2w1 / eps;
    neu_2.w2 -= dn2w2 / eps;
    neu_2.b -= dn2b / eps;
    printf("loss : %f\n", multiLoss(neu_1, neu_2, neu_3));
  }

  // float y = w1 * getNeuron(neu1, x1, x2) + w2 * getNeuron(neu2, x1, x2) + b;
  return 0.0f;
}

// y1 = w11 * x1 + w12 * x2
//
// y2 = w21 * x1 + w22 * x2
//
// y3 = w31 * y1 + w32 * y2 + b
//     = w31(w11*x1 + w12 * x2) + w32(w21 * x1 + w22 * x2) + b
//

//
// float genSingNeuron(float x1, float x2, float w1, float w2, float b) {
//   float res = sigmoid(w1 * x1 + w2 * x2 + b);
//   return res;
// }

int main(int argc, char *argv[]) {

  srand(time(0));
  // float w1 = rand() % 10 / 10.0f;
  // float w2 = rand() % 10 / 10.0f;
  // float b = rand() % 10 / 10.0f;
  //
  // float eps = 1e-1;
  // float rate = 1e0;
  // // printf(" w = %f , w2 = %f, b = %f  , loss: %f\n", w1, w2, b,
  // //        loss_func(w1, w2, b));
  //
  // int train_counts = 2 << 4;
  //
  // Neuron raw = {w1, w2, b};
  // for (int i = 0; i < train_counts; i++) {
  //   Neuron raw_w1 = {raw.w1 + eps, raw.w2, raw.b};
  //   Neuron raw_w2 = {raw.w1, raw.w2 + eps, raw.b};
  //   Neuron raw_b = {raw.w1, raw.w2, raw.b + eps};
  //
  //   printf("before update : %f\n", loss_func(raw));
  //   float l = loss_func(raw);
  //   float dw1 = loss_func(raw_w1) - l;
  //   float dw2 = loss_func(raw_w2) - l;
  //   float db = loss_func(raw_b) - l;
  //
  //   raw.w1 -= rate * (dw1 / eps);
  //   raw.w2 -= rate * (dw2 / eps);
  //   raw.b -= rate * (db / eps);
  //   printf("update :%f\n", loss_func(raw));
  // };
  //
  // for (int i = 0; i < 2; i++) {
  //   for (int j = 0; j < 2; j++) {
  //
  //     float y = sigmoid(b + w1 * i + w2 * j);
  //     // printf(" %d , %d , %f\n", i, j, y);
  //   }
  // }
  //
  multiLayer();

  return EXIT_SUCCESS;
}
