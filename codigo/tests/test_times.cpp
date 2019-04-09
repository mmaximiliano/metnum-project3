#include <gtest/gtest.h>

#include "../src/code/Types.h"
#include "../src/code/Distances.h"
#include "../src/code/Loaders.h"

#define RED 76
#define ORANGE 173
#define YELLOW 225
#define GREEN 75
#define BLUE 29
#define PURPLE 67

TEST(tests_Times, test_simple) {
	std::vector<std::vector<unsigned int> > image = loadImage("../../data-csv/tests.csv");

	ASSERT_EQ(image.size(), 6);
	ASSERT_EQ(image[0].size(), 6);
	ASSERT_EQ(image[1].size(), 6);


	std::vector<std::pair<Point, Point> > rays;
	rays.push_back(std::pair<Point, Point> {Point(0,0),Point(0,5)}); // Primera columna
	rays.push_back(std::pair<Point, Point> {Point(5,0),Point(5,5)}); // Ultima columna
	rays.push_back(std::pair<Point, Point> {Point(0,0),Point(5,0)}); // Primera fila
	rays.push_back(std::pair<Point, Point> {Point(0,5),Point(5,5)}); // Ultima fila

	rays.push_back(std::pair<Point, Point> {Point(0,0),Point(5,4)}); // Primera, segunda, tercera y cuarta

	std::vector<double> times (rays.size());

	std::vector<std::vector<double> > distances = calculateDistances(image, rays, 6, times);

	EXPECT_EQ(times[0], RED + BLUE + GREEN + ORANGE + YELLOW + PURPLE + 6);
	EXPECT_EQ(times[1], RED + BLUE + GREEN + ORANGE + YELLOW + PURPLE + 6);
	EXPECT_EQ(times[2], RED * 6 + 6);
	EXPECT_EQ(times[3], PURPLE * 6 + 6);
	EXPECT_EQ(times[4], 2 * RED + 2 * ORANGE + 2 * YELLOW + 2 * GREEN + BLUE + 9);
}
