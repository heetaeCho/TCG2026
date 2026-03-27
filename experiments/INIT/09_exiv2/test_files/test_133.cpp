#include <gtest/gtest.h>
#include <string>
#include <algorithm>

namespace Exiv2 {

    struct LangAltValueComparator {
    public:
        bool operator()(const std::string& str1, const std::string& str2) const {
            if (str1.size() != str2.size())
                return str1.size() > str2.size();
            auto f = [](unsigned char a, unsigned char b) {
                return std::tolower(a) > std::tolower(b);
            };
            return std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end(), f);
        }
    };
    
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_EqualSizeAndEqual_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "hello";
    std::string str2 = "hello";
    
    // Test: Strings are equal, should return false
    EXPECT_FALSE(comparator(str1, str2)) << "Comparator should return false for equal strings.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_EqualSizeAndDifferent_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "hello";
    std::string str2 = "helli";
    
    // Test: Strings of equal size but different lexicographical order
    EXPECT_TRUE(comparator(str1, str2)) << "Comparator should return true for lexicographically greater first string.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_DifferentSize_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "hello";
    std::string str2 = "hi";
    
    // Test: First string is larger than second string, should return false (size comparison)
    EXPECT_FALSE(comparator(str1, str2)) << "Comparator should return false for larger first string.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_EmptyFirstString_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "";
    std::string str2 = "test";
    
    // Test: First string is empty, should return true as empty string is smaller
    EXPECT_TRUE(comparator(str1, str2)) << "Comparator should return true for empty first string.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_EmptySecondString_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "test";
    std::string str2 = "";
    
    // Test: Second string is empty, should return false as non-empty string is greater
    EXPECT_FALSE(comparator(str1, str2)) << "Comparator should return false for empty second string.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_UpperLowerCaseComparison_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "apple";
    std::string str2 = "Apple";
    
    // Test: Case-insensitive comparison
    EXPECT_TRUE(comparator(str1, str2)) << "Comparator should return true for lexicographically greater string, ignoring case.";
}

TEST_F(LangAltValueComparatorTest_133, CompareStrings_EqualButDifferentCases_133) {
    Exiv2::LangAltValueComparator comparator;

    std::string str1 = "apple";
    std::string str2 = "APPLE";
    
    // Test: Case-insensitive comparison with same characters, should return false
    EXPECT_FALSE(comparator(str1, str2)) << "Comparator should return false for equal strings ignoring case.";
}