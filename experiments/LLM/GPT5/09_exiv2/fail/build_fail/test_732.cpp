// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_uint16_assign_732.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <exiv2/exif.hpp>

namespace {

class ExifdatumUint16AssignTest_732 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeOrientationDatum() {
    // "Exif.Image.Orientation" is commonly represented as an unsigned short (uint16_t).
    Exiv2::ExifKey key("Exif.Image.Orientation");
    return Exiv2::Exifdatum(key, /*pValue=*/nullptr);
  }
};

TEST_F(ExifdatumUint16AssignTest_732, ReturnsSelfReference_732) {
  auto datum = MakeOrientationDatum();

  Exiv2::Exifdatum& ref = (datum = static_cast<uint16_t>(1));
  EXPECT_EQ(&ref, &datum);
}

TEST_F(ExifdatumUint16AssignTest_732, SetsValueForTypicalOrientation_732) {
  auto datum = MakeOrientationDatum();

  datum = static_cast<uint16_t>(1);

  // Observable behavior through the public interface.
  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 1);
}

TEST_F(ExifdatumUint16AssignTest_732, SetsValueBoundaryMinMax_732) {
  auto datum = MakeOrientationDatum();

  datum = static_cast<uint16_t>(0);
  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 0);

  datum = std::numeric_limits<uint16_t>::max();
  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(std::numeric_limits<uint16_t>::max()));
}

TEST_F(ExifdatumUint16AssignTest_732, SupportsChaining_732) {
  auto datum = MakeOrientationDatum();

  (datum = static_cast<uint16_t>(3)) = static_cast<uint16_t>(4);

  EXPECT_EQ(datum.count(), 1u);
  EXPECT_EQ(datum.toInt64(0), 4);
}

}  // namespace