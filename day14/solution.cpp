#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

typedef std::pair<int, int> point;

class Robot
{
    const static int width = 101, height = 103;
    point position, velocity;

public:
    Robot(point p, point v) : position(p), velocity(v) {};

    Robot() : Robot({0, 0}, {0, 0}) {};

    static int getWidth() { return width; }

    static int getHeight() { return height; }

    const point &getPosition() const { return position; }

    const point &getVelocity() const { return velocity; }

    void tick()
    {
        position.first = (position.first + velocity.first + width) % width;
        position.second = (position.second + velocity.second + height) % height;
    }
};

void tickAll(std::vector<Robot> &robots)
{
    for (Robot &robot : robots)
        robot.tick();
}

int safetyFactor(const std::vector<Robot> &robots)
{
    int upperLeft = 0, upperRight = 0, lowerLeft = 0, lowerRight = 0;
    for (const Robot &r : robots)
    {
        if (2 * r.getPosition().first < Robot::getWidth() - 1 && 2 * r.getPosition().second < Robot::getHeight() - 1)
            ++upperLeft;
        if (2 * r.getPosition().first > Robot::getWidth() - 1 && 2 * r.getPosition().second < Robot::getHeight() - 1)
            ++upperRight;
        if (2 * r.getPosition().first < Robot::getWidth() - 1 && 2 * r.getPosition().second > Robot::getHeight() - 1)
            ++lowerLeft;
        if (2 * r.getPosition().first > Robot::getWidth() - 1 && 2 * r.getPosition().second > Robot::getHeight() - 1)
            ++lowerRight;
    }
    return upperLeft * upperRight * lowerLeft * lowerRight;
}

void print(const std::vector<Robot> &robots)
{
    for (int i = 0; i < Robot::getWidth(); ++i)
    {
        for (int j = 0; j < Robot::getHeight(); ++j)
        {
            int numRobots = 0;
            for (const Robot &robot : robots)
                if (robot.getPosition() == std::make_pair(i, j))
                    ++numRobots;
            if (numRobots)
                std::cout << numRobots;
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::string line;
    std::vector<Robot> robots;
    while (getline(std::cin, line))
    {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        robots.push_back(Robot({px, py}, {vx, vy}));
    }

    std::vector<Robot> robotsCopy = robots;

    for (int i = 0; i < 100; ++i)
        tickAll(robots);

    for (int i = 0; i < 7410; ++i)
        tickAll(robotsCopy);

    for (int i = 7411; i < 7420; ++i)
    {
        std::cout << "Number of seconds: " << i << "..." << std::endl;
        tickAll(robotsCopy);
        print(robotsCopy);
        usleep(600000);
        std::cout << "\033[2J\033[1;1H";
    }

    std::cout << "Safety factor after 100 seconds: " << safetyFactor(robots) << std::endl;

    return 0;
}