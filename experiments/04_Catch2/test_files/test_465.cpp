#include <gtest/gtest.h>

#include "catch2/internal/catch_case_insensitive_comparisons.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace Catch::Detail;



class CaseInsensitiveEqualToTest : public ::testing::Test {

protected:

    CaseInsensitiveEqualTo comparator;

};



TEST_F(CaseInsensitiveEqualToTest, EqualStrings_465) {

    StringRef str1("hello");

    StringRef str2("hello");

    EXPECT_TRUE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, DifferentCaseStrings_465) {

    StringRef str1("Hello");

    StringRef str2("hELLO");

    EXPECT_TRUE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, DifferentStrings_465) {

    StringRef str1("hello");

    StringRef str2("world");

    EXPECT_FALSE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, EmptyStringComparison_465) {

    StringRef str1("");

    StringRef str2("");

    EXPECT_TRUE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, EmptyAndNonEmptyStringComparison_465) {

    StringRef str1("");

    StringRef str2("hello");

    EXPECT_FALSE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, CaseInsensitiveWithNumbers_465) {

    StringRef str1("a1B2c3");

    StringRef str2("A1b2C3");

    EXPECT_TRUE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, SpecialCharactersComparison_465) {

    StringRef str1("!@#");

    StringRef str2("!@#");

    EXPECT_TRUE(comparator(str1, str2));

}



TEST_F(CaseInsensitiveEqualToTest, DifferentSpecialCharactersComparison_465) {

    StringRef str1("!@#");

    StringRef str2("#@!");

    EXPECT_FALSE(comparator(str1, str2));

}
