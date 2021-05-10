//
//  main.cpp
//  KTTimming
//
//  Created by Kam on 2021/5/10.
//

#include <iostream>
#include "Timer.hpp"

void HeavyWork() {
    for (int i = 0; i < 999999; i++) {
        __unused int j = rand() % i;
    }
}

int main(int argc, const char * argv[]) {
    
    KT::Timer MainTimer("Main", "timming cost in main function scope");
    
    {
        KT::Timer HeavyWorkTimer("Heavywork", "timming cost in closest scope");
        HeavyWork();
    }
    
    return 0;
}
