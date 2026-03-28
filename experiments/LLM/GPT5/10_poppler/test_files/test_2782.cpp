// File: mul0b_table_test_2782.cc

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <array>

// Mul0bTable is implemented in a .cc file in this codebase; include it directly
// so the type and its constexpr members are visible to this test TU.
#include "poppler/Decrypt.cc"

namespace {

class Mul0bTableTest_2782 : public ::testing::Test {};

// Compile-time checks (kept minimal to avoid asserting any inferred algorithmic meaning).
TEST_F(Mul0bTableTest_2782, ConstexprConstructibleAndCallable_2782)
{
    // Must be usable in constant evaluation.
    constexpr Mul0bTable t{};

    // Verify return type exactly matches the declared interface.
    static_assert(std::is_same_v<decltype(t(uint8_t{0})), unsigned char>);

    // Verify it can be evaluated at compile time (without assuming any specific value).
    constexpr unsigned char v0 = t(uint8_t{0});
    static_assert(v0 == t(uint8_t{0}));

    constexpr unsigned char v255 = t(uint8_t{255});
    static_assert(v255 == t(uint8_t{255}));
}

TEST_F(Mul0bTableTest_2782, BoundaryInputsAreCallableAndDeterministic_2782)
{
    Mul0bTable t{};

    const unsigned char v0_first = t(uint8_t{0});
    const unsigned char v0_second = t(uint8_t{0});
    EXPECT_EQ(v0_first, v0_second);

    const unsigned char v255_first = t(uint8_t{255});
    const unsigned char v255_second = t(uint8_t{255});
    EXPECT_EQ(v255_first, v255_second);
}

TEST_F(Mul0bTableTest_2782, RepeatedCallsReturnSameValueForSameInput_2782)
{
    Mul0bTable t{};

    const std::array<uint8_t, 10> inputs = {0u, 1u, 2u, 3u, 7u, 8u, 15u, 16u, 127u, 255u};
    for (uint8_t in : inputs) {
        const unsigned char a = t(in);
        const unsigned char b = t(in);
        const unsigned char c = t(in);
        EXPECT_EQ(a, b) << "Input=" << static_cast<unsigned>(in);
        EXPECT_EQ(b, c) << "Input=" << static_cast<unsigned>(in);
    }
}

TEST_F(Mul0bTableTest_2782, TwoIndependentInstancesAgreeForAllByteInputs_2782)
{
    Mul0bTable a{};
    Mul0bTable b{};

    for (unsigned i = 0; i < 256; ++i) {
        const auto in = static_cast<uint8_t>(i);
        EXPECT_EQ(a(in), b(in)) << "Input=" << i;
    }
}

TEST_F(Mul0bTableTest_2782, CallableForAllPossibleUint8Values_2782)
{
    Mul0bTable t{};

    // Smoke test across full domain: no assumptions about the mapping.
    // Also verifies the return is representable as an 8-bit value (by type).
    std::array<unsigned char, 256> outputs{};
    for (unsigned i = 0; i < 256; ++i) {
        const auto in = static_cast<uint8_t>(i);
        outputs[i] = t(in);
    }

    // Determinism across a second pass.
    for (unsigned i = 0; i < 256; ++i) {
        const auto in = static_cast<uint8_t>(i);
        EXPECT_EQ(outputs[i], t(in)) << "Input=" << i;
    }
}

} // namespace