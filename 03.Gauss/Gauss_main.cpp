#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Gauss_solve.h"
#include "util.h"

int main(int argc, const char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " input.csv [output.csv]\n";
        return 1;
    }

    try
    {
        auto ab = load_csv_to_matrix(argv[1]);
        const auto solution = Gauss_solve(ab);

        if (argc == 3)
        {
            std::ofstream out(argv[2]);
            if (!out)
            {
                throw std::runtime_error("Cannot open output CSV file");
            }
            print_vector_as_csv(out, solution);
        }
        else
        {
            print_vector_as_csv(std::cout, solution);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 2;
    }

    return 0;
}
