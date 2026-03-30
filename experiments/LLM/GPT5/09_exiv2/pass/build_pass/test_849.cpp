// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmparrayvalue_toUint32_849.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

#include "exiv2/value.hpp"

namespace {

class XmpArrayValueTest_849 : public ::testing::Test {
 protected:
  static Exiv2::XmpArrayValue MakeUut() {
    // XmpArrayValue is an XMP array-type Value; xmpSeq is a commonly used array TypeId in Exiv2.
    return Exiv2::XmpArrayValue(Exiv2::xmpSeq);
  }
};

TEST_F(XmpArrayValueTest_849, ReadSingleNumber_ToUint32ReturnsValue_849) {
  auto uut = MakeUut();

  ASSERT_NO_THROW(uut.read(std::string("42")));
  EXPECT_GE(uut.count(), 1u);

  EXPECT_NO_THROW({
    const uint32_t v = uut.toUint32(0);
    EXPECT_EQ(v, 42u);
  });

  // If parsing succeeded, ok() should remain true.
  EXPECT_TRUE(uut.ok());
}

TEST_F(XmpArrayValueTest_849, ReadMaxUint32_ToUint32ReturnsMax_849) {
  auto uut = MakeUut();

  const std::string s = "4294967295";  // UINT32_MAX
  ASSERT_NO_THROW(uut.read(s));
  EXPECT_GE(uut.count(), 1u);

  EXPECT_NO_THROW({
    const uint32_t v = uut.toUint32(0);
    EXPECT_EQ(v, std::numeric_limits<uint32_t>::max());
  });

  EXPECT_TRUE(uut.ok());
}

TEST_F(XmpArrayValueTest_849, ToUint32_IndexEqualToCount_ThrowsOutOfRange_849) {
  auto uut = MakeUut();

  ASSERT_NO_THROW(uut.read(std::string("1")));
  ASSERT_GE(uut.count(), 1u);

  const size_t out_of_range_index = uut.count();
  EXPECT_THROW((void)uut.toUint32(out_of_range_index), std::out_of_range);
}

TEST_F(XmpArrayValueTest_849, ToUint32_NonNumericInput_SetsOkFalseOrThrows_849) {
  auto uut = MakeUut();

  ASSERT_NO_THROW(uut.read(std::string("not-a-number")));
  ASSERT_GE(uut.count(), 1u);

  try {
    (void)uut.toUint32(0);
    // If no exception, the observable error signal should be ok() becoming false.
    EXPECT_FALSE(uut.ok());
  } catch (...) {
    SUCCEED();  // Exception is also an observable error path.
  }
}

TEST_F(XmpArrayValueTest_849, ToUint32_NegativeInput_SetsOkFalseOrThrows_849) {
  auto uut = MakeUut();

  ASSERT_NO_THROW(uut.read(std::string("-1")));
  ASSERT_GE(uut.count(), 1u);

  try {
    (void)uut.toUint32(0);
    EXPECT_FALSE(uut.ok());
  } catch (...) {
    SUCCEED();
  }
}

TEST_F(XmpArrayValueTest_849, ToUint32_OverflowInput_SetsOkFalseOrThrows_849) {
  auto uut = MakeUut();

  // One more than UINT32_MAX.
  ASSERT_NO_THROW(uut.read(std::string("4294967296")));
  ASSERT_GE(uut.count(), 1u);

  try {
    (void)uut.toUint32(0);
    EXPECT_FALSE(uut.ok());
  } catch (...) {
    SUCCEED();
  }
}

}  // namespace