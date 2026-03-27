#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail::wuint;



TEST(compute_delta_399, NormalOperation_399) {

    cache_entry_type cache{uint128(0x8000000000000000ULL, 0)};

    constexpr ShiftAmountType beta = 0;

    EXPECT_EQ(compute_delta(cache, beta), 1ULL);

}



TEST(compute_delta_399, BoundaryCondition_BetaZero_399) {

    cache_entry_type cache{uint128(0xFFFFFFFFFFFFFFFFULL, 0)};

    constexpr ShiftAmountType beta = 0;

    EXPECT_EQ(compute_delta(cache, beta), 1ULL);

}



TEST(compute_delta_399, BoundaryCondition_TotalBitsMinusOne_399) {

    cache_entry_type cache{uint128(0x8000000000000000ULL, 0)};

    constexpr ShiftAmountType beta = total_bits - 1;

    EXPECT_EQ(compute_delta(cache, beta), 0ULL);

}



TEST(compute_delta_399, BoundaryCondition_TotalBitsMinusTwo_399) {

    cache_entry_type cache{uint128(0xC000000000000000ULL, 0)};

    constexpr ShiftAmountType beta = total_bits - 2;

    EXPECT_EQ(compute_delta(cache, beta), 1ULL);

}



TEST(compute_delta_399, AllBitsSet_TotalBitsMinusOne_399) {

    cache_entry_type cache{uint128(0xFFFFFFFFFFFFFFFFULL, 0)};

    constexpr ShiftAmountType beta = total_bits - 1;

    EXPECT_EQ(compute_delta(cache, beta), 0ULL);

}
