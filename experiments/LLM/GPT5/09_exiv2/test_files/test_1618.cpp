// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_printSonyMisc2bFocusPosition2_1618.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"

#include <sstream>
#include <string>
#include <memory>

namespace {

class SonyMakerNoteTest_1618 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeValue(Exiv2::TypeId type, const std::string& text) {
    auto v = Exiv2::Value::create(type);
    EXPECT_TRUE(!!v);
    // Treat Value as a black box: only use the public read interface.
    v->read(text);
    return v;
  }

  static void setModel(Exiv2::ExifData& exif, const std::string& model) {
    auto mv = makeValue(Exiv2::asciiString, model);
    Exiv2::ExifKey key("Exif.Image.Model");
    exif.add(key, mv.get()); // ExifData::add clones/owns via public API
  }

  static std::string call(const Exiv2::Value& value, const Exiv2::ExifData* md) {
    Exiv2::Internal::SonyMakerNote mn;
    std::ostringstream oss;
    mn.printSonyMisc2bFocusPosition2(oss, value, md);
    return oss.str();
  }
};

TEST_F(SonyMakerNoteTest_1618, ReturnsParenthesizedValueWhenMetadataIsNull_1618) {
  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string out = call(*v, nullptr);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteTest_1618, ReturnsParenthesizedValueWhenCountIsNotOneEvenWithMetadata_1618) {
  Exiv2::ExifData exif;
  setModel(exif, "DSC-RX100"); // any model; behavior should still be parenthesized if count != 1

  auto v = makeValue(Exiv2::unsignedShort, "1 2"); // count expected to be != 1 via public read API
  const std::string out = call(*v, &exif);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteTest_1618, ReturnsParenthesizedValueWhenModelCannotBeObtained_1618) {
  Exiv2::ExifData exif; // no Exif.Image.Model present

  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string out = call(*v, &exif);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteTest_1618, ReturnsNaWhenModelContainsSLTPrefix_1618) {
  Exiv2::ExifData exif;
  setModel(exif, "SLT-A99V");

  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string out = call(*v, &exif);

  EXPECT_EQ(out, "n/a");
}

TEST_F(SonyMakerNoteTest_1618, ReturnsNaWhenModelContainsHVSubstring_1618) {
  Exiv2::ExifData exif;
  setModel(exif, "HVR-Z7"); // contains "HV"

  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string out = call(*v, &exif);

  EXPECT_EQ(out, "n/a");
}

TEST_F(SonyMakerNoteTest_1618, ReturnsNaWhenModelContainsILCAPrefix_1618) {
  Exiv2::ExifData exif;
  setModel(exif, "ILCA-7M3");

  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string out = call(*v, &exif);

  EXPECT_EQ(out, "n/a");
}

TEST_F(SonyMakerNoteTest_1618, ReturnsRawValueWhenModelDoesNotMatchSpecialCases_1618) {
  Exiv2::ExifData exif;
  setModel(exif, "DSC-RX100");

  auto v = makeValue(Exiv2::unsignedShort, "1");
  const std::string expected = [&] {
    std::ostringstream oss;
    oss << *v;
    return oss.str();
  }();

  const std::string out = call(*v, &exif);

  // For normal models, function should stream the value without parentheses.
  EXPECT_EQ(out, expected);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.front(), '(');
  EXPECT_NE(out.back(), ')');
}

} // namespace