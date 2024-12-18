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
	EXPECT_EQ(want_M.size(), map.map.m);
	EXPECT_EQ(want_M[0].size(), map.map.n);
	size_t c1 = 0;
	size_t c2 = 0;
	while (c1 < want_M.size()) {
		c2 = 0;
		while (c2 < want_M[0].size()) {
			EXPECT_EQ(want_M[c1][c2], map.map.mat[c1][c2]);
			EXPECT_EQ(want_color[c1][c2], map.colors[c1][c2]);
			c2++;
		}
		c1++;
	}
}

TEST_P(parseMapTest, parseMapTest) {
	parseMapTestParams params = GetParam();

	t_map map = parse_map(params.filename.c_str());
	if (params.want_M.size() == 0) {
		EXPECT_EQ(nullptr, map.map.mat);
		EXPECT_EQ(nullptr, map.colors);
		EXPECT_EQ(params.want_M.size(), map.map.m);
		EXPECT_EQ(params.want_M.size(), map.map.n);
		return;
	}

	comp_map(params.want_M, params.want_color, map);

	size_t c1 = 0;
	while (c1 < params.want_M.size()) {
		free(map.map.mat[c1]);
		free(map.colors[c1]);
		c1++;
	}
	free(map.map.mat);
	free(map.colors);
}

INSTANTIATE_TEST_SUITE_P(
	parseMapTests, parseMapTest,
	testing::Values(
		parseMapTestParams{"", {}, {}},
		parseMapTestParams{"tests/test_maps/1-1-0.fdf", {{0}}, {{0xFF00FF}}},
		parseMapTestParams{"tests/test_maps/1-1-1.fdf", {{1}}, {{0xFF00FF}}},
		parseMapTestParams{
			"tests/test_maps/1-2.fdf", {{0, 1}}, {{0xFF00FF, 0xFF00FF}}},
		parseMapTestParams{
			"tests/test_maps/1-2-other.fdf", {{2, 3}}, {{0xFF00FF, 0xFF00FF}}},
		parseMapTestParams{"tests/test_maps/1-3.fdf",
						   {{5, 6, 7}},
						   {{0xFF00FF, 0xFF00FF, 0xFF00FF}}},
		parseMapTestParams{
			"tests/test_maps/2-3.fdf",
			{{1, 2, 3}, {5, 6, 7}},
			{{0xFF00FF, 0xFF00FF, 0xFF00FF}, {0xFF00FF, 0xFF00FF, 0xFF00FF}}},
		parseMapTestParams{"tests/test_maps/3-3.fdf",
						   {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
						   {{0xFF00FF, 0xFF00FF, 0xFF00FF},
							{0xFF00FF, 0xFF00FF, 0xFF00FF},
							{0xFF00FF, 0xFF00FF, 0xFF00FF}}},
		parseMapTestParams{"tests/test_maps/3-1.fdf",
						   {{1}, {2}, {3}},
						   {{0xFF00FF}, {0xFF00FF}, {0xFF00FF}}},
		parseMapTestParams{"tests/test_maps/1-1-0-wc.fdf", {{0}}, {{0xff}}},
		parseMapTestParams{"tests/test_maps/3-2-wc.fdf",
						   {{1, 2}, {4, 5}, {7, 8}},
						   {{0xFF00FF, 0x09}, {0xAA, 0xFF00FF}, {0xFF00FF, 0x11}}},
		parseMapTestParams{
			"tests/test_maps/10-2-small.fdf",
			{{1, 0, 0, -1}, {-1, 0, 0, 0}, {-1, 1, 0, 0}, {1, -1, 0, 1}},
			{{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
			 {0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
			 {0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
			 {0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF}}},
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
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF},
				{0xFF00FF,0xFF00FF, 0xFF00FF,0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF}}}
		));


////////////////////////////////////////////////////////////////////////////////////////////////////
// extractPoints

struct mapToVectorsTestParams {
	t_map map;
};

class mapToVectorsTest : public testing::TestWithParam<mapToVectorsTestParams> {};

t_map create_map(std::vector<std::vector<double>> map_matrix) {
	t_map map;
	map.map.mat = create_matrix(map_matrix);
	map.map.m = map_matrix.size();
	if (map.map.m) {
		map.map.n = map_matrix[0].size();
	} else {
		map.map.n = 0;
	}
	return map;
};

TEST_P(mapToVectorsTest, mapToVectorsTest) {
	mapToVectorsTestParams params = GetParam();

	t_matrix points = map_to_vectors(params.map);
	if (params.map.map.m == 0) {
		EXPECT_EQ(nullptr, points.mat);
		EXPECT_EQ(0, points.m);
		EXPECT_EQ(0, points.n);
		return;
	}

	unsigned int want_n = params.map.map.m * params.map.map.n;

	ASSERT_EQ(3, points.m);
	ASSERT_EQ(want_n, points.n);
	size_t i = 0;
	size_t j = 0;
	size_t count = 0;
	while (i < params.map.map.m) {
		j = 0;
		while (j < params.map.map.n) {
			EXPECT_EQ(j, points.mat[0][count]);
			EXPECT_EQ(i, points.mat[1][count]);
			EXPECT_EQ(params.map.map.mat[i][j], points.mat[2][count]);
			count++;
			j++;
		}
		i++;
	}

	count = 0;
	while (count < params.map.map.m) {
		free(params.map.map.mat[count]);
		count++;
	}

	free(params.map.map.mat);
	free(points.mat[0]);
	free(points.mat[1]);
	free(points.mat[2]);
	free(points.mat);
}

INSTANTIATE_TEST_SUITE_P(extractPointsTest, mapToVectorsTest,
                         testing::Values(
							 mapToVectorsTestParams{create_map({})}
							 // mapToVectorsTestParams{create_map({{10}})},
							 // mapToVectorsTestParams{create_map({{10, 11}})},
							 // mapToVectorsTestParams{create_map({{10, 11}, {12, 13}})},
							 // mapToVectorsTestParams{create_map({{10}, {13}})}
							 )
	);
