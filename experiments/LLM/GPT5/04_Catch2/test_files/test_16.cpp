// File: test_xmlformatting_and_16.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Include the header that declares Catch::XmlFormatting and operator&
#include "catch2/internal/catch_xmlwriter.hpp"

namespace {

using Catch::XmlFormatting;

// A tiny helper to compare results in terms of their byte value without
// relying on any internal details beyond what the interface allows.
static inline std::uint8_t as_u8(XmlFormatting v) {
    return static_cast<std::uint8_t>(v);
}

// --- Tests ---

TEST(XmlFormattingOpAnd_16, AndOfNonOverlappingIsZero_16) {
    // 0b0001'0000 & 0b0010'0000 == 0
    XmlFormatting lhs = static_cast<XmlFormatting>(0x10);
    XmlFormatting rhs = static_cast<XmlFormatting>(0x20);

    XmlFormatting res = lhs & rhs;

    EXPECT_EQ(as_u8(res), 0x00);
}

TEST(XmlFormattingOpAnd_16, AndWithItselfReturnsSame_16) {
    XmlFormatting m = static_cast<XmlFormatting>(0b1010'0101); // arbitrary mask
    XmlFormatting res = m & m;

    EXPECT_EQ(as_u8(res), as_u8(m));
}

TEST(XmlFormattingOpAnd_16, AndWithZeroIsZero_16) {
    XmlFormatting m = static_cast<XmlFormatting>(0xAB); // arbitrary
    XmlFormatting zero = static_cast<XmlFormatting>(0x00);

    EXPECT_EQ(as_u8(m & zero), 0x00);
    EXPECT_EQ(as_u8(zero & m), 0x00);
}

TEST(XmlFormattingOpAnd_16, AndWithAllOnesReturnsLhs_16) {
    // Because the implementation casts to uint8_t internally, 0xFF should act
    // like an identity for the low 8 bits.
    XmlFormatting lhs = static_cast<XmlFormatting>(0x5C);
    XmlFormatting all_ones = static_cast<XmlFormatting>(0xFF);

    EXPECT_EQ(as_u8(lhs & all_ones), as_u8(lhs));
    EXPECT_EQ(as_u8(all_ones & lhs), as_u8(lhs));
}

TEST(XmlFormattingOpAnd_16, Commutative_16) {
    XmlFormatting a = static_cast<XmlFormatting>(0x3C);
    XmlFormatting b = static_cast<XmlFormatting>(0x5A);

    EXPECT_EQ(as_u8(a & b), as_u8(b & a));
}

TEST(XmlFormattingOpAnd_16, HighBitsAreMaskedOutToByte_16) {
    // The operator casts both operands to uint8_t before &, so any bits above
    // the low 8 are ignored in the observable result.
    XmlFormatting wide = static_cast<XmlFormatting>(0x1F0); // high nibble beyond 8 bits
    XmlFormatting mask = static_cast<XmlFormatting>(0xFF);

    // Expect only low 8 bits (0xF0) to remain observable.
    EXPECT_EQ(as_u8(wide & mask), static_cast<std::uint8_t>(0xF0));
}

// A compile-time check that the operator is constexpr-usable (does not count as a test).
constexpr bool kConstexprAndOk_16 = []{
    constexpr XmlFormatting a = static_cast<XmlFormatting>(0xAA);
    constexpr XmlFormatting b = static_cast<XmlFormatting>(0x0F);
    constexpr XmlFormatting c = a & b;
    return static_cast<std::uint8_t>(c) == static_cast<std::uint8_t>(0x0A);
}();
static_assert(kConstexprAndOk_16, "operator& should be usable in constexpr context");

} // namespace
