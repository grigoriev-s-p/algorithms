#include <cmath>
#include <random>
#include <stdexcept>

#include <gtest/gtest.h>

#include "Gauss_solve.h"

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(2, 3);
    ab << 1.1, 2.2, 3.3,
    4.4, 5.5, 6.6;

    const auto x = Gauss_solve(ab);

    ASSERT_EQ(x.size(), 2);
    EXPECT_NEAR(x(0), -1.0, 1e-10);
    EXPECT_NEAR(x(1), 2.0, 1e-10);
}

TEST(GaussSolve, Pivoting)
{
    GaussMatrix ab(2, 3);
    ab << 0.0, 2.0, 4.0,
    1.0, -1.0, 1.0;

    const auto x = Gauss_solve(ab);

    ASSERT_EQ(x.size(), 2);
    EXPECT_NEAR(x(0), 3.0, 1e-10);
    EXPECT_NEAR(x(1), 2.0, 1e-10);
}

TEST(GaussSolve, SingularMatrixThrows)
{
    GaussMatrix ab(2, 3);
    ab << 1.0, 2.0, 3.0,
    2.0, 4.0, 6.0;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, ReproducibleGeneratedSystem)
{
    constexpr int n = 40;
    std::mt19937 gen(20240528);
    std::uniform_real_distribution<double> dist(-2.0, 2.0);

    GaussMatrix a(n, n);
    for (int i = 0; i < n; ++i)
    {
        double row_abs_sum = 0.0;
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                a(i, j) = 0.0;
            }
            else
            {
                a(i, j) = dist(gen);
                row_abs_sum += std::abs(a(i, j));
            }
        }
        a(i, i) = row_abs_sum + 1.0 + std::abs(dist(gen));
    }

    GaussVector expected(n);
    for (int i = 0; i < n; ++i)
    {
        expected(i) = dist(gen);
    }

    const GaussVector b = a * expected;

    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = a;
    ab.col(n) = b;

    const auto actual = Gauss_solve(ab);

    EXPECT_LT((actual - expected).norm(), 1e-8);
}
