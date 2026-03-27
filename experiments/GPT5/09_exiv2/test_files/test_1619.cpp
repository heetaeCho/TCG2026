// File: test_sonymn_printSonyMisc3cShotNumberSincePowerUp_1619.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::unsignedLong;

class SonyMakerNoteShotNumberSincePowerUpTest_1619 : public ::testing::Test {
 protected:
  static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    // Value::read(std::string) is part of the public interface.
    (void)v->read(text);
    return v;
  }

  static std::string ParenthesizedValue(const Value& v) {
    std::ostringstream os;
    os << "(" << v << ")";
    return os.str();
  }
};

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, NullMetadataPrintsParenthesizedValue_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(unsignedLong, "123");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, /*metadata=*/nullptr);

  EXPECT_EQ(os.str(), ParenthesizedValue(*v));
}

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, TypeMismatchPrintsParenthesizedValue_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData exif;
  exif["Exif.Image.Model"] = "ILCE-7M2";

  // Wrong type (asciiString) should trigger the early fallback formatting.
  auto v = MakeValue(Exiv2::asciiString, "123");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, &exif);

  EXPECT_EQ(os.str(), ParenthesizedValue(*v));
}

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, MissingModelInMetadataPrintsParenthesizedValue_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData exif;  // no Exif.Image.Model set
  auto v = MakeValue(unsignedLong, "456");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, &exif);

  EXPECT_EQ(os.str(), ParenthesizedValue(*v));
}

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, SupportedModelPrintsNumericShotNumber_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData exif;
  exif["Exif.Image.Model"] = "ILCE-7M2";  // listed in the supported model set

  auto v = MakeValue(unsignedLong, "789");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, &exif);

  // Observable behavior: for supported models, prints value.toInt64()
  std::ostringstream expected;
  expected << v->toInt64();

  EXPECT_EQ(os.str(), expected.str());
}

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, UnsupportedModelPrintsNA_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData exif;
  exif["Exif.Image.Model"] = "SOME-UNSUPPORTED-MODEL";

  auto v = MakeValue(unsignedLong, "321");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, &exif);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNoteShotNumberSincePowerUpTest_1619, CountNotOneFallsBackToParenthesizedValueIfParserCreatesMultipleItems_1619) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData exif;
  exif["Exif.Image.Model"] = "ILCE-7M2";

  // Attempt to create a Value with count != 1 using the public read(string) API.
  // If the underlying parser treats this as multiple items, the function should fall back.
  auto v = MakeValue(unsignedLong, "1 2");
  std::ostringstream os;

  mn.printSonyMisc3cShotNumberSincePowerUp(os, *v, &exif);

  if (v->count() != 1) {
    EXPECT_EQ(os.str(), ParenthesizedValue(*v));
  } else {
    // If the implementation parses "1 2" as a single value, we at least assert
    // the function produces one of the two documented output styles (numeric or fallback),
    // without assuming internal parsing details.
    // For supported model, numeric output is possible when count==1.
    std::ostringstream numeric;
    numeric << v->toInt64();
    const std::string out = os.str();
    EXPECT_TRUE(out == numeric.str() || out == ParenthesizedValue(*v))
        << "Unexpected output: " << out;
  }
}

}  // namespace