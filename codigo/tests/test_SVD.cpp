#include <gtest/gtest.h>

#include "../src/code/tools/SVD.h"

#define EPSILON 0.00001

TEST(tests_SVD, test_identidad) {
	std::vector<std::vector<double> > A =
		{{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1}};

	std::vector<std::vector<double> > Ut;
	std::vector<double> Sigma;
	std::vector<std::vector<double> > Vt;

	getSVD(A, Ut, Sigma, Vt, A[0].size());

	ASSERT_EQ(Sigma.size(), 5);

	// Resultados obtenidos con numpy
	EXPECT_NEAR(Sigma[0], 1, EPSILON);
	EXPECT_NEAR(Sigma[1], 1, EPSILON);
	EXPECT_NEAR(Sigma[2], 1, EPSILON);
	EXPECT_NEAR(Sigma[3], 1, EPSILON);
	EXPECT_NEAR(Sigma[4], 1, EPSILON);
}


TEST(tests_SVD, test_diagonal_decreciente) {
	std::vector<std::vector<double> > A =
		{{10.213, 0, 0, 0, 0},
		{0, 8.231, 0, 0, 0},
		{0, 0, 7.4, 0, 0},
		{0, 0, 0, 2.324, 0},
		{0, 0, 0, 0, 0.21312}};

	std::vector<std::vector<double> > Ut;
	std::vector<double> Sigma;
	std::vector<std::vector<double> > Vt;

	getSVD(A, Ut, Sigma, Vt, A[0].size());

	ASSERT_EQ(Sigma.size(), 5);

	EXPECT_NEAR(Sigma[0], 10.213, EPSILON);
	EXPECT_NEAR(Sigma[1], 8.231, EPSILON);
	EXPECT_NEAR(Sigma[2], 7.4, EPSILON);
	EXPECT_NEAR(Sigma[3], 2.324, EPSILON);
	EXPECT_NEAR(Sigma[4], 0.21312, EPSILON);
}


TEST(tests_SVD, test_diagonal_random) {
	std::vector<std::vector<double> > A =
		{{5.6468, 0, 0, 0, 0},
		{0, 2.5456, 0, 0, 0},
		{0, 0, 0.60258, 0, 0},
		{0, 0, 0, 6.6095, 0},
		{0, 0, 0, 0, 5.0375}};

	std::vector<std::vector<double> > Ut;
	std::vector<double> Sigma;
	std::vector<std::vector<double> > Vt;

	getSVD(A, Ut, Sigma, Vt, A[0].size());

	ASSERT_EQ(Sigma.size(), 5);

	EXPECT_NEAR(Sigma[0], 6.6095, EPSILON);
	EXPECT_NEAR(Sigma[1], 5.6468, EPSILON);
	EXPECT_NEAR(Sigma[2], 5.0375, EPSILON);
	EXPECT_NEAR(Sigma[3], 2.5456, EPSILON);
	EXPECT_NEAR(Sigma[4], 0.60258, EPSILON);
}

TEST(tests_SVD, test_random_hasta_diez) {
	// Tomado de octave
	std::vector<std::vector<double> > A =
		{{4.64218, 7.25457, 7.62096, 5.52883, 1.18379},
		{0.54651, 2.84279, 2.47577, 2.40093, 1.92161},
		{4.03096, 8.24835, 6.21267, 5.51680, 6.89209},
		{3.01898, 5.51470, 9.59258, 6.06209, 5.85903},
		{7.54402, 7.87220, 9.56017, 2.80167, 6.19715}};

	std::vector<std::vector<double> > Ut;
	std::vector<double> Sigma;
	std::vector<std::vector<double> > Vt;

	getSVD(A, Ut, Sigma, Vt, A[0].size());

	ASSERT_EQ(Sigma.size(), 5);

	EXPECT_NEAR(Sigma[0], 28.30494, EPSILON);
	EXPECT_NEAR(Sigma[1], 4.37182, EPSILON);
	EXPECT_NEAR(Sigma[2], 4.20626, EPSILON);
	EXPECT_NEAR(Sigma[3], 3.16999, EPSILON);
	EXPECT_NEAR(Sigma[4], 0.37752, EPSILON);
}

TEST(tests_SVD, test_random_hasta_diez_acotado) {
	// Tomado de octave
	std::vector<std::vector<double> > A =
		{{4.64218, 7.25457, 7.62096, 5.52883, 1.18379},
		{0.54651, 2.84279, 2.47577, 2.40093, 1.92161},
		{4.03096, 8.24835, 6.21267, 5.51680, 6.89209},
		{3.01898, 5.51470, 9.59258, 6.06209, 5.85903},
		{7.54402, 7.87220, 9.56017, 2.80167, 6.19715}};

	std::vector<std::vector<double> > Ut;
	std::vector<double> Sigma;
	std::vector<std::vector<double> > Vt;

	getSVD(A, Ut, Sigma, Vt, 3);

	ASSERT_EQ(Sigma.size(), 3);

	EXPECT_NEAR(Sigma[0], 28.30494, EPSILON);
	EXPECT_NEAR(Sigma[1], 4.37182, EPSILON);
	EXPECT_NEAR(Sigma[2], 4.20626, EPSILON);
}
