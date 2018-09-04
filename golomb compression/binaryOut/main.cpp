//
//  main.cpp
//  binaryOut
//
//  Created by Xu Ke on 2018/9/4.
//  Copyright © 2018 Must Studio. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ios>

void outputByte(int byte) {
    for (int i = 8; i > 0; --i) {
        std::cout << ((byte << (i - 1))? '1': '0');
    }
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cout << "Usage: \n\t" << argv[0] << " filename" << std::endl;
    }
    std::ifstream inf(argv[1], std::ios_base::binary);
    int byte;
    while ((byte = inf.get()) != EOF) {
        outputByte(byte);
    }
    std::cout << std::endl;
    return 0;
}
