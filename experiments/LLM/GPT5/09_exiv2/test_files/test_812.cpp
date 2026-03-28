// File: test_value_stringvaluebase_torational_812.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

#include "exiv2/value.hpp"

namespace {

// Helper to read numerator/denominator without assuming too much.
// Exiv2::Rational is typically a std::pair-like type in Exiv2.
template <typename R>
static auto num(const R& r) -> decltype(r.first) {
  return r.first;
}
template <typename R>
static auto den(const R& r) -> decltype(r.second) {
  return r.second;
}

class StringValueBaseTest_812 : public ::testing::Test {
 protected:
  static Exiv2::TypeId AnyTypeId() {
    // Avoid assuming specific enumerators exist; any value is acceptable for
    // construction since we treat behavior as a black box.
    return static_cast<Exiv2::TypeId>(0);
  }
};

}  // namespace

TEST_F(StringValueBaseTest_812, ToRationalReturnsCharAsNumeratorAndOneAsDenominator_812) {
  Exiv2::StringValueBase v(AnyTypeId(), std::string{});
  v.value_ = "Az";  // public API per provided header

  const auto r0 = v.toRational(0);
  EXPECT_EQ(static_cast<long long>(num(r0)), static_cast<long long>(static_cast<unsigned char>('A')));
  EXPECT_EQ(static_cast<long long>(den(r0)), 1LL);

  const auto r1 = v.toRational(1);
  EXPECT_EQ(static_cast<long long>(num(r1)), static_cast<long long>(static_cast<unsigned char>('z')));
  EXPECT_EQ(static_cast<long long>(den(r1)), 1LL);
}

TEST_F(StringValueBaseTest_812, ToRationalOnEmptyStringThrowsOutOfRange_812) {
  Exiv2::StringValueBase v(AnyTypeId(), std::string{});
  v.value_.clear();

  EXPECT_THROW((void)v.toRational(0), std::out_of_range);
}

TEST_F(StringValueBaseTest_812, ToRationalIndexEqualToSizeThrowsOutOfRange_812) {
  Exiv2::StringValueBase v(AnyTypeId(), std::string{});
  v.value_ = "X";

  // std::string::at(size) throws
  EXPECT_THROW((void)v.toRational(v.value_.size()), std::out_of_range);
}

TEST_F(StringValueBaseTest_812, ToRationalVeryLargeIndexThrowsOutOfRange_812) {
  Exiv2::StringValueBase v(AnyTypeId(), std::string{});
  v.value_ = "Hi";

  EXPECT_THROW((void)v.toRational(static_cast<size_t>(-1)), std::out_of_range);
}