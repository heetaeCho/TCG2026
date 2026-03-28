// File: test_dragonbox_nearest_to_odd_360.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using Policy = YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::nearest_to_odd_t;

class NearestToOddPolicyTest_360 : public ::testing::Test {};

// Helper: compare two objects by representation when it's well-defined to do so.
template <class T>
bool RepEquals(const T& a, const T& b) {
  static_assert(std::is_trivially_copyable_v<T>,
                "RepEquals requires trivially copyable types.");
  return std::memcmp(static_cast<const void*>(&a), static_cast<const void*>(&b), sizeof(T)) == 0;
}

TEST_F(NearestToOddPolicyTest_360, ShorterIntervalIsNoexcept_360) {
  EXPECT_TRUE(noexcept(Policy::shorter_interval(0)));
  EXPECT_TRUE(noexcept(Policy::shorter_interval(std::numeric_limits<int>::min())));
  EXPECT_TRUE(noexcept(Policy::shorter_interval(std::numeric_limits<long long>::max())));
}

TEST_F(NearestToOddPolicyTest_360, ShorterIntervalReturnIsDefaultConstructible_360) {
  using Returned = decltype(Policy::shorter_interval(0));

  EXPECT_TRUE((std::is_default_constructible_v<Returned>));
  EXPECT_TRUE((std::is_copy_constructible_v<Returned>));
  EXPECT_TRUE((std::is_move_constructible_v<Returned>));
}

TEST_F(NearestToOddPolicyTest_360, ShorterIntervalIsConstexprUsable_360) {
  // If this compiles, the function is usable in constant expressions as declared.
  constexpr auto r0 = Policy::shorter_interval(0);
  constexpr auto r1 = Policy::shorter_interval(123);

  (void)r0;
  (void)r1;

  SUCCEED();
}

TEST_F(NearestToOddPolicyTest_360, ShorterIntervalIsStableAcrossBoundaryInputs_360) {
  using Returned = decltype(Policy::shorter_interval(0));

  const auto a = Policy::shorter_interval(0);
  const auto b = Policy::shorter_interval(std::numeric_limits<int>::max());
  const auto c = Policy::shorter_interval(std::numeric_limits<int>::min());
  const auto def = Returned{};

  if constexpr (std::is_trivially_copyable_v<Returned>) {
    // Observable behavior check without assuming any internal fields/operators:
    // boundary inputs yield the same returned representation, and match default construction.
    EXPECT_TRUE(RepEquals(a, b));
    EXPECT_TRUE(RepEquals(a, c));
    EXPECT_TRUE(RepEquals(a, def));
  } else {
    // If representation comparison isn't safe, we still verify calls succeed for boundary inputs.
    SUCCEED();
  }
}

}  // namespace