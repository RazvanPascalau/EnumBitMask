//
//  main.cpp
//  EnumBitMask
//
//  Created by Razvan Pascalau on 29/01/15.
//  Copyright (c) 2015 Razvan Pascalau. All rights reserved.
//

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "EnumBitMask.hpp"
#include "catch.hpp"

TEST_CASE("basic enum bitmask usage", "[EnumBitMask]")
{
    enum class TestEnum {
        firstVal = 1 << 0,
        secondVal = 1 << 1,
        thirdVal = 1 << 2,
        fourthVal = 1 << 3,
    };

    SECTION("when using default c'tor no value must be set")
    {
        EnumBitMask<TestEnum> testBitmask;
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);

        testBitmask.set(TestEnum::secondVal);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == true);
    }

    SECTION("when using initialization list c'tor we must have everything set properly")
    {
        EnumBitMask<TestEnum> testBitmask{ TestEnum::firstVal, TestEnum::thirdVal };
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);
    }
}
