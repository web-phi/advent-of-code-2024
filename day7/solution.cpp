#include <iostream>
#include <string>
#include <sstream>
#include <stack>

long reduce(long bigger, long smaller, long base = 10L)
{
    while (smaller > 0)
    {
        bigger /= base;
        smaller /= base;
    }
    return bigger;
}

bool isSuffix(long bigger, long smaller, long base = 10L)
{
    while (smaller > 0)
    {
        if (bigger % base != smaller % base)
            return false;
        bigger /= base;
        smaller /= base;
    }
    return true;
}

bool checkCalibration(long target, std::stack<long> operands, bool concat = false)
{
    if (operands.size() == 1)
        return target == operands.top();
    long last = operands.top();
    operands.pop();
    bool calibrationPossible = false;
    if (concat && isSuffix(target, last))
        calibrationPossible = calibrationPossible || checkCalibration(reduce(target, last), operands, concat);
    if (target % last == 0)
        calibrationPossible = calibrationPossible || checkCalibration(target / last, operands, concat);
    if (target - last >= 0)
        calibrationPossible = calibrationPossible || checkCalibration(target - last, operands, concat);
    return calibrationPossible;
}

int main()
{
    std::string line;
    long targetSum = 0, targetSumConcat = 0;

    while (getline(std::cin, line))
    {
        std::stringstream operand_stream(line);
        long target, next;
        char _dummy;
        operand_stream >> target >> _dummy;

        std::stack<long> operands;
        while (operand_stream >> next)
            operands.push(next);

        std::stack<long> operandsConcat = operands;

        if (checkCalibration(target, operands))
            targetSum += target;

        if (checkCalibration(target, operandsConcat, true))
            targetSumConcat += target;
    }

    std::cout << "Total sum of targets without concatenation: " << targetSum << std::endl;
    std::cout << "Total sum of targets with concatenation: " << targetSumConcat << std::endl;

    return 0;
}