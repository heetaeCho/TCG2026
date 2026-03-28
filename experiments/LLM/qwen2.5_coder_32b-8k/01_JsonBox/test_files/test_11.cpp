#include <gtest/gtest.h>

#include "Value.h"

#include "Grammar.h"



using namespace JsonBox;



class ValueTest_11 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_11, EscapeMinimumCharacters_NormalOperation_11) {

    std::string input = "Hello \"World\"\twith\\special\ncharacters\r";

    std::string expectedOutput = R"(Hello \"World\"\twith\\special\ncharacters\r)";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}



TEST_F(ValueTest_11, EscapeMinimumCharacters_EmptyString_11) {

    std::string input = "";

    std::string expectedOutput = "";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}



TEST_F(ValueTest_11, EscapeMinimumCharacters_ControlCharacters_11) {

    std::string input = "\x00\x01\x1f";

    std::string expectedOutput = R"(\u0000\u0001\u001f)";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}



TEST_F(ValueTest_11, EscapeMinimumCharacters_NoSpecialCharacters_11) {

    std::string input = "NoSpecialCharactersHere";

    std::string expectedOutput = "NoSpecialCharactersHere";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}



TEST_F(ValueTest_11, EscapeMinimumCharacters_AllSpecialCharacters_11) {

    std::string input = "\"\\/\b\f\n\r\t";

    std::string expectedOutput = R"(\"\u002f\u0008\u000c\u000a\u000d\u0009)";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}



TEST_F(ValueTest_11, EscapeMinimumCharacters_MixedContent_11) {

    std::string input = "Mix of \"quotes\", \\slashes\\, \bbackspaces\b, \fform-feeds\f, \nnewlines\n, \rcarriage-returns\r, and\ttabs.";

    std::string expectedOutput = R"(Mix of \"quotes\"\, \\slashes\\\, \bbackspaces\b, \fform-feeds\f, \nnewlines\n, \rcarriage-returns\r, and\ttabs.)";

    EXPECT_EQ(value.escapeMinimumCharacters(input), expectedOutput);

}
