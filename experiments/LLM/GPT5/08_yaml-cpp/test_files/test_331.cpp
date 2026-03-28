// TEST_ID: 331
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

template <class CacheHolder>
class CompressedCacheHolderTypedTest_331 : public ::testing::Test {};

using CacheHolders_331 = ::testing::Types<
    YAML::jkj::dragonbox::compressed_cache_holder<YAML::jkj::dragonbox::ieee754_binary32, void>,
    YAML::jkj::dragonbox::compressed_cache_holder<YAML::jkj::dragonbox::ieee754_binary64, void>>;

TYPED_TEST_SUITE(CompressedCacheHolderTypedTest_331, CacheHolders_331);

template <class CacheHolder, class ShiftAmountType, class DecimalExponentType>
using GetCacheResultT_331 = decltype(CacheHolder::template get_cache<ShiftAmountType, DecimalExponentType>(
    std::declval<DecimalExponentType>()));

}  // namespace

TYPED_TEST(CompressedCacheHolderTypedTest_331, IsNoexceptAndReturnsCacheEntryType_331) {
  using Holder = TypeParam;

  // Verify noexcept as promised by the signature.
  static_assert(noexcept(Holder::template get_cache<int, int>(0)),
                "get_cache<int,int> must be noexcept");

  // Verify return type matches holder's advertised cache_entry_type.
  static_assert(std::is_same_v<GetCacheResultT_331<Holder, int, int>, typename Holder::cache_entry_type>,
                "get_cache should return cache_entry_type");
}

TYPED_TEST(CompressedCacheHolderTypedTest_331, MinAndMaxKReturnNonZero_331) {
  using Holder = TypeParam;

  const int min_k = Holder::min_k;
  const int max_k = Holder::max_k;

  const auto c_min = Holder::template get_cache<int, int>(min_k);
  const auto c_max = Holder::template get_cache<int, int>(max_k);

  EXPECT_NE(c_min, 0) << "Cache entry at min_k should be non-zero";
  EXPECT_NE(c_max, 0) << "Cache entry at max_k should be non-zero";
}

TYPED_TEST(CompressedCacheHolderTypedTest_331, DeterministicForSameK_331) {
  using Holder = TypeParam;

  const int min_k = Holder::min_k;
  const int max_k = Holder::max_k;
  const int mid_k = min_k + (max_k - min_k) / 2;

  const auto a = Holder::template get_cache<int, int>(mid_k);
  const auto b = Holder::template get_cache<int, int>(mid_k);

  EXPECT_EQ(a, b) << "Calling get_cache twice with the same k should be deterministic";
  EXPECT_NE(a, 0) << "Returned cache entry should be non-zero";
}

TYPED_TEST(CompressedCacheHolderTypedTest_331, NearbyKValuesAreCallableAndNonZero_331) {
  using Holder = TypeParam;

  const int min_k = Holder::min_k;

  const auto c0 = Holder::template get_cache<int, int>(min_k);
  const auto c1 = Holder::template get_cache<int, int>(min_k + 1);

  EXPECT_NE(c0, 0);
  EXPECT_NE(c1, 0);
}

TYPED_TEST(CompressedCacheHolderTypedTest_331, SameKAcrossDifferentExponentTypesMatches_331) {
  using Holder = TypeParam;

  const int min_k = Holder::min_k;
  const int max_k = Holder::max_k;
  const int mid_k = min_k + (max_k - min_k) / 2;

  const auto c_int = Holder::template get_cache<int, int>(mid_k);
  const auto c_ll  = Holder::template get_cache<int, long long>(static_cast<long long>(mid_k));

  EXPECT_EQ(c_int, c_ll) << "Same k should yield same cache entry regardless of exponent type";
  EXPECT_NE(c_int, 0);
}

TYPED_TEST(CompressedCacheHolderTypedTest_331, SameKAcrossDifferentShiftAmountTypesMatches_331) {
  using Holder = TypeParam;

  const int min_k = Holder::min_k;
  const int max_k = Holder::max_k;
  const int mid_k = min_k + (max_k - min_k) / 2;

  const auto c_int_shift = Holder::template get_cache<int, int>(mid_k);
  const auto c_u32_shift =
      Holder::template get_cache<std::uint32_t, int>(mid_k);

  EXPECT_EQ(c_int_shift, c_u32_shift)
      << "Same k should yield same cache entry regardless of shift amount type";
  EXPECT_NE(c_int_shift, 0);
}