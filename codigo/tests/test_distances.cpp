#include <gtest/gtest.h>

#include "../src/code/Types.h"
#include "../src/code/Distances.h"
#include "../src/code/Loaders.h"

#define RED 76
#define BLUE 29
#define GREEN 149
#define YELLOW 225
#define ORANGE 173
#define PURPLE 67


TEST(tests_Distances, test_simple) {
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

	std::vector<double> vector0 = {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0};
	std::vector<double> vector1 = {0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1};
	std::vector<double> vector2 = {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::vector<double> vector3 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1};
	std::vector<double> vector4 = {1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0};

	EXPECT_EQ(distances[0], vector0);
	EXPECT_EQ(distances[1], vector1);
	EXPECT_EQ(distances[2], vector2);
	EXPECT_EQ(distances[3], vector3);
	EXPECT_EQ(distances[4], vector4);
}

TEST(tests_Distances, test_discretizar) {
	std::vector<std::vector<unsigned int> > image = loadImage("../../data-csv/tests.csv");

	ASSERT_EQ(image.size(), 6);
	ASSERT_EQ(image[0].size(), 6);
	ASSERT_EQ(image[1].size(), 6);


	std::vector<std::pair<Point, Point> > rays;
	rays.push_back(std::pair<Point, Point> {Point(0,0),Point(0,5)}); // Primera columna
	rays.push_back(std::pair<Point, Point> {Point(5,0),Point(5,5)}); // Ultima columna
	rays.push_back(std::pair<Point, Point> {Point(0,0),Point(5,0)}); // Primera fila
	rays.push_back(std::pair<Point, Point> {Point(0,5),Point(5,5)}); // Ultima fila

	std::vector<double> times (rays.size());
	std::vector<std::vector<double> > distances = calculateDistances(image, rays, 3, times);

	std::vector<double> vector0 = {2,0,0,2,0,0,2,0,0};
	std::vector<double> vector1 = {0,0,2,0,0,2,0,0,2};
	std::vector<double> vector2 = {2,2,2,0,0,0,0,0,0};
	std::vector<double> vector3 = {0,0,0,0,0,0,2,2,2};
	EXPECT_EQ(distances[0], vector0);
	EXPECT_EQ(distances[1], vector1);
	EXPECT_EQ(distances[2], vector2);
	EXPECT_EQ(distances[3], vector3);
}
