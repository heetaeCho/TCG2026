// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_printSi0x0018_964.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include path if your test target already provides them differently)
#include "canonmn_int.hpp"   // for Exiv2::Internal::CanonMakerNote (or canonmn_int.cpp's corresponding header)
#include "value.hpp"         // for Exiv2::Value / Exiv2::ValueType / Exiv2::Value::create
#include "exif.hpp"          // for Exiv2::ExifData (only used as pointer)

namespace {

// Helper: build a Value holding exactly one signed integer, without assuming internal details.
static Exiv2::Value::UniquePtr MakeIntValue(int64_t v) {
  // Prefer an explicit signed integer value type. If your build uses a different type name,
  // update here (tests should still treat CanonMakerNote as black box).
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::signedLongLong);  // int64-like
  // Use the public API to set the value.
  val->read(std::to_string(v));
  return val;
}

}  // namespace

class CanonMakerNoteTest_964 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote sut_;
};

// Normal operation: positive number divides by 10 and prints as integer division result.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_PositiveDividesBy10_964) {
  auto v = MakeIntValue(123);
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_EQ(os.str(), "12");  // 123 / 10 -> 12 (integer division)
}

// Boundary: exact multiple of 10.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ExactMultipleOf10_964) {
  auto v = MakeIntValue(120);
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_EQ(os.str(), "12");
}

// Boundary: zero.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_Zero_964) {
  auto v = MakeIntValue(0);
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0");
}

// Boundary/behavior: negative values should also be divided by 10 using integer division semantics.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NegativeDividesBy10_964) {
  auto v = MakeIntValue(-123);
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  // C++ integer division truncates toward zero: -123 / 10 == -12
  EXPECT_EQ(os.str(), "-12");
}

// Boundary: smallest/largest int64 should not crash and should produce some output.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_Int64Min_NoCrashAndOutput_964) {
  auto v = MakeIntValue((std::numeric_limits<int64_t>::min)());
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_Int64Max_NoCrashAndOutput_964) {
  auto v = MakeIntValue((std::numeric_limits<int64_t>::max)());
  std::ostringstream os;

  sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_FALSE(os.str().empty());
}

// External interaction: returns the same stream reference (allows chaining).
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ReturnsSameStream_964) {
  auto v = MakeIntValue(55);
  std::ostringstream os;

  std::ostream& ret = sut_.printSi0x0018(os, *v, nullptr);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
  EXPECT_EQ(os.str(), "5");
}

// External interaction: does not require ExifData (null pointer accepted).
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_AllowsNullExifData_964) {
  auto v = MakeIntValue(10);
  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.printSi0x0018(os, *v, nullptr);
  });
  EXPECT_EQ(os.str(), "1");
}

// Exceptional/error-like: if the stream is in a bad state, function should not crash;
// output may not be written, but call should complete.
TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_StreamBadbit_DoesNotThrow_964) {
  auto v = MakeIntValue(999);
  std::ostringstream os;
  os.setstate(std::ios::badbit);

  EXPECT_NO_THROW({
    sut_.printSi0x0018(os, *v, nullptr);
  });
}