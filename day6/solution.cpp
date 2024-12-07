#include <iostream>
#include <set>
#include <string>

#define UP 0b00
#define LEFT 0b01
#define DOWN 0b10
#define RIGHT 0b11

#define OBSTACLE '#'
#define GUARD '^'
#define VISITED 'X'
#define EMPTY '.'

typedef std::pair<int, int> point;

class Board
{
    int width, height;
    point guard;
    std::set<point> obstacles;
    std::set<point> visited;
    char direction;

public:
    Board(int w, int h) : width(w), height(h)
    {
        direction = UP;
        guard = {0, 0};
    };

    Board() : Board(0, 0) {};

    void setGuard(int x, int y)
    {
        if (0 <= x && x < width && 0 <= y && y < height)
            guard = {x, y};
    }

    point getGuard() const { return guard; }

    int getDirection() const { return direction; }

    void setWidth(int w) { width = w; }

    void setHeight(int h) { height = h; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    char checkSquare(point p) const
    {
        if (p == guard)
            return GUARD;
        if (obstacles.contains(p))
            return OBSTACLE;
        if (visited.contains(p))
            return VISITED;
        return EMPTY;
    }

    void turnRight() { direction = (direction) ? (direction - 1) : RIGHT; }

    void addObstacle(int x, int y)
    {
        if (0 <= x && x < width && 0 <= y && y < height)
            obstacles.insert({x, y});
    }

    const std::set<point> &getVisitedSquares() const { return visited; }

    void step()
    {
        point ahead = lookAhead();
        if (obstacles.contains(ahead))
            turnRight();
        else
        {
            visited.insert(guard);
            guard = ahead;
        }
    }

    bool onBoard() { return guard.first >= 0 && guard.first < width && guard.second >= 0 && guard.second < height; }

    point lookAhead()
    {
        int horizontalShift = (direction & 0b01) * ((direction & 0b10) - 1);
        int verticalShift = (1 - (direction & 0b01)) * ((direction & 0b10) - 1);
        return {guard.first + horizontalShift, guard.second + verticalShift};
    }
};

std::ostream &operator<<(std::ostream &out, Board const &board)
{
    for (int i = 0; i < board.getHeight(); ++i)
    {
        for (int j = 0; j < board.getWidth(); ++j)
            out << board.checkSquare({j, i});
        out << '\n';
    }
    return out;
}

bool reunion(const Board &first, const Board &second)
{
    return (first.getGuard() == second.getGuard()) && (first.getDirection() == second.getDirection());
}

int main()
{
    std::string line;
    Board board;
    while (getline(std::cin, line))
    {
        if ((int)line.length() > board.getWidth())
            board.setWidth(line.length());
        board.setHeight(board.getHeight() + 1);
        for (size_t i = 0; i < line.length(); ++i)
        {
            if (line[i] == OBSTACLE)
                board.addObstacle(i, board.getHeight() - 1);
            if (line[i] == GUARD)
                board.setGuard(i, board.getHeight() - 1);
        }
    }

    int numPotentialObstacles = 0;
    Board newBoardTemplate = board;

    while (board.onBoard())
        board.step();

    const std::set<point> &visited = board.getVisitedSquares();

    for (const point &p : visited)
    {
        Board tortoise = newBoardTemplate;
        tortoise.addObstacle(p.first, p.second);
        Board hare = tortoise;
        do
        {
            tortoise.step();
            hare.step();
            hare.step();
        } while (hare.onBoard() && !reunion(hare, tortoise));

        if (reunion(hare, tortoise))
            ++numPotentialObstacles;
    }

    std::cout << "Number of visited squares: " << visited.size() << std::endl;
    std::cout << "Number of potential obstacle locations: " << numPotentialObstacles << std::endl;

    return 0;
}