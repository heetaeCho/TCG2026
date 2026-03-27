// TEST_ID 1598
// File: test_sonymn_int_printaftracking_1598.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

using ::testing::HasSubstr;

class SonyMnPrintAFTrackingTest_1598 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeValue(Exiv2::TypeId type, const std::string& text) {
    auto v = Exiv2::Value::create(type);
    EXPECT_NE(v.get(), nullptr);
    // Black-box: rely only on the public Value interface.
    v->read(text);
    return v;
  }

  static void SetModel(Exiv2::ExifData& exif, const std::string& model) {
    // Black-box: use only public ExifData operator[].
    exif["Exif.Image.Model"] = model;
  }
};

TEST_F(SonyMnPrintAFTrackingTest_1598, NullMetadata_OutputsParenthesizedValue_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  auto v = MakeValue(Exiv2::unsignedByte, "1");

  std::ostringstream os;
  mn.printAFTracking(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMnPrintAFTrackingTest_1598, WrongType_OutputsParenthesizedValue_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;
  SetModel(exif, "ILCE-7M3");

  auto v = MakeValue(Exiv2::asciiString, "1");  // not unsignedByte

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMnPrintAFTrackingTest_1598, WrongCount_OutputsParenthesizedValue_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;
  SetModel(exif, "ILCE-7M3");

  // Attempt to create a value with count != 1 (public API only).
  auto v = MakeValue(Exiv2::unsignedByte, "1 2");

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMnPrintAFTrackingTest_1598, MissingModelInMetadata_OutputsParenthesizedValue_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;  // no model set

  auto v = MakeValue(Exiv2::unsignedByte, "1");

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMnPrintAFTrackingTest_1598, ModelNotDSC_PrintsKnownTagString_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;
  SetModel(exif, "ILCE-7M3");  // does not start with "DSC-"

  auto v = MakeValue(Exiv2::unsignedByte, "1");

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  // Observable behavior: prints tag details (not "n/a" and not parenthesized fallback).
  EXPECT_THAT(out, HasSubstr("Face tracking"));
  EXPECT_THAT(out, ::testing::Not(HasSubstr("n/a")));
  EXPECT_TRUE(out.empty() || out.front() != '(');
}

TEST_F(SonyMnPrintAFTrackingTest_1598, ModelDSCNotInAllowList_PrintsNA_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;
  SetModel(exif, "DSC-ABC");  // starts with DSC-, not in the allow-list

  auto v = MakeValue(Exiv2::unsignedByte, "1");

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  EXPECT_THAT(out, HasSubstr("n/a"));
}

TEST_F(SonyMnPrintAFTrackingTest_1598, ModelDSCInAllowList_PrintsKnownTagString_1598) {
  Exiv2::Internal::SonyMakerNote mn;
  Exiv2::ExifData exif;
  SetModel(exif, "DSC-RX100M7");  // explicitly in the allow-list

  auto v = MakeValue(Exiv2::unsignedByte, "2");

  std::ostringstream os;
  mn.printAFTracking(os, *v, &exif);

  const std::string out = os.str();
  EXPECT_THAT(out, HasSubstr("Lock on AF"));
  EXPECT_THAT(out, ::testing::Not(HasSubstr("n/a")));
  EXPECT_TRUE(out.empty() || out.front() != '(');
}

}  // namespace