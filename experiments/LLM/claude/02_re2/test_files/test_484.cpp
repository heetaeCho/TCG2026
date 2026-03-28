#include "gtest/gtest.h"
#include "re2/unicode_casefold.h"
#include "re2/re2.h"

// We need access to the LookupCaseFold function declaration
namespace re2 {
const CaseFold* LookupCaseFold(const CaseFold*, int, Rune);
}

using re2::CaseFold;
using re2::LookupCaseFold;
using re2::Rune;

class LookupCaseFoldTest_484 : public ::testing::Test {
protected:
    // Helper to create CaseFold entries for testing
    // CaseFold has lo, hi, delta fields
};

// Test with empty array (n=0) and valid ef pointer
TEST_F(LookupCaseFoldTest_484, EmptyArrayReturnsFirstElement_484) {
    CaseFold f[1] = {{65, 90, 32}};  // lo=65('A'), hi=90('Z'), delta=32
    // n=0, so the while loop doesn't execute
    // f < ef (f+1), so returns f
    const CaseFold* result = LookupCaseFold(f, 0, 65);
    EXPECT_EQ(result, &f[0]);
}

// Test finding an element that is exactly at lo boundary
TEST_F(LookupCaseFoldTest_484, FindExactLoMatch_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 30);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 30);
    EXPECT_EQ(result->hi, 40);
    EXPECT_EQ(result->delta, 2);
}

// Test finding an element that is exactly at hi boundary
TEST_F(LookupCaseFoldTest_484, FindExactHiMatch_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 40);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 30);
    EXPECT_EQ(result->hi, 40);
    EXPECT_EQ(result->delta, 2);
}

// Test finding an element in the middle of a range
TEST_F(LookupCaseFoldTest_484, FindMiddleOfRange_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 35);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 30);
    EXPECT_EQ(result->hi, 40);
    EXPECT_EQ(result->delta, 2);
}

// Test finding the first element
TEST_F(LookupCaseFoldTest_484, FindFirstElement_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 15);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 10);
    EXPECT_EQ(result->hi, 20);
    EXPECT_EQ(result->delta, 1);
}

// Test finding the last element
TEST_F(LookupCaseFoldTest_484, FindLastElement_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 55);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 50);
    EXPECT_EQ(result->hi, 60);
    EXPECT_EQ(result->delta, 3);
}

// Test with a value between ranges (not in any range) - returns next element
TEST_F(LookupCaseFoldTest_484, ValueBetweenRangesReturnsNext_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    // 25 is between [10,20] and [30,40]
    // Binary search won't find it in any range, should return next element
    const CaseFold* result = LookupCaseFold(f, 3, 25);
    ASSERT_NE(result, nullptr);
    // Should return the next fold entry after the gap
    EXPECT_EQ(result->lo, 30);
    EXPECT_EQ(result->hi, 40);
}

// Test with a value before all ranges
TEST_F(LookupCaseFoldTest_484, ValueBeforeAllRanges_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 5);
    ASSERT_NE(result, nullptr);
    // Should return the first element
    EXPECT_EQ(result->lo, 10);
    EXPECT_EQ(result->hi, 20);
}

// Test with a value after all ranges - should return NULL
TEST_F(LookupCaseFoldTest_484, ValueAfterAllRangesReturnsNull_484) {
    CaseFold f[3] = {
        {10, 20, 1},
        {30, 40, 2},
        {50, 60, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 100);
    EXPECT_EQ(result, nullptr);
}

// Test with single element array - value in range
TEST_F(LookupCaseFoldTest_484, SingleElementInRange_484) {
    CaseFold f[1] = {{100, 200, 5}};
    const CaseFold* result = LookupCaseFold(f, 1, 150);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 100);
    EXPECT_EQ(result->hi, 200);
    EXPECT_EQ(result->delta, 5);
}

// Test with single element array - value before range
TEST_F(LookupCaseFoldTest_484, SingleElementBeforeRange_484) {
    CaseFold f[1] = {{100, 200, 5}};
    const CaseFold* result = LookupCaseFold(f, 1, 50);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 100);
}

// Test with single element array - value after range
TEST_F(LookupCaseFoldTest_484, SingleElementAfterRange_484) {
    CaseFold f[1] = {{100, 200, 5}};
    const CaseFold* result = LookupCaseFold(f, 1, 300);
    EXPECT_EQ(result, nullptr);
}

// Test with single element - exact lo
TEST_F(LookupCaseFoldTest_484, SingleElementExactLo_484) {
    CaseFold f[1] = {{100, 100, 5}};
    const CaseFold* result = LookupCaseFold(f, 1, 100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 100);
    EXPECT_EQ(result->hi, 100);
}

// Test with two elements
TEST_F(LookupCaseFoldTest_484, TwoElementsFindFirst_484) {
    CaseFold f[2] = {
        {10, 20, 1},
        {30, 40, 2}
    };
    const CaseFold* result = LookupCaseFold(f, 2, 15);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 10);
    EXPECT_EQ(result->delta, 1);
}

TEST_F(LookupCaseFoldTest_484, TwoElementsFindSecond_484) {
    CaseFold f[2] = {
        {10, 20, 1},
        {30, 40, 2}
    };
    const CaseFold* result = LookupCaseFold(f, 2, 35);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 30);
    EXPECT_EQ(result->delta, 2);
}

// Test gap between two elements
TEST_F(LookupCaseFoldTest_484, TwoElementsGapBetween_484) {
    CaseFold f[2] = {
        {10, 20, 1},
        {30, 40, 2}
    };
    const CaseFold* result = LookupCaseFold(f, 2, 25);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 30);
}

// Test with large array to exercise binary search
TEST_F(LookupCaseFoldTest_484, LargeArrayFindMiddle_484) {
    CaseFold f[10] = {
        {100, 110, 1},
        {200, 210, 2},
        {300, 310, 3},
        {400, 410, 4},
        {500, 510, 5},
        {600, 610, 6},
        {700, 710, 7},
        {800, 810, 8},
        {900, 910, 9},
        {1000, 1010, 10}
    };
    const CaseFold* result = LookupCaseFold(f, 10, 505);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 500);
    EXPECT_EQ(result->delta, 5);
}

TEST_F(LookupCaseFoldTest_484, LargeArrayFindFirst_484) {
    CaseFold f[10] = {
        {100, 110, 1},
        {200, 210, 2},
        {300, 310, 3},
        {400, 410, 4},
        {500, 510, 5},
        {600, 610, 6},
        {700, 710, 7},
        {800, 810, 8},
        {900, 910, 9},
        {1000, 1010, 10}
    };
    const CaseFold* result = LookupCaseFold(f, 10, 105);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 100);
    EXPECT_EQ(result->delta, 1);
}

TEST_F(LookupCaseFoldTest_484, LargeArrayFindLast_484) {
    CaseFold f[10] = {
        {100, 110, 1},
        {200, 210, 2},
        {300, 310, 3},
        {400, 410, 4},
        {500, 510, 5},
        {600, 610, 6},
        {700, 710, 7},
        {800, 810, 8},
        {900, 910, 9},
        {1000, 1010, 10}
    };
    const CaseFold* result = LookupCaseFold(f, 10, 1005);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 1000);
    EXPECT_EQ(result->delta, 10);
}

TEST_F(LookupCaseFoldTest_484, LargeArrayAfterAll_484) {
    CaseFold f[10] = {
        {100, 110, 1},
        {200, 210, 2},
        {300, 310, 3},
        {400, 410, 4},
        {500, 510, 5},
        {600, 610, 6},
        {700, 710, 7},
        {800, 810, 8},
        {900, 910, 9},
        {1000, 1010, 10}
    };
    const CaseFold* result = LookupCaseFold(f, 10, 2000);
    EXPECT_EQ(result, nullptr);
}

// Test with the actual unicode case fold tables from re2
TEST_F(LookupCaseFoldTest_484, UseActualUnicodeCaseFoldTable_484) {
    // Test with the actual unicode_casefold tables if accessible
    // Looking up 'A' (65) which should have a case fold to 'a' (97)
    extern const CaseFold unicode_casefold[];
    extern const int num_unicode_casefold;
    
    const CaseFold* result = LookupCaseFold(unicode_casefold, num_unicode_casefold, 'A');
    ASSERT_NE(result, nullptr);
    // 'A' should be within the found range
    EXPECT_LE(result->lo, static_cast<Rune>('A'));
    EXPECT_GE(result->hi, static_cast<Rune>('A'));
}

// Test boundary: lo == hi (single character range)
TEST_F(LookupCaseFoldTest_484, SingleCharRange_484) {
    CaseFold f[3] = {
        {10, 10, 1},
        {20, 20, 2},
        {30, 30, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 20);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 20);
    EXPECT_EQ(result->hi, 20);
    EXPECT_EQ(result->delta, 2);
}

// Test miss on single char range
TEST_F(LookupCaseFoldTest_484, MissSingleCharRange_484) {
    CaseFold f[3] = {
        {10, 10, 1},
        {20, 20, 2},
        {30, 30, 3}
    };
    const CaseFold* result = LookupCaseFold(f, 3, 15);
    ASSERT_NE(result, nullptr);
    // Should return the next entry (20,20)
    EXPECT_EQ(result->lo, 20);
}

// Test value just after last range
TEST_F(LookupCaseFoldTest_484, ValueJustAfterLastRange_484) {
    CaseFold f[2] = {
        {10, 20, 1},
        {30, 40, 2}
    };
    const CaseFold* result = LookupCaseFold(f, 2, 41);
    EXPECT_EQ(result, nullptr);
}

// Test value just before first range
TEST_F(LookupCaseFoldTest_484, ValueJustBeforeFirstRange_484) {
    CaseFold f[2] = {
        {10, 20, 1},
        {30, 40, 2}
    };
    const CaseFold* result = LookupCaseFold(f, 2, 9);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->lo, 10);
}
