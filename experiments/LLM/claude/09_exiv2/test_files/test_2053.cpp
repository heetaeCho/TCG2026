#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <algorithm>

// Include the header that declares the function and types
// Based on the implementation file path, we need the appropriate headers
#include "../../xmpsdk/src/UnicodeConversions.hpp"

// If the header doesn't exist at that path, we may need to declare externally
// The function signature from the code:
// void SwapUTF32(const UTF32Unit* utf32In, UTF32Unit* utf32Out, const size_t utf32Len);
// UTF32Unit is typically uint32_t

#ifndef UTF32Unit
typedef uint32_t UTF32Unit;
#endif

extern "C++" {
    void SwapUTF32(const UTF32Unit* utf32In, UTF32Unit* utf32Out, const size_t utf32Len);
}

class SwapUTF32Test_2053 : public ::testing::Test {
protected:
    // Helper to swap bytes of a 32-bit value
    static UTF32Unit ManualSwap32(UTF32Unit val) {
        return ((val & 0xFF000000) >> 24) |
               ((val & 0x00FF0000) >> 8)  |
               ((val & 0x0000FF00) << 8)  |
               ((val & 0x000000FF) << 24);
    }
};

// Test with zero length - should not crash or modify output
TEST_F(SwapUTF32Test_2053, ZeroLength_2053) {
    UTF32Unit input[] = {0x01020304};
    UTF32Unit output[] = {0xDEADBEEF};
    SwapUTF32(input, output, 0);
    // Output should remain unchanged since no elements are processed
    EXPECT_EQ(output[0], 0xDEADBEEF);
}

// Test swapping a single element
TEST_F(SwapUTF32Test_2053, SingleElement_2053) {
    UTF32Unit input[] = {0x01020304};
    UTF32Unit output[1] = {0};
    SwapUTF32(input, output, 1);
    EXPECT_EQ(output[0], ManualSwap32(0x01020304));
}

// Test swapping multiple elements
TEST_F(SwapUTF32Test_2053, MultipleElements_2053) {
    UTF32Unit input[] = {0x01020304, 0xAABBCCDD, 0x11223344};
    UTF32Unit output[3] = {0};
    SwapUTF32(input, output, 3);
    EXPECT_EQ(output[0], ManualSwap32(0x01020304));
    EXPECT_EQ(output[1], ManualSwap32(0xAABBCCDD));
    EXPECT_EQ(output[2], ManualSwap32(0x11223344));
}

// Test with all zeros
TEST_F(SwapUTF32Test_2053, AllZeros_2053) {
    UTF32Unit input[] = {0x00000000, 0x00000000};
    UTF32Unit output[2] = {0xFFFFFFFF, 0xFFFFFFFF};
    SwapUTF32(input, output, 2);
    EXPECT_EQ(output[0], 0x00000000);
    EXPECT_EQ(output[1], 0x00000000);
}

// Test with all 0xFF bytes - should remain the same after swap
TEST_F(SwapUTF32Test_2053, AllOnes_2053) {
    UTF32Unit input[] = {0xFFFFFFFF};
    UTF32Unit output[1] = {0};
    SwapUTF32(input, output, 1);
    EXPECT_EQ(output[0], 0xFFFFFFFF);
}

// Test that swapping is symmetric (double swap returns original)
TEST_F(SwapUTF32Test_2053, DoubleSwapReturnsOriginal_2053) {
    UTF32Unit input[] = {0x01020304, 0xDEADBEEF, 0x12345678};
    UTF32Unit intermediate[3] = {0};
    UTF32Unit restored[3] = {0};
    SwapUTF32(input, intermediate, 3);
    SwapUTF32(intermediate, restored, 3);
    EXPECT_EQ(restored[0], input[0]);
    EXPECT_EQ(restored[1], input[1]);
    EXPECT_EQ(restored[2], input[2]);
}

// Test with palindromic byte pattern
TEST_F(SwapUTF32Test_2053, PalindromicPattern_2053) {
    UTF32Unit input[] = {0xABCDCDAB};
    UTF32Unit output[1] = {0};
    SwapUTF32(input, output, 1);
    EXPECT_EQ(output[0], ManualSwap32(0xABCDCDAB));
}

// Test in-place swap (input and output point to same buffer)
TEST_F(SwapUTF32Test_2053, InPlaceSwap_2053) {
    UTF32Unit buffer[] = {0x01020304, 0x05060708};
    UTF32Unit expected0 = ManualSwap32(0x01020304);
    UTF32Unit expected1 = ManualSwap32(0x05060708);
    SwapUTF32(buffer, buffer, 2);
    EXPECT_EQ(buffer[0], expected0);
    EXPECT_EQ(buffer[1], expected1);
}

// Test with a larger array
TEST_F(SwapUTF32Test_2053, LargerArray_2053) {
    const size_t len = 100;
    std::vector<UTF32Unit> input(len);
    std::vector<UTF32Unit> output(len, 0);
    for (size_t i = 0; i < len; ++i) {
        input[i] = static_cast<UTF32Unit>(i * 0x01010101);
    }
    SwapUTF32(input.data(), output.data(), len);
    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(output[i], ManualSwap32(input[i])) << "Mismatch at index " << i;
    }
}

// Test boundary value 0x00000001
TEST_F(SwapUTF32Test_2053, BoundaryValueOne_2053) {
    UTF32Unit input[] = {0x00000001};
    UTF32Unit output[1] = {0};
    SwapUTF32(input, output, 1);
    EXPECT_EQ(output[0], 0x01000000);
}

// Test boundary value 0x80000000
TEST_F(SwapUTF32Test_2053, BoundaryValueHighBit_2053) {
    UTF32Unit input[] = {0x80000000};
    UTF32Unit output[1] = {0};
    SwapUTF32(input, output, 1);
    EXPECT_EQ(output[0], 0x00000080);
}

// Test that only the specified number of elements are swapped
TEST_F(SwapUTF32Test_2053, PartialSwap_2053) {
    UTF32Unit input[] = {0x01020304, 0x05060708, 0x090A0B0C};
    UTF32Unit output[] = {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC};
    SwapUTF32(input, output, 2);
    EXPECT_EQ(output[0], ManualSwap32(0x01020304));
    EXPECT_EQ(output[1], ManualSwap32(0x05060708));
    // Third element should be untouched
    EXPECT_EQ(output[2], 0xCCCCCCCC);
}
