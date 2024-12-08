#include <iostream>
#include <string>
#include <map>
#include <set>

#define EMPTY '.'

struct Point
{
    int x, y;
    Point(int first, int second) : x(first), y(second) {}
    Point operator+(const Point &rhs) const { return Point(this->x + rhs.x, this->y + rhs.y); }
    Point operator-(const Point &rhs) const { return Point(this->x - rhs.x, this->y - rhs.y); }
};

bool operator==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
bool operator<(const Point &a, const Point &b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

class Board
{
    size_t width, height;
    std::map<char, std::set<Point>> antennae;
    std::set<Point> antinodes;

public:
    Board() { width = height = 0; }

    bool inBounds(Point p) const { return 0 <= p.x && p.x < (int)width && 0 <= p.y && p.y < (int)height; }

    size_t getAntinodeCount() const { return antinodes.size(); }

    size_t getWidth() const { return width; }

    size_t getHeight() const { return height; }

    void setWidth(size_t w) { width = w; }

    void setHeight(size_t h) { height = h; }

    void addAntenna(char freq, Point p)
    {
        if (!inBounds(p))
            throw std::out_of_range("Antenna is outside of the map bounds.");
        antennae[freq].insert(p);
    }

    void addAntinode(Point p)
    {
        if (!inBounds(p))
            throw std::out_of_range("Antinode is outside of the map bounds.");
        antinodes.insert(p);
    }

    void fillAntinodesForAntenna(char freq, bool include_weak_antinodes = false)
    {
        for (const Point &first : antennae[freq])
        {
            for (const Point &second : antennae[freq])
            {
                if (first == second)
                    continue;
                if (!include_weak_antinodes)
                {
                    Point antinode1 = first - second + first, antinode2 = second - first + second;
                    if (inBounds(antinode1))
                        addAntinode(antinode1);
                    if (inBounds(antinode2))
                        addAntinode(antinode2);
                }
                else
                {
                    for (int x = 0; x < (int)width; ++x)
                    {
                        if ((x - first.x) * (second.y - first.y) % (second.x - first.x))
                            continue;
                        int y = (x - first.x) * (second.y - first.y) / (second.x - first.x) + first.y;
                        Point antinode(x, y);
                        if (inBounds(antinode))
                            addAntinode(antinode);
                    }
                }
            }
        }
    }

    void fillAntinodes(bool include_weak_antinodes = false)
    {
        for (const auto &[freq, _points] : antennae)
            fillAntinodesForAntenna(freq, include_weak_antinodes);
    }
};

int main()
{
    std::string line;
    Board board;

    while (getline(std::cin, line))
    {
        if (line.length() > board.getWidth())
            board.setWidth(line.length());
        board.setHeight(board.getHeight() + 1);
        for (size_t i = 0; i < line.length(); ++i)
            if (line[i] != EMPTY)
                board.addAntenna(line[i], Point(i, board.getHeight() - 1));
    }

    bool display_weak_antinodes = false;
    board.fillAntinodes(display_weak_antinodes);

    std::cout << "Total number of antinodes: " << board.getAntinodeCount() << std::endl;

    return 0;
}