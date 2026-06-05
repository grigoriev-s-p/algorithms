#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

void check_sorted(const std::vector<CollInt>& data, const char *algo_name)
{
    if (!std::is_sorted(data.begin(), data.end()))
    {
        std::cerr << "Sorting failed: " << algo_name << '\n';
        std::exit(1);
    }
}

// Random data
std::vector<CollInt> generate_data(size_t n)
{
    std::vector<CollInt> data(n);
    std::iota(data.begin(), data.end(), CollInt(0));
    return data;
}

void shuffle_data(std::vector<CollInt>& data)
{
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
}

int main()
{
    std::vector<size_t> sizes = {100, 500, 1000, 2000};

    std::cout << "N\tAlgo\t\tComps\t\tSwaps\t\tMoves\n";
    std::cout << "----------------------------------------------------------------\n";

    for (size_t n : sizes)
    {
        auto number_data = generate_data(n);

        // --- Std Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        std::sort(number_data.begin(), number_data.end());
        check_sorted(number_data, "std::sort");
        std::cout << n << "\tstd::sort\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Bubble Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        bubble_sort(number_data.begin(), number_data.end());
        check_sorted(number_data, "Bubble");
        std::cout << n << "\tBubble\t\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Quick Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        quick_sort(number_data.begin(), number_data.end());
        check_sorted(number_data, "Quick");
        std::cout << n << "\tQuick\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        std::cout << "--------------------------------------------------------------\n";
    }

    return 0;
}
