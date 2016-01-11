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
    SECTION("check the isSet function")
    {
        EnumBitMask<TestEnum> testBitmask;
        REQUIRE(testBitmask.getRawValue() == 0);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
    }

    SECTION("when using default c'tor no value must be set")
    {
        EnumBitMask<TestEnum> testBitmask;
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);

        testBitmask.set(TestEnum::secondVal);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == true);
        REQUIRE(testBitmask.getRawValue() == 2);
    }

    SECTION("when using initialization list c'tor we must have everything set properly")
    {
        EnumBitMask<TestEnum> testBitmask{ TestEnum::firstVal, TestEnum::thirdVal };
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);
    }

    WHEN("we check the single assignment setter")
    {
        EnumBitMask<TestEnum> testBitmask{ TestEnum::thirdVal };
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);

        testBitmask.set(TestEnum::firstVal);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);

        THEN("we also check the single flag clear method")
        {
            testBitmask.clear(TestEnum::firstVal);
            REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == true);
            REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);

            testBitmask.clear(TestEnum::thirdVal);
            REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);
        }
    }

    WHEN("we check the multiple assignment setter")
    {
        EnumBitMask<TestEnum> testBitmask;
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);

        testBitmask.set(TestEnum::secondVal, TestEnum::fourthVal);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == true);

        THEN("we also check the multiple flag clear method")
        {
            testBitmask.set(TestEnum::firstVal);
            REQUIRE(testBitmask.isSet(TestEnum::firstVal) == true);
            REQUIRE(testBitmask.isSet(TestEnum::secondVal) == true);
            REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == true);

            testBitmask.clear(TestEnum::firstVal, TestEnum::fourthVal);
            REQUIRE(testBitmask.isSet(TestEnum::firstVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::secondVal) == true);
            REQUIRE(testBitmask.isSet(TestEnum::thirdVal) == false);
            REQUIRE(testBitmask.isSet(TestEnum::fourthVal) == false);
        }
    }

    SECTION("we check the multiple values checker")
    {
        EnumBitMask<TestEnum> testBitmask;
        REQUIRE(testBitmask.isSet(TestEnum::firstVal, TestEnum::secondVal, TestEnum::thirdVal, TestEnum::fourthVal) == false);

        testBitmask.set(TestEnum::secondVal, TestEnum::fourthVal);
        REQUIRE(testBitmask.isSet(TestEnum::secondVal, TestEnum::fourthVal) == true);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal, TestEnum::thirdVal) == false);
        REQUIRE(testBitmask.isSet(TestEnum::firstVal, TestEnum::thirdVal, TestEnum::secondVal, TestEnum::fourthVal) == false); //should be false
    }
}
