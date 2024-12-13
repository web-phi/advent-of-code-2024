#include <iostream>
#include <vector>
#include <map>

std::map<std::pair<size_t, size_t>, size_t> lookup;

size_t numDigits(size_t number, size_t base = 10)
{
    size_t result = 0;
    while (number > 0)
    {
        ++result;
        number /= base;
    }
    return result;
}

std::pair<size_t, size_t> splitNumber(size_t number, size_t base = 10)
{
    size_t split = 1;
    for (size_t _ = 0; _ < numDigits(number, base); _ += 2)
        split *= base;
    return {number / split, number % split};
}

size_t blink(size_t stone, size_t blinks_left)
{
    if (blinks_left == 0)
        return 1;
    if (stone == 0)
        return blink(1, blinks_left - 1);
    if (lookup.contains({stone, blinks_left}))
        return lookup[{stone, blinks_left}];
    if (numDigits(stone) % 2 == 0)
    {
        auto [left, right] = splitNumber(stone);
        lookup[{left, blinks_left - 1}] = blink(left, blinks_left - 1);
        lookup[{right, blinks_left - 1}] = blink(right, blinks_left - 1);
        lookup[{stone, blinks_left}] = lookup[{left, blinks_left - 1}] + lookup[{right, blinks_left - 1}];
        return lookup[{stone, blinks_left}];
    }
    lookup[{stone, blinks_left}] = blink(stone * 2024, blinks_left - 1);
    return lookup[{stone, blinks_left}];
}

int main()
{
    std::vector<size_t> stones;
    size_t nextStone;
    while (std::cin >> nextStone)
        stones.push_back(nextStone);

    size_t numStones25blinks = 0, numStones75blinks = 0;

    for (size_t stone : stones)
        numStones25blinks += blink(stone, 25);

    for (size_t stone : stones)
        numStones75blinks += blink(stone, 75);

    std::cout << "Number of stones left after 25 blinks: " << numStones25blinks << std::endl;
    std::cout << "Number of stones left after 75 blinks: " << numStones75blinks << std::endl;

    return 0;
}