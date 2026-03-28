#include <gtest/gtest.h>
#include <cstring>

// Declare the function under test
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest);

template <>
bool Parse(const char* str, size_t n, unsigned char* dest);
}
}

// Test fixture
class ParseUnsignedCharTest_271 : public ::testing::Test {
protected:
};

// Normal operation: single character with valid destination
TEST_F(ParseUnsignedCharTest_271, SingleCharWithValidDest_271) {
    unsigned char dest = 0;
    const char* str = "A";
    bool result = re2::re2_internal::Parse(str, 1, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ('A', dest);
}

// Normal operation: single character with different values
TEST_F(ParseUnsignedCharTest_271, SingleCharDifferentValues_271) {
    unsigned char dest = 0;
    
    const char* str1 = "z";
    EXPECT_TRUE(re2::re2_internal::Parse(str1, 1, &dest));
    EXPECT_EQ('z', dest);
    
    const char* str2 = "0";
    EXPECT_TRUE(re2::re2_internal::Parse(str2, 1, &dest));
    EXPECT_EQ('0', dest);
}

// Normal operation: null byte character
TEST_F(ParseUnsignedCharTest_271, NullByteChar_271) {
    unsigned char dest = 42;
    const char str[] = {'\0'};
    bool result = re2::re2_internal::Parse(str, 1, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(0, dest);
}

// Normal operation: high value byte (255)
TEST_F(ParseUnsignedCharTest_271, HighValueByte_271) {
    unsigned char dest = 0;
    const char str[] = {static_cast<char>(0xFF)};
    bool result = re2::re2_internal::Parse(str, 1, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(255, dest);
}

// Normal operation: dest is NULL, n == 1 should return true
TEST_F(ParseUnsignedCharTest_271, NullDestWithSingleChar_271) {
    const char* str = "X";
    bool result = re2::re2_internal::Parse(str, 1, static_cast<unsigned char*>(nullptr));
    EXPECT_TRUE(result);
}

// Boundary: n == 0 should return false
TEST_F(ParseUnsignedCharTest_271, ZeroLength_271) {
    unsigned char dest = 42;
    const char* str = "A";
    bool result = re2::re2_internal::Parse(str, 0, &dest);
    EXPECT_FALSE(result);
    // dest should remain unchanged since function returns false early
    EXPECT_EQ(42, dest);
}

// Boundary: n == 2 should return false
TEST_F(ParseUnsignedCharTest_271, LengthTwo_271) {
    unsigned char dest = 42;
    const char* str = "AB";
    bool result = re2::re2_internal::Parse(str, 2, &dest);
    EXPECT_FALSE(result);
    EXPECT_EQ(42, dest);
}

// Boundary: n == 0 with NULL dest should return false
TEST_F(ParseUnsignedCharTest_271, ZeroLengthNullDest_271) {
    bool result = re2::re2_internal::Parse("", 0, static_cast<unsigned char*>(nullptr));
    EXPECT_FALSE(result);
}

// Boundary: n == 2 with NULL dest should return false
TEST_F(ParseUnsignedCharTest_271, LengthTwoNullDest_271) {
    bool result = re2::re2_internal::Parse("AB", 2, static_cast<unsigned char*>(nullptr));
    EXPECT_FALSE(result);
}

// Boundary: large n should return false
TEST_F(ParseUnsignedCharTest_271, LargeLength_271) {
    unsigned char dest = 42;
    const char* str = "Hello, World!";
    bool result = re2::re2_internal::Parse(str, 13, &dest);
    EXPECT_FALSE(result);
    EXPECT_EQ(42, dest);
}

// Edge case: special characters
TEST_F(ParseUnsignedCharTest_271, SpecialChars_271) {
    unsigned char dest = 0;
    
    const char* str1 = " ";
    EXPECT_TRUE(re2::re2_internal::Parse(str1, 1, &dest));
    EXPECT_EQ(' ', dest);
    
    const char* str2 = "\n";
    EXPECT_TRUE(re2::re2_internal::Parse(str2, 1, &dest));
    EXPECT_EQ('\n', dest);
    
    const char* str3 = "\t";
    EXPECT_TRUE(re2::re2_internal::Parse(str3, 1, &dest));
    EXPECT_EQ('\t', dest);
}

// Edge case: value 128 (boundary between signed/unsigned char)
TEST_F(ParseUnsignedCharTest_271, Value128Boundary_271) {
    unsigned char dest = 0;
    const char str[] = {static_cast<char>(128)};
    bool result = re2::re2_internal::Parse(str, 1, &dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(128, dest);
}

// Edge case: very large n value
TEST_F(ParseUnsignedCharTest_271, VeryLargeN_271) {
    unsigned char dest = 42;
    const char* str = "A";
    bool result = re2::re2_internal::Parse(str, static_cast<size_t>(-1), &dest);
    EXPECT_FALSE(result);
    EXPECT_EQ(42, dest);
}

// Verify dest is not modified when n != 1
TEST_F(ParseUnsignedCharTest_271, DestUnmodifiedOnFailure_271) {
    unsigned char dest = 99;
    const char* str = "AB";
    re2::re2_internal::Parse(str, 2, &dest);
    EXPECT_EQ(99, dest);
    
    re2::re2_internal::Parse(str, 0, &dest);
    EXPECT_EQ(99, dest);
    
    re2::re2_internal::Parse(str, 3, &dest);
    EXPECT_EQ(99, dest);
}
