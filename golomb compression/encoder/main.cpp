//
//  main.cpp
//  encoder
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
    int zeroCount = 0, oneCount = 0;
    char lastDigit = 0;
    int lastCount = 0;
    bool firstBitIsZero = false;
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
        lastDigit = c;
    } while (c == '0' || c == '1');
    if (lastCount) {
        input.push_back(lastCount);
    }
    bool useZero = false;
    if (zeroCount > oneCount) {
        useZero = true;
    }
    std::cout << (useZero? '0': '1');
    double p = (useZero? zeroCount: oneCount) / double(zeroCount + oneCount);
    double mup = p * log(2) / (1 - p);
    int m = hob(int(mup));
    int lgm = log2(m);
    bool care = firstBitIsZero ^ useZero;
    int careLast = 0;
    int codeLength = 2;
    for (auto count : input) {
        codeLength += process(count - careLast, m, lgm, care = !care);
        careLast = care ? 1 : 0;
    }
    std::cout << (care? '0': '1') << std::endl;
    std::cout << "CR: " << (zeroCount + oneCount) << "/ " << codeLength << " = " << ((zeroCount + oneCount) / double(codeLength)) << std::endl;
    return 0;
}
