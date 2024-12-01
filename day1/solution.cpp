#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int compare(const void *px, const void *py)
{
    int x = *(int *)px, y = *(int *)py;
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int main()
{
    std::string line;
    std::vector<int> left, right;

    while (getline(std::cin, line))
    {
        std::stringstream nums(line);
        int new_left, new_right;
        nums >> new_left >> new_right;
        left.push_back(new_left);
        right.push_back(new_right);
    }

    std::qsort(left.data(), left.size(), sizeof(int), compare);
    std::qsort(right.data(), right.size(), sizeof(int), compare);

    int distance = 0;

    for (size_t i = 0; i < std::min(left.size(), right.size()); ++i)
        distance += std::max(left[i] - right[i], right[i] - left[i]);

    int similarity = 0;

    size_t left_idx = 0, right_idx = 0;
    while (left_idx < left.size() && right_idx < right.size())
    {
        int left_current = left[left_idx], right_current = right[right_idx];
        if (left_current < right_current)
        {
            ++left_idx;
            continue;
        }
        if (left_current > right_current)
        {
            ++right_idx;
            continue;
        }
        int left_multiplicity = 0, right_multiplicity = 0;

        while (left_idx < left.size() && left[left_idx] == left_current)
        {
            ++left_idx;
            ++left_multiplicity;
        }
        while (right_idx < right.size() && right[right_idx] == right_current)
        {
            ++right_idx;
            ++right_multiplicity;
        }

        similarity += left_current * left_multiplicity * right_multiplicity;
    }

    std::cout << "Total distance: " << distance << std::endl;
    std::cout << "Similarity score: " << similarity << std::endl;

    return 0;
}