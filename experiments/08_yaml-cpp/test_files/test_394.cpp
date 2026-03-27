#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>



// Include the header file containing the function to be tested.

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Test fixture for compute_mul_parity tests.

class ComputeMulParityTest_394 : public ::testing::Test {

protected:

    using ShiftAmountType = int;

};



TEST_F(ComputeMulParityTest_394, NormalOperationTest_394) {

    carrier_uint two_f = 0x123456789ABCDEF0;

    cache_entry_type cache = {0xFEDCBA9876543210};

    ShiftAmountType beta = 16;



    auto result = compute_mul_parity(two_f, cache, beta);



    // Check the expected return values based on observable behavior.

    EXPECT_EQ(result.first, (result.second == 0) ? false : true);

}



TEST_F(ComputeMulParityTest_394, BoundaryConditionBetaMin_394) {

    carrier_uint two_f = 0x123456789ABCDEF0;

    cache_entry_type cache = {0xFEDCBA9876543210};

    ShiftAmountType beta = 1;



    auto result = compute_mul_parity(two_f, cache, beta);



    EXPECT_EQ(result.first, (result.second == 0) ? false : true);

}



TEST_F(ComputeMulParityTest_394, BoundaryConditionBetaMax_394) {

    carrier_uint two_f = 0x123456789ABCDEF0;

    cache_entry_type cache = {0xFEDCBA9876543210};

    ShiftAmountType beta = 32;



    auto result = compute_mul_parity(two_f, cache, beta);



    EXPECT_EQ(result.first, (result.second == 0) ? false : true);

}



TEST_F(ComputeMulParityTest_394, BetaValueGreaterThanMax_394) {

    carrier_uint two_f = 0x123456789ABCDEF0;

    cache_entry_type cache = {0xFEDCBA9876543210};

    ShiftAmountType beta = 33;



    // This should trigger an assertion, but since we're treating it as a black box,

    // we assume the function handles it gracefully and doesn't cause undefined behavior.

    EXPECT_DEATH(compute_mul_parity(two_f, cache, beta), "");

}



TEST_F(ComputeMulParityTest_394, BetaValueLessThanMin_394) {

    carrier_uint two_f = 0x123456789ABCDEF0;

    cache_entry_type cache = {0xFEDCBA9876543210};

    ShiftAmountType beta = 0;



    // This should trigger an assertion, but since we're treating it as a black box,

    // we assume the function handles it gracefully and doesn't cause undefined behavior.

    EXPECT_DEATH(compute_mul_parity(two_f, cache, beta), "");

}

```


