#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils.hpp"

int main() {
    std::string inputFile = "data.txt";
    size_t n;
    double S;
    double *w = nullptr, *r = nullptr;

    if (!ImportData(inputFile, S, n, w, r)) {
        return 1;
    }

    double rateOfReturn = CalculateRateOfReturn(n, w, r);
    double finalValue = CalculateFinalValue(S, rateOfReturn);

    if (!ExportResult("result.txt", S, n, w, r, rateOfReturn, finalValue)) {
        return 1;
    }

    return 0;
}
