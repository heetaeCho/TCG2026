#include <gtest/gtest.h>
#include "cr2header_int.hpp"

// Test the static offset2addr function
TEST(Cr2HeaderTest_1543, Offset2AddrReturnsCorrectValue_1543) {
    uint32_t result = Exiv2::Internal::Cr2Header::offset2addr();
    EXPECT_EQ(result, 12u);
}

TEST(Cr2HeaderTest_1543, Offset2AddrIsConsistent_1543) {
    // Calling multiple times should return the same value
    uint32_t first = Exiv2::Internal::Cr2Header::offset2addr();
    uint32_t second = Exiv2::Internal::Cr2Header::offset2addr();
    EXPECT_EQ(first, second);
}

TEST(Cr2HeaderTest_1543, Offset2AddrReturnType_1543) {
    // Verify the return type is uint32_t and value is non-negative (always true for unsigned)
    auto result = Exiv2::Internal::Cr2Header::offset2addr();
    static_assert(std::is_same<decltype(result), uint32_t>::value, "offset2addr should return uint32_t");
    EXPECT_EQ(result, 12u);
}

TEST(Cr2HeaderTest_1543, Offset2AddrIsStatic_1543) {
    // Verify it can be called without an instance
    EXPECT_EQ(Exiv2::Internal::Cr2Header::offset2addr(), 12u);
}
