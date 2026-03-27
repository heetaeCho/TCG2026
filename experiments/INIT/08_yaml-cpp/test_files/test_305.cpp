// TEST_ID: 305
// File: test_uint128_add_assign_305.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

using UInt128 = YAML::jkj::dragonbox::detail::wuint::uint128;

// Compile-time interface/contract checks (no behavioral inference beyond the signature).
static_assert(noexcept(std::declval<UInt128&>() += stdr::uint_least64_t{}),
              "uint128::operator+= must be noexcept as declared");

using PlusEq = decltype(&UInt128::operator+=);
static_assert(std::is_invocable_v<PlusEq, UInt128&, stdr::uint_least64_t>,
              "operator+= should be invocable on lvalues");
static_assert(!std::is_invocable_v<PlusEq, UInt128&&, stdr::uint_least64_t>,
              "operator+= is '&'-qualified and should not be invocable on rvalues");

class UInt128AddAssignTest_305 : public ::testing::Test {};

TEST_F(UInt128AddAssignTest_305, ConstructorStoresHighLow_305) {
  const stdr::uint_least64_t hi = 0x0123456789abcdefULL;
  const stdr::uint_least64_t lo = 0xfedcba9876543210ULL;

  const UInt128 u(hi, lo);

  EXPECT_EQ(u.high(), hi);
  EXPECT_EQ(u.low(), lo);
}

TEST_F(UInt128AddAssignTest_305, AddZeroDoesNotChangeValue_305) {
  const stdr::uint_least64_t hi = 123;
  const stdr::uint_least64_t lo = 456;

  UInt128 u(hi, lo);
  u += stdr::uint_least64_t{0};

  EXPECT_EQ(u.high(), hi);
  EXPECT_EQ(u.low(), lo);
}

TEST_F(UInt128AddAssignTest_305, AddWithoutCarryUpdatesLowOnly_305) {
  UInt128 u(/*high=*/7, /*low=*/10);

  u += stdr::uint_least64_t{25};

  EXPECT_EQ(u.high(), 7u);
  EXPECT_EQ(u.low(), 35u);
}

TEST_F(UInt128AddAssignTest_305, AddWithCarryIncrementsHighAndWrapsLow_305) {
  const stdr::uint_least64_t max64 = ~stdr::uint_least64_t{0};

  UInt128 u(/*high=*/0, /*low=*/max64 - 1);
  u += stdr::uint_least64_t{2};

  EXPECT_EQ(u.high(), 1u);
  EXPECT_EQ(u.low(), 0u);
}

TEST_F(UInt128AddAssignTest_305, AddOneToMaxLowIncrementsHigh_305) {
  const stdr::uint_least64_t max64 = ~stdr::uint_least64_t{0};

  UInt128 u(/*high=*/5, /*low=*/max64);
  u += stdr::uint_least64_t{1};

  EXPECT_EQ(u.high(), 6u);
  EXPECT_EQ(u.low(), 0u);
}

TEST_F(UInt128AddAssignTest_305, AddMaxToZeroSetsLowToMaxWithoutCarry_305) {
  const stdr::uint_least64_t max64 = ~stdr::uint_least64_t{0};

  UInt128 u(/*high=*/0, /*low=*/0);
  u += max64;

  EXPECT_EQ(u.high(), 0u);
  EXPECT_EQ(u.low(), max64);
}

TEST_F(UInt128AddAssignTest_305, OperatorReturnsSameObjectByReference_305) {
  UInt128 u(/*high=*/1, /*low=*/2);

  UInt128& ref = (u += stdr::uint_least64_t{3});

  EXPECT_EQ(&ref, &u);
  EXPECT_EQ(u.high(), 1u);
  EXPECT_EQ(u.low(), 5u);
}

TEST_F(UInt128AddAssignTest_305, SupportsChainedAddition_305) {
  // Chaining is observable via successive operations on the same object.
  UInt128 u(/*high=*/0, /*low=*/0);

  (u += stdr::uint_least64_t{1}) += stdr::uint_least64_t{2};

  EXPECT_EQ(u.high(), 0u);
  EXPECT_EQ(u.low(), 3u);
}

}  // namespace