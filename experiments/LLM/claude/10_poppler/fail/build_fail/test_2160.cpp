#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// We need to declare the function under test since it's static in the original file.
// However, since it's static, we need to either include the source or redefine the signature.
// For testing purposes, we'll use the same signature and test it via a wrapper approach.
// Since the function is static in the .cc file, we'll test it by including the source
// or by declaring an equivalent external linkage version.

// Since we can't directly access a static function from another translation unit,
// we'll use a workaround: include the relevant portion or define the function
// with the same logic for testing. However, per constraints, we must NOT re-implement.
// 
// The practical approach: we test _poppler_dest_compare_keys by pulling it in.
// In many test setups, the static function is made accessible via a test helper or
// by compiling the test with the source file.

// For this test file, we assume the build system compiles poppler-document.cc
// and exposes _poppler_dest_compare_keys (e.g., via a test-only header or
// by removing `static` in a test build). We declare it here as extern.

extern "C" {
    // If the function is made available for testing:
    gint _poppler_dest_compare_keys(gconstpointer a, gconstpointer b, gpointer user_data);
}

// If the above extern doesn't link, an alternative is to include the source directly:
// This is a common pattern for testing static functions.
// #include "poppler-document.cc"

class PopplerDestCompareKeysTest_2160 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Both strings are identical
TEST_F(PopplerDestCompareKeysTest_2160, IdenticalStrings_2160)
{
    const gchar *a = "hello";
    const gchar *b = "hello";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_EQ(result, 0);
}

// Test: First string is less than second string
TEST_F(PopplerDestCompareKeysTest_2160, FirstLessThanSecond_2160)
{
    const gchar *a = "abc";
    const gchar *b = "def";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: First string is greater than second string
TEST_F(PopplerDestCompareKeysTest_2160, FirstGreaterThanSecond_2160)
{
    const gchar *a = "xyz";
    const gchar *b = "abc";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_GT(result, 0);
}

// Test: Both strings are NULL
TEST_F(PopplerDestCompareKeysTest_2160, BothNull_2160)
{
    gint result = _poppler_dest_compare_keys(nullptr, nullptr, nullptr);
    EXPECT_EQ(result, 0);
}

// Test: First string is NULL, second is non-NULL
TEST_F(PopplerDestCompareKeysTest_2160, FirstNullSecondNonNull_2160)
{
    const gchar *b = "hello";
    gint result = _poppler_dest_compare_keys(nullptr, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: First string is non-NULL, second is NULL
TEST_F(PopplerDestCompareKeysTest_2160, FirstNonNullSecondNull_2160)
{
    const gchar *a = "hello";
    gint result = _poppler_dest_compare_keys(a, nullptr, nullptr);
    EXPECT_GT(result, 0);
}

// Test: Both strings are empty
TEST_F(PopplerDestCompareKeysTest_2160, BothEmpty_2160)
{
    const gchar *a = "";
    const gchar *b = "";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_EQ(result, 0);
}

// Test: First string is empty, second is non-empty
TEST_F(PopplerDestCompareKeysTest_2160, FirstEmptySecondNonEmpty_2160)
{
    const gchar *a = "";
    const gchar *b = "a";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: First string is non-empty, second is empty
TEST_F(PopplerDestCompareKeysTest_2160, FirstNonEmptySecondEmpty_2160)
{
    const gchar *a = "a";
    const gchar *b = "";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_GT(result, 0);
}

// Test: Strings that share a common prefix but differ in length
TEST_F(PopplerDestCompareKeysTest_2160, CommonPrefixDifferentLength_2160)
{
    const gchar *a = "abc";
    const gchar *b = "abcdef";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: Strings with special characters
TEST_F(PopplerDestCompareKeysTest_2160, SpecialCharacters_2160)
{
    const gchar *a = "page#1";
    const gchar *b = "page#2";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: Case sensitivity - uppercase vs lowercase
TEST_F(PopplerDestCompareKeysTest_2160, CaseSensitivity_2160)
{
    const gchar *a = "ABC";
    const gchar *b = "abc";
    // In ASCII, uppercase letters come before lowercase
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);
}

// Test: user_data parameter is ignored (non-null user_data should not affect result)
TEST_F(PopplerDestCompareKeysTest_2160, UserDataIgnored_2160)
{
    const gchar *a = "hello";
    const gchar *b = "hello";
    int dummy_data = 42;
    gint result = _poppler_dest_compare_keys(a, b, &dummy_data);
    EXPECT_EQ(result, 0);
}

// Test: Single character strings comparison
TEST_F(PopplerDestCompareKeysTest_2160, SingleCharComparison_2160)
{
    const gchar *a = "a";
    const gchar *b = "b";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_LT(result, 0);

    result = _poppler_dest_compare_keys(b, a, nullptr);
    EXPECT_GT(result, 0);
}

// Test: Symmetry - if a < b then b > a
TEST_F(PopplerDestCompareKeysTest_2160, SymmetryProperty_2160)
{
    const gchar *a = "alpha";
    const gchar *b = "beta";
    gint result_ab = _poppler_dest_compare_keys(a, b, nullptr);
    gint result_ba = _poppler_dest_compare_keys(b, a, nullptr);

    // They should have opposite signs
    EXPECT_LT(result_ab, 0);
    EXPECT_GT(result_ba, 0);
}

// Test: Strings with numeric content
TEST_F(PopplerDestCompareKeysTest_2160, NumericStrings_2160)
{
    // Lexicographic comparison: "2" > "10" because '2' > '1'
    const gchar *a = "2";
    const gchar *b = "10";
    gint result = _poppler_dest_compare_keys(a, b, nullptr);
    EXPECT_GT(result, 0);
}

// Test: Long identical strings
TEST_F(PopplerDestCompareKeysTest_2160, LongIdenticalStrings_2160)
{
    std::string long_str(1000, 'x');
    gint result = _poppler_dest_compare_keys(long_str.c_str(), long_str.c_str(), nullptr);
    EXPECT_EQ(result, 0);
}

// Test: Long strings differing at the end
TEST_F(PopplerDestCompareKeysTest_2160, LongStringsDifferAtEnd_2160)
{
    std::string a(999, 'x');
    a += 'a';
    std::string b(999, 'x');
    b += 'b';
    gint result = _poppler_dest_compare_keys(a.c_str(), b.c_str(), nullptr);
    EXPECT_LT(result, 0);
}
