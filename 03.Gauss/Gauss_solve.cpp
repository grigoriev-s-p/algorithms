#include <cmath>
#include <stdexcept>

#include "Gauss_solve.h"

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const int n = static_cast<int>(ab.rows());
    const int cols = static_cast<int>(ab.cols());

    if (n == 0 || cols != n + 1)
    {
        throw std::invalid_argument("Augmented matrix must have size n x (n + 1)");
    }

    constexpr double eps = 1e-12;

    for (int col = 0; col < n; ++col)
    {
        int pivot_row = col;
        double pivot_abs = std::abs(ab(col, col));

        for (int row = col + 1; row < n; ++row)
        {
            const double current_abs = std::abs(ab(row, col));
            if (current_abs > pivot_abs)
            {
                pivot_abs = current_abs;
                pivot_row = row;
            }
        }

        if (pivot_abs < eps)
        {
            throw std::runtime_error("System has no unique solution");
        }

        if (pivot_row != col)
        {
            ab.row(col).swap(ab.row(pivot_row));
        }

        for (int row = col + 1; row < n; ++row)
        {
            const double factor = ab(row, col) / ab(col, col);
            ab.row(row).tail(cols - col) -= factor * ab.row(col).tail(cols - col);
            ab(row, col) = 0.0;
        }
    }

    GaussVector x(n);
    for (int row = n - 1; row >= 0; --row)
    {
        double rhs = ab(row, n);
        if (row + 1 < n)
        {
            rhs -= ab.row(row).segment(row + 1, n - row - 1).dot(x.segment(row + 1, n - row - 1));
        }

        if (std::abs(ab(row, row)) < eps)
        {
            throw std::runtime_error("System has no unique solution");
        }

        x(row) = rhs / ab(row, row);
    }

    return x;
}
