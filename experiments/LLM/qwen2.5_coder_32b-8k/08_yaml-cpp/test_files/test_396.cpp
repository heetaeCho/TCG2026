#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



using namespace jkj::dragonbox;



// Define a struct to mimic cache_entry_type for testing purposes

struct MockCacheEntry {

    carrier_uint value;

};



TEST(compute_right_endpoint_for_shorter_interval_case_Test_396, NormalOperation_396) {

    MockCacheEntry cache = {1024};

    ShiftAmountType beta = 2;

    carrier_uint result = compute_right_endpoint_for_shorter_interval_case(cache.value, beta);

    // Assuming the expected value is calculated based on the given formula

    EXPECT_EQ(result, (cache.value + (cache.value >> (significand_bits + 1))) >> (cache_bits - significand_bits - 1 - beta));

}



TEST(compute_right_endpoint_for_shorter_interval_case_Test_396, BoundaryCondition_ZeroCache_396) {

    MockCacheEntry cache = {0};

    ShiftAmountType beta = 2;

    carrier_uint result = compute_right_endpoint_for_shorter_interval_case(cache.value, beta);

    EXPECT_EQ(result, 0);

}



TEST(compute_right_endpoint_for_shorter_interval_case_Test_396, BoundaryCondition_MaxBeta_396) {

    MockCacheEntry cache = {1024};

    ShiftAmountType beta = cache_bits - significand_bits - 1;

    carrier_uint result = compute_right_endpoint_for_shorter_interval_case(cache.value, beta);

    // Assuming the expected value is calculated based on the given formula

    EXPECT_EQ(result, (cache.value + (cache.value >> (significand_bits + 1))) >> 0);

}



TEST(compute_right_endpoint_for_shorter_interval_case_Test_396, BoundaryCondition_MaxCache_396) {

    MockCacheEntry cache = {std::numeric_limits<carrier_uint>::max()};

    ShiftAmountType beta = 2;

    carrier_uint result = compute_right_endpoint_for_shorter_interval_case(cache.value, beta);

    // Assuming the expected value is calculated based on the given formula

    EXPECT_EQ(result, (cache.value + (cache.value >> (significand_bits + 1))) >> (cache_bits - significand_bits - 1 - beta));

}



TEST(compute_right_endpoint_for_shorter_interval_case_Test_396, BoundaryCondition_ZeroBeta_396) {

    MockCacheEntry cache = {1024};

    ShiftAmountType beta = 0;

    carrier_uint result = compute_right_endpoint_for_shorter_interval_case(cache.value, beta);

    // Assuming the expected value is calculated based on the given formula

    EXPECT_EQ(result, (cache.value + (cache.value >> (significand_bits + 1))) >> (cache_bits - significand_bits - 1));

}



}}}}
