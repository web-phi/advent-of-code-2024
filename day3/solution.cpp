#include <iostream>
#include <string>
#include <sstream>
#include <regex>

int main()
{
    std::regex mul_regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    std::stringstream memory_block_stream;
    std::string line;

    while (getline(std::cin, line))
        memory_block_stream << line;

    std::string memory_block = memory_block_stream.str();
    size_t start, end; 
    
    while ((start = memory_block.find("don't()")) != std::string::npos)
    {
        end = memory_block.find("do()", start + 6) + 3;
        memory_block.erase(start, end - start);
    }

    std::smatch instructions;
    int total = 0, left_product, right_product;

    while (regex_search(memory_block, instructions, mul_regex))
    {
        sscanf(instructions.str().c_str(), "mul(%d,%d)", &left_product, &right_product);
        total += left_product * right_product;
        memory_block = instructions.suffix().str();
    }

    std::cout << "Sum total of products: " << total << std::endl;

    return 0;
}