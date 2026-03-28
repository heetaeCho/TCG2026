// File: test_xmparrayvalue_tofloat_850.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <limits>
#include <string>
#include <vector>

// Exiv2
#include "exiv2/value.hpp"

namespace {

class XmpArrayValueTest_850 : public ::testing::Test {
protected:
  // Avoid relying on specific enum constants that may vary across builds.
  static Exiv2::TypeId AnyTypeId() { return static_cast<Exiv2::TypeId>(0); }

  static Exiv2::XmpArrayValue MakeSut() { return Exiv2::XmpArrayValue(AnyTypeId()); }

  // Black-box probing helper: try multiple plausible textual encodings for "array containing 1".
  // We don't assume parsing rules; we only assert that *some* supported format exists.
  static bool ReadAnyOf(Exiv2::XmpArrayValue& v, const std::vector<std::string>& candidates) {
    for (const auto& s : candidates) {
      // If read throws for some formats, that's fine; keep probing.
      try {
        (void)v.read(s);
      } catch (...) {
        continue;
      }
      if (v.count() > 0) return true;
    }
    return false;
  }
};

TEST_F(XmpArrayValueTest_850, ToFloatOnEmptyThrowsOutOfRange_850) {
  Exiv2::XmpArrayValue v = MakeSut();

  ASSERT_EQ(v.count(), 0u);
  EXPECT_THROW((void)v.toFloat(0), std::out_of_range);
}

TEST_F(XmpArrayValueTest_850, ToFloatAtIndexEqualToCountThrowsOutOfRange_850) {
  Exiv2::XmpArrayValue v = MakeSut();

  // Whether read succeeds depends on implementation; boundary behavior we test is:
  // "n == count()" must be out-of-range, for any count (including 0).
  const size_t n = v.count();
  EXPECT_THROW((void)v.toFloat(n), std::out_of_range);
}

TEST_F(XmpArrayValueTest_850, ToFloatDoesNotChangeOkFlagWhenIndexOutOfRange_850) {
  Exiv2::XmpArrayValue v = MakeSut();

  const bool ok_before = v.ok();
  ASSERT_EQ(v.count(), 0u);

  EXPECT_THROW((void)v.toFloat(0), std::out_of_range);
  EXPECT_EQ(v.ok(), ok_before);

  // Repeating should remain consistent and also not alter ok().
  EXPECT_THROW((void)v.toFloat(0), std::out_of_range);
  EXPECT_EQ(v.ok(), ok_before);
}

TEST_F(XmpArrayValueTest_850, ToFloatWorksForFirstElementWhenReadableNumericInputProvided_850) {
  Exiv2::XmpArrayValue v = MakeSut();

  // Probe a small set of common representations without assuming which one is correct.
  const std::vector<std::string> candidates = {
      "1",
      " 1 ",
      "1,2",
      "1 2",
      "1;2",
      "[1,2]",
      "{1,2}",
  };

  ASSERT_TRUE(ReadAnyOf(v, candidates)) << "Unable to populate XmpArrayValue via read() using common numeric formats.";
  ASSERT_GT(v.count(), 0u);

  // Now that at least one element exists, toFloat(0) should be observable and not throw.
  float f = std::numeric_limits<float>::quiet_NaN();
  EXPECT_NO_THROW(f = v.toFloat(0));

  // Black-box but reasonable observable expectation: a representation containing leading "1"
  // should yield a float close to 1.0 for element 0 when parsing is supported.
  EXPECT_TRUE(std::isfinite(f));
  EXPECT_NEAR(f, 1.0f, 1e-6f);

  // Calling again should be stable (same index, same observable result).
  float f2 = std::numeric_limits<float>::quiet_NaN();
  EXPECT_NO_THROW(f2 = v.toFloat(0));
  EXPECT_NEAR(f2, f, 0.0f);
}

TEST_F(XmpArrayValueTest_850, ToFloatThrowsForIndexPastLastElementAfterSuccessfulRead_850) {
  Exiv2::XmpArrayValue v = MakeSut();

  const std::vector<std::string> candidates = {
      "1",
      "1,2",
      "1 2",
      "[1,2]",
  };

  ASSERT_TRUE(ReadAnyOf(v, candidates)) << "Unable to populate XmpArrayValue via read() using common numeric formats.";
  ASSERT_GT(v.count(), 0u);

  const size_t last_plus_one = v.count();  // boundary: just past last valid index
  EXPECT_THROW((void)v.toFloat(last_plus_one), std::out_of_range);
}

}  // namespace