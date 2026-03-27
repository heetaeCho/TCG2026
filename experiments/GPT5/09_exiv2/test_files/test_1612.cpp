// ============================================================================
// Unit tests for Exiv2::Internal::SonyMakerNote::printHighISONoiseReduction2
// File: sonymn_int.cpp
//
// TEST_ID: 1612
// ============================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::AsciiValue;
using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  // Value::read returns int; treat as black-box: we only use the created value via its public interface.
  (void)v->read(text);
  return v;
}

static void AddModel(ExifData& exif, const std::string& model) {
  auto mv = MakeValue(Exiv2::asciiString, model);
  exif.add(ExifKey("Exif.Image.Model"), mv.get());
}

static std::string CallPrint(const Value& value, const ExifData* md) {
  SonyMakerNote mn;
  std::ostringstream os;
  mn.printHighISONoiseReduction2(os, value, md);
  return os.str();
}

static bool LooksParenthesized(const std::string& s) {
  return s.size() >= 2 && s.front() == '(' && s.back() == ')';
}

class SonyMakerNotePrintHighISONoiseReduction2Test_1612 : public ::testing::Test {};

}  // namespace

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, NullMetadata_PrintsParenthesizedValue_1612) {
  auto v = MakeValue(Exiv2::unsignedShort, "0");
  const std::string out = CallPrint(*v, nullptr);

  EXPECT_TRUE(LooksParenthesized(out));
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, WrongType_PrintsParenthesizedValue_1612) {
  ExifData exif;
  AddModel(exif, "DSC-TEST");

  auto v = MakeValue(Exiv2::unsignedLong, "0");  // wrong typeId for this API
  const std::string out = CallPrint(*v, &exif);

  EXPECT_TRUE(LooksParenthesized(out));
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, CountNotOne_PrintsParenthesizedValue_1612) {
  ExifData exif;
  AddModel(exif, "DSC-TEST");

  auto v = MakeValue(Exiv2::unsignedShort, "0 1");  // attempts to produce count != 1
  ASSERT_NE(v->count(), 1u);                        // observable via public interface
  const std::string out = CallPrint(*v, &exif);

  EXPECT_TRUE(LooksParenthesized(out));
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, MissingModel_PrintsParenthesizedValue_1612) {
  ExifData exif;  // no Exif.Image.Model present
  auto v = MakeValue(Exiv2::unsignedShort, "0");

  const std::string out = CallPrint(*v, &exif);

  EXPECT_TRUE(LooksParenthesized(out));
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, ModelStartsWithDSC_PrintsMappedLabel_1612) {
  ExifData exif;
  AddModel(exif, "DSC-ABC123");

  auto v = MakeValue(Exiv2::unsignedShort, "0");

  const std::string out = CallPrint(*v, &exif);

  // For DSC-* models, the function delegates to the tag printer; verify an observable label appears.
  EXPECT_FALSE(LooksParenthesized(out));
  EXPECT_NE(out.find("Normal"), std::string::npos);
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, ModelStartsWithStellar_PrintsMappedLabel_1612) {
  ExifData exif;
  AddModel(exif, "Stellar-XYZ");

  auto v = MakeValue(Exiv2::unsignedShort, "1");

  const std::string out = CallPrint(*v, &exif);

  EXPECT_FALSE(LooksParenthesized(out));
  EXPECT_NE(out.find("High"), std::string::npos);
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, OtherModel_PrintsNA_1612) {
  ExifData exif;
  AddModel(exif, "ILCE-7M3");  // not DSC-* and not Stellar*

  auto v = MakeValue(Exiv2::unsignedShort, "0");

  const std::string out = CallPrint(*v, &exif);

  EXPECT_FALSE(LooksParenthesized(out));
  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintHighISONoiseReduction2Test_1612, BoundaryValue65535_WithDSCModel_PrintsNA_1612) {
  ExifData exif;
  AddModel(exif, "DSC-BOUNDARY");

  auto v = MakeValue(Exiv2::unsignedShort, "65535");

  const std::string out = CallPrint(*v, &exif);

  // Tag details include {65535, "n/a"}; verify observable output contains "n/a".
  EXPECT_FALSE(LooksParenthesized(out));
  EXPECT_NE(out.find("n/a"), std::string::npos);
}