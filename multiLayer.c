#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

float rand_float() { return ((float)rand() / RAND_MAX); }

typedef struct Model {
  float and_one[3];
  float and_two[3];
  float or[3];
} Model;

float and_train[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

float or_train[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

float d_train[][3] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

float xor_train[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 1},
    {1, 1, 1},
};

float sigmoid(float v) { return (1.0f) / (1 + expf(-v)); }

float forward(Model m, float x1, float x2) {

  float a = sigmoid(m.and_one[2] + m.and_one[0] * x1 + m.and_one[1] * x2);
  float b = sigmoid(m.and_two[2] + m.and_two[0] * x1 + m.and_two[1] * x2);
  return sigmoid(m.or[2] + m.or[0] * a + m.or[1] * b);
}

float loss(Model m, float train[][3]) {
  float loss = 0;
  for (size_t i = 0; i < 4; i++) {
    float c = forward(m, train[i][0], train[i][1]) - train[i][2];
    loss += c * c;
  }
  return loss;
}

Model diff(Model m, float train[][3]) {
  float eps = 1e-1 + 1e-0 * rand_float();
  Model temp = m;
  Model adj_model;

  for (size_t i = 0; i < 3; i++) {
    m.and_one[i] -= eps;
    adj_model.and_one[i] = (loss(temp, train) - loss(m, train)) / eps;
    m = temp;
  }

  for (size_t i = 0; i < 3; i++) {
    m.and_two[i] -= eps;
    adj_model.and_two[i] = (loss(temp, train) - loss(m, train)) / eps;
    m = temp;
  }
  for (size_t i = 0; i < 3; i++) {
    m.or[i] -= eps;
    adj_model.or[i] = (loss(temp, train) - loss(m, train)) / eps;
    m = temp;
  }
  return adj_model;
}

Model train(Model m, float train[][3], float rate1) {
  // Model new_model = m;
  float rate = rate1;
  for (size_t j = 0; j < 1000000; j++) {
    Model dm = diff(m, train);

    for (size_t i = 0; i < 3; i++) {
      m.and_one[i] -= rate * dm.and_one[i];
    }

    for (size_t i = 0; i < 3; i++) {
      m.and_two[i] -= rate * dm.and_two[i];
    }

    for (size_t i = 0; i < 3; i++) {
      m.or[i] -= rate * dm.or[i];
    }
    // printf("loss : %f\n", loss(m, xor_train));
  }
  return m;
}

void print_Model(Model m) {

  printf(" Model : \n and_one: w1=%f w2=%f b=%f \n and_two: w1=%f w2=%f b=%f\n "
         "or: w1=%f w2=%f b=%f\n",
         m.and_one[0], m.and_one[1], m.and_one[2], m.and_two[0], m.and_two[1],
         m.and_two[2], m.and_two[0], m.or[1], m.or[2]);
}

Model initRandomModel() {
  Model m;
  for (size_t i = 0; i < 3; i++) {
    m.and_one[i] = rand_float();
  }
  for (size_t i = 0; i < 3; i++) {
    m.and_two[i] = rand_float();
  }
  for (size_t i = 0; i < 3; i++) {
    m.or[i] = rand_float();
  }
  return m;
}

typedef float sample[3];

int main() {
  int s = 1792147306;
  printf("seed = %d \n", s);
  srand(s);

  sample *data = d_train;

  Model m = initRandomModel();
  // float *train = or_train;
  // &and_train;
  // printf("loss: %f\n", loss(m, train));
  printf("loss : %f\n", loss(m, data));
  printf("------------------------------------\n");
  // print_Model(diff(m, data));
  // printf("------------------------------------\n");
  Model n = train(m, data, 1e-0);
  print_Model(n);
  printf("loss : %f\n", loss(n, data));

  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 2; j++) {
      printf("%zu xor %zu = %f \n", i, j, forward(n, i, j));
    }
  }

  // printf("hello World\n");

  return EXIT_SUCCESS;
}
