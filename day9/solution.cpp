#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define BASELINE '0'
#define EMPTY -1

size_t findSpace(const std::vector<int> &decompressed, size_t size, int end)
{
    for (size_t asc = 0; (int)asc <= end && asc < decompressed.size(); ++asc)
    {
        if (decompressed[asc] != EMPTY)
            continue;
        size_t emptyRunLength = 1;
        while (decompressed[asc + 1] == EMPTY)
        {
            ++asc;
            ++emptyRunLength;
        }
        if (emptyRunLength >= size)
            return asc - emptyRunLength + 1;
    }
    return std::string::npos;
}

void print(const std::vector<int> &numbers)
{
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        if (numbers[i] == EMPTY)
            std::cout << '.';
        else
            std::cout << numbers[i];
    }
    std::cout << std::endl;
}

void decompress(std::vector<int> &target, const std::vector<int> &compressed_list)
{
    for (size_t i = 0; i < compressed_list.size(); ++i)
        for (int j = 0; j < compressed_list[i]; ++j)
            target.push_back(i % 2 ? EMPTY : i / 2);
}

void defragment(std::vector<int> &decompressed)
{
    std::vector<int>::iterator next = std::find(decompressed.begin(), decompressed.end(), EMPTY);
    while (next != decompressed.end())
    {
        *next = decompressed[decompressed.size() - 1];
        decompressed.pop_back();
        next = std::find(next, decompressed.end(), EMPTY);
    }
}

unsigned long digest(const std::vector<int> &hashable)
{
    unsigned long checksum = 0;
    for (size_t i = 0; i < hashable.size(); ++i)
        if (hashable[i] != EMPTY)
            checksum += i * hashable[i];
    return checksum;
}

void defragment_cont(std::vector<int> &decompressed)
{
    for (int desc = decompressed.size() - 1; desc > 0; --desc)
    {
        if (decompressed[desc] == EMPTY)
            continue;
        int memID = decompressed[desc], runLength = 1;
        while (memID == decompressed[desc - 1])
        {
            --desc;
            ++runLength;
        }
        size_t emptyRun = findSpace(decompressed, runLength, desc);
        if (emptyRun != std::string::npos)
            for (int i = 0; i < runLength; ++i)
                std::swap(decompressed[emptyRun + i], decompressed[desc + i]);
    }
}

int main()
{
    std::string numbers_str;
    std::cin >> numbers_str;
    std::vector<int> numbers;
    for (char c : numbers_str)
        numbers.push_back(c - BASELINE);

    std::vector<int> expanded, expanded_cont;
    decompress(expanded, numbers);
    defragment(expanded);

    decompress(expanded_cont, numbers);
    defragment_cont(expanded_cont);

    std::cout << "Non-contiguous checksum: " << digest(expanded) << std::endl;
    std::cout << "Contiguous checksum: " << digest(expanded_cont) << std::endl;

    return 0;
}