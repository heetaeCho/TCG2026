// ============================================================================
//  Unit tests for Exiv2::XmpArrayValue (value.cpp / value.hpp)
//  TEST_ID: 847
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

class XmpArrayValueTest_847 : public ::testing::Test {
 protected:
  // Avoid depending on specific TypeId enumerators (not guaranteed by the prompt).
  static Exiv2::TypeId AnyTypeId() { return static_cast<Exiv2::TypeId>(0); }
};

TEST_F(XmpArrayValueTest_847, ToStringThrowsOutOfRangeWhenEmpty_847) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  EXPECT_THROW((void)v.toString(0), std::out_of_range);
}

TEST_F(XmpArrayValueTest_847, ToStringThrowsOutOfRangeForMaxIndex_847) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  const size_t huge = (std::numeric_limits<size_t>::max)();
  EXPECT_THROW((void)v.toString(huge), std::out_of_range);
}

TEST_F(XmpArrayValueTest_847, ToStringSetsOkTrueEvenWhenThrowing_847) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  // Ensure an out_of_range is observable through the interface, and also that
  // ok() is true after the call (based on the provided partial implementation).
  try {
    (void)v.toString(0);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range&) {
    // expected
  }

  EXPECT_TRUE(v.ok());
}

TEST_F(XmpArrayValueTest_847, ReadThenToStringIndex0IfAvailableOtherwiseSkip_847) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  // We do not assume the parsing format of read(). We only attempt a simple read,
  // then use count() to decide whether index 0 is a valid boundary.
  (void)v.read(std::string("one"));

  const size_t c = v.count();
  if (c == 0) {
    GTEST_SKIP() << "read(\"one\") produced an empty array; cannot observe normal toString(0).";
  }

  EXPECT_NO_THROW((void)v.toString(0));
  EXPECT_TRUE(v.ok());
}

TEST_F(XmpArrayValueTest_847, WriteToOstreamDoesNotCrash_847) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  // No assumptions about formatting; only that write is callable and returns an ostream reference.
  std::ostringstream os;
  EXPECT_NO_THROW({
    const std::ostream& ref = v.write(os);
    (void)ref;
  });
}

}  // namespace