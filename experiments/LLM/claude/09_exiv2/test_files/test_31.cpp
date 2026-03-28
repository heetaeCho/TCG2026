#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace {

// A simple struct that supports equality comparison with an int key
struct TagInfo {
    int id;
    const char* name;

    bool operator==(int key) const {
        return id == key;
    }
};

// A struct with string-based key comparison
struct StringEntry {
    std::string key;
    int value;

    bool operator==(const std::string& k) const {
        return key == k;
    }
};

// Test fixture
class FindTest_31 : public ::testing::Test {
protected:
    TagInfo tags[5] = {
        {1, "Tag1"},
        {2, "Tag2"},
        {3, "Tag3"},
        {4, "Tag4"},
        {5, "Tag5"},
    };

    StringEntry stringEntries[3] = {
        {"alpha", 10},
        {"beta", 20},
        {"gamma", 30},
    };

    int intArray[6] = {10, 20, 30, 40, 50, 60};
};

// Test finding an element that exists at the beginning
TEST_F(FindTest_31, FindFirstElement_31) {
    const TagInfo* result = Exiv2::find(tags, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->id, 1);
    EXPECT_STREQ(result->name, "Tag1");
}

// Test finding an element that exists at the end
TEST_F(FindTest_31, FindLastElement_31) {
    const TagInfo* result = Exiv2::find(tags, 5);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->id, 5);
    EXPECT_STREQ(result->name, "Tag5");
}

// Test finding an element in the middle
TEST_F(FindTest_31, FindMiddleElement_31) {
    const TagInfo* result = Exiv2::find(tags, 3);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->id, 3);
    EXPECT_STREQ(result->name, "Tag3");
}

// Test finding an element that does not exist
TEST_F(FindTest_31, FindNonExistentElement_31) {
    const TagInfo* result = Exiv2::find(tags, 99);
    EXPECT_EQ(result, nullptr);
}

// Test finding with negative key that doesn't exist
TEST_F(FindTest_31, FindNegativeKeyNotFound_31) {
    const TagInfo* result = Exiv2::find(tags, -1);
    EXPECT_EQ(result, nullptr);
}

// Test finding with zero key that doesn't exist
TEST_F(FindTest_31, FindZeroKeyNotFound_31) {
    const TagInfo* result = Exiv2::find(tags, 0);
    EXPECT_EQ(result, nullptr);
}

// Test with a single element array - found
TEST_F(FindTest_31, FindSingleElementArrayFound_31) {
    TagInfo single[1] = {{42, "Only"}};
    const TagInfo* result = Exiv2::find(single, 42);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->id, 42);
    EXPECT_STREQ(result->name, "Only");
}

// Test with a single element array - not found
TEST_F(FindTest_31, FindSingleElementArrayNotFound_31) {
    TagInfo single[1] = {{42, "Only"}};
    const TagInfo* result = Exiv2::find(single, 43);
    EXPECT_EQ(result, nullptr);
}

// Test with string-based keys - found
TEST_F(FindTest_31, FindStringKeyFound_31) {
    const StringEntry* result = Exiv2::find(stringEntries, std::string("beta"));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->key, "beta");
    EXPECT_EQ(result->value, 20);
}

// Test with string-based keys - not found
TEST_F(FindTest_31, FindStringKeyNotFound_31) {
    const StringEntry* result = Exiv2::find(stringEntries, std::string("delta"));
    EXPECT_EQ(result, nullptr);
}

// Test with plain integer array - found
TEST_F(FindTest_31, FindIntArrayFound_31) {
    const int* result = Exiv2::find(intArray, 30);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 30);
}

// Test with plain integer array - not found
TEST_F(FindTest_31, FindIntArrayNotFound_31) {
    const int* result = Exiv2::find(intArray, 99);
    EXPECT_EQ(result, nullptr);
}

// Test with plain integer array - first element
TEST_F(FindTest_31, FindIntArrayFirstElement_31) {
    const int* result = Exiv2::find(intArray, 10);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 10);
}

// Test with plain integer array - last element
TEST_F(FindTest_31, FindIntArrayLastElement_31) {
    const int* result = Exiv2::find(intArray, 60);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 60);
}

// Test that find returns a pointer to the correct position in the array
TEST_F(FindTest_31, FindReturnsCorrectPointer_31) {
    const TagInfo* result = Exiv2::find(tags, 3);
    ASSERT_NE(result, nullptr);
    // The returned pointer should point to the third element (index 2)
    EXPECT_EQ(result, &tags[2]);
}

// Test with duplicate keys - should return the first match
TEST_F(FindTest_31, FindDuplicateKeysReturnsFirst_31) {
    TagInfo duplicates[4] = {
        {1, "First"},
        {2, "Second"},
        {2, "Duplicate"},
        {3, "Third"},
    };
    const TagInfo* result = Exiv2::find(duplicates, 2);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->id, 2);
    EXPECT_STREQ(result->name, "Second");
    // Verify it's pointing to the first occurrence
    EXPECT_EQ(result, &duplicates[1]);
}

// Test with string key - first element
TEST_F(FindTest_31, FindStringKeyFirstElement_31) {
    const StringEntry* result = Exiv2::find(stringEntries, std::string("alpha"));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 10);
}

// Test with string key - last element
TEST_F(FindTest_31, FindStringKeyLastElement_31) {
    const StringEntry* result = Exiv2::find(stringEntries, std::string("gamma"));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 30);
}

// Test with empty string key
TEST_F(FindTest_31, FindEmptyStringKeyNotFound_31) {
    const StringEntry* result = Exiv2::find(stringEntries, std::string(""));
    EXPECT_EQ(result, nullptr);
}

// Test with an array of empty string entries
TEST_F(FindTest_31, FindEmptyStringKeyFound_31) {
    StringEntry emptyEntries[2] = {
        {"", 100},
        {"notempty", 200},
    };
    const StringEntry* result = Exiv2::find(emptyEntries, std::string(""));
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value, 100);
}

// Test constness - result should be const pointer
TEST_F(FindTest_31, FindReturnsConstPointer_31) {
    const TagInfo* result = Exiv2::find(tags, 1);
    ASSERT_NE(result, nullptr);
    // This test simply verifies the return type is const T*
    static_assert(std::is_same<decltype(result), const TagInfo*>::value,
                  "find should return const T*");
}

}  // namespace
