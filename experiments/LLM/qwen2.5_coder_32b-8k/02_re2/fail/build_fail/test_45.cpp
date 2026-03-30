#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



TEST_F(RE2_OctalTest_45, OctalValidInput_45) {

    int result = 0;

    RE2::Arg arg = RE2().Octal(&result);

    EXPECT_TRUE(RE2::FullMatch("17", RE2("\\d+"), arg));

    EXPECT_EQ(result, 15);

}



TEST_F(RE2_OctalTest_45, OctalInvalidInput_45) {

    int result = 0;

    RE2::Arg arg = RE2().Octal(&result);

    EXPECT_FALSE(RE2::FullMatch("8", RE2("\\d+"), arg));

    EXPECT_EQ(result, 0); // Result should remain unchanged

}



TEST_F(RE2_OctalTest_45, OctalBoundaryCondition_45) {

    int result = 0;

    RE2::Arg arg = RE2().Octal(&result);

    EXPECT_TRUE(RE2::FullMatch("77", RE2("\\d+"), arg));

    EXPECT_EQ(result, 63); // 77 in octal is 63 in decimal

}



TEST_F(RE2_OctalTest_45, OctalNullPointer_45) {

    int* nullPtr = nullptr;

    RE2::Arg arg = RE2().Octal(nullPtr);

    EXPECT_FALSE(RE2::FullMatch("17", RE2("\\d+"), arg));

}



TEST_F(RE2_OctalTest_45, OctalLargeInput_45) {

    long result = 0;

    RE2::Arg arg = RE2().Octal(&result);

    EXPECT_TRUE(RE2::FullMatch("177777", RE2("\\d+"), arg));

    EXPECT_EQ(result, 32767); // 177777 in octal is 32767 in decimal

}



TEST_F(RE2_OctalTest_45, OctalNonOctalInput_45) {

    int result = 0;

    RE2::Arg arg = RE2().Octal(&result);

    EXPECT_FALSE(RE2::FullMatch("18", RE2("\\d+"), arg));

    EXPECT_EQ(result, 0); // Result should remain unchanged

}
