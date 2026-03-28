#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch::Detail;

using namespace testing;



TEST_F(ConvertIntoStringTest_257, NormalOperationWithoutEscaping_257) {

    StringRef str("Hello, World!");

    std::string result = convertIntoString(str, false);

    EXPECT_EQ(result, "\"Hello, World!\"");

}



TEST_F(ConvertIntoStringTest_257, NormalOperationWithEscaping_257) {

    StringRef str("Hello\nWorld\t!");

    std::string result = convertIntoString(str, true);

    EXPECT_EQ(result, "\"Hello\\nWorld\\t!\"");

}



TEST_F(ConvertIntoStringTest_257, EmptyStringWithoutEscaping_257) {

    StringRef str("");

    std::string result = convertIntoString(str, false);

    EXPECT_EQ(result, "\"\"");

}



TEST_F(ConvertIntoStringTest_257, EmptyStringWithEscaping_257) {

    StringRef str("");

    std::string result = convertIntoString(str, true);

    EXPECT_EQ(result, "\"\"");

}



TEST_F(ConvertIntoStringTest_257, SpecialCharactersWithoutEscaping_257) {

    StringRef str("\r\n\t\f");

    std::string result = convertIntoString(str, false);

    EXPECT_EQ(result, "\"\r\n\t\f\"");

}



TEST_F(ConvertIntoStringTest_257, SpecialCharactersWithEscaping_257) {

    StringRef str("\r\n\t\f");

    std::string result = convertIntoString(str, true);

    EXPECT_EQ(result, "\"\\r\\n\\t\\f\"");

}
