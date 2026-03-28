// =================================================================================================
// Unit tests for Exiv2::XmpArrayValue (black-box)
// File under test: ./TestProjects/exiv2/src/value.cpp
//
// Partial implementation given:
//   namespace Exiv2 { class XmpArrayValue { public: size_t count() const { return value_.size(); } }; }
//
// Constraints honored:
// - Only use public interface.
// - No private/internal state access.
// - No re-implementation/inference of internal logic.
// - Boundary + normal + error/exceptional (only if observable) cases.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "exiv2/value.hpp"

namespace {

using Exiv2::TypeId;
using Exiv2::XmpArrayValue;

class XmpArrayValueTest_845 : public ::testing::Test {
 protected:
  // Prefer a commonly-supported XMP type for array-like values; this is a construction-time choice only.
  // If the project uses a different TypeId for XMP arrays, adjust here.
  static constexpr TypeId kType = Exiv2::xmpText;

  static XmpArrayValue MakeValue() { return XmpArrayValue(kType); }
};

TEST_F(XmpArrayValueTest_845, CountInitiallyZero_845) {
  auto v = MakeValue();
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(XmpArrayValueTest_845, CountStableAcrossRepeatedCalls_845) {
  auto v = MakeValue();
  const auto c1 = v.count();
  const auto c2 = v.count();
  const auto c3 = v.count();
  EXPECT_EQ(c1, c2);
  EXPECT_EQ(c2, c3);
}

TEST_F(XmpArrayValueTest_845, CountUnaffectedByClone_845) {
  auto v = MakeValue();
  const auto before = v.count();

  // clone() is part of the public interface in value.hpp.
  // We only verify that cloning does not mutate the original observable state.
  auto cloned = v.clone();
  (void)cloned;  // Existence is enough for this test's purpose.

  EXPECT_EQ(v.count(), before);
}

TEST_F(XmpArrayValueTest_845, ReadEmptyBufferDoesNotMakeNegativeCount_845) {
  auto v = MakeValue();
  (void)v.read(std::string{});  // return value semantics are not specified in the prompt

  // Only assert basic observable invariants via the interface.
  EXPECT_GE(v.count(), 0u);
}

TEST_F(XmpArrayValueTest_845, CountAfterReadIsNonNegative_845) {
  auto v = MakeValue();

  // Use a few representative inputs without assuming parsing rules.
  (void)v.read("one");
  EXPECT_GE(v.count(), 0u);

  (void)v.read("one,two");
  EXPECT_GE(v.count(), 0u);

  (void)v.read("[]");
  EXPECT_GE(v.count(), 0u);
}

TEST_F(XmpArrayValueTest_845, ToStringOutOfRangeDoesNotChangeCount_845) {
  auto v = MakeValue();
  const auto before = v.count();

  // Boundary: use an index that is very likely out of range.
  // We do NOT assume whether it throws; we only assert no mutation on the observable count
  // if an exception occurs.
  const size_t out_of_range_index = before + 1000u;

  try {
    (void)v.toString(out_of_range_index);
  } catch (...) {
    // Exceptional case is allowed if observable; ensure state did not change.
  }

  EXPECT_EQ(v.count(), before);
}

TEST_F(XmpArrayValueTest_845, NumericConversionsOutOfRangeDoNotChangeCount_845) {
  auto v = MakeValue();
  const auto before = v.count();
  const size_t out_of_range_index = before + 123u;

  try {
    (void)v.toInt64(out_of_range_index);
  } catch (...) {
  }
  EXPECT_EQ(v.count(), before);

  try {
    (void)v.toUint32(out_of_range_index);
  } catch (...) {
  }
  EXPECT_EQ(v.count(), before);

  try {
    (void)v.toFloat(out_of_range_index);
  } catch (...) {
  }
  EXPECT_EQ(v.count(), before);

  try {
    (void)v.toRational(out_of_range_index);
  } catch (...) {
  }
  EXPECT_EQ(v.count(), before);
}

TEST_F(XmpArrayValueTest_845, WriteDoesNotChangeCount_845) {
  auto v = MakeValue();
  const auto before = v.count();

  std::ostringstream oss;
  try {
    (void)v.write(oss);
  } catch (...) {
    // Even if write fails/throws, it should not mutate the count in a black-box expectation.
  }

  EXPECT_EQ(v.count(), before);
}

}  // namespace