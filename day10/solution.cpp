#include <iostream>
#include <string>
#include <set>
#include <vector>

#define SEA_LEVEL '0'

typedef std::pair<int, int> point;
typedef std::vector<std::vector<int>> grid;

std::set<point> climbUp(const grid &map, const std::set<point> &startPoints)
{
    std::set<point> reachable;
    for (const auto &[i, j] : startPoints)
    {
        if (i > 0 && map[i - 1][j] == map[i][j] + 1)
            reachable.insert({i - 1, j});
        if (j > 0 && map[i][j - 1] == map[i][j] + 1)
            reachable.insert({i, j - 1});
        if (i < (int)map.size() - 1 && map[i + 1][j] == map[i][j] + 1)
            reachable.insert({i + 1, j});
        if (j < (int)map[i].size() - 1 && map[i][j + 1] == map[i][j] + 1)
            reachable.insert({i, j + 1});
    }
    return reachable;
}

int numPaths(const grid &map, point startPoint)
{
    if (map[startPoint.first][startPoint.second] == 9)
        return 1;
    int total = 0;
    for (const point &p : climbUp(map, {startPoint}))
        total += numPaths(map, p);
    return total;
}

int main()
{
    grid map;
    std::string line;
    while (getline(std::cin, line))
    {
        std::vector<int> row;
        for (char height : line)
            row.push_back(height - SEA_LEVEL);
        map.push_back(row);
    }

    int totalScore = 0, totalRating = 0;
    for (int i = 0; i < (int)map.size(); ++i)
    {
        for (int j = 0; j < (int)map[i].size(); ++j)
        {
            if (map[i][j] == 0)
            {
                std::set<point> levelPoints = {{i, j}};
                for (int _ = 0; _ < 9; ++_)
                    levelPoints = climbUp(map, levelPoints);
                totalScore += levelPoints.size();
                totalRating += numPaths(map, {i, j});
            }
        }
    }

    std::cout << "Total score: " << totalScore << std::endl;
    std::cout << "Total rating: " << totalRating << std::endl;

    return 0;
}