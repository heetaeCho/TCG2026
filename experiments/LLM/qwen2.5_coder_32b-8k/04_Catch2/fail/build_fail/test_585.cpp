#include <gtest/gtest.h>

#include "catch2/internal/catch_string_manip.cpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



TEST_F(StringRefTest_585, StartsWidth_ReturnsTrue_WhenStringStartsWithPrefix_585) {

    StringRef str("hello");

    char prefix = 'h';

    EXPECT_TRUE(startsWith(str, prefix));

}



TEST_F(StringRefTest_585, StartsWidth_ReturnsFalse_WhenStringDoesNotStartWithPrefix_585) {

    StringRef str("world");

    char prefix = 'h';

    EXPECT_FALSE(startsWith(str, prefix));

}



TEST_F(StringRefTest_585, StartsWidth_ReturnsFalse_WhenStringIsEmpty_585) {

    StringRef str("");

    char prefix = 'h';

    EXPECT_FALSE(startsWith(str, prefix));

}



TEST_F(StringRefTest_585, StartsWidth_HandlesSingleCharacterStringsCorrectly_585) {

    StringRef str("a");

    char prefix = 'a';

    EXPECT_TRUE(startsWith(str, prefix));

}



TEST_F(StringRefTest_585, StartsWidth_ReturnsFalse_ForDifferentCasePrefix_585) {

    StringRef str("Hello");

    char prefix = 'h';

    EXPECT_FALSE(startsWith(str, prefix));

}
