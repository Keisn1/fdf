#include <gtest/gtest.h>
#include "fdf.h"
#include <fcntl.h>


TEST(parseMapTest, parseMapTest) {
	std::string filename = "../tests/test_maps/empty.fdf";
	double** M = parse_map(filename.c_str());
	EXPECT_EQ(nullptr, M);

	filename = "tests/test_maps/1-1-0.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(0, M[0][0]);
	free(M[0]);
	free(M);

	filename = "tests/test_maps/1-1-1.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(1, M[0][0]);
	free(M[0]);
	free(M);

	filename = "tests/test_maps/1-2.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(0, M[0][0]);
	EXPECT_EQ(1, M[0][1]);
	free(M[0]);
	free(M);

	filename = "tests/test_maps/1-2-other.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(2, M[0][0]);
	EXPECT_EQ(3, M[0][1]);
	free(M[0]);
	free(M);

	filename = "tests/test_maps/1-3.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(5, M[0][0]);
	EXPECT_EQ(6, M[0][1]);
	EXPECT_EQ(7, M[0][2]);
	free(M[0]);
	free(M);

	filename = "tests/test_maps/2-3.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(1, M[0][0]);
	EXPECT_EQ(2, M[0][1]);
	EXPECT_EQ(3, M[0][2]);
	EXPECT_EQ(5, M[1][0]);
	EXPECT_EQ(6, M[1][1]);
	EXPECT_EQ(7, M[1][2]);
	free(M[0]);
	free(M[1]);
	free(M);

	filename = "tests/test_maps/3-3.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(1, M[0][0]);
	EXPECT_EQ(2, M[0][1]);
	EXPECT_EQ(3, M[0][2]);
	EXPECT_EQ(4, M[1][0]);
	EXPECT_EQ(5, M[1][1]);
	EXPECT_EQ(6, M[1][2]);
	EXPECT_EQ(7, M[2][0]);
	EXPECT_EQ(8, M[2][1]);
	EXPECT_EQ(9, M[2][2]);
	free(M[0]);
	free(M[1]);
	free(M[2]);
	free(M);

	filename = "tests/test_maps/3-1.fdf";
	M = parse_map(filename.c_str());
	EXPECT_EQ(1, M[0][0]);
	EXPECT_EQ(2, M[1][0]);
	EXPECT_EQ(3, M[2][0]);
	free(M[0]);
	free(M[1]);
	free(M[2]);
	free(M);
}
