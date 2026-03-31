#include <gtest/gtest.h>
#include <cstring>
#include <climits>

// Forward declare the function under test
namespace YAML {
namespace detail {
namespace fp_formatting {
int ConvertToChars(char* begin, char* end, size_t value, int width = 1);
}
}
}

using YAML::detail::fp_formatting::ConvertToChars;

class ConvertToCharsTest_430 : public ::testing::Test {
protected:
    char buffer[64];
    
    void SetUp() override {
        std::memset(buffer, 'X', sizeof(buffer));
    }
};

// Normal operation: convert a simple single-digit value
TEST_F(ConvertToCharsTest_430, SingleDigitValue_430) {
    int result = ConvertToChars(buffer, buffer + 20, 5);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], '5');
}

// Normal operation: convert a multi-digit value
TEST_F(ConvertToCharsTest_430, MultiDigitValue_430) {
    int result = ConvertToChars(buffer, buffer + 20, 12345);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(std::string(buffer, result), "12345");
}

// Normal operation: convert zero with default width
TEST_F(ConvertToCharsTest_430, ZeroValueDefaultWidth_430) {
    int result = ConvertToChars(buffer, buffer + 20, 0);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], '0');
}

// Normal operation: convert zero with larger width
TEST_F(ConvertToCharsTest_430, ZeroValueWithWidth5_430) {
    int result = ConvertToChars(buffer, buffer + 20, 0, 5);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(std::string(buffer, result), "00000");
}

// Normal operation: width larger than number of digits causes zero-padding
TEST_F(ConvertToCharsTest_430, PaddingWithWidth_430) {
    int result = ConvertToChars(buffer, buffer + 20, 42, 5);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(std::string(buffer, result), "00042");
}

// Normal operation: width equal to number of digits
TEST_F(ConvertToCharsTest_430, WidthEqualToDigits_430) {
    int result = ConvertToChars(buffer, buffer + 20, 999, 3);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(std::string(buffer, result), "999");
}

// Normal operation: width less than number of digits (value has more digits than width)
TEST_F(ConvertToCharsTest_430, ValueWiderThanWidth_430) {
    int result = ConvertToChars(buffer, buffer + 20, 12345, 2);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(std::string(buffer, result), "12345");
}

// Normal operation: large value
TEST_F(ConvertToCharsTest_430, LargeValue_430) {
    int result = ConvertToChars(buffer, buffer + 20, 1000000000ULL);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(std::string(buffer, result), "1000000000");
}

// Normal operation: value 1
TEST_F(ConvertToCharsTest_430, ValueOne_430) {
    int result = ConvertToChars(buffer, buffer + 20, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], '1');
}

// Normal operation: value 10 with width 1
TEST_F(ConvertToCharsTest_430, ValueTenWidthOne_430) {
    int result = ConvertToChars(buffer, buffer + 20, 10, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(std::string(buffer, result), "10");
}

// Boundary: buffer exactly 20 bytes
TEST_F(ConvertToCharsTest_430, ExactMinimumBufferSize_430) {
    char smallbuf[20];
    std::memset(smallbuf, 'X', sizeof(smallbuf));
    int result = ConvertToChars(smallbuf, smallbuf + 20, 99, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(std::string(smallbuf, result), "99");
}

// Error case: buffer smaller than 20 bytes
TEST_F(ConvertToCharsTest_430, BufferTooSmall_430) {
    int result = ConvertToChars(buffer, buffer + 19, 42);
    EXPECT_EQ(result, -1);
}

// Error case: width less than 1
TEST_F(ConvertToCharsTest_430, WidthLessThanOne_430) {
    int result = ConvertToChars(buffer, buffer + 20, 42, 0);
    EXPECT_EQ(result, -1);
}

// Error case: end before begin
TEST_F(ConvertToCharsTest_430, EndBeforeBegin_430) {
    int result = ConvertToChars(buffer + 20, buffer, 42);
    EXPECT_EQ(result, -1);
}

// Error case: width larger than buffer
TEST_F(ConvertToCharsTest_430, WidthLargerThanBuffer_430) {
    // buffer of 20, but width = 21
    int result = ConvertToChars(buffer, buffer + 20, 42, 21);
    EXPECT_EQ(result, -1);
}

// Normal operation: width of 1 with value 0
TEST_F(ConvertToCharsTest_430, WidthOneZero_430) {
    int result = ConvertToChars(buffer, buffer + 20, 0, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buffer[0], '0');
}

// Normal operation: larger buffer than needed
TEST_F(ConvertToCharsTest_430, LargerBufferThanNeeded_430) {
    int result = ConvertToChars(buffer, buffer + 64, 789, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(std::string(buffer, result), "789");
}

// Normal operation: padding with width 10 and small value
TEST_F(ConvertToCharsTest_430, PaddingWidth10SmallValue_430) {
    int result = ConvertToChars(buffer, buffer + 20, 7, 10);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(std::string(buffer, result), "0000000007");
}

// Normal operation: all nines
TEST_F(ConvertToCharsTest_430, AllNines_430) {
    int result = ConvertToChars(buffer, buffer + 20, 9999999999ULL, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(std::string(buffer, result), "9999999999");
}

// Normal operation: value with trailing zeros
TEST_F(ConvertToCharsTest_430, ValueWithTrailingZeros_430) {
    int result = ConvertToChars(buffer, buffer + 20, 100, 1);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(std::string(buffer, result), "100");
}

// Boundary: width exactly equal to buffer size of 20
TEST_F(ConvertToCharsTest_430, Width20Buffer20_430) {
    int result = ConvertToChars(buffer, buffer + 20, 0, 20);
    ASSERT_GT(result, 0);
    EXPECT_EQ(result, 20);
    EXPECT_EQ(std::string(buffer, result), "00000000000000000000");
}

// Normal operation: value that uses exactly 20 digits (max for size_t on 64-bit)
TEST_F(ConvertToCharsTest_430, MaxSizeT64Bit_430) {
    // Only run meaningful test on 64-bit platforms
    if (sizeof(size_t) == 8) {
        size_t maxval = 18446744073709551615ULL; // UINT64_MAX
        int result = ConvertToChars(buffer, buffer + 20, maxval, 1);
        ASSERT_GT(result, 0);
        EXPECT_EQ(result, 20);
        EXPECT_EQ(std::string(buffer, result), "18446744073709551615");
    }
}

// Error case: end equals begin (buffer size 0)
TEST_F(ConvertToCharsTest_430, ZeroSizeBuffer_430) {
    int result = ConvertToChars(buffer, buffer, 42);
    EXPECT_EQ(result, -1);
}

// Normal: width 1 and single digit values 0-9
TEST_F(ConvertToCharsTest_430, AllSingleDigits_430) {
    for (size_t i = 0; i <= 9; ++i) {
        std::memset(buffer, 'X', sizeof(buffer));
        int result = ConvertToChars(buffer, buffer + 20, i, 1);
        ASSERT_GT(result, 0);
        EXPECT_EQ(result, 1);
        EXPECT_EQ(buffer[0], '0' + static_cast<char>(i));
    }
}

// Error case: negative width (width = -1)
TEST_F(ConvertToCharsTest_430, NegativeWidth_430) {
    int result = ConvertToChars(buffer, buffer + 20, 42, -1);
    EXPECT_EQ(result, -1);
}
