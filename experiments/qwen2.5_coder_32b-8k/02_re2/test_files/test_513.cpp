#include <gtest/gtest.h>

#include "absl/strings/string_view.h"



namespace re2 {



bool ParseInteger(absl::string_view* s, int* np);



class ParseIntegerTest_513 : public ::testing::Test {

protected:

    absl::string_view input;

    int result;

};



TEST_F(ParseIntegerTest_513, ValidSingleDigitNumber_513) {

    input = "7";

    EXPECT_TRUE(ParseInteger(&input, &result));

    EXPECT_EQ(result, 7);

    EXPECT_EQ(input, "");

}



TEST_F(ParseIntegerTest_513, ValidMultiDigitNumber_513) {

    input = "12345";

    EXPECT_TRUE(ParseInteger(&input, &result));

    EXPECT_EQ(result, 12345);

    EXPECT_EQ(input, "");

}



TEST_F(ParseIntegerTest_513, LeadingZero_513) {

    input = "07";

    EXPECT_FALSE(ParseInteger(&input, &result));

    EXPECT_EQ(input, "07");

}



TEST_F(ParseIntegerTest_513, ValidNumberWithNonDigitSuffix_513) {

    input = "6abc";

    EXPECT_TRUE(ParseInteger(&input, &result));

    EXPECT_EQ(result, 6);

    EXPECT_EQ(input, "abc");

}



TEST_F(ParseIntegerTest_513, EmptyString_513) {

    input = "";

    EXPECT_FALSE(ParseInteger(&input, &result));

    EXPECT_EQ(input, "");

}



TEST_F(ParseIntegerTest_513, NonDigitStart_513) {

    input = "abc123";

    EXPECT_FALSE(ParseInteger(&input, &result));

    EXPECT_EQ(input, "abc123");

}



TEST_F(ParseIntegerTest_513, LargeNumberExceedingLimit_513) {

    input = "1000000009";

    EXPECT_FALSE(ParseInteger(&input, &result));

    EXPECT_EQ(input, "1000000009");

}



TEST_F(ParseIntegerTest_513, LargeValidNumberOnBoundary_513) {

    input = "100000000";

    EXPECT_TRUE(ParseInteger(&input, &result));

    EXPECT_EQ(result, 100000000);

    EXPECT_EQ(input, "");

}



} // namespace re2
