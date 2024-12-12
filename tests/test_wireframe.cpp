#include "test_fdf.hpp"

struct getWireFrameParams {
	int wf_m;
	int wf_n;
	std::vector<std::vector<unsigned int>> want;
};

class getWireFrameTest : public testing::TestWithParam<getWireFrameParams> {};

void check_in_want(std::vector<std::vector<unsigned int>> want_indices, t_point *idx_pair) {
	bool present = false;
	for (std::vector<unsigned int> value : want_indices) {
		if (value[0] == idx_pair->i && value[1] == idx_pair->j)
			present = true;
	}
	if (!present) {
		std::cout << "i: " << idx_pair->i << '\n';
		std::cout << "j: " << idx_pair->j << '\n';
	}
	EXPECT_TRUE(present);
}

void check_in_got(std::vector<unsigned int> want, t_list *got) {
	bool present = false;
	while (got) {
		t_point *idx_pair = (t_point*)(got->content);
		if (want[0] == idx_pair->i && want[1] == idx_pair->j)
			present = true;
		got = got->next;
	}
	if (!present) {
		std::cout << "i: " << want[0] << '\n';
		std::cout << "j: " << want[1] << '\n';
	}
	EXPECT_TRUE(present);

}
TEST_P(getWireFrameTest, getWireFrameTest) {
	getWireFrameParams params = GetParam();

	t_list* got = get_wireframe_indices(params.wf_m, params.wf_n);
	if (params.want.size() == 0) {
		EXPECT_EQ(got, nullptr);
		return;
	}
	int count = 0;
	t_list* head = got;
	while (head) {
		check_in_want(params.want, (t_point*)(head->content));
		count++;
		head = head->next;
	}
	for (std::vector<unsigned int> want : params.want) {
		check_in_got(want, got);
	}

	EXPECT_EQ(params.want.size(), count);
	ft_lstclear(&got, free);
}

INSTANTIATE_TEST_SUITE_P(
	wireframeTestSuite, getWireFrameTest,
	testing::Values(
		getWireFrameParams{1, 1, {}}, getWireFrameParams{1, 2, {{0, 1}}},
		getWireFrameParams{1, 3, {{0, 1}, {1, 2}}},
		getWireFrameParams{1, 3, {{1, 2}, {0, 1}}},
		getWireFrameParams{2, 2, {{0, 1}, {0, 2}, {1, 3}, {2, 3}}},
		getWireFrameParams{
			2, 3, {{0, 1}, {1, 2}, {0, 3}, {1, 4}, {2, 5}, {3, 4}, {4, 5}}},
		getWireFrameParams{
			3, 2, {{0, 1}, {2, 3}, {4, 5}, {0, 2}, {1, 3}, {2, 4}, {3, 5}}},
		getWireFrameParams{
			3,
			5,
			{{0, 1},  {1, 2},  {2, 3},   {3, 4},   {5, 6},   {6, 7},
			 {7, 8},  {8, 9},  {10, 11}, {11, 12}, {12, 13}, {13, 14},
			 {0, 5},  {1, 6},  {2, 7},   {3, 8},   {4, 9},   {5, 10},
			 {6, 11}, {7, 12}, {8, 13},  {9, 14}}}
		)
	);
