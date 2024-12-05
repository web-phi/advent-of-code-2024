#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

template <typename T>
using relation = std::set<std::pair<T, T>>;

template <typename T>
bool checkOrder(relation<T> &rules, std::vector<T> &order)
{
    for (size_t i = 1; i < order.size(); ++i)
        if (!rules.contains({order[i - 1], order[i]}))
            return false;
    return true;
}

template <typename T>
void sortByOrderRules(std::vector<T> &list, relation<T> &rules)
{
    for (size_t i = 1; i < list.size(); ++i)
        for (size_t j = 0; j < list.size() - i; ++j)
            if (!rules.contains({list[j], list[j + 1]}))
                std::swap(list[j], list[j + 1]);
}

int main()
{
    std::string line;
    relation<int> orderingRules;

    getline(std::cin, line);
    while (line.size() > 0)
    {
        int left, right;
        sscanf(line.c_str(), "%d|%d", &left, &right);
        orderingRules.insert({left, right});
        getline(std::cin, line);
    }

    int totalMidPageOrdered = 0, totalMidPageUnordered = 0;

    while (getline(std::cin, line))
    {
        std::vector<int> pageOrder;
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream pages(line);
        int newPage;
        while (pages >> newPage)
            pageOrder.push_back(newPage);

        if (checkOrder(orderingRules, pageOrder))
            totalMidPageOrdered += pageOrder[pageOrder.size() / 2];

        if (!checkOrder(orderingRules, pageOrder))
        {
            sortByOrderRules(pageOrder, orderingRules);
            totalMidPageUnordered += pageOrder[pageOrder.size() / 2];
        }
    }

    std::cout << "Sum of mid pages from correct orderings: " << totalMidPageOrdered << std::endl;
    std::cout << "Sum of mid pages from incorrect orderings: " << totalMidPageUnordered << std::endl;

    return 0;
}