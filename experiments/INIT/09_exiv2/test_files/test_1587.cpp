// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_getfocusmode2_1587.cpp
//
// Unit tests for Exiv2::Internal::getFocusMode2 (from ./TestProjects/exiv2/src/sonymn_int.cpp)
//
// NOTE: The function under test has internal linkage (static in a .cpp). To test it as a black box
// via its real implementation, we include the .cpp into this test translation unit.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <string>

// Include the production .cpp so the internal-linkage function is in this TU.
#include "./TestProjects/exiv2/src/sonymn_int.cpp"

namespace {

class GetFocusMode2Test_1587 : public ::testing::Test {
 protected:
  // Adds an Exifdatum for `keyStr` with a Value of `typeId`, optionally reading `valueText`.
  // This only uses public Exiv2 interfaces (ExifKey, Value factory, Exifdatum, ExifData::add).
  static void addDatum(Exiv2::ExifData& exif, const std::string& keyStr, Exiv2::TypeId typeId,
                       const std::string* valueTextOrNull) {
    Exiv2::ExifKey key(keyStr);
    Exiv2::Value::UniquePtr v(Exiv2::Value::create(typeId));
    ASSERT_TRUE(static_cast<bool>(v)) << "Value::create returned null for typeId=" << typeId;

    if (valueTextOrNull != nullptr) {
      // Use Value::read to set content; this is public API.
      ASSERT_EQ(0, v->read(*valueTextOrNull)) << "Value::read failed for key=" << keyStr;
    }

    Exiv2::Exifdatum datum(key, v.get());
    exif.add(datum);
  }
};

TEST_F(GetFocusMode2Test_1587, ReturnsFalseAndZeroWhenNoKeysPresent_1587) {
  Exiv2::ExifData exif;
  uint32_t val = 1234;

  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(0u, val);
}

TEST_F(GetFocusMode2Test_1587, ReturnsTrueAndReadsValueFromSony1WhenPresent_1587) {
  Exiv2::ExifData exif;

  const std::string vText = "7";
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony1.FocusMode2", Exiv2::unsignedByte, &vText));

  uint32_t val = 0;
  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(7u, val);
}

TEST_F(GetFocusMode2Test_1587, FallsBackToSony2WhenSony1Missing_1587) {
  Exiv2::ExifData exif;

  const std::string vText = "3";
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony2.FocusMode2", Exiv2::unsignedByte, &vText));

  uint32_t val = 0;
  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(3u, val);
}

TEST_F(GetFocusMode2Test_1587, ReturnsFalseWhenSony1PresentButEmptyValue_1587) {
  Exiv2::ExifData exif;

  // Create an unsignedByte value but do not read any content -> size() expected to be 0.
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony1.FocusMode2", Exiv2::unsignedByte, /*valueTextOrNull=*/nullptr));

  uint32_t val = 999;
  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(0u, val);
}

TEST_F(GetFocusMode2Test_1587, IgnoresSony1WhenTypeIsNotUnsignedByteAndUsesSony2_1587) {
  Exiv2::ExifData exif;

  // Sony1 exists but wrong type -> should not be accepted.
  const std::string sony1Text = "7";
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony1.FocusMode2", Exiv2::asciiString, &sony1Text));

  // Sony2 is valid and should be used.
  const std::string sony2Text = "9";
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony2.FocusMode2", Exiv2::unsignedByte, &sony2Text));

  uint32_t val = 0;
  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_TRUE(ok);
  EXPECT_EQ(9u, val);
}

TEST_F(GetFocusMode2Test_1587, ReturnsFalseWhenBothKeysPresentButWrongTypes_1587) {
  Exiv2::ExifData exif;

  const std::string t1 = "1";
  const std::string t2 = "2";
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony1.FocusMode2", Exiv2::asciiString, &t1));
  ASSERT_NO_FATAL_FAILURE(
      addDatum(exif, "Exif.Sony2.FocusMode2", Exiv2::asciiString, &t2));

  uint32_t val = 42;
  const bool ok = Exiv2::Internal::getFocusMode2(&exif, val);

  EXPECT_FALSE(ok);
  EXPECT_EQ(0u, val);
}

}  // namespace