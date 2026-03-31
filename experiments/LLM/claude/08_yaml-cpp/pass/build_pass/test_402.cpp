#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;
using namespace YAML::jkj::dragonbox::detail;

// Test using uint128 directly as cache_entry_type
class Uint128Test_402 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(Uint128Test_402, DefaultConstruction_402) {
    wuint::uint128 val;
    // Default constructed - just verify it compiles and doesn't crash
    (void)val;
}

TEST_F(Uint128Test_402, ParameterizedConstruction_402) {
    wuint::uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    EXPECT_EQ(val.high(), 0x1234567890ABCDEFull);
    EXPECT_EQ(val.low(), 0xFEDCBA0987654321ull);
}

TEST_F(Uint128Test_402, HighAndLowAccessors_402) {
    wuint::uint128 val(42ull, 100ull);
    EXPECT_EQ(val.high(), 42ull);
    EXPECT_EQ(val.low(), 100ull);
}

TEST_F(Uint128Test_402, ZeroValues_402) {
    wuint::uint128 val(0ull, 0ull);
    EXPECT_EQ(val.high(), 0ull);
    EXPECT_EQ(val.low(), 0ull);
}

TEST_F(Uint128Test_402, MaxValues_402) {
    wuint::uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

TEST_F(Uint128Test_402, PlusEqualsNoCarry_402) {
    wuint::uint128 val(10ull, 20ull);
    val += 5ull;
    EXPECT_EQ(val.low(), 25ull);
    EXPECT_EQ(val.high(), 10ull);
}

TEST_F(Uint128Test_402, PlusEqualsWithCarry_402) {
    wuint::uint128 val(10ull, UINT64_MAX);
    val += 1ull;
    EXPECT_EQ(val.low(), 0ull);
    EXPECT_EQ(val.high(), 11ull);
}

TEST_F(Uint128Test_402, PlusEqualsZero_402) {
    wuint::uint128 val(5ull, 10ull);
    val += 0ull;
    EXPECT_EQ(val.low(), 10ull);
    EXPECT_EQ(val.high(), 5ull);
}

TEST_F(Uint128Test_402, PlusEqualsWithLargeCarry_402) {
    wuint::uint128 val(0ull, UINT64_MAX);
    val += UINT64_MAX;
    // UINT64_MAX + UINT64_MAX = 2^64 - 2, with carry
    EXPECT_EQ(val.low(), UINT64_MAX - 1ull);
    EXPECT_EQ(val.high(), 1ull);
}

TEST_F(Uint128Test_402, ConstAccessors_402) {
    const wuint::uint128 val(123ull, 456ull);
    EXPECT_EQ(val.high(), 123ull);
    EXPECT_EQ(val.low(), 456ull);
}

TEST_F(Uint128Test_402, HighOnlySet_402) {
    wuint::uint128 val(0xFFFFFFFFFFFFFFFFull, 0ull);
    EXPECT_EQ(val.high(), 0xFFFFFFFFFFFFFFFFull);
    EXPECT_EQ(val.low(), 0ull);
}

TEST_F(Uint128Test_402, LowOnlySet_402) {
    wuint::uint128 val(0ull, 0xFFFFFFFFFFFFFFFFull);
    EXPECT_EQ(val.high(), 0ull);
    EXPECT_EQ(val.low(), 0xFFFFFFFFFFFFFFFFull);
}

} // namespace
