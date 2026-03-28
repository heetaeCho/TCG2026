#include <gtest/gtest.h>
#include <string>
#include <memory>

// Include the necessary headers
#include "goo/GooString.h"
#include "poppler/Catalog.cc"

class EntryGooStringComparerTest_1896 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get() returns the correct string reference from a GooString pointer
TEST_F(EntryGooStringComparerTest_1896, GetFromGooStringPointer_ReturnsCorrectString_1896) {
    GooString str("hello");
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_EQ(result, "hello");
}

// Test that get() returns a reference to the underlying string
TEST_F(EntryGooStringComparerTest_1896, GetFromGooStringPointer_ReturnsSameReference_1896) {
    GooString str("test");
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_EQ(&result, &str.toStr());
}

// Test with an empty GooString
TEST_F(EntryGooStringComparerTest_1896, GetFromEmptyGooString_ReturnsEmptyString_1896) {
    GooString str("");
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_TRUE(result.empty());
}

// Test with a GooString containing special characters
TEST_F(EntryGooStringComparerTest_1896, GetFromGooStringWithSpecialChars_1896) {
    GooString str("hello\0world", 11);
    const std::string &result = EntryGooStringComparer::get(&str);
    // The string may contain embedded null depending on construction
    EXPECT_EQ(result.size(), 11u);
}

// Test with a long string
TEST_F(EntryGooStringComparerTest_1896, GetFromLongGooString_1896) {
    std::string longStr(10000, 'a');
    GooString str(longStr);
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_EQ(result, longStr);
    EXPECT_EQ(result.size(), 10000u);
}

// Test the comparison operator - equal strings
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesEqualGooStrings_1896) {
    GooString str1("abc");
    GooString str2("abc");
    EntryGooStringComparer comparer;
    // For equal strings, neither lhs < rhs nor rhs < lhs should be true
    EXPECT_FALSE(comparer(&str1, &str2));
    EXPECT_FALSE(comparer(&str2, &str1));
}

// Test the comparison operator - different strings, lexicographic order
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesLessThan_1896) {
    GooString str1("abc");
    GooString str2("def");
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(&str1, &str2));
    EXPECT_FALSE(comparer(&str2, &str1));
}

// Test the comparison operator - prefix strings
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesPrefixStrings_1896) {
    GooString str1("abc");
    GooString str2("abcdef");
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(&str1, &str2));
    EXPECT_FALSE(comparer(&str2, &str1));
}

// Test the comparison operator with empty strings
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesEmptyStrings_1896) {
    GooString str1("");
    GooString str2("");
    EntryGooStringComparer comparer;
    EXPECT_FALSE(comparer(&str1, &str2));
    EXPECT_FALSE(comparer(&str2, &str1));
}

// Test the comparison operator - empty vs non-empty
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesEmptyVsNonEmpty_1896) {
    GooString str1("");
    GooString str2("abc");
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(&str1, &str2));
    EXPECT_FALSE(comparer(&str2, &str1));
}

// Test get with a std::string (the auto& overload)
TEST_F(EntryGooStringComparerTest_1896, GetFromStdString_1896) {
    std::string str = "hello";
    const std::string &result = EntryGooStringComparer::get(str);
    EXPECT_EQ(result, "hello");
}

// Test comparison with std::string vs GooString (heterogeneous comparison)
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesStdStringVsGooString_1896) {
    std::string str1 = "abc";
    GooString str2("def");
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(str1, &str2));
    EXPECT_FALSE(comparer(&str2, str1));
}

// Test comparison with two std::strings
TEST_F(EntryGooStringComparerTest_1896, OperatorComparesTwoStdStrings_1896) {
    std::string str1 = "abc";
    std::string str2 = "xyz";
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(str1, str2));
    EXPECT_FALSE(comparer(str2, str1));
}

// Test GooString constructed from const char* with specific length
TEST_F(EntryGooStringComparerTest_1896, GetFromGooStringWithLength_1896) {
    GooString str("hello world", 5);
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_EQ(result, "hello");
    EXPECT_EQ(result.size(), 5u);
}

// Test single character strings
TEST_F(EntryGooStringComparerTest_1896, GetFromSingleCharGooString_1896) {
    GooString str("x");
    const std::string &result = EntryGooStringComparer::get(&str);
    EXPECT_EQ(result, "x");
    EXPECT_EQ(result.size(), 1u);
}

// Test comparison transitivity: if a < b and b < c then a < c
TEST_F(EntryGooStringComparerTest_1896, OperatorTransitivity_1896) {
    GooString strA("apple");
    GooString strB("banana");
    GooString strC("cherry");
    EntryGooStringComparer comparer;
    EXPECT_TRUE(comparer(&strA, &strB));
    EXPECT_TRUE(comparer(&strB, &strC));
    EXPECT_TRUE(comparer(&strA, &strC));
}
