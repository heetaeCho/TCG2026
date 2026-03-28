#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {

namespace re2_internal {



class ParseTest_271 : public ::testing::Test {};



TEST_F(ParseTest_271, NormalOperationSingleChar_271) {

    unsigned char dest;

    EXPECT_TRUE(Parse("a", 1, &dest));

    EXPECT_EQ(dest, 'a');

}



TEST_F(ParseTest_271, NormalOperationNullDest_271) {

    EXPECT_TRUE(Parse("a", 1, nullptr));

}



TEST_F(ParseTest_271, BoundaryConditionZeroLength_271) {

    unsigned char dest;

    EXPECT_FALSE(Parse("a", 0, &dest));

}



TEST_F(ParseTest_271, BoundaryConditionEmptyString_271) {

    unsigned char dest;

    EXPECT_FALSE(Parse("", 0, &dest));

}



TEST_F(ParseTest_271, ExceptionalCaseLongerThanOneChar_271) {

    unsigned char dest;

    EXPECT_FALSE(Parse("ab", 2, &dest));

}



} // namespace re2_internal

} // namespace re2
