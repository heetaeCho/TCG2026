#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Test fixture for float format cache tests
class CompressedCacheHolderFloatTest_330 : public ::testing::Test {
protected:
    using float_format = ieee754_binary32;
    using holder = compressed_cache_holder<float_format, void>;
};

// Test fixture for double format cache tests
class CompressedCacheHolderDoubleTest_330 : public ::testing::Test {
protected:
    using float_format = ieee754_binary64;
    using holder = compressed_cache_holder<float_format, void>;
};

// Test that get_cache returns a valid cache entry for float format at minimum k
TEST_F(CompressedCacheHolderFloatTest_330, GetCacheAtMinK_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    auto result = holder::get_cache<int, int>(min_k);
    auto expected = cache_h::cache[0];
    EXPECT_EQ(result, expected);
}

// Test that get_cache returns a valid cache entry for float format at max k
TEST_F(CompressedCacheHolderFloatTest_330, GetCacheAtMaxK_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    constexpr auto max_k = cache_h::max_k;
    auto result = holder::get_cache<int, int>(max_k);
    auto expected = cache_h::cache[max_k - min_k];
    EXPECT_EQ(result, expected);
}

// Test that get_cache returns correct entry for a mid-range k value (float)
TEST_F(CompressedCacheHolderFloatTest_330, GetCacheAtMidK_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    constexpr auto max_k = cache_h::max_k;
    constexpr auto mid_k = (min_k + max_k) / 2;
    auto result = holder::get_cache<int, int>(mid_k);
    auto expected = cache_h::cache[mid_k - min_k];
    EXPECT_EQ(result, expected);
}

// Test that get_cache returns a valid cache entry for double format at minimum k
TEST_F(CompressedCacheHolderDoubleTest_330, GetCacheAtMinK_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    auto result = holder::get_cache<int, int>(min_k);
    // The result should be a valid cache entry; we verify it's non-zero
    // For uint128, check that at least one component is non-zero
    EXPECT_TRUE(result.high() != 0 || result.low() != 0);
}

// Test that get_cache returns a valid cache entry for double format at max k
TEST_F(CompressedCacheHolderDoubleTest_330, GetCacheAtMaxK_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    constexpr auto max_k = cache_h::max_k;
    auto result = holder::get_cache<int, int>(max_k);
    EXPECT_TRUE(result.high() != 0 || result.low() != 0);
}

// Test consistency: calling get_cache twice with same k returns same result (float)
TEST_F(CompressedCacheHolderFloatTest_330, GetCacheConsistency_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    auto result1 = holder::get_cache<int, int>(min_k);
    auto result2 = holder::get_cache<int, int>(min_k);
    EXPECT_EQ(result1, result2);
}

// Test that different k values produce different cache entries (float)
TEST_F(CompressedCacheHolderFloatTest_330, DifferentKProduceDifferentResults_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    auto result1 = holder::get_cache<int, int>(min_k);
    auto result2 = holder::get_cache<int, int>(min_k + 1);
    EXPECT_NE(result1, result2);
}

// Test with different ShiftAmountType template parameter
TEST_F(CompressedCacheHolderFloatTest_330, GetCacheWithDifferentShiftType_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    auto result1 = holder::get_cache<int, int>(min_k);
    auto result2 = holder::get_cache<unsigned, int>(min_k);
    EXPECT_EQ(result1, result2);
}

// Test sequential k values for float format
TEST_F(CompressedCacheHolderFloatTest_330, SequentialKValues_330) {
    using cache_h = cache_holder<float_format>;
    constexpr auto min_k = cache_h::min_k;
    constexpr auto max_k = cache_h::max_k;
    // Verify all entries are accessible without error
    for (int k = min_k; k <= max_k; ++k) {
        auto result = holder::get_cache<int, int>(k);
        auto expected = cache_h::cache[k - min_k];
        EXPECT_EQ(result, expected) << "Mismatch at k=" << k;
    }
}

}  // namespace
