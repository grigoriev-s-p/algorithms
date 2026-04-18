#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include "sorting.h"

TEST(BubbleSortTest, EmptyVector)
{
    std::vector<int> data;
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(BubbleSortTest, OneElement)
{
    std::vector<int> data = {5};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({5}));
}

TEST(BubbleSortTest, DifferentNumbers)
{
    std::vector<int> data = {5, 1, 4, 2, 8, -3, 0};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, WithRepeatingElements)
{
    std::vector<int> data = {3, 1, 3, 2, 2, 1, 0};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, EmptyVector)
{
    std::vector<int> data;
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(QuickSortTest, OneElement)
{
    std::vector<int> data = {10};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({10}));
}

TEST(QuickSortTest, DifferentNumbers)
{
    std::vector<int> data = {9, 4, 7, 3, 10, 1, -5, 6};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, WithRepeatingElements)
{
    std::vector<int> data = {4, 2, 4, 1, 3, 2, 4, 0};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}
