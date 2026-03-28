#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <type_traits>

namespace {

using namespace YAML::jkj::dragonbox;

// Alias for convenience
using full_cache = policy::cache::full_t;

// Test fixture
class DragonboxFullCacheTest_390 : public ::testing::Test {
protected:
};

// Test that get_cache compiles and returns for float format at min_k
TEST_F(DragonboxFullCacheTest_390, FloatGetCacheAtMinK_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto result = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    
    // The result should match the first element in the cache array
    EXPECT_EQ(result, CacheHolder::cache[0]);
}

// Test that get_cache returns correctly for float format at max_k
TEST_F(DragonboxFullCacheTest_390, FloatGetCacheAtMaxK_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto max_k = CacheHolder::max_k;
    auto min_k = CacheHolder::min_k;
    auto result = full_cache::get_cache<FloatFormat, int, decltype(max_k)>(max_k);
    
    auto index = static_cast<std::size_t>(max_k - min_k);
    EXPECT_EQ(result, CacheHolder::cache[index]);
}

// Test that get_cache compiles and returns for double format at min_k
TEST_F(DragonboxFullCacheTest_390, DoubleGetCacheAtMinK_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto result = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    
    EXPECT_EQ(result, CacheHolder::cache[0]);
}

// Test that get_cache returns correctly for double format at max_k
TEST_F(DragonboxFullCacheTest_390, DoubleGetCacheAtMaxK_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto max_k = CacheHolder::max_k;
    auto min_k = CacheHolder::min_k;
    auto result = full_cache::get_cache<FloatFormat, int, decltype(max_k)>(max_k);
    
    auto index = static_cast<std::size_t>(max_k - min_k);
    EXPECT_EQ(result, CacheHolder::cache[index]);
}

// Test float format with a middle value of k
TEST_F(DragonboxFullCacheTest_390, FloatGetCacheAtMiddleK_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    auto mid_k = min_k + (max_k - min_k) / 2;
    
    auto result = full_cache::get_cache<FloatFormat, int, decltype(mid_k)>(mid_k);
    
    auto index = static_cast<std::size_t>(mid_k - min_k);
    EXPECT_EQ(result, CacheHolder::cache[index]);
}

// Test double format with a middle value of k
TEST_F(DragonboxFullCacheTest_390, DoubleGetCacheAtMiddleK_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    auto mid_k = min_k + (max_k - min_k) / 2;
    
    auto result = full_cache::get_cache<FloatFormat, int, decltype(mid_k)>(mid_k);
    
    auto index = static_cast<std::size_t>(mid_k - min_k);
    EXPECT_EQ(result, CacheHolder::cache[index]);
}

// Test that the function is noexcept
TEST_F(DragonboxFullCacheTest_390, GetCacheIsNoexcept_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    EXPECT_TRUE(noexcept(full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k)));
}

// Test that the function is noexcept for double
TEST_F(DragonboxFullCacheTest_390, DoubleGetCacheIsNoexcept_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    EXPECT_TRUE(noexcept(full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k)));
}

// Test consecutive k values return different cache entries for float
TEST_F(DragonboxFullCacheTest_390, FloatConsecutiveKReturnDifferentEntries_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    
    if (max_k > min_k) {
        auto result1 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
        auto result2 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k + 1);
        // Consecutive cache entries should generally be different
        EXPECT_NE(result1, result2);
    }
}

// Test consecutive k values return different cache entries for double
TEST_F(DragonboxFullCacheTest_390, DoubleConsecutiveKReturnDifferentEntries_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    
    if (max_k > min_k) {
        auto result1 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
        auto result2 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k + 1);
        EXPECT_NE(result1, result2);
    }
}

// Test that calling get_cache with k=0 (if in range) works for float
TEST_F(DragonboxFullCacheTest_390, FloatGetCacheAtZeroK_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    
    if (min_k <= 0 && max_k >= 0) {
        auto result = full_cache::get_cache<FloatFormat, int, int>(0);
        auto index = static_cast<std::size_t>(0 - min_k);
        EXPECT_EQ(result, CacheHolder::cache[index]);
    }
}

// Test that calling get_cache with k=0 (if in range) works for double
TEST_F(DragonboxFullCacheTest_390, DoubleGetCacheAtZeroK_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto max_k = CacheHolder::max_k;
    
    if (min_k <= 0 && max_k >= 0) {
        auto result = full_cache::get_cache<FloatFormat, int, int>(0);
        auto index = static_cast<std::size_t>(0 - min_k);
        EXPECT_EQ(result, CacheHolder::cache[index]);
    }
}

// Test idempotency - same k returns same result
TEST_F(DragonboxFullCacheTest_390, FloatSameKReturnsSameResult_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto result1 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    auto result2 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    EXPECT_EQ(result1, result2);
}

// Test idempotency for double
TEST_F(DragonboxFullCacheTest_390, DoubleSameKReturnsSameResult_390) {
    using FloatFormat = ieee754_binary64;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto result1 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    auto result2 = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    EXPECT_EQ(result1, result2);
}

// Test with different ShiftAmountType template parameter
TEST_F(DragonboxFullCacheTest_390, FloatDifferentShiftAmountType_390) {
    using FloatFormat = ieee754_binary32;
    using CacheHolder = cache_holder_type<FloatFormat>;
    
    auto min_k = CacheHolder::min_k;
    auto result_int = full_cache::get_cache<FloatFormat, int, decltype(min_k)>(min_k);
    auto result_short = full_cache::get_cache<FloatFormat, short, decltype(min_k)>(min_k);
    EXPECT_EQ(result_int, result_short);
}

} // namespace
