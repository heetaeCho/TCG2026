// TEST_ID 789
// Unit tests for ./TestProjects/exiv2/src/value.cpp
//
// Partial interface under test:
// namespace Exiv2 {
//   class Value {
//    public:
//     std::string toString(size_t /*n*/) const { return toString(); }
//   };
// }
//
// Constraints note:
// - We treat implementation as a black box.
// - We only test observable behavior through the public interface.
// - This snippet provides only one observable behavior: that toString(size_t) delegates to toString().

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "value.hpp"  // Expected to provide Exiv2::Value (and its virtual toString()).

namespace {

class ValueTest_789 : public ::testing::Test {};

// A test double that derives from Exiv2::Value to make behavior observable.
// This is NOT re-implementing Exiv2::Value logic; it only provides an override
// for the parameterless toString() so we can verify delegation.
class TestValue : public Exiv2::Value {
 public:
  explicit TestValue(std::string s) : s_(std::move(s)) {}

  // Assumes Exiv2::Value has a virtual toString() const, which is typical in Exiv2.
  // If it is not virtual in your build, this will fail to compile (which is still
  // an accurate signal that delegation can't be observed via overriding).
  std::string toString() const override { return s_; }

 private:
  std::string s_;
};

TEST_F(ValueTest_789, ToStringSizeT_DelegatesToParameterless_789) {
  const TestValue v("hello");
  EXPECT_EQ(v.toString(static_cast<size_t>(0)), v.toString());
  EXPECT_EQ(v.toString(static_cast<size_t>(1)), v.toString());
  EXPECT_EQ(v.toString(static_cast<size_t>(999)), v.toString());
}

TEST_F(ValueTest_789, ToStringSizeT_IgnoresIndexAndReturnsSameString_789) {
  const TestValue v("same-for-all");

  const std::string s0 = v.toString(static_cast<size_t>(0));
  const std::string s1 = v.toString(static_cast<size_t>(1));
  const std::string smax = v.toString(static_cast<size_t>(-1));

  EXPECT_EQ(s0, "same-for-all");
  EXPECT_EQ(s1, "same-for-all");
  EXPECT_EQ(smax, "same-for-all");
  EXPECT_EQ(s0, s1);
  EXPECT_EQ(s1, smax);
}

TEST_F(ValueTest_789, ToStringSizeT_HandlesBoundaryValues_789) {
  const TestValue v("boundary");

  // Boundary values for size_t
  constexpr size_t kZero = static_cast<size_t>(0);
  constexpr size_t kOne = static_cast<size_t>(1);
  const size_t kMax = static_cast<size_t>(-1);

  EXPECT_EQ(v.toString(kZero), "boundary");
  EXPECT_EQ(v.toString(kOne), "boundary");
  EXPECT_EQ(v.toString(kMax), "boundary");
}

}  // namespace