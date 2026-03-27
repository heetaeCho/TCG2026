#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "re2/re2.h"

#include <absl/types/optional.h>



namespace re2 {

namespace re2_internal {



class ParseTest_40 : public ::testing::Test {};



TEST_F(ParseTest_40, NormalOperation_StringToInt_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse("123", 3, &result));

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, 123);

}



TEST_F(ParseTest_40, NormalOperation_EmptyString_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse("", 0, &result));

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseTest_40, BoundaryCondition_MaxInt_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse("2147483647", 10, &result));

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, 2147483647);

}



TEST_F(ParseTest_40, BoundaryCondition_MinInt_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse("-2147483648", 11, &result));

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, -2147483648);

}



TEST_F(ParseTest_40, ErrorCase_NegativeNumberToInt_40) {

    absl::optional<int> result;

    EXPECT_FALSE(Parse("-1", 2, &result));

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseTest_40, ErrorCase_InvalidString_40) {

    absl::optional<int> result;

    EXPECT_FALSE(Parse("abc", 3, &result));

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseTest_40, ErrorCase_StringTooLong_40) {

    absl::optional<int> result;

    EXPECT_FALSE(Parse("12345678901234567890", 20, &result));

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseTest_40, EdgeCase_NullString_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse(nullptr, 0, &result));

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseTest_40, EdgeCase_ZeroLengthString_40) {

    absl::optional<int> result;

    EXPECT_TRUE(Parse("", 0, &result));

    EXPECT_FALSE(result.has_value());

}



}  // namespace re2_internal

}  // namespace re2
