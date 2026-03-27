#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"

#include "catch2/catch_case_sensitive.hpp"



using namespace Catch::Matchers;

using namespace Catch;



class CasedStringTest_217 : public ::testing::Test {

protected:

    std::string testStr = "example";

};



TEST_F(CasedStringTest_217, CaseSensitiveSuffix_ReturnsEmptyStringForCaseSensitive_217) {

    CasedString casedString(testStr, CaseSensitive::Yes);

    EXPECT_EQ(casedString.caseSensitivitySuffix(), StringRef(""));

}



TEST_F(CasedStringTest_217, CaseSensitiveSuffix_ReturnsCaseInsensitiveSuffixForCaseInsensitive_217) {

    CasedString casedString(testStr, CaseSensitive::No);

    EXPECT_EQ(casedString.caseSensitivitySuffix(), StringRef(" (case insensitive)"));

}
