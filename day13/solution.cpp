#include <iostream>
#include <string>
#include <algorithm>

#define ERROR 10000000000000

int main()
{
    std::string line;
    size_t Ax, Ay, Bx, By, x, y, totalPrice = 0, totalPriceAfterErrorCorrection = 0;
    while (getline(std::cin, line))
    {
        if (line.size() == 0)
            continue;
        sscanf(line.c_str(), "Button A: X+%ld, Y+%ld", &Ax, &Ay);
        getline(std::cin, line);
        sscanf(line.c_str(), "Button B: X+%ld, Y+%ld", &Bx, &By);
        getline(std::cin, line);
        sscanf(line.c_str(), "Prize: X=%ld, Y=%ld", &x, &y);
        x += ERROR;
        y += ERROR;

        size_t minPrice = __LONG_MAX__;
        for (size_t i = 0; i <= 100; ++i)
            for (size_t j = 0; j <= 100; ++j)
                if (i * Ax + j * Bx == (x - ERROR) && i * Ay + j * By == (y - ERROR) && 3 * i + j < minPrice)
                    minPrice = 3 * i + j;

        if (minPrice < __LONG_MAX__)
            totalPrice += minPrice;

        long num1 = x * Ay - y * Ax, num2 = y * Bx - x * By, den = Bx * Ay - Ax * By;

        if (num1 % den || num2 % den)
            continue;

        long aK = num2 / den, bK = num1 / den;

        if (aK < 0 || bK < 0) continue;

        if (aK * Ax + bK * Bx == x && aK * Ay + bK * By == y)
            totalPriceAfterErrorCorrection += 3 * aK + bK;
    }

    std::cout << "Total price before error correction: " << totalPrice << std::endl;
    std::cout << "Total price after error correction: " << totalPriceAfterErrorCorrection << std::endl;

    return 0;
}