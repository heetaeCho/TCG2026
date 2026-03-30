// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3_makernote_printExternalFlashData4_501.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

// SUT
#include "nikonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

class Nikon3MakerNoteTest_501 : public ::testing::Test {
 protected:
  static std::string CallPrintExternalFlashData4(const Value& value, const ExifData* metadata) {
    std::ostringstream os;
    Exiv2::Internal::Nikon3MakerNote sut;
    sut.printExternalFlashData4(os, value, metadata);
    return os.str();
  }

  static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    // Use string-based read to avoid depending on ByteOrder details.
    // If parsing fails, Value implementations typically still remain safe to stream.
    (void)v->read(text);
    return v;
  }
};

TEST_F(Nikon3MakerNoteTest_501, WrongType_PrintsParenthesizedValue_501) {
  auto v = MakeValue(TypeId::asciiString, "1");
  const std::string out = CallPrintExternalFlashData4(*v, nullptr);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_501, WrongCountZero_PrintsParenthesizedValue_501) {
  // Create an unsignedByte value but do not populate it => count() is expected to be != 1.
  auto v = Value::create(TypeId::unsignedByte);

  const std::string out = CallPrintExternalFlashData4(*v, nullptr);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_501, WrongCountTwo_PrintsParenthesizedValue_501) {
  // Try to produce a count != 1 using a typical "two values" textual representation.
  auto v = MakeValue(TypeId::unsignedByte, "1 2");

  const std::string out = CallPrintExternalFlashData4(*v, nullptr);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_501, ValidUnsignedByte0_PrintsIlluminationPatternStandard_501) {
  auto v = MakeValue(TypeId::unsignedByte, "0");

  const std::string out = CallPrintExternalFlashData4(*v, nullptr);

  // Based on the provided TagDetails list for nikonFlashIlluminationPat.
  EXPECT_NE(out.find("Illumination Pat."), std::string::npos);
  EXPECT_NE(out.find("Standard"), std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, ValidUnsignedByte1_PrintsIlluminationPatternCenterWeighted_501) {
  auto v = MakeValue(TypeId::unsignedByte, "1");

  const std::string out = CallPrintExternalFlashData4(*v, nullptr);

  EXPECT_NE(out.find("Illumination Pat."), std::string::npos);
  EXPECT_NE(out.find("Center-weighted"), std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, ValidUnsignedByte2_WithMetadata_PrintsIlluminationPatternEven_501) {
  auto v = MakeValue(TypeId::unsignedByte, "2");
  ExifData metadata;

  const std::string out = CallPrintExternalFlashData4(*v, &metadata);

  EXPECT_NE(out.find("Illumination Pat."), std::string::npos);
  EXPECT_NE(out.find("Even"), std::string::npos);
}

}  // namespace