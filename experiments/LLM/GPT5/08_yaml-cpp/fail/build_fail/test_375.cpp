// File: test_dragonbox_nearest_always_open_375.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using NearestAlwaysOpen =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail::nearest_always_open_t;

using OpenInterval =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::open;

// C++17 detection for operator==
template <class T, class = void>
struct HasEqual : std::false_type {};
template <class T>
struct HasEqual<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};
template <class T>
constexpr bool HasEqualV = HasEqual<T>::value;

template <class T>
void ExpectSameAsDefaultConstructed(const T& value) {
  // If == exists, use it.
  if constexpr (HasEqualV<T>) {
    const T def{};
    EXPECT_TRUE(value == def);
    return;
  }

  // Otherwise, if trivially copyable, compare object representation.
  if constexpr (std::is_trivially_copyable<T>::value) {
    const T def{};
    EXPECT_EQ(0, std::memcmp(&value, &def, sizeof(T)));
    return;
  }

  // Fallback: we can at least assert the type is default-constructible and we got *a* value.
  static_assert(std::is_default_constructible<T>::value,
                "OpenInterval must be default-constructible for this test.");
  (void)value;
  SUCCEED();
}

}  // namespace

TEST(DragonboxNearestAlwaysOpenTest_375, NormalIntervalTypeAndNoexcept_375) {
  // Return type check (observable from the interface).
  static_assert(std::is_same<decltype(NearestAlwaysOpen::normal_interval(std::int32_t{})),
                             OpenInterval>::value,
                "normal_interval(...) must return interval_type::open");

  // noexcept is part of the observable interface contract.
  static_assert(noexcept(NearestAlwaysOpen::normal_interval(std::int32_t{})),
                "normal_interval(...) must be noexcept");

  // Also verify at runtime it doesn't throw.
  EXPECT_NO_THROW({
    (void)NearestAlwaysOpen::normal_interval(std::int32_t{0});
    (void)NearestAlwaysOpen::normal_interval(std::int32_t{1});
    (void)NearestAlwaysOpen::normal_interval(std::int32_t{-1});
  });
}

TEST(DragonboxNearestAlwaysOpenTest_375, NormalIntervalIsUsableInConstexprContext_375) {
  // If this compiles, the function is usable in a constant-expression context.
  constexpr auto v0 = NearestAlwaysOpen::normal_interval(std::int32_t{0});
  constexpr auto v1 = NearestAlwaysOpen::normal_interval(std::int64_t{123});

  (void)v0;
  (void)v1;

  static_assert(sizeof(v0) == sizeof(OpenInterval), "Unexpected OpenInterval size mismatch");
  static_assert(sizeof(v1) == sizeof(OpenInterval), "Unexpected OpenInterval size mismatch");
}

TEST(DragonboxNearestAlwaysOpenTest_375, NormalIntervalMatchesDefaultConstructed_375) {
  // The provided implementation returns {} (value-initialized OpenInterval).
  // We validate that the returned value matches a default-constructed OpenInterval,
  // using the best comparison available without accessing internals.
  {
    const auto got = NearestAlwaysOpen::normal_interval(std::int32_t{0});
    ExpectSameAsDefaultConstructed(got);
  }
  {
    const auto got = NearestAlwaysOpen::normal_interval(std::int32_t{1});
    ExpectSameAsDefaultConstructed(got);
  }
  {
    const auto got = NearestAlwaysOpen::normal_interval(std::int32_t{-1});
    ExpectSameAsDefaultConstructed(got);
  }
}

TEST(DragonboxNearestAlwaysOpenTest_375, NormalIntervalBoundaryValues_375) {
  // Boundary conditions on SignedSignificandBits argument.
  // We don’t assume any specific interval contents; only that calls succeed and return the right type.
  {
    const auto got = NearestAlwaysOpen::normal_interval(
        std::numeric_limits<std::int32_t>::min());
    ExpectSameAsDefaultConstructed(got);
  }
  {
    const auto got = NearestAlwaysOpen::normal_interval(
        std::numeric_limits<std::int32_t>::max());
    ExpectSameAsDefaultConstructed(got);
  }
  {
    const auto got = NearestAlwaysOpen::normal_interval(
        std::numeric_limits<std::int64_t>::min());
    ExpectSameAsDefaultConstructed(got);
  }
  {
    const auto got = NearestAlwaysOpen::normal_interval(
        std::numeric_limits<std::int64_t>::max());
    ExpectSameAsDefaultConstructed(got);
  }
}

TEST(DragonboxNearestAlwaysOpenTest_375, NormalIntervalDifferentSignedTypes_375) {
  // Same observable behavior across different signed integral types.
  const auto a = NearestAlwaysOpen::normal_interval(short{7});
  const auto b = NearestAlwaysOpen::normal_interval(int{-42});
  const auto c = NearestAlwaysOpen::normal_interval(long{0});
  const auto d = NearestAlwaysOpen::normal_interval(long long{999});

  ExpectSameAsDefaultConstructed(a);
  ExpectSameAsDefaultConstructed(b);
  ExpectSameAsDefaultConstructed(c);
  ExpectSameAsDefaultConstructed(d);
}