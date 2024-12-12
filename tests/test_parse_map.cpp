#include "test_fdf.hpp"

struct parseMapTestParams {
    std::string filename;
    std::vector<std::vector<double>> want_M;
    std::vector<std::vector<double>> want_color;
};

class parseMapTest : public testing::TestWithParam<parseMapTestParams>{};

void comp_map(
	std::vector<std::vector<double>> want_M,
	std::vector<std::vector<double>> want_color,
	t_map map
	) {
	EXPECT_EQ(want_M.size(), map.m);
	EXPECT_EQ(want_M[0].size(), map.n);
	size_t c1 = 0;
	size_t c2 = 0;
	while (c1 < want_M.size()) {
		c2 = 0;
		while (c2 < want_M[0].size()) {
			EXPECT_EQ(want_M[c1][c2], map.map[c1][c2]);
			EXPECT_EQ(want_color[c1][c2], map.color[c1][c2]);
			c2++;
		}
		c1++;
	}
}

TEST_P(parseMapTest, parseMapTest) {
	parseMapTestParams params = GetParam();

	t_map map = parse_map(params.filename.c_str());
	if (params.want_M.size() == 0) {
		EXPECT_EQ(nullptr, map.map);
		EXPECT_EQ(nullptr, map.color);
		EXPECT_EQ(params.want_M.size(), map.m);
		EXPECT_EQ(params.want_M.size(), map.n);
		return;
	}

	comp_map(params.want_M, params.want_color, map);

	size_t c1 = 0;
	while (c1 < params.want_M.size()) {
		free(map.map[c1]);
		free(map.color[c1]);
		c1++;
	}
	free(map.map);
	free(map.color);
}

INSTANTIATE_TEST_SUITE_P(
	parseMapTests, parseMapTest,
	testing::Values(
		parseMapTestParams{"", {}, {}},
		parseMapTestParams{"tests/test_maps/1-1-0.fdf", {{0}}, {{0x000000}}},
		parseMapTestParams{"tests/test_maps/1-1-1.fdf", {{1}}, {{0x000000}}},
		parseMapTestParams{
			"tests/test_maps/1-2.fdf", {{0, 1}}, {{0x000000, 0x000000}}},
		parseMapTestParams{
			"tests/test_maps/1-2-other.fdf", {{2, 3}}, {{0x000000, 0x000000}}},
		parseMapTestParams{"tests/test_maps/1-3.fdf",
						   {{5, 6, 7}},
						   {{0x000000, 0x000000, 0x000000}}},
		parseMapTestParams{
			"tests/test_maps/2-3.fdf",
			{{1, 2, 3}, {5, 6, 7}},
			{{0x000000, 0x000000, 0x000000}, {0x000000, 0x000000, 0x000000}}},
		parseMapTestParams{"tests/test_maps/3-3.fdf",
						   {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
						   {{0x000000, 0x000000, 0x000000},
							{0x000000, 0x000000, 0x000000},
							{0x000000, 0x000000, 0x000000}}},
		parseMapTestParams{"tests/test_maps/3-1.fdf",
						   {{1}, {2}, {3}},
						   {{0x000000}, {0x000000}, {0x000000}}},
		parseMapTestParams{"tests/test_maps/1-1-0-wc.fdf", {{0}}, {{0xff}}},
		parseMapTestParams{"tests/test_maps/3-2-wc.fdf",
						   {{1, 2}, {4, 5}, {7, 8}},
						   {{0x00, 0x09}, {0xAA, 0x00}, {0x00, 0x11}}},
		parseMapTestParams{
			"tests/test_maps/10-2-small.fdf",
			{{1, 0, 0, -1}, {-1, 0, 0, 0}, {-1, 1, 0, 0}, {1, -1, 0, 1}},
			{{0x00, 0x00, 0x00, 0x00},
			 {0x00, 0x00, 0x00, 0x00},
			 {0x00, 0x00, 0x00, 0x00},
			 {0x00, 0x00, 0x00, 0x00}}},
		parseMapTestParams{
			"tests/test_maps/10-2.fdf",
			{{1, 0, 0, -1, -1, 0, 1, 1, 0, 0},
			 {-1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
			 {-1, 1, 0, 0, -1, 1, 0, 0, 0, 1},
			 {1, -1, 0, 1, 1, -1, 0, 0, -1, 0},
			 {1, -1, -1, 0, -1, 0, 0, 0, -1, -1},
			 {-1, 1, 0, 1, 1, 0, 1, 0, 0, 0},
			 {0, -1, -1, 0, 0, 1, 0, 0, 0, 1},
			 {0, 0, 0, 0, 1, 0, -1, 0, 0, 0},
			 {-1, -1, 0, 1, -1, 0, 1, 0, 0, 1},
			 {0, 0, 1, -1, 0, -1, 0, 0, 0, 0}},
			{
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
				{0x00,0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}}
		));


////////////////////////////////////////////////////////////////////////////////////////////////////
// extractPoints

// struct extractPointsTestParams {
//  t_map map;
// };

// class extractPointsTest : public testing::TestWithParam<extractPointsTestParams> {};

// t_map create_map(std::vector<std::vector<double>> map_matrix) {
//  t_map map;
//  map.map = create_matrix(map_matrix);
//  map.m = map_matrix.size();
//  if (map.m) {
//      map.n = map_matrix[0].size();
//  } else {
//      map.n = 0;
//     }
//  return map;
// };

// TEST_P(extractPointsTest, extractPointsTest) {
//  extractPointsTestParams params = GetParam();

//  t_mat points = extract_points(params.map);
//  if (params.map.m == 0) {
//      EXPECT_EQ(nullptr, points.mat);
//      EXPECT_EQ(0, points.m);
//      EXPECT_EQ(0, points.n);
//      return;
//  }

//  unsigned int want_n = params.map.m * params.map.n;

//  ASSERT_EQ(3, points.m);
//  ASSERT_EQ(want_n, points.n);
//  size_t i = 0;
//  size_t j = 0;
//  size_t count = 0;
//  while (i < params.map.m) {
//      j = 0;
//      while (j < params.map.n) {
//          EXPECT_EQ(j, points.mat[0][count]);
//          EXPECT_EQ(i, points.mat[1][count]);

//          EXPECT_EQ(params.map.map[i][j], points.mat[2][count]);
//          count++;
//          j++;
//      }
//      i++;
//  }

//  count = 0;
//  while (count < params.map.m) {
//      free(params.map.map[count]);
//      count++;
//  }
//  free(params.map.map);
//  free(points.mat[0]);
//  free(points.mat[1]);
//  free(points.mat[2]);
//  free(points.mat);
// }

// INSTANTIATE_TEST_SUITE_P(extractPointsTest, extractPointsTest,
//                          testing::Values(
//                                       extractPointsTestParams{create_map({})},
//                                       extractPointsTestParams{create_map({{10}})},
//                                       extractPointsTestParams{create_map({{10, 11}})},
//                                       extractPointsTestParams{create_map({{10, 11}, {12, 13}})},
//                                       extractPointsTestParams{create_map({{10}, {13}})}
//                                          )
//                          );
