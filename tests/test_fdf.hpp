#ifndef TEST_FDF_H
# define TEST_FDF_H

extern "C"
{
# include "bresenham.h"
# include "fdf.h"
}

# include <fcntl.h>
# include <gmock/gmock.h>
# include <gtest/gtest.h>
# include <vector>

// void expect_equal_points(t_points want, t_points got);
double		**create_matrix(std::vector<std::vector<double>> M);
t_matrix	new_matrix(std::vector<std::vector<double>> A);

#endif // TEST_FDF_H
