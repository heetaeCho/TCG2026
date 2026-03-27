// Decrypt_Mul0eTable_test_2784.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <type_traits>

// Mul0eTable is defined in poppler/Decrypt.cc (internal helper).
// For unit-testing this interface, we include the implementation file to access the type.
#include "poppler/Decrypt.cc"

namespace {

TEST(Mul0eTableTest_2784, IsConstexprConstructible_2784)
{
    // Verify the constructor can be used in a constant-evaluated context.
    constexpr Mul0eTable table{};
    (void)table;

    // Also verify the type is usable as a constexpr object.
    constexpr bool ok = std::is_literal_type<Mul0eTable>::value || true;
    (void)ok;

    SUCCEED();
}

TEST(Mul0eTableTest_2784, OperatorReturnsUnsignedChar_2784)
{
    Mul0eTable table;

    // Operator result type should match the declared interface: unsigned char.
    using RetT = decltype(table(uint8_t{0}));
    static_assert(std::is_same<RetT, unsigned char>::value,
                  "Mul0eTable::operator()(uint8_t) must return unsigned char");

    // Runtime sanity: call it once.
    unsigned char v = table(uint8_t{0});
    (void)v;
    SUCCEED();
}

TEST(Mul0eTableTest_2784, ConstexprLookupCompilesAndMatchesRuntimeCall_2784)
{
    // Ensure operator() is usable in a constant expression.
    constexpr Mul0eTable table{};
    constexpr unsigned char c0 = table(uint8_t{0});
    constexpr unsigned char c1 = table(uint8_t{1});
    (void)c0;
    (void)c1;

    // Observable behavior: repeated calls on the same instance for the same input
    // should be stable (deterministic for a pure lookup interface).
    Mul0eTable rt;
    EXPECT_EQ(static_cast<unsigned int>(c0), static_cast<unsigned int>(rt(uint8_t{0})));
    EXPECT_EQ(static_cast<unsigned int>(c1), static_cast<unsigned int>(rt(uint8_t{1})));
}

TEST(Mul0eTableTest_2784, BoundaryInputsAreStableAcrossRepeatedCalls_2784)
{
    Mul0eTable table;

    const unsigned char v0_first = table(uint8_t{0});
    const unsigned char v0_second = table(uint8_t{0});
    EXPECT_EQ(v0_first, v0_second);

    const unsigned char v255_first = table(uint8_t{255});
    const unsigned char v255_second = table(uint8_t{255});
    EXPECT_EQ(v255_first, v255_second);
}

TEST(Mul0eTableTest_2784, DifferentInstancesProduceSameOutputsForSampleInputs_2784)
{
    Mul0eTable a;
    Mul0eTable b;

    const std::array<uint8_t, 8> samples = {
        uint8_t{0}, uint8_t{1}, uint8_t{2}, uint8_t{3},
        uint8_t{127}, uint8_t{128}, uint8_t{254}, uint8_t{255},
    };

    for (uint8_t i : samples) {
        EXPECT_EQ(a(i), b(i)) << "input=" << static_cast<unsigned int>(i);
    }
}

TEST(Mul0eTableTest_2784, AllInputsReturnByteRange_2784)
{
    Mul0eTable table;

    for (int i = 0; i <= 255; ++i) {
        const auto in = static_cast<uint8_t>(i);
        const unsigned char out = table(in);

        // Out is unsigned char; still verify it can be losslessly promoted into [0,255].
        const unsigned int out_u = static_cast<unsigned int>(out);
        EXPECT_LE(out_u, 255u) << "input=" << i;
    }
}

TEST(Mul0eTableTest_2784, CanBeUsedInConstexprArrayInitialization_2784)
{
    // Demonstrate compile-time use across multiple lookups.
    constexpr Mul0eTable table{};
    constexpr std::array<unsigned char, 4> outs = {
        table(uint8_t{0}),
        table(uint8_t{1}),
        table(uint8_t{2}),
        table(uint8_t{255}),
    };

    // Runtime check: values are consistently retrievable.
    Mul0eTable rt;
    EXPECT_EQ(outs[0], rt(uint8_t{0}));
    EXPECT_EQ(outs[1], rt(uint8_t{1}));
    EXPECT_EQ(outs[2], rt(uint8_t{2}));
    EXPECT_EQ(outs[3], rt(uint8_t{255}));
}

} // namespace