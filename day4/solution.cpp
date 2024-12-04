#include <iostream>
#include <string>
#include <vector>

template <typename T>
bool checkDirection(std::vector<std::vector<T>> &grid, std::vector<T> &key, int x, int y, int dx, int dy)
{
    int stride = key.size() - 1, max_x = grid.size(), max_y = grid[x].size();
    if (x + stride * dx < 0 || x + stride * dx >= max_x || y + stride * dy < 0 || y + stride * dy >= max_y)
        return false;

    for (size_t k = 0; k < key.size(); ++k)
        if (grid[x + k * dx][y + k * dy] != key[k])
            return false;

    return true;
}

template <typename T>
int countOccurences(std::vector<std::vector<T>> &grid, std::vector<T> &keyword)
{
    if (keyword.empty())
        return 0;

    int numOccurences = 0;

    for (size_t i = 0; i < grid.size(); ++i)
        for (size_t j = 0; j < grid[i].size(); ++j)
            if (grid[i][j] == keyword[0])
                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy)
                        numOccurences += checkDirection(grid, keyword, i, j, dx, dy);

    return numOccurences;
}

template <typename T>
int countXShapes(std::vector<std::vector<T>> &grid, const T &left, const T &mid, const T &right)
{
    int numXShapes = 0;

    for (size_t i = 1; i < grid.size() - 1; ++i)
        for (size_t j = 1; j < grid[i].size() - 1; ++j)
            if (grid[i][j] == mid)
            {
                bool mainDiagonal = (grid[i - 1][j - 1] == left && grid[i + 1][j + 1] == right);
                mainDiagonal |= (grid[i - 1][j - 1] == right && grid[i + 1][j + 1] == left);
                bool antiDiagonal = (grid[i - 1][j + 1] == left && grid[i + 1][j - 1] == right);
                antiDiagonal |= (grid[i - 1][j + 1] == right && grid[i + 1][j - 1] == left);
                numXShapes += (mainDiagonal && antiDiagonal);
            }
    
    return numXShapes;
}

int main()
{
    std::vector<std::vector<char>> grid;
    std::string line;

    while (getline(std::cin, line))
    {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    std::string keyword("XMAS");
    std::vector<char> key_vector(keyword.begin(), keyword.end());

    std::cout << "Number of XMAS occurences: " << countOccurences(grid, key_vector) << std::endl;

    std::cout << "Number of X-MAS occurences: " << countXShapes(grid, 'M', 'A', 'S') << std::endl;

    return 0;
}