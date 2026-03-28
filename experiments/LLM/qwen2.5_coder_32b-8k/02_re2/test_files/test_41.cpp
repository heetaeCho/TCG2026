#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include <absl/optional.h>



using namespace re2::re2_internal;

using ::testing::_;

using ::testing::Eq;



class ParseTest_41 : public ::testing::Test {

protected:

    absl::optional<int> dest;

};



TEST_F(ParseTest_41, NullString_ReturnsTrueAndResetsDest_41) {

    EXPECT_TRUE(Parse(nullptr, 0, &dest, 10));

    EXPECT_FALSE(dest.has_value());

}



TEST_F(ParseTest_41, ValidInteger_ReturnsTrueAndSetsDest_41) {

    EXPECT_TRUE(Parse("123", 3, &dest, 10));

    EXPECT_EQ(dest.value(), 123);

}



TEST_F(ParseTest_41, EmptyString_ReturnsFalse_41) {

    EXPECT_FALSE(Parse("", 0, &dest, 10));

    EXPECT_FALSE(dest.has_value());

}



TEST_F(ParseTest_41, InvalidInteger_ReturnsFalse_41) {

    EXPECT_FALSE(Parse("abc", 3, &dest, 10));

    EXPECT_FALSE(dest.has_value());

}



TEST_F(ParseTest_41, LeadingSpaces_ReturnsTrueAndSetsDest_41) {

    EXPECT_TRUE(Parse("   456", 6, &dest, 10));

    EXPECT_EQ(dest.value(), 456);

}



TEST_F(ParseTest_41, TrailingSpaces_ReturnsFalse_41) {

    EXPECT_FALSE(Parse("789   ", 6, &dest, 10));

    EXPECT_FALSE(dest.has_value());

}



TEST_F(ParseTest_41, HexadecimalParsing_ReturnsTrueAndSetsDest_41) {

    EXPECT_TRUE(Parse("1A3F", 4, &dest, 16));

    EXPECT_EQ(dest.value(), 0x1A3F);

}



TEST_F(ParseTest_41, OctalParsing_ReturnsTrueAndSetsDest_41) {

    EXPECT_TRUE(Parse("175", 3, &dest, 8));

    EXPECT_EQ(dest.value(), 0o175);

}



TEST_F(ParseTest_41, BinaryParsing_ReturnsTrueAndSetsDest_41) {

    EXPECT_TRUE(Parse("1101", 4, &dest, 2));

    EXPECT_EQ(dest.value(), 0b1101);

}
