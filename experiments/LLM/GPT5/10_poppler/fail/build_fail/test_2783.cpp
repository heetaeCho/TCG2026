// File: Mul0dTableTest_2783.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// Mul0dTable is defined in Decrypt.cc (not a public header in the provided snippet).
// Including the .cc is intentional here to access the black-box type as-is.
#include "poppler/Decrypt.cc"

namespace {

class Mul0dTableTest_2783 : public ::testing::Test {};

TEST_F(Mul0dTableTest_2783, CanConstructDefault_2783)
{
    Mul0dTable t{};
    (void)t;
    SUCCEED();
}

TEST_F(Mul0dTableTest_2783, OperatorAcceptsUint8AndReturnsUnsignedChar_2783)
{
    Mul0dTable t{};

    uint8_t i = 0;
    auto v = t(i);

    static_assert(std::is_same_v<decltype(v), unsigned char>,
                  "Mul0dTable::operator()(uint8_t) must return unsigned char");
    SUCCEED();
}

TEST_F(Mul0dTableTest_2783, OperatorIsCallableForBoundaryInputs_2783)
{
    Mul0dTable t{};

    // Boundary inputs for uint8_t domain.
    (void)t(static_cast<uint8_t>(0));
    (void)t(static_cast<uint8_t>(1));
    (void)t(static_cast<uint8_t>(254));
    (void)t(static_cast<uint8_t>(255));

    SUCCEED();
}

TEST_F(Mul0dTableTest_2783, DeterministicForSameInstance_2783)
{
    Mul0dTable t{};

    for (int x = 0; x < 256; ++x) {
        const auto i = static_cast<uint8_t>(x);
        const unsigned char a = t(i);
        const unsigned char b = t(i);
        EXPECT_EQ(a, b) << "Input=" << x;
    }
}

TEST_F(Mul0dTableTest_2783, DeterministicAcrossDifferentInstances_2783)
{
    Mul0dTable t1{};
    Mul0dTable t2{};

    for (int x = 0; x < 256; ++x) {
        const auto i = static_cast<uint8_t>(x);
        EXPECT_EQ(t1(i), t2(i)) << "Input=" << x;
    }
}

TEST_F(Mul0dTableTest_2783, ProducesAByteValueForAllInputs_2783)
{
    Mul0dTable t{};

    // Since the return type is unsigned char, the observable contract is that
    // results always fit in a byte. We simply exercise the full domain.
    for (int x = 0; x < 256; ++x) {
        const auto i = static_cast<uint8_t>(x);
        const unsigned char v = t(i);
        (void)v;
    }

    SUCCEED();
}

// Compile-time checks (observable interface / type properties; no value assumptions).
static_assert(std::is_default_constructible_v<Mul0dTable>,
              "Mul0dTable should be default-constructible (per provided interface)");
static_assert(std::is_copy_constructible_v<Mul0dTable>,
              "Mul0dTable should be copy-constructible (table-like value type)");

// Verify constexpr usability without asserting specific numeric outputs.
constexpr bool Mul0dTable_ConstexprSmoke_2783()
{
    constexpr Mul0dTable t{};
    // Must be callable in constexpr context; avoid assuming any specific mapping.
    const unsigned char a = t(static_cast<uint8_t>(0));
    const unsigned char b = t(static_cast<uint8_t>(0));
    return a == b;
}
static_assert(Mul0dTable_ConstexprSmoke_2783(),
              "Mul0dTable should be usable in constexpr context and be deterministic");

} // namespace