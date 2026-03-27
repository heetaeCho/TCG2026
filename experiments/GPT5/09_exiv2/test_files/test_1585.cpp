// File: test_sonymn_int_getAFAreaModeSetting_1585.cpp
// Unit tests for Exiv2::Internal::getAFAreaModeSetting (from sonymn_int.cpp)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <exiv2/i18n.h>

#include <cstdint>
#include <memory>
#include <string>

// Include the implementation file to access the TU-local static function.
// This keeps the function black-box while still allowing observable-behavior testing.
#include "sonymn_int.cpp"

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::TypeId;

static void AddUnsignedByte(ExifData& ed, const std::string& key, uint32_t v) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
  ASSERT_NE(val.get(), nullptr);
  // Exiv2 values commonly accept numeric strings via read().
  ASSERT_EQ(0, val->read(std::to_string(v)));
  ed.add(ExifKey(key), val.get());
}

static void AddUnsignedShort(ExifData& ed, const std::string& key, uint32_t v) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(val.get(), nullptr);
  ASSERT_EQ(0, val->read(std::to_string(v)));
  ed.add(ExifKey(key), val.get());
}

static void AddEmptyUnsignedByte(ExifData& ed, const std::string& key) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
  ASSERT_NE(val.get(), nullptr);
  // Intentionally do not set/read any data => expect size() == 0 in typical Exiv2 behavior.
  ed.add(ExifKey(key), val.get());
}

class GetAFAreaModeSettingTest_1585 : public ::testing::Test {
 protected:
  static constexpr const char* kSony1 = "Exif.Sony1.AFAreaModeSetting";
  static constexpr const char* kSony2 = "Exif.Sony2.AFAreaModeSetting";
};

TEST_F(GetAFAreaModeSettingTest_1585, MissingKeys_ReturnsFalseAndZerosVal_1585) {
  ExifData md;
  uint32_t out = 1234;

  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(0u, out);
}

TEST_F(GetAFAreaModeSettingTest_1585, Sony1UnsignedBytePresent_ReturnsTrueAndSetsVal_1585) {
  ExifData md;
  AddUnsignedByte(md, kSony1, 7);

  uint32_t out = 0;
  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(7u, out);
}

TEST_F(GetAFAreaModeSettingTest_1585, Sony2UsedWhenSony1Missing_ReturnsTrueAndSetsVal_1585) {
  ExifData md;
  AddUnsignedByte(md, kSony2, 9);

  uint32_t out = 0;
  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(9u, out);
}

TEST_F(GetAFAreaModeSettingTest_1585, Sony1TakesPrecedenceOverSony2_WhenBothValid_1585) {
  ExifData md;
  AddUnsignedByte(md, kSony1, 1);
  AddUnsignedByte(md, kSony2, 2);

  uint32_t out = 0;
  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(1u, out);
}

TEST_F(GetAFAreaModeSettingTest_1585, Sony1WrongType_FallsBackToSony2IfValid_1585) {
  ExifData md;
  // Sony1 exists but is not unsignedByte => should be ignored.
  AddUnsignedShort(md, kSony1, 777);
  AddUnsignedByte(md, kSony2, 3);

  uint32_t out = 0;
  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(3u, out);
}

TEST_F(GetAFAreaModeSettingTest_1585, EmptyUnsignedByteValue_IsTreatedAsNotPresent_ReturnsFalse_1585) {
  ExifData md;
  AddEmptyUnsignedByte(md, kSony1);

  uint32_t out = 55;
  const bool ok = Exiv2::Internal::getAFAreaModeSetting(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(0u, out);
}

}  // namespace