//
//  main.cpp
//  EnumBitMask
//
//  Created by Razvan Pascalau on 29/01/15.
//  Copyright (c) 2015 Razvan Pascalau. All rights reserved.
//

#include "EnumBitMask.hpp"
#include <iostream>
enum class TestEnum {
    firstVal,
    secondVal
};

int main(int argc, const char* argv[])
{
    // insert code here...
    EnumBitMask<TestEnum> myEnum{ TestEnum::firstVal };
    auto result = myEnum.isSet(TestEnum::firstVal);
    auto secondResult = myEnum.isSet(TestEnum::secondVal);
    auto val = TestEnum::firstVal;
    auto val2 = TestEnum::secondVal;

    std::cout << "Hello, World!\n";
    return 0;
}
