#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using namespace detail::wuint;



struct CacheEntryMock {

    std::uint_least64_t high;

    std::uint_least64_t low;

};



TEST_F(DragonboxTest_400, ComputeMulParity_NormalOperation_400) {

    carrier_uint two_f = 123456789;

    CacheEntryMock cache{0xABCDEF1234567890, 0x0123456789ABCDEF};

    ShiftAmountType beta = 10;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_FALSE(result.is_zero);

}



TEST_F(DragonboxTest_400, ComputeMulParity_BoundaryCondition_ZeroBeta_400) {

    carrier_uint two_f = 123456789;

    CacheEntryMock cache{0xABCDEF1234567890, 0x0123456789ABCDEF};

    ShiftAmountType beta = 1;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_FALSE(result.is_zero);

}



TEST_F(DragonboxTest_400, ComputeMulParity_BoundaryCondition_MaxBeta_400) {

    carrier_uint two_f = 123456789;

    CacheEntryMock cache{0xABCDEF1234567890, 0x0123456789ABCDEF};

    ShiftAmountType beta = 63;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_FALSE(result.is_zero);

}



TEST_F(DragonboxTest_400, ComputeMulParity_ExceptionalCase_ZeroCacheHighLow_400) {

    carrier_uint two_f = 123456789;

    CacheEntryMock cache{0x0, 0x0};

    ShiftAmountType beta = 10;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_TRUE(result.is_zero);

}



TEST_F(DragonboxTest_400, ComputeMulParity_ExceptionalCase_MaxTwoF_400) {

    carrier_uint two_f = UINT64_C(0xFFFFFFFFFFFFFFFF);

    CacheEntryMock cache{0xABCDEF1234567890, 0x0123456789ABCDEF};

    ShiftAmountType beta = 10;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_FALSE(result.is_zero);

}



TEST_F(DragonboxTest_400, ComputeMulParity_ExceptionalCase_MaxCacheHighLow_400) {

    carrier_uint two_f = 123456789;

    CacheEntryMock cache{UINT64_C(0xFFFFFFFFFFFFFFFF), UINT64_C(0xFFFFFFFFFFFFFFFF)};

    ShiftAmountType beta = 10;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Verify the results based on observable behavior

    EXPECT_FALSE(result.parity);

    EXPECT_FALSE(result.is_zero);

}



}}} // namespace YAML::jkj::dragonbox
