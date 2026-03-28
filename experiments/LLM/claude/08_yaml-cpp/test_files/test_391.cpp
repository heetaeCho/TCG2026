#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Type aliases for convenience
using float_format = typename float_format_of<float>::type;
using double_format = typename float_format_of<double>::type;

using compact_cache = policy::cache::compact_t;

// Test fixture
class CompactCacheTest_391 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== Float format tests =====================

TEST_F(CompactCacheTest_391, GetCacheFloatMinK_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    auto result = compact_cache::get_cache<float_format, int, int>(min_k);
    // Should return a valid cache entry without asserting
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheFloatMaxK_391) {
    constexpr auto max_k = cache_holder<float_format>::max_k;
    auto result = compact_cache::get_cache<float_format, int, int>(max_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheFloatMidK_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    constexpr auto max_k = cache_holder<float_format>::max_k;
    constexpr auto mid_k = min_k + (max_k - min_k) / 2;
    auto result = compact_cache::get_cache<float_format, int, int>(mid_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheFloatZeroK_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    constexpr auto max_k = cache_holder<float_format>::max_k;
    if (min_k <= 0 && max_k >= 0) {
        auto result = compact_cache::get_cache<float_format, int, int>(0);
        (void)result;
    }
}

TEST_F(CompactCacheTest_391, GetCacheFloatConsistentResults_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    auto result1 = compact_cache::get_cache<float_format, int, int>(min_k);
    auto result2 = compact_cache::get_cache<float_format, int, int>(min_k);
    EXPECT_EQ(result1, result2);
}

// ===================== Double format tests =====================

TEST_F(CompactCacheTest_391, GetCacheDoubleMinK_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    auto result = compact_cache::get_cache<double_format, int, int>(min_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheDoubleMaxK_391) {
    constexpr auto max_k = cache_holder<double_format>::max_k;
    auto result = compact_cache::get_cache<double_format, int, int>(max_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheDoubleMidK_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    constexpr auto max_k = cache_holder<double_format>::max_k;
    constexpr auto mid_k = min_k + (max_k - min_k) / 2;
    auto result = compact_cache::get_cache<double_format, int, int>(mid_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheDoubleZeroK_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    constexpr auto max_k = cache_holder<double_format>::max_k;
    if (min_k <= 0 && max_k >= 0) {
        auto result = compact_cache::get_cache<double_format, int, int>(0);
        (void)result;
    }
}

TEST_F(CompactCacheTest_391, GetCacheDoubleConsistentResults_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    auto result1 = compact_cache::get_cache<double_format, int, int>(min_k);
    auto result2 = compact_cache::get_cache<double_format, int, int>(min_k);
    EXPECT_EQ(result1, result2);
}

TEST_F(CompactCacheTest_391, GetCacheDoubleAdjacentKValuesDiffer_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    constexpr auto max_k = cache_holder<double_format>::max_k;
    if (min_k < max_k) {
        auto result1 = compact_cache::get_cache<double_format, int, int>(min_k);
        auto result2 = compact_cache::get_cache<double_format, int, int>(min_k + 1);
        EXPECT_NE(result1, result2);
    }
}

TEST_F(CompactCacheTest_391, GetCacheFloatAdjacentKValuesDiffer_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    constexpr auto max_k = cache_holder<float_format>::max_k;
    if (min_k < max_k) {
        auto result1 = compact_cache::get_cache<float_format, int, int>(min_k);
        auto result2 = compact_cache::get_cache<float_format, int, int>(min_k + 1);
        EXPECT_NE(result1, result2);
    }
}

TEST_F(CompactCacheTest_391, GetCacheDoubleAllValuesInRange_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    constexpr auto max_k = cache_holder<double_format>::max_k;
    // Iterate through all valid k values to ensure no assertion failures
    for (auto k = min_k; k <= max_k; ++k) {
        auto result = compact_cache::get_cache<double_format, int, int>(k);
        (void)result;
    }
}

TEST_F(CompactCacheTest_391, GetCacheFloatAllValuesInRange_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    constexpr auto max_k = cache_holder<float_format>::max_k;
    for (auto k = min_k; k <= max_k; ++k) {
        auto result = compact_cache::get_cache<float_format, int, int>(k);
        (void)result;
    }
}

// Test with different DecimalExponentType
TEST_F(CompactCacheTest_391, GetCacheFloatWithLongExponentType_391) {
    constexpr long min_k = static_cast<long>(cache_holder<float_format>::min_k);
    auto result = compact_cache::get_cache<float_format, int, long>(min_k);
    (void)result;
}

TEST_F(CompactCacheTest_391, GetCacheDoubleWithLongExponentType_391) {
    constexpr long min_k = static_cast<long>(cache_holder<double_format>::min_k);
    auto result = compact_cache::get_cache<double_format, int, long>(min_k);
    (void)result;
}

// Boundary: min_k and max_k should be non-empty range
TEST_F(CompactCacheTest_391, FloatCacheRangeIsValid_391) {
    constexpr auto min_k = cache_holder<float_format>::min_k;
    constexpr auto max_k = cache_holder<float_format>::max_k;
    EXPECT_LE(min_k, max_k);
}

TEST_F(CompactCacheTest_391, DoubleCacheRangeIsValid_391) {
    constexpr auto min_k = cache_holder<double_format>::min_k;
    constexpr auto max_k = cache_holder<double_format>::max_k;
    EXPECT_LE(min_k, max_k);
}

}  // namespace
