#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for LangAltValueComparator

class LangAltValueComparatorTest_133 : public ::testing::Test {

protected:

    LangAltValueComparator comparator;

};



TEST_F(LangAltValueComparatorTest_133, CompareDifferentLengthStrings_133) {

    EXPECT_TRUE(comparator("abcde", "abcd"));

    EXPECT_FALSE(comparator("abcd", "abcde"));

}



TEST_F(LangAltValueComparatorTest_133, CompareSameLengthStrings_UppercaseLowercase_133) {

    EXPECT_TRUE(comparator("ZEBRA", "zebra"));

    EXPECT_FALSE(comparator("zebra", "ZEBRA"));

}



TEST_F(LangAltValueComparatorTest_133, CompareSameLengthStrings_SameCase_133) {

    EXPECT_TRUE(comparator("zebra", "apple"));

    EXPECT_FALSE(comparator("apple", "zebra"));

}



TEST_F(LangAltValueComparatorTest_133, CompareEmptyStrings_133) {

    EXPECT_FALSE(comparator("", ""));

}



TEST_F(LangAltValueComparatorTest_133, CompareEmptyStringWithNonEmptyString_133) {

    EXPECT_TRUE(comparator("nonempty", ""));

    EXPECT_FALSE(comparator("", "nonempty"));

}
