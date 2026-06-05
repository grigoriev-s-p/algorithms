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
    if (begin == end)
    {
        return;
    }

    for (Iterator l = end; l != begin; --l)
    {
        bool changed = false;

        for (Iterator r = begin; r + 1 != l; ++r)
        {
            if (*(r + 1) < *r)
            {
                using std::swap;
                swap(*r, *(r + 1));
                changed = true;
            }
        }

        if (!changed)
        {
            break;
        }
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin <= 1)
    {
        return;
    }

    auto pivot = *(begin + (end - begin) / 2);
    Iterator left = begin;
    Iterator right = end;

    while (left < right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        do
        {
            --right;
        }
        while (pivot < *right);

        if (left >= right)
        {
            break;
        }

        using std::swap;
        swap(*left, *right);
        ++left;
    }

    quick_sort(begin, left);
    quick_sort(left, end);
}

#endif // SORTING_H
