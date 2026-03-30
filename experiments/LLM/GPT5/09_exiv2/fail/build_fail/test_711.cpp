// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_panasonicmn_int_print0x0036_test_711.cpp
//
// Unit tests for:
//   Exiv2::Internal::PanasonicMakerNote::print0x0036(std::ostream&, const Value&, const ExifData*)
//
// Constraints honored:
// - Treat implementation as a black box (no internal-state access, no inferred logic beyond observable I/O).
// - Verify observable behavior via produced stream text.
// - Use Exiv2 public types only (Value/ExifData).
//
// NOTE: This test assumes Exiv2 headers are available in the include path.

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::Value::UniquePtr;

class PanasonicMakerNoteTest_711 : public ::testing::Test {
 protected:
  // Helper: create a Value holding a single unsigned short (common for maker note tags).
  static UniquePtr MakeUShortValue(uint16_t v) {
    auto val = Value::create(Exiv2::unsignedShort);
    ASSERT_NE(val.get(), nullptr);
    ASSERT_NO_THROW(val->read(std::to_string(v)));
    return val;
  }

  // Helper: create a Value holding a single signed long (fallback if needed).
  static UniquePtr MakeLongValue(int64_t v) {
    auto val = Value::create(Exiv2::signedLong);
    ASSERT_NE(val.get(), nullptr);
    ASSERT_NO_THROW(val->read(std::to_string(v)));
    return val;
  }
};

TEST_F(PanasonicMakerNoteTest_711, PrintsNotSetWhenValueIs65535_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  // Prefer a type that can represent 65535 naturally.
  auto value = MakeUShortValue(65535);

  // Act
  std::ostream& ret = mn.print0x0036(os, *value, &exif);

  // Assert: returns same stream and prints "not set"
  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), std::string("not set"));
}

TEST_F(PanasonicMakerNoteTest_711, PrintsNumericValueWhenNot65535_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  auto value = MakeUShortValue(123);

  // Act
  std::ostream& ret = mn.print0x0036(os, *value, &exif);

  // Assert
  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), std::string("123"));
}

TEST_F(PanasonicMakerNoteTest_711, BoundaryZeroPrintsAsZero_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  auto value = MakeUShortValue(0);

  // Act
  mn.print0x0036(os, *value, &exif);

  // Assert
  EXPECT_EQ(os.str(), std::string("0"));
}

TEST_F(PanasonicMakerNoteTest_711, Boundary65534PrintsAsNumber_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  auto value = MakeUShortValue(65534);

  // Act
  mn.print0x0036(os, *value, &exif);

  // Assert
  EXPECT_EQ(os.str(), std::string("65534"));
}

TEST_F(PanasonicMakerNoteTest_711, ExifDataPointerMayBeNull_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  std::ostringstream os;

  auto value = MakeUShortValue(321);

  // Act / Assert: should not crash; output should still be the value.
  std::ostream& ret = mn.print0x0036(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), std::string("321"));
}

TEST_F(PanasonicMakerNoteTest_711, WorksWithDifferentValueTypeStillPrintable_711) {
  // Arrange
  // This is an error/robustness-style test: pass a different numeric Value type and ensure
  // behavior remains observable (no throw, produces something sensible).
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  auto value = MakeLongValue(42);

  // Act / Assert
  EXPECT_NO_THROW({
    std::ostream& ret = mn.print0x0036(os, *value, &exif);
    EXPECT_EQ(&ret, &os);
  });
  EXPECT_EQ(os.str(), std::string("42"));
}

TEST_F(PanasonicMakerNoteTest_711, LongTypeValue65535StillPrintsNotSet_711) {
  // Arrange
  Exiv2::Internal::PanasonicMakerNote mn;
  ExifData exif;
  std::ostringstream os;

  auto value = MakeLongValue(65535);

  // Act
  mn.print0x0036(os, *value, &exif);

  // Assert
  EXPECT_EQ(os.str(), std::string("not set"));
}

}  // namespace