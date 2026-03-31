#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

// We need to test the get_cache function from the compressed_cache_holder.
// Since the code is deeply nested in namespaces and templates, we need to
// identify the correct types and instantiation.

// The compressed_cache_holder is templated on FloatFormat and Dummy.
// For float (IEEE 754 binary32), the cache_entry_type is typically uint64_t.
// For double (IEEE 754 binary64), the cache_entry_type is typically uint128.
// The partial code shown uses umul128 and uint64_t operations, suggesting
// this is the float specialization (single precision) where cache entries are uint64_t.

namespace {

// Use the YAML namespace to access the types
using namespace YAML::jkj::dragonbox;

// For IEEE binary32 (float), we test the compressed cache
// The float format in dragonbox is typically ieee754_binary32
// We'll try to use the actual types from the library

class CompressedCacheTest_331 : public ::testing::Test {
protected:
    // Helper to call get_cache for float format
    // The compressed_cache_holder for ieee754_binary32 should have the
    // implementation shown in the partial code
};

// Test that get_cache returns non-zero for offset == 0 case (k aligned with compression ratio)
TEST_F(CompressedCacheTest_331, GetCacheAtBaseIndex_331) {
    // For float (binary32), min_k is around -31 and max_k around 46
    // When k = min_k, offset should be 0, so we get the base cache directly
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // k = min_k should give offset == 0
    auto result = holder::get_cache<int, int>(holder::min_k);
    EXPECT_NE(result, 0u);
}

// Test that get_cache returns non-zero for non-zero offset
TEST_F(CompressedCacheTest_331, GetCacheWithOffset_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // k = min_k + 1 should give offset == 1
    auto result = holder::get_cache<int, int>(holder::min_k + 1);
    EXPECT_NE(result, 0u);
}

// Test boundary: k = max_k
TEST_F(CompressedCacheTest_331, GetCacheAtMaxK_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    auto result = holder::get_cache<int, int>(holder::max_k);
    EXPECT_NE(result, 0u);
}

// Test multiple values within range
TEST_F(CompressedCacheTest_331, GetCacheMultipleValues_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    for (int k = holder::min_k; k <= holder::max_k; ++k) {
        auto result = holder::get_cache<int, int>(k);
        EXPECT_NE(result, 0u) << "Failed for k = " << k;
    }
}

// Test that different k values can produce different cache entries
TEST_F(CompressedCacheTest_331, DifferentKProduceDifferentCache_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    auto result1 = holder::get_cache<int, int>(holder::min_k);
    auto result2 = holder::get_cache<int, int>(holder::max_k);
    // min_k and max_k should produce different cache values
    EXPECT_NE(result1, result2);
}

// Test that consecutive k values produce results (no crash, valid results)
TEST_F(CompressedCacheTest_331, ConsecutiveKValues_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // Test a few consecutive values around a compression boundary
    int mid_k = (holder::min_k + holder::max_k) / 2;
    auto result_prev = holder::get_cache<int, int>(mid_k);
    auto result_curr = holder::get_cache<int, int>(mid_k + 1);
    
    EXPECT_NE(result_prev, 0u);
    EXPECT_NE(result_curr, 0u);
}

// Test with offset at compression_ratio - 1 (max offset before next base)
TEST_F(CompressedCacheTest_331, GetCacheMaxOffset_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // compression_ratio is 13, so offset can be up to 12
    // k = min_k + 12 should give offset == 12
    int k = holder::min_k + 12;
    if (k <= holder::max_k) {
        auto result = holder::get_cache<int, int>(k);
        EXPECT_NE(result, 0u);
    }
}

// Test at second base cache index (offset == 0 again)
TEST_F(CompressedCacheTest_331, GetCacheSecondBaseIndex_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // k = min_k + 13 should be the second base (offset == 0)
    int k = holder::min_k + 13;
    if (k <= holder::max_k) {
        auto result = holder::get_cache<int, int>(k);
        EXPECT_NE(result, 0u);
    }
}

// Test with offset == 6 (boundary for pow5 computation)
TEST_F(CompressedCacheTest_331, GetCacheOffsetSix_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // offset == 6: uses pow5_table[6] directly (offset < 7 path)
    int k = holder::min_k + 6;
    if (k <= holder::max_k) {
        auto result = holder::get_cache<int, int>(k);
        EXPECT_NE(result, 0u);
    }
}

// Test with offset == 7 (boundary for pow5 computation, uses multiplication path)
TEST_F(CompressedCacheTest_331, GetCacheOffsetSeven_331) {
    using holder = compressed_cache_detail::compressed_cache_holder<
        ieee754_binary32, void>;
    
    // offset == 7: uses pow5_table[6] * pow5_table[1] path
    int k = holder::min_k + 7;
    if (k <= holder::max_k) {
        auto result = holder::get_cache<int, int>(k);
        EXPECT_NE(result, 0u);
    }
}

} // anonymous namespace
