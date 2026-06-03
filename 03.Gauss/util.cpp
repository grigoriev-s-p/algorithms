#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "util.h"

namespace
{
    std::string trim(std::string s)
    {
        if (s.size() >= 3 &&
            static_cast<unsigned char>(s[0]) == 0xEF &&
            static_cast<unsigned char>(s[1]) == 0xBB &&
            static_cast<unsigned char>(s[2]) == 0xBF)
        {
            s.erase(0, 3);
        }

        const auto is_not_space = [](unsigned char ch) { return !std::isspace(ch); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_not_space));
        s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
        return s;
    }

    bool parse_double(const std::string &text, double &value)
    {
        const std::string t = trim(text);
        if (t.empty())
        {
            return false;
        }

        std::size_t pos = 0;
        try
        {
            value = std::stod(t, &pos);
        }
        catch (...)
        {
            return false;
        }

        while (pos < t.size() && std::isspace(static_cast<unsigned char>(t[pos])))
        {
            ++pos;
        }

        return pos == t.size();
    }

    std::vector<std::string> split_csv_line(const std::string &line)
    {
        std::vector<std::string> cells;
        std::string cell;
        std::stringstream ss(line);

        while (std::getline(ss, cell, ','))
        {
            cells.push_back(cell);
        }

        if (!line.empty() && line.back() == ',')
        {
            cells.emplace_back();
        }

        return cells;
    }
}

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::ifstream in(filename);
    if (!in)
    {
        throw std::runtime_error("Cannot open input CSV file");
    }

    std::vector<std::vector<double>> rows;
    std::string line;

    while (std::getline(in, line))
    {
        line = trim(line);
        if (line.empty())
        {
            continue;
        }

        const auto cells = split_csv_line(line);
        std::vector<double> row;
        bool numeric_row = true;

        for (const auto &cell : cells)
        {
            double value = 0.0;
            if (!parse_double(cell, value))
            {
                numeric_row = false;
                break;
            }
            row.push_back(value);
        }

        if (!numeric_row)
        {
            if (rows.empty())
            {
                continue;
            }
            throw std::runtime_error("CSV contains a non-numeric row after matrix data");
        }

        if (!rows.empty() && row.size() != rows.front().size())
        {
            throw std::runtime_error("CSV rows have different lengths");
        }

        rows.push_back(std::move(row));
    }

    if (rows.empty())
    {
        throw std::runtime_error("CSV file does not contain matrix data");
    }

    const int row_count = static_cast<int>(rows.size());
    const int col_count = static_cast<int>(rows.front().size());

    GaussMatrix matrix(row_count, col_count);
    for (int i = 0; i < row_count; ++i)
    {
        for (int j = 0; j < col_count; ++j)
        {
            matrix(i, j) = rows[i][j];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix &matrix, int prec)
{
    for (int j = 0; j < matrix.cols(); ++j)
    {
        out << 'A' << j + 1;
        if (j < matrix.cols() - 1)
        {
            out << ',';
        }
    }
    out << '\n';

    out << std::fixed << std::setprecision(prec);

    for (int i = 0; i < matrix.rows(); ++i)
    {
        for (int j = 0; j < matrix.cols(); ++j)
        {
            out << matrix(i, j);
            if (j < matrix.cols() - 1)
            {
                out << ',';
            }
        }
        out << '\n';
    }
}

void print_vector_as_csv(std::ostream& out, const GaussVector &vector, int prec)
{
    out << "x\n";
    out << std::fixed << std::setprecision(prec);

    for (int i = 0; i < vector.size(); ++i)
    {
        out << vector(i) << '\n';
    }
}
