#include "test_fdf.hpp"


auto main(int argc, char *argv[]) -> int {
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::GTEST_FLAG(filter) = "bresPlotlineSimpleTest*";
    // ::testing::GTEST_FLAG(filter) = "wireframeTest*";
    // ::testing::GTEST_FLAG(filter) = "parseMapTest*";
    // ::testing::GTEST_FLAG(filter) = "mapToVectorsTest*";
    // ::testing::GTEST_FLAG(filter) = "scaleTest*";

    return RUN_ALL_TESTS();
}
