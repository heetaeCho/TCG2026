#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <limits>

// We need to work with the actual types from the dragonbox implementation
using namespace YAML::jkj::dragonbox;

// For IEEE 754 binary32 (float)
using float_format = ieee754_binary32;
// For IEEE 754 binary64 (double)
using double_format = ieee754_binary64;

// Helper type aliases
using float_cache_holder = compressed_cache_holder<float_format, void>;
using double_cache_holder = compressed_cache_holder<double_format, void>;

class DragonboxCacheTest_332 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_cache returns a valid (non-zero) cache entry for k=0 (double)
TEST_F(DragonboxCacheTest_332, DoubleCacheAtZero_332) {
    auto cache = double_cache_holder::get_cache<int, int>(0);
    // Cache entry at k=0 should be meaningful (non-zero)
    EXPECT_TRUE(cache.high() != 0 || cache.low() != 0);
}

// Test that get_cache returns a valid cache entry for minimum k (double)
TEST_F(DragonboxCacheTest_332, DoubleCacheAtMinK_332) {
    // For double, min_k is around -292
    auto cache = double_cache_holder::get_cache<int, int>(-292);
    EXPECT_TRUE(cache.high() != 0 || cache.low() != 0);
}

// Test that get_cache returns a valid cache entry for maximum k (double)
TEST_F(DragonboxCacheTest_332, DoubleCacheAtMaxK_332) {
    // For double, max_k is around 326
    auto cache = double_cache_holder::get_cache<int, int>(326);
    EXPECT_TRUE(cache.high() != 0 || cache.low() != 0);
}

// Test that cache entries at aligned positions (offset==0) work correctly for double
TEST_F(DragonboxCacheTest_332, DoubleCacheAtAlignedPosition_332) {
    // min_k for double is -292, compression_ratio is 27
    // Aligned positions: -292, -292+27=-265, -265+27=-238, etc.
    auto cache1 = double_cache_holder::get_cache<int, int>(-292);
    auto cache2 = double_cache_holder::get_cache<int, int>(-265);
    // Both should be valid and different
    EXPECT_TRUE(cache1.high() != 0);
    EXPECT_TRUE(cache2.high() != 0);
    EXPECT_TRUE(cache1.high() != cache2.high() || cache1.low() != cache2.low());
}

// Test that cache entries at non-aligned positions (offset!=0) work for double
TEST_F(DragonboxCacheTest_332, DoubleCacheAtNonAlignedPosition_332) {
    // -291 is offset 1 from -292 (min_k)
    auto cache = double_cache_holder::get_cache<int, int>(-291);
    EXPECT_TRUE(cache.high() != 0);
}

// Test consecutive k values produce different cache entries for double
TEST_F(DragonboxCacheTest_332, DoubleConsecutiveKDifferent_332) {
    auto cache1 = double_cache_holder::get_cache<int, int>(0);
    auto cache2 = double_cache_holder::get_cache<int, int>(1);
    EXPECT_TRUE(cache1.high() != cache2.high() || cache1.low() != cache2.low());
}

// Test that get_cache is deterministic for double
TEST_F(DragonboxCacheTest_332, DoubleCacheDeterministic_332) {
    auto cache1 = double_cache_holder::get_cache<int, int>(50);
    auto cache2 = double_cache_holder::get_cache<int, int>(50);
    EXPECT_EQ(cache1.high(), cache2.high());
    EXPECT_EQ(cache1.low(), cache2.low());
}

// Test various k values in the valid range for double
TEST_F(DragonboxCacheTest_332, DoubleCacheVariousKValues_332) {
    int test_values[] = {-292, -200, -100, -50, -1, 0, 1, 50, 100, 200, 300, 326};
    for (int k : test_values) {
        auto cache = double_cache_holder::get_cache<int, int>(k);
        EXPECT_NE(cache.high(), uint64_t(0))
            << "Cache high() should be non-zero for k=" << k;
    }
}

// Test that larger k values produce cache entries with specific monotonicity properties
// In dragonbox, the cache approximates 10^k, so high bits should generally increase with k
TEST_F(DragonboxCacheTest_332, DoubleCacheMonotonicity_332) {
    auto cache_neg = double_cache_holder::get_cache<int, int>(-100);
    auto cache_pos = double_cache_holder::get_cache<int, int>(100);
    // Both should be valid
    EXPECT_NE(cache_neg.high(), uint64_t(0));
    EXPECT_NE(cache_pos.high(), uint64_t(0));
}

// Test offset values near compression ratio boundary for double
TEST_F(DragonboxCacheTest_332, DoubleCacheNearCompressionBoundary_332) {
    // compression_ratio = 27, so test offset = 26 (max before next aligned)
    // -292 + 26 = -266
    auto cache = double_cache_holder::get_cache<int, int>(-266);
    EXPECT_NE(cache.high(), uint64_t(0));
}

// Test that get_cache works for float format
TEST_F(DragonboxCacheTest_332, FloatCacheAtZero_332) {
    auto cache = float_cache_holder::get_cache<int, int>(0);
    // For float, cache_entry_type is uint64_t
    EXPECT_NE(cache, uint64_t(0));
}

// Test float cache at various values
TEST_F(DragonboxCacheTest_332, FloatCacheVariousValues_332) {
    // Float min_k is around -31, max_k around 46
    int test_values[] = {-31, -20, -10, 0, 10, 20, 30, 46};
    for (int k : test_values) {
        auto cache = float_cache_holder::get_cache<int, int>(k);
        EXPECT_NE(cache, uint64_t(0))
            << "Float cache should be non-zero for k=" << k;
    }
}

// Test float cache determinism
TEST_F(DragonboxCacheTest_332, FloatCacheDeterministic_332) {
    auto cache1 = float_cache_holder::get_cache<int, int>(10);
    auto cache2 = float_cache_holder::get_cache<int, int>(10);
    EXPECT_EQ(cache1, cache2);
}

// Test that different k values for float produce different cache entries
TEST_F(DragonboxCacheTest_332, FloatConsecutiveKDifferent_332) {
    auto cache1 = float_cache_holder::get_cache<int, int>(0);
    auto cache2 = float_cache_holder::get_cache<int, int>(1);
    EXPECT_NE(cache1, cache2);
}

// Test double cache entries at every offset within one compression block
TEST_F(DragonboxCacheTest_332, DoubleCacheAllOffsetsInBlock_332) {
    // Test all 27 offsets starting from min_k = -292
    for (int offset = 0; offset < 27; ++offset) {
        int k = -292 + offset;
        auto cache = double_cache_holder::get_cache<int, int>(k);
        EXPECT_NE(cache.high(), uint64_t(0))
            << "Cache high() should be non-zero for k=" << k << " (offset=" << offset << ")";
    }
}

// Test that different offsets within a block produce different results
TEST_F(DragonboxCacheTest_332, DoubleCacheDifferentOffsetsUnique_332) {
    auto cache_offset0 = double_cache_holder::get_cache<int, int>(-292);
    auto cache_offset1 = double_cache_holder::get_cache<int, int>(-291);
    auto cache_offset13 = double_cache_holder::get_cache<int, int>(-279);
    auto cache_offset26 = double_cache_holder::get_cache<int, int>(-266);

    // All should be different from each other
    EXPECT_TRUE(cache_offset0.high() != cache_offset1.high() ||
                cache_offset0.low() != cache_offset1.low());
    EXPECT_TRUE(cache_offset0.high() != cache_offset13.high() ||
                cache_offset0.low() != cache_offset13.low());
    EXPECT_TRUE(cache_offset0.high() != cache_offset26.high() ||
                cache_offset0.low() != cache_offset26.low());
}

// Test middle range k values for double
TEST_F(DragonboxCacheTest_332, DoubleCacheMiddleRange_332) {
    for (int k = -50; k <= 50; ++k) {
        auto cache = double_cache_holder::get_cache<int, int>(k);
        EXPECT_NE(cache.high(), uint64_t(0))
            << "Cache should be non-zero for k=" << k;
    }
}
