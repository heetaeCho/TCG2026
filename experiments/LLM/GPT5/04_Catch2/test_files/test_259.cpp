// raw_memory_to_string_test.cpp
// Tests for Catch::Detail::rawMemoryToString
// TEST_ID: 259

#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

namespace Catch { namespace Detail {
// Forward declaration based on the provided interface
std::string rawMemoryToString(const void* object, std::size_t size);
}}

// ---------- Tests ----------

TEST(RawMemoryToStringTest_259, SingleByteFormatting_LowerHexAndPad_259) {
    uint8_t b = 0x0A; // decimal 10
    std::string s = Catch::Detail::rawMemoryToString(&b, sizeof(b));
    EXPECT_EQ(s, "0x0a");
}

TEST(RawMemoryToStringTest_259, ZeroSize_ReturnsJust0x_259) {
    // Valid to pass nullptr when size == 0; function should not dereference
    std::string s = Catch::Detail::rawMemoryToString(nullptr, 0);
    EXPECT_EQ(s, "0x");
}

TEST(RawMemoryToStringTest_259, Uint16_CanonicalOrder_259) {
    // Observable behavior: 16-bit value 0x1234 prints as "0x1234"
    uint16_t v = static_cast<uint16_t>(0x1234);
    std::string s = Catch::Detail::rawMemoryToString(&v, sizeof(v));
    EXPECT_EQ(s, "0x1234");
}

TEST(RawMemoryToStringTest_259, Uint16_PreservesLeadingZeros_259) {
    uint16_t v = static_cast<uint16_t>(0x0001);
    std::string s = Catch::Detail::rawMemoryToString(&v, sizeof(v));
    EXPECT_EQ(s, "0x0001");
}

TEST(RawMemoryToStringTest_259, Uint32_CanonicalOrderAndZeroPadding_259) {
    uint32_t v = 0x00C0FFEEu;
    std::string s = Catch::Detail::rawMemoryToString(&v, sizeof(v));
    EXPECT_EQ(s, "0x00c0ffee");
}

TEST(RawMemoryToStringTest_259, Uint64_CanonicalOrder_259) {
    uint64_t v = 0x0123456789ABCDEFULL;
    std::string s = Catch::Detail::rawMemoryToString(&v, sizeof(v));
    EXPECT_EQ(s, "0x0123456789abcdef");
}

TEST(RawMemoryToStringTest_259, NegativeInt16_TwosComplementShown_259) {
    int16_t v = static_cast<int16_t>(-1); // 0xFFFF in two's complement
    std::string s = Catch::Detail::rawMemoryToString(&v, sizeof(v));
    EXPECT_EQ(s, "0xffff");
}

TEST(RawMemoryToStringTest_259, OutputLengthMatches2xSizePlus2_259) {
    // Using all-zero bytes avoids any platform-dependent content issues
    uint8_t buf[7] = {0};
    std::string s = Catch::Detail::rawMemoryToString(buf, sizeof(buf));
    ASSERT_EQ(s.size(), 2 + 2 * sizeof(buf)); // "0x" + two hex chars per byte
    // And for zeros specifically, the content is deterministic:
    EXPECT_EQ(s, "0x00000000000000");
}
