#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

// We need to include the relevant headers from the poppler project
// Since we're testing EntryGooStringComparer, we need the Catalog header
#include "poppler/Catalog.h"
#include "poppler/GooString.h"

// Since we need to work with the EntryGooStringComparer struct and its interface,
// we'll create minimal test structures that match what the comparer expects.

// Test fixture for EntryGooStringComparer
class EntryGooStringComparerTest_1897 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper struct to simulate an entry with a 'name' field that has toStr()
// This mimics what the actual codebase entries look like
struct MockEntry {
    GooString name;
    MockEntry(const char *n) : name(n) {}
};

// Test that the comparer's get function returns the correct string from an entry
TEST_F(EntryGooStringComparerTest_1897, GetReturnsEntryName_1897) {
    auto entry = std::make_unique<MockEntry>("testName");
    EntryGooStringComparer comparer;
    const std::string &result = EntryGooStringComparer::get(entry);
    EXPECT_EQ(result, "testName");
}

// Test with empty string entry
TEST_F(EntryGooStringComparerTest_1897, GetReturnsEmptyStringForEmptyName_1897) {
    auto entry = std::make_unique<MockEntry>("");
    const std::string &result = EntryGooStringComparer::get(entry);
    EXPECT_EQ(result, "");
}

// Test with a longer string
TEST_F(EntryGooStringComparerTest_1897, GetReturnsLongString_1897) {
    std::string longName(1000, 'a');
    auto entry = std::make_unique<MockEntry>(longName.c_str());
    const std::string &result = EntryGooStringComparer::get(entry);
    EXPECT_EQ(result, longName);
}

// Test the comparison operator - comparing two entries where lhs < rhs
TEST_F(EntryGooStringComparerTest_1897, ComparerOrdersAlphabetically_1897) {
    auto entry1 = std::make_unique<MockEntry>("apple");
    auto entry2 = std::make_unique<MockEntry>("banana");
    EntryGooStringComparer comparer;
    // The operator() should provide ordering
    bool result = comparer(entry1, entry2);
    EXPECT_TRUE(result); // "apple" < "banana"
}

// Test the comparison operator - comparing two entries where lhs > rhs
TEST_F(EntryGooStringComparerTest_1897, ComparerOrdersReverseAlphabetically_1897) {
    auto entry1 = std::make_unique<MockEntry>("banana");
    auto entry2 = std::make_unique<MockEntry>("apple");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    EXPECT_FALSE(result); // "banana" > "apple"
}

// Test the comparison operator - comparing two equal entries
TEST_F(EntryGooStringComparerTest_1897, ComparerEqualEntries_1897) {
    auto entry1 = std::make_unique<MockEntry>("same");
    auto entry2 = std::make_unique<MockEntry>("same");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    EXPECT_FALSE(result); // "same" is not less than "same"
}

// Test comparison with empty strings
TEST_F(EntryGooStringComparerTest_1897, ComparerEmptyStrings_1897) {
    auto entry1 = std::make_unique<MockEntry>("");
    auto entry2 = std::make_unique<MockEntry>("");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    EXPECT_FALSE(result); // "" is not less than ""
}

// Test comparison where one is empty
TEST_F(EntryGooStringComparerTest_1897, ComparerEmptyVsNonEmpty_1897) {
    auto entry1 = std::make_unique<MockEntry>("");
    auto entry2 = std::make_unique<MockEntry>("nonempty");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    EXPECT_TRUE(result); // "" < "nonempty"
}

// Test that comparer can be used for sorting a vector of entries
TEST_F(EntryGooStringComparerTest_1897, ComparerWorksWithSort_1897) {
    std::vector<std::unique_ptr<MockEntry>> entries;
    entries.push_back(std::make_unique<MockEntry>("cherry"));
    entries.push_back(std::make_unique<MockEntry>("apple"));
    entries.push_back(std::make_unique<MockEntry>("banana"));

    EntryGooStringComparer comparer;
    std::sort(entries.begin(), entries.end(), comparer);

    EXPECT_EQ(EntryGooStringComparer::get(entries[0]), "apple");
    EXPECT_EQ(EntryGooStringComparer::get(entries[1]), "banana");
    EXPECT_EQ(EntryGooStringComparer::get(entries[2]), "cherry");
}

// Test get with GooString pointer (the other overload)
TEST_F(EntryGooStringComparerTest_1897, GetFromGooStringPointer_1897) {
    GooString gooStr("hello");
    const std::string &result = EntryGooStringComparer::get(&gooStr);
    EXPECT_EQ(result, "hello");
}

// Test get with GooString pointer for empty string
TEST_F(EntryGooStringComparerTest_1897, GetFromGooStringPointerEmpty_1897) {
    GooString gooStr("");
    const std::string &result = EntryGooStringComparer::get(&gooStr);
    EXPECT_EQ(result, "");
}

// Test comparison with special characters
TEST_F(EntryGooStringComparerTest_1897, ComparerSpecialCharacters_1897) {
    auto entry1 = std::make_unique<MockEntry>("!special");
    auto entry2 = std::make_unique<MockEntry>("normal");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    // '!' has lower ASCII value than 'n', so should be true
    EXPECT_TRUE(result);
}

// Test comparison with numeric strings
TEST_F(EntryGooStringComparerTest_1897, ComparerNumericStrings_1897) {
    auto entry1 = std::make_unique<MockEntry>("123");
    auto entry2 = std::make_unique<MockEntry>("456");
    EntryGooStringComparer comparer;
    bool result = comparer(entry1, entry2);
    EXPECT_TRUE(result); // "123" < "456" lexicographically
}

// Test comparison is strict weak ordering (irreflexivity)
TEST_F(EntryGooStringComparerTest_1897, ComparerIrreflexive_1897) {
    auto entry = std::make_unique<MockEntry>("test");
    EntryGooStringComparer comparer;
    // An element should not be less than itself
    EXPECT_FALSE(comparer(entry, entry));
}
