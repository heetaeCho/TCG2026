// Decrypt_Mul03Table_test_2780.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// Mul03Table is defined in a .cc file. For unit-testing this internal helper,
// we include the implementation unit directly so the type is visible here.
#include "poppler/Decrypt.cc"

namespace {

// Compile-time checks (requires Mul03Table ctor + operator() to be constexpr).
constexpr Mul03Table kTable{};

// Known AES/Rijndael GF(2^8) "multiply by 3" golden values (externally specified).
static_assert(kTable(0x00) == 0x00, "mul03(0x00) should be 0x00");
static_assert(kTable(0x01) == 0x03, "mul03(0x01) should be 0x03");
static_assert(kTable(0x02) == 0x06, "mul03(0x02) should be 0x06");
static_assert(kTable(0x03) == 0x05, "mul03(0x03) should be 0x05");
static_assert(kTable(0x10) == 0x30, "mul03(0x10) should be 0x30");
static_assert(kTable(0x7f) == 0x81, "mul03(0x7f) should be 0x81");
static_assert(kTable(0x80) == 0x9b, "mul03(0x80) should be 0x9b");
static_assert(kTable(0xff) == 0x1a, "mul03(0xff) should be 0x1a");
static_assert(kTable(0x1b) == 0x2d, "mul03(0x1b) should be 0x2d");

}  // namespace

class Mul03TableTest_2780 : public ::testing::Test {};

TEST_F(Mul03TableTest_2780, OperatorReturnTypeIsByteLike_2780)
{
    Mul03Table t;
    using Ret = decltype(t(std::uint8_t{0}));

    EXPECT_TRUE((std::is_integral_v<Ret>));
    EXPECT_EQ(sizeof(Ret), sizeof(unsigned char));
}

TEST_F(Mul03TableTest_2780, KnownValuesAtRuntime_2780)
{
    Mul03Table t;

    EXPECT_EQ(t(static_cast<std::uint8_t>(0x00)), static_cast<unsigned char>(0x00));
    EXPECT_EQ(t(static_cast<std::uint8_t>(0x01)), static_cast<unsigned char>(0x03));
    EXPECT_EQ(t(static_cast<std::uint8_t>(0x02)), static_cast<unsigned char>(0x06));
    EXPECT_EQ(t(static_cast<std::uint8_t>(0x03)), static_cast<unsigned char>(0x05));

    // Boundary-ish / representative values.
    EXPECT_EQ(t(static_cast<std::uint8_t>(0x7f)), static_cast<unsigned char>(0x81));
    EXPECT_EQ(t(static_cast<std::uint8_t>(0x80)), static_cast<unsigned char>(0x9b));
    EXPECT_EQ(t(static_cast<std::uint8_t>(0xff)), static_cast<unsigned char>(0x1a));
}

TEST_F(Mul03TableTest_2780, ConstexprConstructionAndCall_2780)
{
    constexpr Mul03Table t{};
    constexpr unsigned char v = t(static_cast<std::uint8_t>(0x80));
    EXPECT_EQ(v, static_cast<unsigned char>(0x9b));
}

TEST_F(Mul03TableTest_2780, AcceptsAllPossibleInputsWithoutError_2780)
{
    Mul03Table t;

    // Error/exceptional behavior isn't specified; we validate that the interface
    // is callable for the full uint8_t domain.
    for (int i = 0; i <= 255; ++i) {
        volatile unsigned char out = t(static_cast<std::uint8_t>(i));
        (void)out;
    }

    SUCCEED();
}

TEST_F(Mul03TableTest_2780, OutputFitsInUnsignedCharRange_2780)
{
    Mul03Table t;

    for (int i = 0; i <= 255; ++i) {
        const unsigned char out = t(static_cast<std::uint8_t>(i));
        // This is an "observable" boundary property: output is an unsigned byte.
        EXPECT_LE(static_cast<unsigned int>(out), 255u);
    }
}