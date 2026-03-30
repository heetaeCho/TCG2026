#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



TEST_F(StringMatcherBaseTest_218, DescribeConstructsCorrectDescriptionWithCaseSensitiveString_218) {

    CasedString casedStr("example", CaseSensitive::Yes);

    StringRef operation("equals");

    StringMatcherBase matcher(operation, casedStr);

    

    EXPECT_EQ(matcher.describe(), "equals: \"example\"");

}



TEST_F(StringMatcherBaseTest_218, DescribeConstructsCorrectDescriptionWithCaseInsensitiveString_218) {

    CasedString casedStr("example", CaseSensitive::No);

    StringRef operation("contains");

    StringMatcherBase matcher(operation, casedStr);

    

    EXPECT_EQ(matcher.describe(), "contains: \"example\" (case-insensitive)");

}



TEST_F(StringMatcherBaseTest_218, DescribeHandlesEmptyOperationString_218) {

    CasedString casedStr("example", CaseSensitive::Yes);

    StringRef operation("");

    StringMatcherBase matcher(operation, casedStr);

    

    EXPECT_EQ(matcher.describe(), ": \"example\"");

}



TEST_F(StringMatcherBaseTest_218, DescribeHandlesEmptyComparatorString_218) {

    CasedString casedStr("", CaseSensitive::Yes);

    StringRef operation("equals");

    StringMatcherBase matcher(operation, casedStr);

    

    EXPECT_EQ(matcher.describe(), "equals: \"\" (case-sensitive)");

}
