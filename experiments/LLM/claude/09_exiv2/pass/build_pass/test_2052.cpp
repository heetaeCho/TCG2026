#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <algorithm>

// Include the necessary headers for the types and function under test
// Based on the code, we need UTF16Unit type and the SwapUTF16 function declaration

// Forward declarations matching what we can infer from the interface
typedef unsigned short UTF16Unit;

// Declaration of the function under test
extern void SwapUTF16(const UTF16Unit* utf16In, UTF16Unit* utf16Out, const size_t utf16Len);

// Helper to swap bytes of a UTF16Unit
static UTF16Unit ManualSwap(UTF16Unit val) {
    return static_cast<UTF16Unit>((val >> 8) | (val << 8));
}

class SwapUTF16Test_2052 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: swap a single element
TEST_F(SwapUTF16Test_2052, SingleElement_2052) {
    UTF16Unit input[] = {0x0041};  // 'A' in UTF-16
    UTF16Unit output[1] = {0};
    
    SwapUTF16(input, output, 1);
    
    EXPECT_EQ(output[0], ManualSwap(0x0041));
}

// Test normal operation: swap multiple elements
TEST_F(SwapUTF16Test_2052, MultipleElements_2052) {
    UTF16Unit input[] = {0x0041, 0x0042, 0x0043, 0x0044};
    UTF16Unit output[4] = {0};
    
    SwapUTF16(input, output, 4);
    
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(output[i], ManualSwap(input[i])) << "Mismatch at index " << i;
    }
}

// Test boundary condition: zero length - should not modify output
TEST_F(SwapUTF16Test_2052, ZeroLength_2052) {
    UTF16Unit input[] = {0x1234};
    UTF16Unit output[] = {0xFFFF};
    
    SwapUTF16(input, output, 0);
    
    // Output should remain unchanged
    EXPECT_EQ(output[0], 0xFFFF);
}

// Test with byte values that result in known swaps
TEST_F(SwapUTF16Test_2052, KnownByteSwapValues_2052) {
    UTF16Unit input[] = {0x1234, 0xABCD, 0xFF00, 0x00FF};
    UTF16Unit output[4] = {0};
    
    SwapUTF16(input, output, 4);
    
    EXPECT_EQ(output[0], static_cast<UTF16Unit>(0x3412));
    EXPECT_EQ(output[1], static_cast<UTF16Unit>(0xCDAB));
    EXPECT_EQ(output[2], static_cast<UTF16Unit>(0x00FF));
    EXPECT_EQ(output[3], static_cast<UTF16Unit>(0xFF00));
}

// Test that swapping twice returns to original
TEST_F(SwapUTF16Test_2052, DoubleSwapReturnsOriginal_2052) {
    UTF16Unit input[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    UTF16Unit intermediate[4] = {0};
    UTF16Unit output[4] = {0};
    
    SwapUTF16(input, intermediate, 4);
    SwapUTF16(intermediate, output, 4);
    
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(output[i], input[i]) << "Double swap mismatch at index " << i;
    }
}

// Test in-place swap (input and output are the same buffer)
TEST_F(SwapUTF16Test_2052, InPlaceSwap_2052) {
    UTF16Unit buffer[] = {0x1234, 0x5678};
    UTF16Unit expected0 = ManualSwap(0x1234);
    UTF16Unit expected1 = ManualSwap(0x5678);
    
    SwapUTF16(buffer, buffer, 2);
    
    EXPECT_EQ(buffer[0], expected0);
    EXPECT_EQ(buffer[1], expected1);
}

// Test with all zeros
TEST_F(SwapUTF16Test_2052, AllZeros_2052) {
    UTF16Unit input[] = {0x0000, 0x0000, 0x0000};
    UTF16Unit output[3] = {0xFFFF, 0xFFFF, 0xFFFF};
    
    SwapUTF16(input, output, 3);
    
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(output[i], static_cast<UTF16Unit>(0x0000)) << "Index " << i;
    }
}

// Test with all 0xFFFF
TEST_F(SwapUTF16Test_2052, AllOnes_2052) {
    UTF16Unit input[] = {0xFFFF, 0xFFFF};
    UTF16Unit output[2] = {0};
    
    SwapUTF16(input, output, 2);
    
    EXPECT_EQ(output[0], static_cast<UTF16Unit>(0xFFFF));
    EXPECT_EQ(output[1], static_cast<UTF16Unit>(0xFFFF));
}

// Test with a larger buffer
TEST_F(SwapUTF16Test_2052, LargerBuffer_2052) {
    const size_t len = 256;
    std::vector<UTF16Unit> input(len);
    std::vector<UTF16Unit> output(len, 0);
    
    for (size_t i = 0; i < len; ++i) {
        input[i] = static_cast<UTF16Unit>(i * 257); // various values
    }
    
    SwapUTF16(input.data(), output.data(), len);
    
    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(output[i], ManualSwap(input[i])) << "Mismatch at index " << i;
    }
}

// Test with surrogate pair values (valid UTF-16 surrogates)
TEST_F(SwapUTF16Test_2052, SurrogatePairValues_2052) {
    UTF16Unit input[] = {0xD800, 0xDC00};  // High and low surrogates
    UTF16Unit output[2] = {0};
    
    SwapUTF16(input, output, 2);
    
    EXPECT_EQ(output[0], ManualSwap(0xD800));
    EXPECT_EQ(output[1], ManualSwap(0xDC00));
}

// Test that only utf16Len elements are written (partial buffer)
TEST_F(SwapUTF16Test_2052, PartialBufferSwap_2052) {
    UTF16Unit input[] = {0x1234, 0x5678, 0x9ABC};
    UTF16Unit output[] = {0xDEAD, 0xBEEF, 0xCAFE};
    
    // Only swap first 2 elements
    SwapUTF16(input, output, 2);
    
    EXPECT_EQ(output[0], ManualSwap(0x1234));
    EXPECT_EQ(output[1], ManualSwap(0x5678));
    // Third element should remain untouched
    EXPECT_EQ(output[2], static_cast<UTF16Unit>(0xCAFE));
}

// Test with symmetric byte pattern
TEST_F(SwapUTF16Test_2052, SymmetricBytePattern_2052) {
    // Values where high byte == low byte; swap should be identity
    UTF16Unit input[] = {0x0000, 0x0101, 0x2222, 0xAAAA, 0xFFFF};
    UTF16Unit output[5] = {0};
    
    SwapUTF16(input, output, 5);
    
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(output[i], input[i]) << "Symmetric value should remain same at index " << i;
    }
}
