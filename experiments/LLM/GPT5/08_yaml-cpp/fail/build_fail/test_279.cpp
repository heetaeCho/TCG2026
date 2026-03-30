// File: test_ieee754_binary_traits_has_all_zero_significand_bits_279.cpp

#include <gtest/gtest.h>
#include <cstdint>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

struct Format32_279 {
    static constexpr int total_bits = 32;
};

struct Format64_279 {
    static constexpr int total_bits = 64;
};

using Traits32_279 =
    YAML::jkj::dragonbox::ieee754_binary_traits<Format32_279, std::uint32_t, std::int32_t>;
using Traits64_279 =
    YAML::jkj::dragonbox::ieee754_binary_traits<Format64_279, std::uint64_t, std::int32_t>;

class HasAllZeroSignificandBitsTest_279 : public ::testing::Test {};

}  // namespace

TEST_F(HasAllZeroSignificandBitsTest_279, ZeroValueReturnsTrue_279) {
    EXPECT_TRUE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0}));
    EXPECT_TRUE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, SignBitOnlyReturnsTrue_279) {
    EXPECT_TRUE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0x80000000u}));
    EXPECT_TRUE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0x8000000000000000ull}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, AnyLowBitSetReturnsFalse_279) {
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{1u}));
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{2u}));
    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{1ull}));
    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{2ull}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, AnyNonSignHighBitSetReturnsFalse_279) {
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0x40000000u}));
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0x7FFFFFFFu}));

    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0x4000000000000000ull}));
    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0x7FFFFFFFFFFFFFFFull}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, SignBitPlusAnyOtherBitReturnsFalse_279) {
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0x80000001u}));
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0xC0000000u}));

    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0x8000000000000001ull}));
    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0xC000000000000000ull}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, AllOnesReturnsFalse_279) {
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(std::uint32_t{0xFFFFFFFFu}));
    EXPECT_FALSE(Traits64_279::has_all_zero_significand_bits(std::uint64_t{0xFFFFFFFFFFFFFFFFull}));
}

TEST_F(HasAllZeroSignificandBitsTest_279, ConstexprEvaluationMatchesRuntime_279) {
    constexpr std::uint32_t u32_zero = 0u;
    constexpr std::uint32_t u32_sign = 0x80000000u;
    constexpr std::uint32_t u32_one  = 1u;

    static_assert(Traits32_279::has_all_zero_significand_bits(u32_zero), "expected true");
    static_assert(Traits32_279::has_all_zero_significand_bits(u32_sign), "expected true");
    static_assert(!Traits32_279::has_all_zero_significand_bits(u32_one), "expected false");

    EXPECT_TRUE(Traits32_279::has_all_zero_significand_bits(u32_zero));
    EXPECT_TRUE(Traits32_279::has_all_zero_significand_bits(u32_sign));
    EXPECT_FALSE(Traits32_279::has_all_zero_significand_bits(u32_one));
}