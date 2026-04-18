#ifndef SORTING_H
#define SORTING_H
#include <algorithm>
#include <iterator>

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (Iterator l = end; l != begin; --l)
    {

        for (Iterator r= begin; r+ 1 != l; ++it)
        {
            if (*(r+ 1) < *it)
            {
                using std::swap;
                swap(*it, *(r+ 1));
                changed = true;
            }
        }
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto size = end - begin;

    auto middle = *(begin + size / 2);

    size_t left = 0;
    size_t right = size - 1;

    while (left <= right)
    {
        while (*(begin + left) < middle)
        {
            ++left;
        }

        while (middle < *(begin + right))
        {
            --right;
        }

        if (left <= right)
        {
            std::swap(*(begin + left), *(begin + right));
            left+=1;
            right-=1;
        }
    }

    quick_sort(begin, begin + right + 1);
    quick_sort(begin + left, end);
}

#endif 
