// TEST_ID 798
// Unit tests for Exiv2::DataValue::toString(size_t)
//
// Constraints respected:
// - Treat implementation as a black box (assert only observable behavior).
// - No access to private/internal state.
// - Use only public/protected interface (we only use public DataValue::value_ which is part of the interface).

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstddef>
#include <string>
#include <type_traits>

namespace {

class DataValueToStringTest_798 : public ::testing::Test {
 protected:
  static Exiv2::DataValue MakeDataValue() {
    // Pick a well-known TypeId enumerator from Exiv2.
    // The actual TypeId value shouldn't affect toString's observable behavior in these tests,
    // as we populate the public value_ container directly.
    return Exiv2::DataValue(Exiv2::unsignedLong);
  }

  template <typename IntT>
  static void Push(Exiv2::DataValue& dv, IntT v) {
    using Container = std::remove_reference_t<decltype(dv.value_)>;
    using Elem = typename Container::value_type;
    dv.value_.push_back(static_cast<Elem>(v));
  }
};

TEST_F(DataValueToStringTest_798, ReturnsDecimalStringForFirstAndLastElements_798) {
  auto dv = MakeDataValue();
  Push(dv, 0);
  Push(dv, 42);
  Push(dv, 1000000);

  EXPECT_EQ(dv.toString(0), std::string("0"));
  EXPECT_EQ(dv.toString(2), std::string("1000000"));
}

TEST_F(DataValueToStringTest_798, ReturnsDecimalStringForMiddleElement_798) {
  auto dv = MakeDataValue();
  Push(dv, 7);
  Push(dv, 8);
  Push(dv, 9);

  EXPECT_EQ(dv.toString(1), std::string("8"));
}

TEST_F(DataValueToStringTest_798, CallableOnConstObject_798) {
  auto dv_mut = MakeDataValue();
  Push(dv_mut, 123);

  const Exiv2::DataValue& dv = dv_mut;
  EXPECT_EQ(dv.toString(0), std::string("123"));
}

TEST_F(DataValueToStringTest_798, DoesNotChangeStoredValues_798) {
  auto dv = MakeDataValue();
  Push(dv, 11);
  Push(dv, 22);

  const auto before0 = dv.value_.at(0);
  const auto before1 = dv.value_.at(1);

  (void)dv.toString(0);
  (void)dv.toString(1);

  EXPECT_EQ(dv.value_.at(0), before0);
  EXPECT_EQ(dv.value_.at(1), before1);
}

TEST_F(DataValueToStringTest_798, ThrowsOutOfRangeWhenIndexEqualsSize_798) {
  auto dv = MakeDataValue();
  Push(dv, 1);
  Push(dv, 2);

  const std::size_t size = dv.value_.size();
  EXPECT_THROW((void)dv.toString(size), std::out_of_range);
}

TEST_F(DataValueToStringTest_798, ThrowsOutOfRangeWhenIndexIsFarBeyondSize_798) {
  auto dv = MakeDataValue();
  Push(dv, 5);

  EXPECT_THROW((void)dv.toString(static_cast<std::size_t>(999999)), std::out_of_range);
}

}  // namespace