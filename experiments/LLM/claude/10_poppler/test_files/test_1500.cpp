#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <functional>
#include "NameToCharCode.h"

class NameToCharCodeTest_1500 : public ::testing::Test {
protected:
    NameToCharCode::string_hasher hasher;
};

// Test that hashing a simple C-string produces a non-zero result (usually)
TEST_F(NameToCharCodeTest_1500, HashCStringBasic_1500) {
    const char *txt = "hello";
    size_t result = hasher(txt);
    // We just verify it doesn't crash and returns a value
    // Compare with known std::hash<std::string_view>
    size_t expected = std::hash<std::string_view>{}(std::string_view(txt));
    EXPECT_EQ(result, expected);
}

// Test that hashing a std::string produces consistent result with string_view hash
TEST_F(NameToCharCodeTest_1500, HashStdStringBasic_1500) {
    std::string txt = "hello";
    size_t result = hasher(txt);
    size_t expected = std::hash<std::string_view>{}(std::string_view(txt));
    EXPECT_EQ(result, expected);
}

// Test that C-string and std::string with same content produce same hash
TEST_F(NameToCharCodeTest_1500, CStringAndStdStringConsistency_1500) {
    const char *cstr = "test_string";
    std::string stdstr = "test_string";
    EXPECT_EQ(hasher(cstr), hasher(stdstr));
}

// Test hashing an empty C-string
TEST_F(NameToCharCodeTest_1500, HashEmptyCString_1500) {
    const char *txt = "";
    size_t result = hasher(txt);
    size_t expected = std::hash<std::string_view>{}(std::string_view(""));
    EXPECT_EQ(result, expected);
}

// Test hashing an empty std::string
TEST_F(NameToCharCodeTest_1500, HashEmptyStdString_1500) {
    std::string txt = "";
    size_t result = hasher(txt);
    size_t expected = std::hash<std::string_view>{}(std::string_view(""));
    EXPECT_EQ(result, expected);
}

// Test that different strings produce different hashes (probabilistic but very likely)
TEST_F(NameToCharCodeTest_1500, DifferentStringsDifferentHashes_1500) {
    size_t hash1 = hasher("abc");
    size_t hash2 = hasher("def");
    EXPECT_NE(hash1, hash2);
}

// Test that same string always produces the same hash (determinism)
TEST_F(NameToCharCodeTest_1500, SameStringConsistentHash_1500) {
    const char *txt = "consistent";
    EXPECT_EQ(hasher(txt), hasher(txt));
}

// Test hashing a single character string
TEST_F(NameToCharCodeTest_1500, HashSingleCharCString_1500) {
    const char *txt = "A";
    size_t result = hasher(txt);
    size_t expected = std::hash<std::string_view>{}(std::string_view("A"));
    EXPECT_EQ(result, expected);
}

// Test hashing a long string
TEST_F(NameToCharCodeTest_1500, HashLongString_1500) {
    std::string longStr(10000, 'x');
    size_t result = hasher(longStr);
    size_t expected = std::hash<std::string_view>{}(std::string_view(longStr));
    EXPECT_EQ(result, expected);
}

// Test with special characters
TEST_F(NameToCharCodeTest_1500, HashSpecialCharacters_1500) {
    const char *txt = "hello\nworld\t!@#$%^&*()";
    size_t result = hasher(txt);
    size_t expected = std::hash<std::string_view>{}(std::string_view(txt));
    EXPECT_EQ(result, expected);
}

// Test strings that differ by one character
TEST_F(NameToCharCodeTest_1500, StringsDifferByOneChar_1500) {
    size_t hash1 = hasher("abcd");
    size_t hash2 = hasher("abce");
    EXPECT_NE(hash1, hash2);
}

// Test that the hasher can be used in an unordered_map-like context
TEST_F(NameToCharCodeTest_1500, UsableAsHashFunction_1500) {
    std::unordered_map<std::string, int, NameToCharCode::string_hasher> map;
    map["key1"] = 1;
    map["key2"] = 2;
    EXPECT_EQ(map["key1"], 1);
    EXPECT_EQ(map["key2"], 2);
}
