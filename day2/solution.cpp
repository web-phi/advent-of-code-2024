#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool isSafe(std::vector<int> &levels)
{
    if (levels.size() < 2)
        return true;

    if (levels[0] < levels[1])
    {
        for (size_t i = 1; i < levels.size(); ++i)
            if (levels[i] - levels[i - 1] < 1 || levels[i] - levels[i - 1] > 3)
                return false;
        return true;
    }

    if (levels[0] > levels[1])
    {
        for (size_t i = 1; i < levels.size(); ++i)
            if (levels[i - 1] - levels[i] < 1 || levels[i - 1] - levels[i] > 3)
                return false;
        return true;
    }

    return false;
}

bool isWeaklySafe(std::vector<int> &levels)
{
    if (isSafe(levels))
        return true;
    for (size_t k = 0; k < levels.size(); ++k)
    {
        std::vector<int> copy;
        for (size_t i = 0; i < levels.size(); ++i)
            if (i != k)
                copy.push_back(levels[i]);
        if (isSafe(copy))
            return true;
    }
    return false;
}

int main()
{
    std::string line;
    int safeCount = 0, weaklySafeCount = 0;

    while (getline(std::cin, line))
    {
        std::vector<int> levels;
        std::stringstream report(line);
        int nextLevel;

        while (report >> nextLevel)
            levels.push_back(nextLevel);

        if (isSafe(levels))
            ++safeCount;

        if (isWeaklySafe(levels))
            ++weaklySafeCount;
    }

    std::cout << "Total strongly safe reports: " << safeCount << std::endl;
    std::cout << "Total weakly safe reports: " << weaklySafeCount << std::endl;

    return 0;
}