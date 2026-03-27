#include <gtest/gtest.h>

#include "TestProjects/ninja/src/util.cc"



TEST(GetWin32EscapedStringTest_141, NormalOperationNoEscapeNeeded_141) {

    std::string input = "HelloWorld";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "HelloWorld");

}



TEST(GetWin32EscapedStringTest_141, NormalOperationWithQuotes_141) {

    std::string input = "Hello \"World\"";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"Hello \\\"World\\\"\"");

}



TEST(GetWin32EscapedStringTest_141, NormalOperationWithBackslashes_141) {

    std::string input = "C:\\path\\to\\file";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"C:\\\\path\\\\to\\\\file\"");

}



TEST(GetWin32EscapedStringTest_141, BoundaryConditionEmptyString_141) {

    std::string input = "";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"\"");

}



TEST(GetWin32EscapedStringTest_141, BoundaryConditionSingleQuote_141) {

    std::string input = "\"";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"\\\"\"");

}



TEST(GetWin32EscapedStringTest_141, BoundaryConditionSingleBackslash_141) {

    std::string input = "\\";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"\\\\\"");

}



TEST(GetWin32EscapedStringTest_141, ExceptionalCaseNullResultPointer_141) {

    std::string input = "HelloWorld";

    EXPECT_DEATH(GetWin32EscapedString(input, nullptr), "");

}



TEST(GetWin32EscapedStringTest_141, ComplexScenarioMixedContent_141) {

    std::string input = "He\"l\\lo Wo\"rld\\";

    std::string result;

    GetWin32EscapedString(input, &result);

    EXPECT_EQ(result, "\"He\\\"l\\\\lo Wo\\\"rld\\\\\"");

}
