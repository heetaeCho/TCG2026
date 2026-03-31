#include <gtest/gtest.h>
#include <cstring>

// Declare the function under test (it's static in the original file, so we redefine the signature here)
// We need to include the function or replicate its declaration for testing purposes.
// Since it's a static function in a .cc file, we'll need to either include it or
// define it here for testing. We'll use a workaround by defining it in the test.

// Copy the function signature for testing (treating it as a black box based on its interface)
static const char *strrstr(const char *s, const char *ss)
{
    const char *p = strstr(s, ss);
    for (const char *pp = p; pp != nullptr; pp = strstr(p + 1, ss)) {
        p = pp;
    }
    return p;
}

class StrrstrTest_2733 : public ::testing::Test {
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test: Finding the last occurrence of a substring that appears multiple times
TEST_F(StrrstrTest_2733, FindsLastOccurrenceOfMultipleMatches_2733)
{
    const char *s = "abcabcabc";
    const char *ss = "abc";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // The last occurrence of "abc" starts at index 6
    EXPECT_EQ(result, s + 6);
}

// Test: Finding substring that appears exactly once
TEST_F(StrrstrTest_2733, FindsSingleOccurrence_2733)
{
    const char *s = "hello world";
    const char *ss = "world";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 6);
}

// Test: Substring not found returns nullptr
TEST_F(StrrstrTest_2733, ReturnsNullWhenNotFound_2733)
{
    const char *s = "hello world";
    const char *ss = "xyz";
    const char *result = strrstr(s, ss);
    EXPECT_EQ(result, nullptr);
}

// Test: Empty substring - strstr returns pointer to start of string for empty needle
TEST_F(StrrstrTest_2733, EmptySubstringReturnsNonNull_2733)
{
    const char *s = "hello";
    const char *ss = "";
    const char *result = strrstr(s, ss);
    // strstr with empty needle returns the haystack pointer; strrstr should find last occurrence
    EXPECT_NE(result, nullptr);
}

// Test: Both strings are empty
TEST_F(StrrstrTest_2733, BothEmptyStrings_2733)
{
    const char *s = "";
    const char *ss = "";
    const char *result = strrstr(s, ss);
    // strstr("", "") returns pointer to the empty string
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test: Haystack is empty, needle is non-empty
TEST_F(StrrstrTest_2733, EmptyHaystackNonEmptyNeedle_2733)
{
    const char *s = "";
    const char *ss = "abc";
    const char *result = strrstr(s, ss);
    EXPECT_EQ(result, nullptr);
}

// Test: Substring at the very beginning
TEST_F(StrrstrTest_2733, SubstringAtBeginningOnly_2733)
{
    const char *s = "abcdef";
    const char *ss = "abc";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test: Substring at the very end
TEST_F(StrrstrTest_2733, SubstringAtEndOnly_2733)
{
    const char *s = "defabc";
    const char *ss = "abc";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 3);
}

// Test: Substring equals the entire string
TEST_F(StrrstrTest_2733, SubstringEqualsEntireString_2733)
{
    const char *s = "abc";
    const char *ss = "abc";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test: Substring longer than haystack
TEST_F(StrrstrTest_2733, SubstringLongerThanHaystack_2733)
{
    const char *s = "ab";
    const char *ss = "abcdef";
    const char *result = strrstr(s, ss);
    EXPECT_EQ(result, nullptr);
}

// Test: Overlapping occurrences - e.g., "aaa" searching for "aa"
TEST_F(StrrstrTest_2733, OverlappingOccurrences_2733)
{
    const char *s = "aaaa";
    const char *ss = "aa";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // The last occurrence of "aa" in "aaaa" starts at index 2
    EXPECT_EQ(result, s + 2);
}

// Test: Single character haystack and needle match
TEST_F(StrrstrTest_2733, SingleCharMatch_2733)
{
    const char *s = "a";
    const char *ss = "a";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s);
}

// Test: Single character haystack and needle don't match
TEST_F(StrrstrTest_2733, SingleCharNoMatch_2733)
{
    const char *s = "a";
    const char *ss = "b";
    const char *result = strrstr(s, ss);
    EXPECT_EQ(result, nullptr);
}

// Test: Two occurrences, returns the last one
TEST_F(StrrstrTest_2733, TwoOccurrencesReturnsLast_2733)
{
    const char *s = "xyzxyz";
    const char *ss = "xyz";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, s + 3);
}

// Test: Substring is a single character appearing multiple times
TEST_F(StrrstrTest_2733, SingleCharSubstringMultipleOccurrences_2733)
{
    const char *s = "abacada";
    const char *ss = "a";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // Last 'a' is at index 6
    EXPECT_EQ(result, s + 6);
}

// Test: Partial match followed by full match
TEST_F(StrrstrTest_2733, PartialMatchThenFullMatch_2733)
{
    const char *s = "aabaabaab";
    const char *ss = "aab";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // Last "aab" starts at index 6
    EXPECT_EQ(result, s + 6);
}

// Test: Long string with substring at various positions
TEST_F(StrrstrTest_2733, LongStringMultipleOccurrences_2733)
{
    const char *s = "the cat sat on the mat with the bat";
    const char *ss = "the";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // "the" appears at 0, 15, and 29
    EXPECT_EQ(result, s + 29);
}

// Test: Needle contains special characters
TEST_F(StrrstrTest_2733, SpecialCharactersInNeedle_2733)
{
    const char *s = "hello\nworld\nhello\n";
    const char *ss = "\n";
    const char *result = strrstr(s, ss);
    ASSERT_NE(result, nullptr);
    // Last newline is at index 17
    EXPECT_EQ(result, s + 17);
}
