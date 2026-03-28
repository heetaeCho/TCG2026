#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpParseFlagsTest_170 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if needed.

    }

};



TEST_F(RegexpParseFlagsTest_170, NormalOperation_170) {

    Regexp::ParseFlags flagA = static_cast<Regexp::ParseFlags>(3);  // Example flags

    Regexp::ParseFlags flagB = static_cast<Regexp::ParseFlags>(6);  // Example flags

    Regexp::ParseFlags result = flagA & flagB;

    EXPECT_EQ(result, static_cast<Regexp::ParseFlags>(2));

}



TEST_F(RegexpParseFlagsTest_170, BoundaryConditions_170) {

    Regexp::ParseFlags flagZero = static_cast<Regexp::ParseFlags>(0);

    Regexp::ParseFlags flagMax = static_cast<Regexp::ParseFlags>(std::numeric_limits<int>::max());

    EXPECT_EQ(flagZero & flagMax, static_cast<Regexp::ParseFlags>(0));

    EXPECT_EQ(flagMax & flagMax, flagMax);

}



TEST_F(RegexpParseFlagsTest_170, ExceptionalOrErrorCases_170) {

    // Since the operator& is a simple bitwise operation and does not throw exceptions,

    // there are no exceptional or error cases to test for this specific function.

}



// No external interactions to verify as the function is standalone and does not involve mocks or callbacks.
