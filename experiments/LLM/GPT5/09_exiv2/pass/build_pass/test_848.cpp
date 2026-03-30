// TEST_ID: 848
// File: test_xmp_array_value_to_int64_848.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>

#include "exiv2/value.hpp"

namespace {

class XmpArrayValueTest_848 : public ::testing::Test {
protected:
  static Exiv2::XmpArrayValue makeValue() {
    // XmpArrayValue is an XmpValue; in Exiv2 this is typically used for xmpSeq/xmpBag/xmpAlt.
    // We only rely on public behavior; the specific array TypeId is just to satisfy construction.
    return Exiv2::XmpArrayValue(Exiv2::xmpSeq);
  }
};

TEST_F(XmpArrayValueTest_848, DefaultIsEmpty_ToInt64OutOfRangeThrows_848) {
  auto v = makeValue();

  EXPECT_EQ(v.count(), 0u);

  // value_.at(n) is used internally, so out-of-range should be observable as an exception.
  EXPECT_THROW((void)v.toInt64(0), std::out_of_range);
  EXPECT_THROW((void)v.toInt64(1), std::out_of_range);
}

TEST_F(XmpArrayValueTest_848, ReadSingleNumericElement_ToInt64ReturnsValue_848) {
  auto v = makeValue();

  const int rc = v.read(std::string("123"));
  EXPECT_EQ(rc, 0);

  ASSERT_GE(v.count(), 1u);

  // Observable conversion result.
  EXPECT_EQ(v.toInt64(0), static_cast<int64_t>(123));

  // For a valid numeric conversion, ok() should remain true (observable via public API).
  EXPECT_TRUE(v.ok());
}

TEST_F(XmpArrayValueTest_848, ReadNonNumericElement_ToInt64MarksNotOk_848) {
  auto v = makeValue();

  const int rc = v.read(std::string("not-a-number"));
  EXPECT_EQ(rc, 0);

  ASSERT_GE(v.count(), 1u);

  // We do not assume what numeric value is returned on failure (black-box),
  // but failure should be observable via ok().
  (void)v.toInt64(0);
  EXPECT_FALSE(v.ok());
}

}  // namespace