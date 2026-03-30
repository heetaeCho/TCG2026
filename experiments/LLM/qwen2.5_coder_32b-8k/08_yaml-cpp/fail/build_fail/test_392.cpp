#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox;

using namespace YAML::jkj::dragonbox::detail;



// Mocking the carrier_uint and cache_entry_type for testing purposes

class MockCarrierUint {

public:

    MockCarrierUint(uint64_t value) : value_(value) {}

    operator uint64_t() const { return value_; }

private:

    uint64_t value_;

};



class MockCacheEntryType {

public:

    MockCacheEntryType(uint64_t upper, uint64_t lower) : upper_(upper), lower_(lower) {}

    uint64_t upper() const { return upper_; }

    uint64_t lower() const { return lower_; }

private:

    uint64_t upper_;

    uint64_t lower_;

};



// Test fixture

class DragonboxTest_392 : public ::testing::Test {

protected:

    using CarrierUint = MockCarrierUint;

    using CacheEntryType = MockCacheEntryType;



    void SetUp() override {

        // Setup code if necessary

    }

};



// Normal operation test

TEST_F(DragonboxTest_392, ComputeMul_NormalOperation_392) {

    CarrierUint u(123456789);

    CacheEntryType cache(987654321, 0);

    auto result = compute_mul(u, cache);

    EXPECT_EQ(result.multiplier, 121932631137021795ul); // Pre-calculated expected value

    EXPECT_TRUE(result.is_zero);

}



// Boundary condition test with zero multiplier

TEST_F(DragonboxTest_392, ComputeMul_ZeroMultiplier_392) {

    CarrierUint u(0);

    CacheEntryType cache(987654321, 0);

    auto result = compute_mul(u, cache);

    EXPECT_EQ(result.multiplier, 0ul);

    EXPECT_TRUE(result.is_zero);

}



// Boundary condition test with zero cache

TEST_F(DragonboxTest_392, ComputeMul_ZeroCache_392) {

    CarrierUint u(123456789);

    CacheEntryType cache(0, 0);

    auto result = compute_mul(u, cache);

    EXPECT_EQ(result.multiplier, 0ul);

    EXPECT_TRUE(result.is_zero);

}



// Exceptional case test with max values (no exception expected, but boundary check)

TEST_F(DragonboxTest_392, ComputeMul_MaxValues_392) {

    CarrierUint u(UINT64_MAX);

    CacheEntryType cache(UINT64_MAX, UINT64_MAX);

    auto result = compute_mul(u, cache);

    // Expected value is pre-calculated based on the function's behavior

    EXPECT_EQ(result.multiplier, 1ul); 

    EXPECT_FALSE(result.is_zero);

}
