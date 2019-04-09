#include <gtest/gtest.h>

#include "../src/code/tools/Lineal.h"

#define EPSILON 0.000001

TEST(tests_Lineal, test_identidad) {
	std::vector<std::vector<double> > A =
		{{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};

  std::vector<double> v = {1,2,3,4,5,6,7,8,9,10,11,12,13};

  std::vector<double> res = A * v;

	// Resultados obtenidos con numpy
	for (int i = 0; i < res.size(); i++) {
    EXPECT_NEAR(res[i], v[i], EPSILON);
  }
}

TEST(tests_Lineal, test_stress) {
	std::vector<std::vector<double> > A(20000);

  for (auto &e : A) {
    auto i = &e - &A[0];
    e = std::vector<double>(20000, i);
  }

  std::vector<double> v(20000, 1.0);

  std::vector<double> res = A * v;

	// Resultados obtenidos con numpy
	for (int i = 0; i < res.size(); i++) {
    EXPECT_NEAR(res[i], i * 20000.0, EPSILON);
  }
}

TEST(tests_Lineal, test_normal) {
	std::vector<std::vector<double> > A(20000);

  for (auto &e : A) {
    auto i = &e - &A[0];
    e = std::vector<double>(20000, i);
  }

  std::vector<double> v(20000, 1.0);

  std::vector<double> res = mul(A,v);

	// Resultados obtenidos con numpy
	for (int i = 0; i < res.size(); i++) {
    EXPECT_NEAR(res[i], i * 20000.0, EPSILON);
  }
}
