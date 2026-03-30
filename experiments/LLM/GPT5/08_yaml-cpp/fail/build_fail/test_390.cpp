// File: dragonbox_full_cache_policy_test_390.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::policy::cache::full_t;
using YAML::jkj::dragonbox::policy::cache::cache_holder_type;

template <class FloatT>
using Holder = cache_holder_type<FloatT>;

template <class FloatT>
using KType = decltype(Holder<FloatT>::min_k);

template <class FloatT>
void CallAt(KType<FloatT> k) {
  (void)full_t::get_cache<FloatT, int, KType<FloatT>>(k);
}

template <class FloatT>
void CallAndCheckRepeatability(KType<FloatT> k) {
  const auto a = full_t::get_cache<FloatT, int, KType<FloatT>>(k);
  const auto b = full_t::get_cache<FloatT, int, KType<FloatT>>(k);
  // Black-box observable property: repeated calls with same input should be stable.
  EXPECT_EQ(a, b);
}

}  // namespace

TEST(FullCachePolicyTest_390, GetCacheAtMinAndMaxDoesNotCrash_390) {
  CallAt<float>(Holder<float>::min_k);
  CallAt<float>(Holder<float>::max_k);

  CallAt<double>(Holder<double>::min_k);
  CallAt<double>(Holder<double>::max_k);
}

TEST(FullCachePolicyTest_390, GetCacheIsRepeatableForSameK_390) {
  CallAndCheckRepeatability<float>(Holder<float>::min_k);
  CallAndCheckRepeatability<float>(Holder<float>::max_k);

  CallAndCheckRepeatability<double>(Holder<double>::min_k);
  CallAndCheckRepeatability<double>(Holder<double>::max_k);
}

TEST(FullCachePolicyTest_390, GetCacheCanBeUsedInConstexprContext_390) {
  // This test is about the function being constexpr-usable (as declared).
  // If it isn't, this will fail to compile.
  {
    constexpr auto v = full_t::get_cache<float, int, KType<float>>(Holder<float>::min_k);
    (void)v;
  }
  {
    constexpr auto v = full_t::get_cache<double, int, KType<double>>(Holder<double>::min_k);
    (void)v;
  }
  SUCCEED();
}

TEST(FullCachePolicyTest_390, GetCacheOutOfRangeDiesWhenAssertsEnabled_390) {
#if defined(NDEBUG)
  GTEST_SKIP() << "Asserts are disabled in NDEBUG builds.";
#else
  // The implementation uses assert(k between min_k and max_k) (when constexpr14 is available).
  // We only run death checks when the exponent type is signed to avoid unsigned wraparound.
  if constexpr (std::is_signed_v<KType<float>>) {
    const auto kmin = Holder<float>::min_k;
    const auto kmax = Holder<float>::max_k;
    EXPECT_DEATH((void)full_t::get_cache<float, int, KType<float>>(KType<float>(kmin - 1)), "");
    EXPECT_DEATH((void)full_t::get_cache<float, int, KType<float>>(KType<float>(kmax + 1)), "");
  } else {
    GTEST_SKIP() << "Exponent type for float cache is unsigned; skipping wraparound-prone death tests.";
  }

  if constexpr (std::is_signed_v<KType<double>>) {
    const auto kmin = Holder<double>::min_k;
    const auto kmax = Holder<double>::max_k;
    EXPECT_DEATH((void)full_t::get_cache<double, int, KType<double>>(KType<double>(kmin - 1)), "");
    EXPECT_DEATH((void)full_t::get_cache<double, int, KType<double>>(KType<double>(kmax + 1)), "");
  } else {
    GTEST_SKIP() << "Exponent type for double cache is unsigned; skipping wraparound-prone death tests.";
  }
#endif
}