// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_operator_assign_int16_t_735.cpp

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>

#include <cstdint>
#include <limits>
#include <string>

namespace {

class ExifdatumOperatorAssignInt16Test_735 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum& MakeDatum(Exiv2::ExifData& exif) {
    // Use ExifData::operator[] to obtain a mutable Exifdatum without relying on Exifdatum constructors.
    // The specific key should not matter for testing operator=(int16_t) as a black box.
    return exif["Exif.Image.ImageWidth"];
  }
};

TEST_F(ExifdatumOperatorAssignInt16Test_735, ReturnsSelfReference_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  const int16_t v = 42;
  Exiv2::Exifdatum& ret = (datum = v);

  EXPECT_EQ(&ret, &datum);
}

TEST_F(ExifdatumOperatorAssignInt16Test_735, AssignPositiveValueUpdatesObservableConversions_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  const int16_t v = 1234;
  datum = v;

  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(datum.count(), 1u);

  const std::string s = datum.toString();
  EXPECT_NE(s.find("1234"), std::string::npos);
}

TEST_F(ExifdatumOperatorAssignInt16Test_735, AssignNegativeValueUpdatesObservableConversions_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  const int16_t v = static_cast<int16_t>(-1234);
  datum = v;

  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(v));

  const std::string s = datum.toString();
  // Be tolerant of formatting differences (e.g., spaces); just require the minus sign and digits.
  EXPECT_NE(s.find("-1234"), std::string::npos);
}

TEST_F(ExifdatumOperatorAssignInt16Test_735, AssignMinAndMaxInt16_Boundary_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  const int16_t minv = std::numeric_limits<int16_t>::min();
  const int16_t maxv = std::numeric_limits<int16_t>::max();

  datum = minv;
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(minv));

  datum = maxv;
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(maxv));
}

TEST_F(ExifdatumOperatorAssignInt16Test_735, ReassignOverwritesPreviousValue_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  datum = static_cast<int16_t>(10);
  EXPECT_EQ(datum.toInt64(0), 10);

  datum = static_cast<int16_t>(-20);
  EXPECT_EQ(datum.toInt64(0), -20);

  EXPECT_EQ(datum.count(), 1u);
}

TEST_F(ExifdatumOperatorAssignInt16Test_735, OutOfRangeIndexIsObservableError_735) {
  Exiv2::ExifData exif;
  Exiv2::Exifdatum& datum = MakeDatum(exif);

  datum = static_cast<int16_t>(7);
  ASSERT_EQ(datum.count(), 1u);

  // Exceptional / error case observable through the public interface:
  // querying an index beyond the stored count should throw.
  EXPECT_THROW((void)datum.toInt64(1), Exiv2::Error);
}

}  // namespace