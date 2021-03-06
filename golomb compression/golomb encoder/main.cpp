//
//  main.cpp
//  golomb encoder
//
//  Created by Xu Ke on 2018/9/4.
//  Copyright © 2018 Must Studio. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <vector>

int hob(int num)
{
    if (!num) {
        return 0;
    }
    int ret = 1;
    while (num >>= 1) {
        ret <<= 1;
    }
    return ret;
}

int process(int count, int m, int lgm, bool mpb) {
    int length = 0;
    if (!mpb) {
        while (count --> 0) {
            do {
                std::cout << '0';
                length += 1;
            } while(lgm --> 0);
        }
    } else {
        int q = count / m;
        int r = count % m;
        while (q --> 0) {
            std::cout << '1';
            length += 1;
        }
        std::cout << '0';
        length += 1;
        while (lgm --> 0) {
            std::cout << ((r & (1 << lgm))?'1':'0');
            length += 1;
        }
    }
    return length;
}

int main(int argc, const char * argv[]) {
    char c;
    std::vector<int> input;
    std::vector<int> inputDiff;
    int zeroCount = 0, oneCount = 0;
    int zeroCountDiff = 0, oneCountDiff = 0;
    char lastDigit = 0;
    int lastCount = 0;
    char lastDigitDiff = 0;
    int lastCountDiff = 0;
    bool firstBitIsZero = false;
    bool firstBitIsZeroDiff = false;
    do {
        std::cin >> c;
        if (c != '0' && c != '1') {
            break;
        }
        if (lastDigit == 0) {
            firstBitIsZero = c == '0';
            lastDigit = c;
        }
        if (c == lastDigit) {
            lastCount += 1;
        } else {
            input.push_back(lastCount);
            lastCount = 1;
        }
        if (c == '0') {
            zeroCount += 1;
        }
        if (c == '1') {
            oneCount += 1;
        }
        
        char lastDiffForConstruction;
        if (lastDigitDiff == 0) {
            firstBitIsZeroDiff = c == '0';
            lastDiffForConstruction = lastDigitDiff = c;
        } else {
            if (lastDigit == c) {
                lastDiffForConstruction = '0';
            } else {
                lastDiffForConstruction = '1';
            }
        }
        if (lastDiffForConstruction == lastDigitDiff) {
            lastCountDiff += 1;
        } else {
            inputDiff.push_back(lastCountDiff);
            lastCountDiff = 1;
        }
        if (lastDiffForConstruction == '0') {
            zeroCountDiff += 1;
        }
        if (lastDiffForConstruction == '1') {
            oneCountDiff += 1;
        }
        if (lastDigit == c) {
            lastDigitDiff = '0';
        } else {
            lastDigitDiff = '1';
        }
        lastDigit = c;
    } while (c == '0' || c == '1');
    if (lastCount) {
        input.push_back(lastCount);
    }
    if (lastCountDiff) {
        inputDiff.push_back(lastCountDiff);
    }
    bool useZero = false;
    if (zeroCount > oneCount) {
        useZero = true;
    }
    bool useZeroDiff = false;
    if (zeroCountDiff > oneCountDiff) {
        useZeroDiff = true;
    }
    std::cout << (useZero? '0': '1');
    double p = (useZero? zeroCount: oneCount) / double(zeroCount + oneCount);
    double mup = p * log(2) / (1 - p);
    int m = hob(int(mup));
    if (m == 0) {
        m = 1;
    }
    int lgm = log2(m);
    std::cerr << "p = " << p << ", mup = " << mup << ", m = " << m << ", lgm = " << lgm << std::endl;
    bool care = firstBitIsZero ^ useZero;
    int careLast = 0;
    int codeLength = 2;
    for (auto count : input) {
        codeLength += process(count - careLast, m, lgm, care = !care);
        careLast = care ? 1 : 0;
    }
    std::cout << (care? '0': '1') << std::endl;
    std::cout << (useZeroDiff? '0': '1');
    double pDiff = (useZeroDiff? zeroCountDiff: oneCountDiff) / double(zeroCountDiff + oneCountDiff);
    double mupDiff = pDiff * log(2) / (1 - pDiff);
    int mDiff = hob(int(mupDiff));
    if (mDiff == 0) {
        mDiff = 1;
    }
    int lgmDiff = log2(mDiff);
    std::cerr << "p = " << pDiff << ", mup = " << mupDiff << ", m = " << mDiff << ", lgm = " << lgmDiff << std::endl;
    bool careDiff = firstBitIsZeroDiff ^ useZeroDiff;
    int careLastDiff = 0;
    int codeLengthDiff = 2;
    for (auto count : inputDiff) {
        codeLengthDiff += process(count - careLastDiff, mDiff, lgmDiff, careDiff = !careDiff);
        careLastDiff = careDiff ? 1 : 0;
    }
    std::cout << (careDiff? '0': '1') << std::endl;
    std::cerr << "CR-No diff:\t" << (zeroCount + oneCount) << "/\t" << codeLength << "\t= " << ((zeroCount + oneCount) / double(codeLength)) << std::endl;
    std::cerr << "CR-Diff:\t" << (zeroCountDiff + oneCountDiff) << "/\t" << codeLengthDiff << "\t= " << ((zeroCountDiff + oneCountDiff) / double(codeLengthDiff)) << std::endl;
    return 0;
}
