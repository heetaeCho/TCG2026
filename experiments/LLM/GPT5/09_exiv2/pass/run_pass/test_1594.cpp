// File: test_sonymn_int_printAFAreaModeSetting_1594.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

class SonyAFAreaModeSettingTest_1594 : public ::testing::Test {
 protected:
  static Value::UniquePtr makeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    // Treat as black box: rely only on public interface.
    // If parsing fails, the tests that require "count()==1" may fail, which is correct signal.
    (void)v->read(text);
    return v;
  }

  static ExifData makeMetadataWithModel(const std::string& model) {
    ExifData md;
    // Exiv2 commonly uses Exif.Image.Model for camera model.
    // Use only public ExifData interface; actual Exiv2 provides operator[] assignment helpers.
    md["Exif.Image.Model"] = model;
    return md;
  }

  static std::string print(const Value& value, const ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::SonyMakerNote mn;
    mn.printAFAreaModeSetting(os, value, md);
    return os.str();
  }
};

TEST_F(SonyAFAreaModeSettingTest_1594, ReturnsParenWrappedWhenMetadataNull_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "0");
  const std::string out = print(*v, nullptr);

  // Implementation explicitly: return os << "(" << value << ")"
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyAFAreaModeSettingTest_1594, ReturnsParenWrappedWhenTypeIsNotUnsignedByte_1594) {
  auto v = makeValue(Exiv2::unsignedShort, "0");
  ExifData md = makeMetadataWithModel("ILCE-7M3");
  const std::string out = print(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyAFAreaModeSettingTest_1594, ReturnsParenWrappedWhenModelCannotBeObtained_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "0");
  ExifData md;  // no model tag
  const std::string out = print(*v, &md);

  // If getModel(...) fails, implementation returns "(" << value << ")"
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyAFAreaModeSettingTest_1594, UsesSet1ForSLTPrefix_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "0");  // set1: 0 -> "Wide"
  ExifData md = makeMetadataWithModel("SLT-A99");
  const std::string out = print(*v, &md);

  EXPECT_NE(out.find("Wide"), std::string::npos);
}

TEST_F(SonyAFAreaModeSettingTest_1594, UsesSet1ForHVPrefix_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "4");  // set1: 4 -> "Local"
  ExifData md = makeMetadataWithModel("HV-123");
  const std::string out = print(*v, &md);

  EXPECT_NE(out.find("Local"), std::string::npos);
}

TEST_F(SonyAFAreaModeSettingTest_1594, UsesSet2ForILCEPrefix_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "3");  // set2: 3 -> "Flexible Spot"
  ExifData md = makeMetadataWithModel("ILCE-7M3");
  const std::string out = print(*v, &md);

  EXPECT_NE(out.find("Flexible"), std::string::npos);
}

TEST_F(SonyAFAreaModeSettingTest_1594, UsesSet2ForRX100M7ExactModel_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "12");  // set2: 12 -> "Expanded flexible spot"
  ExifData md = makeMetadataWithModel("DSC-RX100M7");
  const std::string out = print(*v, &md);

  EXPECT_NE(out.find("Expanded"), std::string::npos);
}

TEST_F(SonyAFAreaModeSettingTest_1594, UsesSet3ForILCAPrefix_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "9");  // set3: 9 -> "Center"
  ExifData md = makeMetadataWithModel("ILCA-77M2");
  const std::string out = print(*v, &md);

  EXPECT_NE(out.find("Center"), std::string::npos);
}

TEST_F(SonyAFAreaModeSettingTest_1594, ReturnsNaForUnknownModelPrefix_1594) {
  auto v = makeValue(Exiv2::unsignedByte, "0");
  ExifData md = makeMetadataWithModel("SOME-UNKNOWN-MODEL");
  const std::string out = print(*v, &md);

  // Implementation ends with: return os << _("n/a");
  EXPECT_NE(out.find("n/a"), std::string::npos);
}

}  // namespace