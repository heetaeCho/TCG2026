#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_12 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_12, EscapeAllCharacters_NormalOperation_12) {

    std::string input = "Hello, World!";

    std::string expectedOutput = "Hello, World!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeDoubleQuotes_12) {

    std::string input = R"("Hello, World!")";

    std::string expectedOutput = R"(\"Hello, World!\")";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeBackslash_12) {

    std::string input = R"(Hello\World!)";

    std::string expectedOutput = R"(Hello\\World!)";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeSolidus_12) {

    std::string input = "Hello/World!";

    std::string expectedOutput = "Hello\\/World!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeBackspace_12) {

    std::string input = "Hello\bWorld!";

    std::string expectedOutput = "Hello\\bWorld!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeFormFeed_12) {

    std::string input = "Hello\fWorld!";

    std::string expectedOutput = "Hello\\fWorld!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeLineFeed_12) {

    std::string input = "Hello\nWorld!";

    std::string expectedOutput = "Hello\\nWorld!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeCarriageReturn_12) {

    std::string input = "Hello\rWorld!";

    std::string expectedOutput = "Hello\\rWorld!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_EscapeTab_12) {

    std::string input = "Hello\tWorld!";

    std::string expectedOutput = "Hello\\tWorld!";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_ControlCharacters_12) {

    std::string input = "\x00\x01\x1F";

    std::string expectedOutput = "\\u0000\\u0001\\u001f";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}



TEST_F(ValueTest_12, EscapeAllCharacters_MixedCharacters_12) {

    std::string input = R"("Hello\b\f\n\r\tWorld!")";

    std::string expectedOutput = R"(\"Hello\\b\\f\\n\\r\\tWorld!\")";

    EXPECT_EQ(value.escapeAllCharacters(input), expectedOutput);

}
