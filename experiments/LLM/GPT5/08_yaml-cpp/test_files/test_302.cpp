// File: ./TestProjects/yaml-cpp/test/rotr_test_302.cpp

#include <cstdint>
#include <type_traits>
#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::bits::rotr;

// Helper: build a mask of width W for type UInt (works for W==0 too).
template <std::size_t W, class UInt>
constexpr UInt WidthMask() {
    static_assert(std::is_unsigned<UInt>::value, "UInt must be unsigned for these tests");
    if constexpr (W == 0) {
        return UInt{0};
    } else if constexpr (W >= sizeof(UInt) * 8) {
        return ~UInt{0};
    } else {
        return (UInt{1} << W) - UInt{1};
    }
}

// Helper: reference rotation within width W only, expressed from observable bit behavior.
// (This does not infer internal code; it encodes the public contract of "rotate right within bit_width".)
template <std::size_t W, class UInt>
constexpr UInt RefRotrWithinWidth(UInt n, unsigned int r) {
    const UInt mask = WidthMask<W, UInt>();
    n &= mask;

    if constexpr (W == 0) {
        return UInt{0};
    } else {
        const unsigned int rr = (W == 1) ? 0u : (r & static_cast<unsigned int>(W - 1));
        if constexpr (W == 1) {
            (void)rr;
            return n; // only one bit
        } else {
            const unsigned int left = (rr == 0) ? 0u : (static_cast<unsigned int>(W) - rr);
            // Ensure shifts never exceed width (rr in [0, W-1], left in [0, W-1])
            const UInt res = ((n >> rr) | ((n << left) & mask)) & mask;
            return res;
        }
    }
}

// Helper: expected single-bit movement property.
template <std::size_t W, class UInt>
constexpr UInt OneHotAt(unsigned int pos) {
    return (UInt{1} << pos) & WidthMask<W, UInt>();
}

} // namespace

// ---------------------- Normal operation ----------------------

TEST(RotrTest_302, RotrZeroStaysZero_302) {
    constexpr std::uint32_t n = 0u;
    EXPECT_EQ((rotr<8, std::uint32_t>(n, 0)), 0u);
    EXPECT_EQ((rotr<8, std::uint32_t>(n, 1)), 0u);
    EXPECT_EQ((rotr<8, std::uint32_t>(n, 7)), 0u);
    EXPECT_EQ((rotr<8, std::uint32_t>(n, 1000)), 0u);
}

TEST(RotrTest_302, RotrByZeroIsIdentityWithinWidth_302) {
    constexpr std::uint32_t n = 0b1010'0110u; // within 8 bits
    EXPECT_EQ((rotr<8, std::uint32_t>(n, 0)), (n & 0xFFu));
    EXPECT_EQ((rotr<16, std::uint32_t>(n, 0)), (n & 0xFFFFu));
}

TEST(RotrTest_302, RotrMatchesReferenceForSeveralValues_302) {
    // A small sweep of representative patterns and rotations for an 8-bit width.
    const std::uint32_t values[] = {
        0x00u, 0x01u, 0x02u, 0x7Fu, 0x80u, 0xA5u, 0xFFu
    };
    const unsigned int rotations[] = {0u, 1u, 2u, 3u, 7u, 8u, 9u, 15u, 16u, 31u, 32u, 1000u};

    for (auto v : values) {
        for (auto r : rotations) {
            const auto got = rotr<8, std::uint32_t>(v, r);
            const auto exp = RefRotrWithinWidth<8, std::uint32_t>(v, r);
            EXPECT_EQ(got & 0xFFu, exp) << "v=" << v << " r=" << r;
        }
    }
}

TEST(RotrTest_302, RotrDoesNotLeakBitsOutsideWidth_302) {
    // Put bits above the active width; result should still be confined to that width (masked).
    constexpr std::uint32_t n = 0xFFFF'00A5u; // many high bits set, low 8 bits == 0xA5
    const auto got = rotr<8, std::uint32_t>(n, 3);
    EXPECT_EQ(got & ~0xFFu, 0u); // all bits above width are zero in the rotated-within-width sense
    EXPECT_EQ(got, RefRotrWithinWidth<8, std::uint32_t>(n, 3));
}

TEST(RotrTest_302, RotrOneHotBitMovesToExpectedPosition_302) {
    // For width 8: a bit at position p should move to (p - r) mod 8.
    for (unsigned int p = 0; p < 8; ++p) {
        const std::uint32_t n = OneHotAt<8, std::uint32_t>(p);
        for (unsigned int r = 0; r < 8; ++r) {
            const unsigned int new_pos = (p + 8 - r) % 8;
            const std::uint32_t expected = OneHotAt<8, std::uint32_t>(new_pos);
            EXPECT_EQ(rotr<8, std::uint32_t>(n, r), expected) << "p=" << p << " r=" << r;
        }
    }
}

// ---------------------- Boundary conditions ----------------------

TEST(RotrTest_302, RotationCountIsReducedModuloWidth_302) {
    constexpr std::uint32_t n = 0xA5u; // 8-bit pattern
    EXPECT_EQ(rotr<8, std::uint32_t>(n, 0), rotr<8, std::uint32_t>(n, 8));
    EXPECT_EQ(rotr<8, std::uint32_t>(n, 1), rotr<8, std::uint32_t>(n, 9));
    EXPECT_EQ(rotr<8, std::uint32_t>(n, 7), rotr<8, std::uint32_t>(n, 15));
    EXPECT_EQ(rotr<8, std::uint32_t>(n, 3), rotr<8, std::uint32_t>(n, 3 + 8 * 1234));
}

TEST(RotrTest_302, BitWidthOneAlwaysReturnsLowestBit_302) {
    // For width 1, rotation count is effectively 0; only the lowest bit matters.
    EXPECT_EQ(rotr<1, std::uint32_t>(0u, 0), 0u);
    EXPECT_EQ(rotr<1, std::uint32_t>(1u, 0), 1u);
    EXPECT_EQ(rotr<1, std::uint32_t>(2u, 0), 0u); // only LSB within width 1
    EXPECT_EQ(rotr<1, std::uint32_t>(3u, 5), 1u); // 3 -> LSB is 1, rotation irrelevant
}

TEST(RotrTest_302, WorksAtTypeBitWidthBoundary_302) {
    // Use full width of the type (32 for uint32_t). Rotation should match reference.
    constexpr std::uint32_t n = 0xDEADBEEFu;
    const unsigned int rotations[] = {0u, 1u, 4u, 8u, 16u, 31u, 32u, 33u, 1000u};

    for (auto r : rotations) {
        const auto got = rotr<32, std::uint32_t>(n, r);
        const auto exp = RefRotrWithinWidth<32, std::uint32_t>(n, r);
        EXPECT_EQ(got, exp) << "r=" << r;
    }
}

// ---------------------- Exceptional / error cases (observable via compilation) ----------------------
// NOTE: The implementation uses static_assert for invalid bit_width values.
// Those are compile-time errors and cannot be asserted at runtime.
// This test suite intentionally avoids instantiations like rotr<0, UInt> or rotr<bit_width too large,...>
// because doing so would fail compilation, which is the expected behavior.

// ---------------------- No external interactions ----------------------
// rotr is a pure function template with no collaborators/callbacks.
// Therefore, no Google Mock usage is necessary.