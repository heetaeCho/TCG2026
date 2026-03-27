#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/re2.cc"



using namespace re2::re2_internal;



TEST(ParseTest_269, NormalOperation_ValidInput_269) {

    char dest;

    EXPECT_TRUE(Parse("a", 1, &dest));

    EXPECT_EQ(dest, 'a');

}



TEST(ParseTest_269, NormalOperation_NullDest_269) {

    EXPECT_TRUE(Parse("a", 1, nullptr));

}



TEST(ParseTest_269, BoundaryCondition_ZeroLength_269) {

    char dest;

    EXPECT_FALSE(Parse("", 0, &dest));

}



TEST(ParseTest_269, BoundaryCondition_EmptyStringNonZeroLength_269) {

    char dest;

    EXPECT_FALSE(Parse("", 1, &dest));

}



TEST(ParseTest_269, BoundaryCondition_LongerString_269) {

    char dest;

    EXPECT_FALSE(Parse("ab", 2, &dest));

}



TEST(ParseTest_269, ExceptionalCase_NullStr_269) {

    char dest;

    EXPECT_FALSE(Parse(nullptr, 1, &dest));

}
