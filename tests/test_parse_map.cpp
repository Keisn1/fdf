#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "fdf.h"
#include <fcntl.h>
#include <vector>

struct parseMapTestParams {
	std::string filename;
	std::vector<std::vector<double>> want_M;
	std::vector<std::vector<double>> want_color;
};

class parseMapTest : public testing::TestWithParam<parseMapTestParams>{};


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

	EXPECT_EQ(params.want_M.size(), map.m);
	EXPECT_EQ(params.want_M[0].size(), map.n);
	size_t c1 = 0;
	size_t c2 = 0;
	while (c1 < params.want_M.size()) {
		c2 = 0;
		while (c2 < params.want_M[0].size()) {
			EXPECT_EQ(params.want_M[c1][c2], map.map[c1][c2]);
			EXPECT_EQ(params.want_color[c1][c2], map.color[c1][c2]);
			c2++;
			}
		c1++;
	}

	c1 = 0;
	while (c1 < params.want_M.size()) {
		free(map.map[c1]);
		free(map.color[c1]);
		c1++;
	}
	free(map.map);
	free(map.color);
}

INSTANTIATE_TEST_SUITE_P(parseMapTests, parseMapTest,
                         testing::Values(
							 parseMapTestParams{"", {}, {}},
							 parseMapTestParams{"tests/test_maps/1-1-0.fdf", {{0}}, {{0x000000}}},
							 parseMapTestParams{"tests/test_maps/1-1-1.fdf", {{1}}, {{0x000000}}},
							 parseMapTestParams{"tests/test_maps/1-2.fdf", {{0, 1}}, {{0x000000, 0x000000}}},
							 parseMapTestParams{"tests/test_maps/1-2-other.fdf", {{2, 3}}, {{0x000000, 0x000000}}},
							 parseMapTestParams{"tests/test_maps/1-3.fdf", {{5, 6, 7}}, {{0x000000, 0x000000, 0x000000}}},
							 parseMapTestParams{"tests/test_maps/2-3.fdf", {{1, 2, 3}, {5, 6, 7}}, {{0x000000, 0x000000, 0x000000},{0x000000, 0x000000, 0x000000}}},
							 parseMapTestParams{"tests/test_maps/3-3.fdf", {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {{0x000000, 0x000000, 0x000000}, {0x000000, 0x000000, 0x000000},{0x000000, 0x000000, 0x000000}}},
							 parseMapTestParams{"tests/test_maps/3-1.fdf", {{1}, {2}, {3}}, {{0x000000}, {0x000000},{0x000000}}}
                             ));

