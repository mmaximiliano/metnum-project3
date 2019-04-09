#include <gtest/gtest.h>
#include "math.h"
#include "../src/code/Metrics.h"

TEST(tests_Metrics, test_simple) {
  std::vector<std::vector<unsigned int> > A = { {1} };
  std::vector<std::vector<unsigned int> > B = { {2} };

  double psnr = calculatePSNR(A, B);
  double expected = 10 * log10(255.0*255.0);
  double epsilon = std::numeric_limits<double>::epsilon();
  EXPECT_NEAR(psnr, expected, epsilon);
}

TEST(tests_Metrics, test_bigger) {
  std::vector<std::vector<unsigned int> > A = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
  std::vector<std::vector<unsigned int> > B = { {3, 2, 1}, {6, 5, 4}, {9, 8, 7} };

  double psnr = calculatePSNR(A, B);
  double expected = 43.87111628595629; // Calculado con python
  double epsilon = std::numeric_limits<double>::epsilon();
  EXPECT_NEAR(psnr, expected, epsilon);
}