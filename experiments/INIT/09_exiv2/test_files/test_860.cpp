// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 860
//
// Unit tests for Exiv2::LangAltValue::toFloat(size_t) const
//
// Constraints honored:
// - Black-box testing via public interface only
// - No reliance on private/internal state (e.g., ok_)
// - Covers normal + boundary + observable “error” behavior (constant return)
// - Ensures no exceptions are thrown

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

// Prefer the public Exiv2 header that declares LangAltValue.
#include <exiv2/value.hpp>

namespace {

class LangAltValueTest_860 : public ::testing::Test {};

TEST_F(LangAltValueTest_860, ToFloatReturnsZeroForZeroIndex_860) {
  const Exiv2::LangAltValue v;
  EXPECT_FLOAT_EQ(0.0f, v.toFloat(static_cast<size_t>(0)));
}

TEST_F(LangAltValueTest_860, ToFloatReturnsZeroForNonZeroIndex_860) {
  const Exiv2::LangAltValue v;
  EXPECT_FLOAT_EQ(0.0f, v.toFloat(static_cast<size_t>(1)));
  EXPECT_FLOAT_EQ(0.0f, v.toFloat(static_cast<size_t>(2)));
  EXPECT_FLOAT_EQ(0.0f, v.toFloat(static_cast<size_t>(123)));
}

TEST_F(LangAltValueTest_860, ToFloatReturnsZeroForMaxSizeTIndex_860) {
  const Exiv2::LangAltValue v;
  const size_t maxN = (std::numeric_limits<size_t>::max)();
  EXPECT_FLOAT_EQ(0.0f, v.toFloat(maxN));
}

TEST_F(LangAltValueTest_860, ToFloatDoesNotThrowForVariousIndices_860) {
  const Exiv2::LangAltValue v;

  EXPECT_NO_THROW((void)v.toFloat(static_cast<size_t>(0)));
  EXPECT_NO_THROW((void)v.toFloat(static_cast<size_t>(1)));
  EXPECT_NO_THROW((void)v.toFloat(static_cast<size_t>(9999)));
  EXPECT_NO_THROW((void)v.toFloat((std::numeric_limits<size_t>::max)()));
}

TEST_F(LangAltValueTest_860, ToFloatIsConsistentAcrossRepeatedCalls_860) {
  const Exiv2::LangAltValue v;

  const float a = v.toFloat(static_cast<size_t>(0));
  const float b = v.toFloat(static_cast<size_t>(0));
  const float c = v.toFloat(static_cast<size_t>(1));
  const float d = v.toFloat(static_cast<size_t>(1));

  EXPECT_FLOAT_EQ(0.0f, a);
  EXPECT_FLOAT_EQ(0.0f, b);
  EXPECT_FLOAT_EQ(0.0f, c);
  EXPECT_FLOAT_EQ(0.0f, d);
}

}  // namespace