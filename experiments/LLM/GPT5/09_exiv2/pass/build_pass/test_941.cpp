// =================================================================================================
// TEST_ID: 941
// Unit tests for Exiv2::Internal::CanonMakerNote::printFiFileNumber
// File: ./TestProjects/exiv2/src/canonmn_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

#include "canonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

class CanonMakerNotePrintFiFileNumberTest_941 : public ::testing::Test {
 protected:
  static Value::UniquePtr MakeULongValue(uint32_t v) {
    auto val = Value::create(TypeId::unsignedLong);
    // Use the public string read API (black-box friendly).
    val->read(std::to_string(v));
    return val;
  }

  static Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto val = Value::create(TypeId::asciiString);
    val->read(s);
    return val;
  }

  static std::string CallPrint(const Value& value, const ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::CanonMakerNote::printFiFileNumber(os, value, md);
    return os.str();
  }

  static bool LooksLikeDashedFourDigits(const std::string& s) {
    // Expect something like "<some digits>-<exactly 4 digits>" and NOT the fallback "(...)".
    if (s.empty()) return false;
    if (s.front() == '(') return false;
    const auto dash = s.find('-');
    if (dash == std::string::npos) return false;
    if (dash == 0 || dash + 5 != s.size()) return false;  // "-dddd" at end
    for (size_t i = 0; i < dash; ++i) {
      if (s[i] < '0' || s[i] > '9') return false;
    }
    for (size_t i = dash + 1; i < s.size(); ++i) {
      if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
  }
};

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, NullMetadataFallsBackToParenthesizedValue_941) {
  auto v = MakeULongValue(123u);

  const std::string out = CallPrint(*v, nullptr);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, WrongTypeFallsBackToParenthesizedValue_941) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("Canon EOS 20D");

  auto v = MakeAsciiValue("123");

  const std::string out = CallPrint(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, ZeroCountFallsBackToParenthesizedValue_941) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("Canon EOS 20D");

  // Create unsignedLong but do not populate it -> count() is expected to be 0 per interface usage.
  auto v = Value::create(TypeId::unsignedLong);

  const std::string out = CallPrint(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, MissingModelKeyFallsBackToParenthesizedValue_941) {
  ExifData md;  // No Exif.Image.Model
  auto v = MakeULongValue(0x12345678u);

  const std::string out = CallPrint(*v, &md);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, Recognized20DStyleModelProducesDashedNumber_941) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("Canon EOS 20D");

  auto v = MakeULongValue(0x12345678u);

  const std::string out = CallPrint(*v, &md);

  EXPECT_TRUE(LooksLikeDashedFourDigits(out)) << "Output was: " << out;
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, Recognized30DStyleModelProducesDashedNumber_941) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("Canon EOS 30D");

  auto v = MakeULongValue(0x00ABCDEFu);

  const std::string out = CallPrint(*v, &md);

  EXPECT_TRUE(LooksLikeDashedFourDigits(out)) << "Output was: " << out;
}

TEST_F(CanonMakerNotePrintFiFileNumberTest_941, ShortModelStringMayThrowOutOfRange_941) {
  ExifData md;
  // Very short model string: does not contain any of the recognized tokens, but is shorter than 8.
  // If implementation uses substr(model.size()-8, 8) without guarding, std::out_of_range may occur.
  md["Exif.Image.Model"] = std::string("EOS");

  auto v = MakeULongValue(42u);

  EXPECT_ANY_THROW({
    std::ostringstream os;
    Exiv2::Internal::CanonMakerNote::printFiFileNumber(os, *v, &md);
  });
}

}  // namespace