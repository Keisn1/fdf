#include <gtest/gtest.h>
#include "test_fdf.hpp"


auto main(int argc, char *argv[]) -> int {
    ::testing::InitGoogleTest(&argc, argv);

    // ::testing::GTEST_FLAG(filter) = "wireframeTest*";
    ::testing::GTEST_FLAG(filter) = "parseMapTest*";

	return RUN_ALL_TESTS();
}