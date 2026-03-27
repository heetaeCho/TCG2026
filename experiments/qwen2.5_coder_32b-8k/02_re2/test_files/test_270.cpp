#include <gtest/gtest.h>

#include "re2/re2_internal.h"



namespace re2 {

namespace re2_internal {



class ParseTest_270 : public ::testing::Test {};



TEST_F(ParseTest_270, NormalOperation_SingleCharString_270) {

  signed char dest = 0;

  EXPECT_TRUE(Parse("A", 1, &dest));

  EXPECT_EQ(dest, 'A');

}



TEST_F(ParseTest_270, BoundaryCondition_EmptyString_270) {

  signed char dest = 0;

  EXPECT_FALSE(Parse("", 0, &dest));

}



TEST_F(ParseTest_270, BoundaryCondition_StringLengthOne_NullDestination_270) {

  EXPECT_TRUE(Parse("A", 1, nullptr));

}



TEST_F(ParseTest_270, ExceptionalCase_ZeroLengthString_NonNullDestination_270) {

  signed char dest = 0;

  EXPECT_FALSE(Parse("", 0, &dest));

}



TEST_F(ParseTest_270, ExceptionalCase_StringLongerThanOneChar_270) {

  signed char dest = 0;

  EXPECT_FALSE(Parse("AB", 2, &dest));

}



}  // namespace re2_internal

}  // namespace re2
