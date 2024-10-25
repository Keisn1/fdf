#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <vector>
#include "fdf.h"


struct GradientTestParam {
	int width;
	std::vector<int> want_grad;
};

class GradientTest : public testing::TestWithParam<GradientTestParam> {};

TEST_P(GradientTest, GradientTest) {
	GradientTestParam param = GetParam();
	unsigned int *grad = gradient(param.width);

	if (param.want_grad.size() == 0) {
		ASSERT_EQ(grad, nullptr);
	}
	return;
}

INSTANTIATE_TEST_SUITE_P(
    GradientTests,
    GradientTest,
    ::testing::Values(
		// We would probably want the user to have control over starting and ending colors
		// We would therefore need to adjust api, not doing it yet
		GradientTestParam{0, {}}
));
