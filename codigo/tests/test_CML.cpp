#include <gtest/gtest.h>

#include "../src/code/CML.h"

#define EPSILON 0.000001

TEST(tests_CML, test_simple) {
	std::vector<std::vector<double> > A =
		{{ 0,  4,  7,  1},
		{ 5, 10,  0,  5},
		{ 3,  2,  5,  0},
		{ 0,  0,  5,  5},
		{ 1,  2,  0,  3}};
	std::vector<double> b = {40, 73, 54, 32, 20};

	Config config;

	std::vector<std::vector<unsigned int> > x = reconstructImage(b, A, A[0].size(), "NULL", config);

	ASSERT_EQ(x.size(), 2);
	ASSERT_EQ(x[0].size(), 2);
	ASSERT_EQ(x[1].size(), 2);

	// Resultados obtenidos con numpy
	EXPECT_EQ(x[0][0], 9);
	EXPECT_EQ(x[0][1], 1);
	EXPECT_EQ(x[1][0], 4);
	EXPECT_EQ(x[1][1], 2);
}
