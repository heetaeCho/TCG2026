// TEST_ID 879
// Unit tests for Exiv2::TimeValue::count() behavior (black-box).
//
// File under test: exiv2/src/value.cpp (partial)
// Interface header: exiv2/value.hpp

#include <gtest/gtest.h>

#include <string>

#include <exiv2/value.hpp>

namespace {

class TimeValueTest_879 : public ::testing::Test {
 protected:
  Exiv2::TimeValue makeDefault() { return Exiv2::TimeValue(); }

  Exiv2::TimeValue makeParam() {
    // Use a clearly valid time and timezone offset.
    return Exiv2::TimeValue(/*hour*/ 12, /*minute*/ 34, /*second*/ 56, /*tzHour*/ 9, /*tzMinute*/ 0);
  }
};

TEST_F(TimeValueTest_879, DefaultCtor_CountEqualsSize_879) {
  const Exiv2::TimeValue v = makeDefault();

  // Observable contract from provided partial implementation:
  // count() should return size().
  EXPECT_NO_THROW({
    const size_t c = v.count();
    const size_t s = v.size();
    EXPECT_EQ(c, s);
  });
}

TEST_F(TimeValueTest_879, ParamCtor_CountEqualsSize_879) {
  const Exiv2::TimeValue v = makeParam();

  EXPECT_NO_THROW({
    const size_t c = v.count();
    const size_t s = v.size();
    EXPECT_EQ(c, s);
  });
}

TEST_F(TimeValueTest_879, ConstObject_RepeatedCallsRemainConsistent_879) {
  const Exiv2::TimeValue v = makeParam();

  EXPECT_NO_THROW({
    const size_t c1 = v.count();
    const size_t s1 = v.size();
    const size_t c2 = v.count();
    const size_t s2 = v.size();

    EXPECT_EQ(c1, s1);
    EXPECT_EQ(c2, s2);
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(s1, s2);
  });
}

TEST_F(TimeValueTest_879, ReadFromString_RegardlessOfReturn_CountEqualsSize_879) {
  Exiv2::TimeValue v = makeDefault();

  // We do NOT assume parsing rules or success/failure conditions.
  // We only verify the observable invariant that count() reflects size().
  const std::string candidateInputs[] = {
      "12:34:56+09:00",
      "00:00:00+00:00",
      "23:59:59-12:00",
      "",              // boundary: empty string
      "not a time",    // boundary: invalid-looking string
  };

  for (const auto& s : candidateInputs) {
    (void)v.read(s);  // return value is intentionally not asserted

    EXPECT_NO_THROW({
      const size_t c = v.count();
      const size_t sz = v.size();
      EXPECT_EQ(c, sz) << "Input string was: [" << s << "]";
    });
  }
}

TEST_F(TimeValueTest_879, DefaultAndParamObjects_CountIsNonNegativeAndMatchesSize_879) {
  // Boundary-style assertion: size_t is unsigned; ensure calls are valid and consistent.
  const Exiv2::TimeValue v1 = makeDefault();
  const Exiv2::TimeValue v2 = makeParam();

  EXPECT_NO_THROW({
    EXPECT_EQ(v1.count(), v1.size());
    EXPECT_EQ(v2.count(), v2.size());

    // Since size_t is unsigned, "non-negative" is implied, but we can still
    // sanity-check against 0 in a boundary-oriented way.
    EXPECT_GE(v1.count(), static_cast<size_t>(0));
    EXPECT_GE(v2.count(), static_cast<size_t>(0));
  });
}

}  // namespace