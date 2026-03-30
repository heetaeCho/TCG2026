// TEST_ID: 376
// File: test_dragonbox_nearest_always_open_376.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <type_traits>

// NOTE: The project layout in the prompt indicates this header exists in the codebase.
// Adjust include path if your build exposes it differently.
#include "contrib/dragonbox.h"

namespace {

using NearestAlwaysOpen =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail::nearest_always_open_t;

using IntervalOpen =
    YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::interval_type::open;

template <class T>
void AssertReturnedValueLooksDefaultConstructed(const T& value) {
  // We cannot assume operator== exists. For trivially-copyable, standard-layout types,
  // a bytewise comparison with a value-initialized instance is a reasonable observable check.
  if constexpr (std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>) {
    T expected{};
    EXPECT_EQ(0, std::memcmp(&value, &expected, sizeof(T)));
  } else {
    // For non-trivial types, we only assert that default construction is valid and that
    // we received an object (i.e., the call succeeded).
    (void)value;
    SUCCEED();
  }
}

struct WeirdSignedBits {
  int v;
};

}  // namespace

class NearestAlwaysOpenTest_376 : public ::testing::Test {};

TEST_F(NearestAlwaysOpenTest_376, ReturnTypeIsIntervalOpen_376) {
  using Ret = decltype(NearestAlwaysOpen::shorter_interval(0));
  EXPECT_TRUE((std::is_same_v<Ret, IntervalOpen>));
}

TEST_F(NearestAlwaysOpenTest_376, IsNoexcept_376) {
  EXPECT_TRUE(noexcept(NearestAlwaysOpen::shorter_interval(0)));
  EXPECT_TRUE(noexcept(NearestAlwaysOpen::shorter_interval(-1)));
}

TEST_F(NearestAlwaysOpenTest_376, CallableWithVariousSignedSignificandBits_376) {
  // Normal / typical integral types.
  auto r1 = NearestAlwaysOpen::shorter_interval(0);
  auto r2 = NearestAlwaysOpen::shorter_interval(1);
  auto r3 = NearestAlwaysOpen::shorter_interval(-1);

  // Boundary-ish values for a wider type.
  const std::int64_t min64 = (std::numeric_limits<std::int64_t>::min)();
  const std::int64_t max64 = (std::numeric_limits<std::int64_t>::max)();
  auto r4 = NearestAlwaysOpen::shorter_interval(min64);
  auto r5 = NearestAlwaysOpen::shorter_interval(max64);

  // A non-integral user-defined type still satisfies the template parameter,
  // as long as it can be passed by value.
  WeirdSignedBits w{123};
  auto r6 = NearestAlwaysOpen::shorter_interval(w);

  // Basic sanity: all calls returned *some* IntervalOpen object.
  (void)r1;
  (void)r2;
  (void)r3;
  (void)r4;
  (void)r5;
  (void)r6;

  SUCCEED();
}

TEST_F(NearestAlwaysOpenTest_376, ReturnsDefaultConstructedIntervalOpen_376) {
  // Observable behavior: the returned object is an IntervalOpen.
  // If it is trivially copyable + standard layout, we also verify it matches bytes of a
  // value-initialized IntervalOpen (i.e., appears default-constructed).
  auto ret0 = NearestAlwaysOpen::shorter_interval(0);
  auto ret1 = NearestAlwaysOpen::shorter_interval(123);
  auto ret2 = NearestAlwaysOpen::shorter_interval(-123);

  AssertReturnedValueLooksDefaultConstructed(ret0);
  AssertReturnedValueLooksDefaultConstructed(ret1);
  AssertReturnedValueLooksDefaultConstructed(ret2);
}