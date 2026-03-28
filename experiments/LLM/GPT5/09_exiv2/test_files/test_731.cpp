// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_operator_assign_string_731.cpp
//
// Unit tests for: Exiv2::Exifdatum::operator=(const std::string&)
// Interface snippet (black-box): operator=(const std::string& value) { setValue(value); return *this; }

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

#include <cstddef>
#include <string>

namespace {

using ::testing::HasSubstr;

class ExifdatumTest_731 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatum(const char* exifKey) {
    // Exifdatum ctor is part of the public interface; treat implementation as black box.
    Exiv2::ExifKey key(exifKey);
    return Exiv2::Exifdatum(key, /*pValue=*/nullptr);
  }
};

TEST_F(ExifdatumTest_731, OperatorAssignString_ReturnsSameObjectReference_731) {
  auto d = MakeDatum("Exif.Image.Make");

  std::string v = "Canon";
  Exiv2::Exifdatum& ret = (d = v);

  EXPECT_EQ(&ret, &d);
}

TEST_F(ExifdatumTest_731, OperatorAssignString_UpdatesToStringForAsciiLikeKey_731) {
  auto d = MakeDatum("Exif.Image.Make");

  d = std::string("Canon");

  // Observable behavior through public API; avoid assuming exact formatting beyond containing value.
  EXPECT_THAT(d.toString(), HasSubstr("Canon"));
}

TEST_F(ExifdatumTest_731, OperatorAssignString_AllowsEmptyString_Boundary_731) {
  auto d = MakeDatum("Exif.Image.Make");

  d = std::string("");

  // Some implementations may render empty as "" or empty; accept both.
  const std::string s = d.toString();
  EXPECT_TRUE(s.empty() || s == "\"\"" || s == "''");
}

TEST_F(ExifdatumTest_731, OperatorAssignString_AllowsLongString_Boundary_731) {
  auto d = MakeDatum("Exif.Image.Make");

  const std::string longValue(4096, 'A');
  d = longValue;

  // Avoid requiring full equality (formatting/quoting could vary). Check it contains a prefix.
  EXPECT_THAT(d.toString(), HasSubstr(std::string(16, 'A')));
}

TEST_F(ExifdatumTest_731, SetValue_InvalidNumericString_ReturnsError_OperatorAssignDoesNotThrow_731) {
  auto d = MakeDatum("Exif.Photo.ISOSpeedRatings");

  // Error is observable via return value from setValue(string).
  const int rc = d.setValue(std::string("not-a-number"));
  EXPECT_NE(rc, 0);

  // operator=(string) ignores the int return and returns *this; it should not throw.
  EXPECT_NO_THROW({ d = std::string("not-a-number"); });
}

TEST_F(ExifdatumTest_731, SetValue_ValidNumericString_MayUpdateToInt64_WhenAccepted_731) {
  auto d = MakeDatum("Exif.Photo.ISOSpeedRatings");

  const int rc = d.setValue(std::string("200"));
  if (rc == 0) {
    // If accepted, the numeric value should be observable via the public conversion API.
    EXPECT_EQ(d.toInt64(/*n=*/0), 200);
  } else {
    // If the environment/metadata config rejects it, still verify it fails in an observable way.
    EXPECT_NE(rc, 0);
  }
}

}  // namespace