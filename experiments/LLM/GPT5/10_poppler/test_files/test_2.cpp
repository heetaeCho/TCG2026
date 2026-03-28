// TEST_ID: 2
// Unit tests for ./TestProjects/poppler/goo/GooCheckedOps.h
//
// Target API:
//   template<typename T> inline bool checkedAssign(long long lz, T *z);
//
// Behavior (observable from interface):
//   - Returns true if lz does NOT fit into T (overflow/underflow would occur); must not require *z update.
//   - Returns false if lz fits into T; assigns *z = static_cast<T>(lz).
//
// Notes:
//   - Tests are black-box and only validate return values + observable effect on *z.
//   - We avoid relying on any internal logic besides what the signature and documented behavior imply.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

// Include the header under test
#include "TestProjects/poppler/goo/GooCheckedOps.h"

namespace {

// Helper: pick a sentinel value that is unlikely to equal any assigned value in the tested scenario.
template <typename T>
T SentinelValue() {
  if constexpr (std::is_integral_v<T>) {
    // For integrals, choose max-1 when possible, else max.
    return (std::numeric_limits<T>::max)() == (std::numeric_limits<T>::min)()
               ? (std::numeric_limits<T>::max)()
               : static_cast<T>((std::numeric_limits<T>::max)() - 1);
  } else {
    // Not expected for these tests; keep it simple.
    return T{};
  }
}

}  // namespace

// -------------------------
// Normal operation
// -------------------------

TEST(GooCheckedOps_checkedAssignTest_2, AssignsWithinRange_Int32_2) {
  int32_t z = SentinelValue<int32_t>();
  const long long lz = 12345;

  const bool overflow = checkedAssign<int32_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, static_cast<int32_t>(lz));
}

TEST(GooCheckedOps_checkedAssignTest_2, AssignsNegativeWithinRange_Int16_2) {
  int16_t z = SentinelValue<int16_t>();
  const long long lz = -123;

  const bool overflow = checkedAssign<int16_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, static_cast<int16_t>(lz));
}

TEST(GooCheckedOps_checkedAssignTest_2, AssignsZero_Unsigned16_2) {
  uint16_t z = SentinelValue<uint16_t>();
  const long long lz = 0;

  const bool overflow = checkedAssign<uint16_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, static_cast<uint16_t>(lz));
}

// -------------------------
// Boundary conditions
// -------------------------

TEST(GooCheckedOps_checkedAssignTest_2, AssignsAtMaxBoundary_Int16_2) {
  int16_t z = SentinelValue<int16_t>();
  const long long lz = static_cast<long long>((std::numeric_limits<int16_t>::max)());

  const bool overflow = checkedAssign<int16_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, (std::numeric_limits<int16_t>::max)());
}

TEST(GooCheckedOps_checkedAssignTest_2, AssignsAtMinBoundary_Int16_2) {
  int16_t z = SentinelValue<int16_t>();
  const long long lz = static_cast<long long>((std::numeric_limits<int16_t>::min)());

  const bool overflow = checkedAssign<int16_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, (std::numeric_limits<int16_t>::min)());
}

TEST(GooCheckedOps_checkedAssignTest_2, AssignsAtMaxBoundary_Uint16_2) {
  uint16_t z = SentinelValue<uint16_t>();
  const long long lz = static_cast<long long>((std::numeric_limits<uint16_t>::max)());

  const bool overflow = checkedAssign<uint16_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, (std::numeric_limits<uint16_t>::max)());
}

TEST(GooCheckedOps_checkedAssignTest_2, OverflowJustAboveMax_Int16_2) {
  int16_t z = SentinelValue<int16_t>();
  const int16_t sentinel = z;
  const long long lz =
      static_cast<long long>((std::numeric_limits<int16_t>::max)()) + 1LL;

  const bool overflow = checkedAssign<int16_t>(lz, &z);

  EXPECT_TRUE(overflow);
  // On overflow, observable requirement: should not need to update z.
  EXPECT_EQ(z, sentinel);
}

TEST(GooCheckedOps_checkedAssignTest_2, UnderflowJustBelowMin_Int16_2) {
  int16_t z = SentinelValue<int16_t>();
  const int16_t sentinel = z;
  const long long lz =
      static_cast<long long>((std::numeric_limits<int16_t>::min)()) - 1LL;

  const bool overflow = checkedAssign<int16_t>(lz, &z);

  EXPECT_TRUE(overflow);
  EXPECT_EQ(z, sentinel);
}

TEST(GooCheckedOps_checkedAssignTest_2, NegativeIsOutOfRange_ForUnsigned_2) {
  uint32_t z = SentinelValue<uint32_t>();
  const uint32_t sentinel = z;
  const long long lz = -1;

  const bool overflow = checkedAssign<uint32_t>(lz, &z);

  EXPECT_TRUE(overflow);
  EXPECT_EQ(z, sentinel);
}

// -------------------------
// Exceptional / error-like cases (observable)
// -------------------------
// There are no exceptions specified; the only observable "error" is the boolean result.
// We still validate extreme values as error-like behavior.

TEST(GooCheckedOps_checkedAssignTest_2, OverflowForVeryLargePositive_Int32_2) {
  int32_t z = SentinelValue<int32_t>();
  const int32_t sentinel = z;
  const long long lz = (std::numeric_limits<long long>::max)();

  const bool overflow = checkedAssign<int32_t>(lz, &z);

  EXPECT_TRUE(overflow);
  EXPECT_EQ(z, sentinel);
}

TEST(GooCheckedOps_checkedAssignTest_2, UnderflowForVeryLargeNegative_Int32_2) {
  int32_t z = SentinelValue<int32_t>();
  const int32_t sentinel = z;
  const long long lz = (std::numeric_limits<long long>::min)();

  const bool overflow = checkedAssign<int32_t>(lz, &z);

  EXPECT_TRUE(overflow);
  EXPECT_EQ(z, sentinel);
}

// -------------------------
// Verification of external interactions
// -------------------------
// No collaborators/callbacks exist; the only "interaction" is writing through the pointer.
// We verify it only mutates on success and does not require mutation on overflow.

TEST(GooCheckedOps_checkedAssignTest_2, DoesNotModifyOnOverflow_Uint8_2) {
  uint8_t z = SentinelValue<uint8_t>();
  const uint8_t sentinel = z;

  // One above max for uint8_t.
  const long long lz =
      static_cast<long long>((std::numeric_limits<uint8_t>::max)()) + 1LL;

  const bool overflow = checkedAssign<uint8_t>(lz, &z);

  EXPECT_TRUE(overflow);
  EXPECT_EQ(z, sentinel);
}

TEST(GooCheckedOps_checkedAssignTest_2, ModifiesOnSuccess_Uint8_2) {
  uint8_t z = SentinelValue<uint8_t>();
  const long long lz = static_cast<long long>((std::numeric_limits<uint8_t>::max)());

  const bool overflow = checkedAssign<uint8_t>(lz, &z);

  EXPECT_FALSE(overflow);
  EXPECT_EQ(z, (std::numeric_limits<uint8_t>::max)());
}