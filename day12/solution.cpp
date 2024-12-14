#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>

typedef std::pair<int, int> point;
typedef std::pair<char, std::set<point>> field;

void expandField(field &fieldToExpand, point startPoint, const std::map<point, char> &fields)
{
    if (fieldToExpand.second.empty())
        fieldToExpand = {fields.at(startPoint), std::set<point>()};
    fieldToExpand.second.insert(startPoint);
    auto [x, y] = startPoint;
    if (!fieldToExpand.second.contains({x - 1, y}) && fields.contains({x - 1, y}))
        if (fields.at({x - 1, y}) == fieldToExpand.first)
            expandField(fieldToExpand, {x - 1, y}, fields);
    if (!fieldToExpand.second.contains({x, y - 1}) && fields.contains({x, y - 1}))
        if (fields.at({x, y - 1}) == fieldToExpand.first)
            expandField(fieldToExpand, {x, y - 1}, fields);
    if (!fieldToExpand.second.contains({x + 1, y}) && fields.contains({x + 1, y}))
        if (fields.at({x + 1, y}) == fieldToExpand.first)
            expandField(fieldToExpand, {x + 1, y}, fields);
    if (!fieldToExpand.second.contains({x, y + 1}) && fields.contains({x, y + 1}))
        if (fields.at({x, y + 1}) == fieldToExpand.first)
            expandField(fieldToExpand, {x, y + 1}, fields);
}

int countCorners(const point &p, const std::set<point> &polygon)
{
    int numCorners = 0;
    if (!polygon.contains({p.first - 1, p.second}) && !polygon.contains({p.first, p.second - 1}))
        ++numCorners;
    if (!polygon.contains({p.first - 1, p.second}) && !polygon.contains({p.first, p.second + 1}))
        ++numCorners;
    if (!polygon.contains({p.first + 1, p.second}) && !polygon.contains({p.first, p.second - 1}))
        ++numCorners;
    if (!polygon.contains({p.first + 1, p.second}) && !polygon.contains({p.first, p.second + 1}))
        ++numCorners;
    if (polygon.contains({p.first - 1, p.second}) && polygon.contains({p.first, p.second - 1}))
        if (!polygon.contains({p.first - 1, p.second - 1}))
            ++numCorners;
    if (polygon.contains({p.first - 1, p.second}) && polygon.contains({p.first, p.second + 1}))
        if (!polygon.contains({p.first - 1, p.second + 1}))
            ++numCorners;
    if (polygon.contains({p.first + 1, p.second}) && polygon.contains({p.first, p.second - 1}))
        if (!polygon.contains({p.first + 1, p.second - 1}))
            ++numCorners;
    if (polygon.contains({p.first + 1, p.second}) && polygon.contains({p.first, p.second + 1}))
        if (!polygon.contains({p.first + 1, p.second + 1}))
            ++numCorners;
    return numCorners;
}

int fenceCost(const field &field)
{
    int area = field.second.size(), perimeter = 0;
    for (const auto &[x, y] : field.second)
    {
        int neighbours = 0;
        if (field.second.contains({x - 1, y}))
            ++neighbours;
        if (field.second.contains({x, y - 1}))
            ++neighbours;
        if (field.second.contains({x + 1, y}))
            ++neighbours;
        if (field.second.contains({x, y + 1}))
            ++neighbours;
        perimeter += 4 - neighbours;
    }
    return area * perimeter;
}

int fenceCostDiscounted(const field &field)
{
    int area = field.second.size(), numSides = 0;
    for (const point &p : field.second)
        numSides += countCorners(p, field.second);
    return area * numSides;
}

int main()
{
    std::string line;
    int height = 0, width = 0;
    std::map<point, char> field_map;
    std::set<point> availablePoints;
    for (int i = 0; getline(std::cin, line); ++i)
    {
        std::stringstream field_stream(line);
        char field;
        for (int j = 0; field_stream >> field; ++j)
        {
            field_map[{j, i}] = field;
            availablePoints.insert({j, i});
            if (j + 1 > width)
                width = j + 1;
        }
        if (i + 1 > height)
            height = i + 1;
    }

    std::set<field> field_set;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (availablePoints.contains({i, j}))
            {
                field newField = {'\0', std::set<point>()};
                expandField(newField, {i, j}, field_map);
                field_set.insert(newField);
                for (point p : newField.second)
                    availablePoints.erase(p);
            }
        }
    }

    int totalCost = 0, totalCostDiscounted = 0;
    for (const field &f : field_set)
    {
        totalCost += fenceCost(f);
        totalCostDiscounted += fenceCostDiscounted(f);
    }

    std::cout << "Total fence cost: " << totalCost << std::endl;
    std::cout << "Total fence cost with the discount: " << totalCostDiscounted << std::endl;

    return 0;
}