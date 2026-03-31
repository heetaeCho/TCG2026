#include <gtest/gtest.h>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

// We need to include the necessary headers from the poppler project
// Based on the interface, we need GooString and the Catalog header
#include "GooString.h"
#include "Catalog.h"

// If Catalog.h doesn't directly expose EntryGooStringComparer, we may need
// to include the cc file or a specific header. Based on the provided code,
// the struct is defined in Catalog.cc. We'll test it through its observable behavior.

// Since EntryGooStringComparer is defined in Catalog.cc, we need to recreate
// enough of the interface to test. However, per constraints, we treat it as
// a black box. Let's include what's needed.

// The struct has two static get() overloads:
// 1. get(const GooString *string) -> returns const std::string&
// 2. get(const auto &entry) -> returns const std::string& (for other entry types)
// And operator() that compares using get() on both sides

class EntryGooStringComparerTest_1898 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that comparing two GooString pointers where lhs < rhs returns true
TEST_F(EntryGooStringComparerTest_1898, LhsLessThanRhs_GooStringPtr_1898) {
    EntryGooStringComparer comparer;
    GooString a("apple");
    GooString b("banana");
    
    EXPECT_TRUE(comparer(&a, &b));
}

// Test that comparing two GooString pointers where lhs > rhs returns false
TEST_F(EntryGooStringComparerTest_1898, LhsGreaterThanRhs_GooStringPtr_1898) {
    EntryGooStringComparer comparer;
    GooString a("banana");
    GooString b("apple");
    
    EXPECT_FALSE(comparer(&a, &b));
}

// Test that comparing two equal GooString pointers returns false (strict weak ordering)
TEST_F(EntryGooStringComparerTest_1898, EqualStrings_GooStringPtr_1898) {
    EntryGooStringComparer comparer;
    GooString a("same");
    GooString b("same");
    
    EXPECT_FALSE(comparer(&a, &b));
}

// Test with empty strings - both empty should return false
TEST_F(EntryGooStringComparerTest_1898, BothEmptyStrings_1898) {
    EntryGooStringComparer comparer;
    GooString a("");
    GooString b("");
    
    EXPECT_FALSE(comparer(&a, &b));
}

// Test with empty string vs non-empty string
TEST_F(EntryGooStringComparerTest_1898, EmptyVsNonEmpty_1898) {
    EntryGooStringComparer comparer;
    GooString a("");
    GooString b("notempty");
    
    EXPECT_TRUE(comparer(&a, &b));
}

// Test with non-empty string vs empty string
TEST_F(EntryGooStringComparerTest_1898, NonEmptyVsEmpty_1898) {
    EntryGooStringComparer comparer;
    GooString a("notempty");
    GooString b("");
    
    EXPECT_FALSE(comparer(&a, &b));
}

// Test that the comparer works with single character strings
TEST_F(EntryGooStringComparerTest_1898, SingleCharStrings_1898) {
    EntryGooStringComparer comparer;
    GooString a("a");
    GooString b("z");
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}

// Test lexicographic ordering - prefix comparison
TEST_F(EntryGooStringComparerTest_1898, PrefixComparison_1898) {
    EntryGooStringComparer comparer;
    GooString a("app");
    GooString b("apple");
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}

// Test case sensitivity - uppercase vs lowercase
TEST_F(EntryGooStringComparerTest_1898, CaseSensitivity_1898) {
    EntryGooStringComparer comparer;
    GooString a("Apple");
    GooString b("apple");
    
    // 'A' (65) < 'a' (97) in ASCII
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}

// Test that the comparer can be used with std::set for ordering
TEST_F(EntryGooStringComparerTest_1898, UsableInStdSet_1898) {
    std::set<GooString *, EntryGooStringComparer> sortedSet;
    
    GooString c("cherry");
    GooString a("apple");
    GooString b("banana");
    
    sortedSet.insert(&c);
    sortedSet.insert(&a);
    sortedSet.insert(&b);
    
    EXPECT_EQ(sortedSet.size(), 3u);
    
    auto it = sortedSet.begin();
    // Should be in alphabetical order: apple, banana, cherry
    EXPECT_EQ((*it)->toStr(), "apple");
    ++it;
    EXPECT_EQ((*it)->toStr(), "banana");
    ++it;
    EXPECT_EQ((*it)->toStr(), "cherry");
}

// Test irreflexivity - a < a should be false
TEST_F(EntryGooStringComparerTest_1898, Irreflexivity_1898) {
    EntryGooStringComparer comparer;
    GooString a("test");
    
    EXPECT_FALSE(comparer(&a, &a));
}

// Test asymmetry - if a < b then !(b < a)
TEST_F(EntryGooStringComparerTest_1898, Asymmetry_1898) {
    EntryGooStringComparer comparer;
    GooString a("abc");
    GooString b("def");
    
    if (comparer(&a, &b)) {
        EXPECT_FALSE(comparer(&b, &a));
    } else {
        EXPECT_TRUE(comparer(&b, &a));
    }
}

// Test transitivity - if a < b and b < c then a < c
TEST_F(EntryGooStringComparerTest_1898, Transitivity_1898) {
    EntryGooStringComparer comparer;
    GooString a("aaa");
    GooString b("bbb");
    GooString c("ccc");
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_TRUE(comparer(&b, &c));
    EXPECT_TRUE(comparer(&a, &c));
}

// Test with numeric strings
TEST_F(EntryGooStringComparerTest_1898, NumericStrings_1898) {
    EntryGooStringComparer comparer;
    GooString a("123");
    GooString b("456");
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}

// Test with strings containing special characters
TEST_F(EntryGooStringComparerTest_1898, SpecialCharacters_1898) {
    EntryGooStringComparer comparer;
    GooString a("!special");
    GooString b("~special");
    
    // '!' (33) < '~' (126)
    EXPECT_TRUE(comparer(&a, &b));
}

// Test that duplicates are detected (set won't insert duplicates)
TEST_F(EntryGooStringComparerTest_1898, DuplicateDetectionInSet_1898) {
    std::set<GooString *, EntryGooStringComparer> sortedSet;
    
    GooString a("duplicate");
    GooString b("duplicate");
    
    sortedSet.insert(&a);
    sortedSet.insert(&b);
    
    // Both have same string value, so set should treat them as equivalent
    EXPECT_EQ(sortedSet.size(), 1u);
}

// Test with long strings
TEST_F(EntryGooStringComparerTest_1898, LongStrings_1898) {
    EntryGooStringComparer comparer;
    std::string longA(1000, 'a');
    std::string longB(1000, 'b');
    GooString a(longA);
    GooString b(longB);
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}

// Test with strings differing only at the end
TEST_F(EntryGooStringComparerTest_1898, DifferOnlyAtEnd_1898) {
    EntryGooStringComparer comparer;
    GooString a("identical_prefix_a");
    GooString b("identical_prefix_b");
    
    EXPECT_TRUE(comparer(&a, &b));
    EXPECT_FALSE(comparer(&b, &a));
}
