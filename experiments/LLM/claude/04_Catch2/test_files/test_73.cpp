#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test fixture for catch_strnlen tests
class CatchStrnlenTest_73 : public ::testing::Test {
protected:
    // Helper to call the function under test
    std::size_t strnlen(const char* str, std::size_t n) {
        return Catch::Detail::catch_strnlen(str, n);
    }
};

// Normal operation: simple null-terminated string shorter than n
TEST_F(CatchStrnlenTest_73, NullTerminatedStringShorterThanN_73) {
    const char* str = "hello";
    std::size_t result = strnlen(str, 10);
    EXPECT_EQ(result, 5u);
}

// Normal operation: string exactly fitting within n (null at position < n)
TEST_F(CatchStrnlenTest_73, StringExactlyFitsInN_73) {
    const char* str = "hello";
    // "hello" has length 5, null at index 5, n=6 means we search 6 chars
    std::size_t result = strnlen(str, 6);
    EXPECT_EQ(result, 5u);
}

// Boundary: n equals the string length (null terminator is at index n, outside search range)
TEST_F(CatchStrnlenTest_73, NEqualsStringLengthNoNullFound_73) {
    const char* str = "hello";
    // n=5, search chars at indices 0..4, which are 'h','e','l','l','o' — no null
    std::size_t result = strnlen(str, 5);
    EXPECT_EQ(result, 5u);
}

// Boundary: n is greater than string length, null terminator found
TEST_F(CatchStrnlenTest_73, NGreaterThanStringLength_73) {
    const char* str = "abc";
    std::size_t result = strnlen(str, 100);
    EXPECT_EQ(result, 3u);
}

// Boundary: empty string (null terminator at position 0)
TEST_F(CatchStrnlenTest_73, EmptyString_73) {
    const char* str = "";
    std::size_t result = strnlen(str, 10);
    EXPECT_EQ(result, 0u);
}

// Boundary: empty string with n=0
TEST_F(CatchStrnlenTest_73, EmptyStringWithNZero_73) {
    const char* str = "";
    std::size_t result = strnlen(str, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: non-empty string with n=0
TEST_F(CatchStrnlenTest_73, NonEmptyStringWithNZero_73) {
    const char* str = "hello";
    std::size_t result = strnlen(str, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: n=1 with single character string
TEST_F(CatchStrnlenTest_73, SingleCharStringNEqualsOne_73) {
    const char* str = "a";
    // n=1, search index 0 which is 'a', no null found
    std::size_t result = strnlen(str, 1);
    EXPECT_EQ(result, 1u);
}

// Boundary: n=2 with single character string (null at index 1)
TEST_F(CatchStrnlenTest_73, SingleCharStringNEqualsTwo_73) {
    const char* str = "a";
    std::size_t result = strnlen(str, 2);
    EXPECT_EQ(result, 1u);
}

// Normal: string with embedded null character
TEST_F(CatchStrnlenTest_73, StringWithEmbeddedNull_73) {
    const char str[] = "hel\0lo";
    std::size_t result = strnlen(str, 6);
    EXPECT_EQ(result, 3u);
}

// Normal: string starting with null character
TEST_F(CatchStrnlenTest_73, StringStartingWithNull_73) {
    const char str[] = "\0hello";
    std::size_t result = strnlen(str, 6);
    EXPECT_EQ(result, 0u);
}

// Boundary: n=1 with empty string (null at index 0)
TEST_F(CatchStrnlenTest_73, EmptyStringNEqualsOne_73) {
    const char* str = "";
    std::size_t result = strnlen(str, 1);
    EXPECT_EQ(result, 0u);
}

// Normal: longer string
TEST_F(CatchStrnlenTest_73, LongerString_73) {
    const char* str = "The quick brown fox jumps over the lazy dog";
    std::size_t expected = std::strlen(str);
    std::size_t result = strnlen(str, 100);
    EXPECT_EQ(result, expected);
}

// Boundary: n exactly one more than string length
TEST_F(CatchStrnlenTest_73, NExactlyOneMoreThanLength_73) {
    const char* str = "test";
    // strlen("test") = 4, n = 5, null at index 4 is within range
    std::size_t result = strnlen(str, 5);
    EXPECT_EQ(result, 4u);
}

// Normal: buffer with no null terminator within n
TEST_F(CatchStrnlenTest_73, BufferWithNoNullTerminator_73) {
    char buf[5] = {'a', 'b', 'c', 'd', 'e'};
    std::size_t result = strnlen(buf, 5);
    EXPECT_EQ(result, 5u);
}

// Boundary: all null characters
TEST_F(CatchStrnlenTest_73, AllNullCharacters_73) {
    char buf[5] = {'\0', '\0', '\0', '\0', '\0'};
    std::size_t result = strnlen(buf, 5);
    EXPECT_EQ(result, 0u);
}

// Normal: null at the last position within n
TEST_F(CatchStrnlenTest_73, NullAtLastPositionWithinN_73) {
    char buf[5] = {'a', 'b', 'c', 'd', '\0'};
    std::size_t result = strnlen(buf, 5);
    EXPECT_EQ(result, 4u);
}
