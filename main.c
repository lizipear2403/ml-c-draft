#include <assert.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
  KWords *res = (KWords *)malloc(sizeof(sizeof(KWords) * 1));
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

int main(int argc, char *argv[]) {

  printf("\033[31maaaaa\033[0m");
  char *words[] = {"is", "a"};
  StringTable posWords = {words, 2};
  genCheckTable(posWords);
  // printCheck(posWords, table);
  // table[BKDRHash("with")] = 1;
  // printf("table[%d]=%d\n", BKDRHash("with"), table[BKDRHash("with")]);
  // printf("Hello, MechineLearning!\n");
  return EXIT_SUCCESS;
}
