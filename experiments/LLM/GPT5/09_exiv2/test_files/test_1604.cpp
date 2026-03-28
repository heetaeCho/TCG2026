// File: test_sonymn_printColorTemperature_1604.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// SonyMakerNote is an internal component; in the Exiv2 codebase this header is typically available.
#include "sonymn_int.hpp"

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;

static std::string StreamValueToString(const Exiv2::Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

static Exiv2::Value::UniquePtr MakeValue(Exiv2::TypeId type, const std::string& text) {
  auto v = Exiv2::Value::create(type);
  if (!text.empty()) {
    // read() is public API for populating Value from textual representation.
    v->read(text);
  }
  return v;
}

class SonyMakerNotePrintColorTemperatureTest_1604 : public ::testing::Test {
 protected:
  SonyMakerNote mn_;
};

}  // namespace

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, ReturnsParenWrappedValueWhenCountIsNotOne_1604) {
  auto v = MakeValue(Exiv2::unsignedLong, "1 2");  // count() != 1
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = StreamValueToString(*v);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, ReturnsParenWrappedValueWhenTypeIsNotUnsignedLong_1604) {
  auto v = MakeValue(Exiv2::unsignedShort, "0");  // typeId() != unsignedLong
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = StreamValueToString(*v);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, PrintsAutoWhenValueIsZero_1604) {
  auto v = MakeValue(Exiv2::unsignedLong, "0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  // Observable behavior: the function writes a localized "Auto" token.
  EXPECT_EQ(os.str(), "Auto");
}

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, PrintsNAWhenValueIsAllOnes_1604) {
  // 0xffffffff as unsigned long
  auto v = MakeValue(Exiv2::unsignedLong, "4294967295");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  // Observable behavior: the function writes a localized "n/a" token.
  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, PrintsKelvinSuffixForTypicalTemperature_1604) {
  auto v = MakeValue(Exiv2::unsignedLong, "5500");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  EXPECT_EQ(os.str(), "5500 K");
}

TEST_F(SonyMakerNotePrintColorTemperatureTest_1604, BoundaryValueOnePrintsOneKelvin_1604) {
  auto v = MakeValue(Exiv2::unsignedLong, "1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printColorTemperature(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1 K");
}