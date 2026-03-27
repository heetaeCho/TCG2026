// File: ./TestProjects/yaml-cpp/test/dragonbox_compact_cache_test_391.cpp

#include <cstdint>
#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

class CompactTTest_391 : public ::testing::Test {};

// Helper to keep tests readable across FloatFormat choices.
template <class FloatFormat>
struct CacheTraits_391 {
  using Holder = YAML::jkj::dragonbox::cache_holder<FloatFormat>;
  using Entry = typename Holder::cache_entry_type;

  static constexpr int MinK = static_cast<int>(Holder::min_k);
  static constexpr int MaxK = static_cast<int>(Holder::max_k);
};

}  // namespace

// These type names are part of the upstream Dragonbox API and are typically present
// in yaml-cpp's contrib copy as well.
using Binary32_391 = YAML::jkj::dragonbox::ieee754_binary32;
using Binary64_391 = YAML::jkj::dragonbox::ieee754_binary64;

TEST_F(CompactTTest_391, GetCache_IsNoexceptForBinary32_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  static_assert(noexcept(YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<
                         Binary32_391, std::uint32_t>(Traits::MinK)));
  static_assert(std::is_same_v<
                decltype(YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<
                         Binary32_391, std::uint32_t>(Traits::MinK)),
                typename Traits::Entry>);
  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_IsNoexceptForBinary64_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  static_assert(noexcept(YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<
                         Binary64_391, std::uint32_t>(Traits::MinK)));
  static_assert(std::is_same_v<
                decltype(YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<
                         Binary64_391, std::uint32_t>(Traits::MinK)),
                typename Traits::Entry>);
  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary32_MinK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  const int k = Traits::MinK;

  // Observable behavior available through the interface: it returns a value and does not terminate.
  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary32_MaxK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  const int k = Traits::MaxK;

  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary32_MiddleK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  const int k = Traits::MinK + (Traits::MaxK - Traits::MinK) / 2;

  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary64_MinK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  const int k = Traits::MinK;

  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary64_MaxK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  const int k = Traits::MaxK;

  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_Binary64_MiddleK_DoesNotCrash_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  const int k = Traits::MinK + (Traits::MaxK - Traits::MinK) / 2;

  auto entry = YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_CanBeUsedInConstexprContext_Binary32_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  constexpr int k = Traits::MinK;

  // This is an observable contract in the signature/macros: JKJ_CONSTEXPR20 indicates constexpr intent.
  // If the implementation does not support constexpr in the current build mode, this will fail to compile.
  constexpr auto entry =
      YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

TEST_F(CompactTTest_391, GetCache_CanBeUsedInConstexprContext_Binary64_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  constexpr int k = Traits::MinK;

  constexpr auto entry =
      YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k);
  (void)entry;

  SUCCEED();
}

#ifndef NDEBUG
TEST_F(CompactTTest_391, GetCache_Binary32_BelowMinK_TriggersAssertDeath_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  const int k = Traits::MinK - 1;

  EXPECT_DEATH_IF_SUPPORTED(
      (void)YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k),
      ".*");
}

TEST_F(CompactTTest_391, GetCache_Binary32_AboveMaxK_TriggersAssertDeath_391) {
  using Traits = CacheTraits_391<Binary32_391>;
  const int k = Traits::MaxK + 1;

  EXPECT_DEATH_IF_SUPPORTED(
      (void)YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary32_391, std::uint32_t>(k),
      ".*");
}

TEST_F(CompactTTest_391, GetCache_Binary64_BelowMinK_TriggersAssertDeath_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  const int k = Traits::MinK - 1;

  EXPECT_DEATH_IF_SUPPORTED(
      (void)YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k),
      ".*");
}

TEST_F(CompactTTest_391, GetCache_Binary64_AboveMaxK_TriggersAssertDeath_391) {
  using Traits = CacheTraits_391<Binary64_391>;
  const int k = Traits::MaxK + 1;

  EXPECT_DEATH_IF_SUPPORTED(
      (void)YAML::jkj::dragonbox::policy::cache::compact_t::get_cache<Binary64_391, std::uint32_t>(k),
      ".*");
}
#endif  // !NDEBUG