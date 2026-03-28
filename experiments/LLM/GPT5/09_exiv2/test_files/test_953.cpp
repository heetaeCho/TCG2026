// File: test_canonmn_int_printSi0x0001_953.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cctype>
#include <limits>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// CanonMakerNote is an internal component; include the internal header.
#include "canonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

static bool LooksLikeNumber(const std::string& s) {
  // Accept digits, optional sign, decimal point, exponent markers, and whitespace.
  bool has_digit = false;
  for (unsigned char ch : s) {
    if (std::isdigit(ch)) has_digit = true;
    if (!(std::isdigit(ch) || ch == '+' || ch == '-' || ch == '.' || ch == 'e' || ch == 'E' ||
          std::isspace(ch))) {
      return false;
    }
  }
  return has_digit;
}

static std::string Trim(const std::string& s) {
  size_t b = 0;
  while (b < s.size() && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
  size_t e = s.size();
  while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
  return s.substr(b, e - b);
}

static Value::UniquePtr MakeUShortValueFromString(const std::string& text) {
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  v->read(text);
  return v;
}

static Value::UniquePtr MakeULongValueFromString(const std::string& text) {
  Value::UniquePtr v = Value::create(Exiv2::unsignedLong);
  v->read(text);
  return v;
}

class CanonMakerNoteTest_953 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote sut_;
};

TEST_F(CanonMakerNoteTest_953, UnsignedShortWithCountPositive_AppendsNumericOutput_953) {
  auto v = MakeUShortValueFromString("0");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream os;
  const std::string prefix = "prefix:";
  os << prefix;

  sut_.printSi0x0001(os, *v, static_cast<const ExifData*>(nullptr));

  const std::string out = os.str();
  ASSERT_GE(out.size(), prefix.size());
  EXPECT_EQ(out.substr(0, prefix.size()), prefix);
  EXPECT_GT(out.size(), prefix.size()) << "Expected some output to be appended for valid input.";

  const std::string appended = Trim(out.substr(prefix.size()));
  EXPECT_FALSE(appended.empty());
  EXPECT_TRUE(LooksLikeNumber(appended)) << "Appended content should look like a number: [" << appended
                                         << "]";
}

TEST_F(CanonMakerNoteTest_953, UnsignedShortWithMultipleValues_StillAppendsSomething_953) {
  auto v = MakeUShortValueFromString("1 2");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream os;
  const std::string prefix = "X";
  os << prefix;

  sut_.printSi0x0001(os, *v, static_cast<const ExifData*>(nullptr));

  const std::string out = os.str();
  EXPECT_EQ(out.substr(0, prefix.size()), prefix);
  EXPECT_GT(out.size(), prefix.size());
}

TEST_F(CanonMakerNoteTest_953, WrongType_DoesNotModifyStream_953) {
  auto v = MakeULongValueFromString("0");
  ASSERT_NE(v->typeId(), Exiv2::unsignedShort);

  std::ostringstream os;
  const std::string before = "unchanged";
  os << before;

  sut_.printSi0x0001(os, *v, static_cast<const ExifData*>(nullptr));

  EXPECT_EQ(os.str(), before) << "Stream should remain unchanged for non-unsignedShort types.";
}

TEST_F(CanonMakerNoteTest_953, UnsignedShortWithZeroCount_DoesNotModifyStream_953) {
  // Create unsignedShort Value but do not read/assign any data => count is expected to be 0.
  Value::UniquePtr v = Value::create(Exiv2::unsignedShort);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_EQ(v->count(), 0u);

  std::ostringstream os;
  const std::string before = "keep";
  os << before;

  sut_.printSi0x0001(os, *v, static_cast<const ExifData*>(nullptr));

  EXPECT_EQ(os.str(), before) << "Stream should remain unchanged when count() == 0.";
}

TEST_F(CanonMakerNoteTest_953, LargeUnsignedShortValue_AppendsFiniteNumber_953) {
  auto v = MakeUShortValueFromString("65535");
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream os;
  const std::string prefix = "p:";
  os << prefix;

  sut_.printSi0x0001(os, *v, static_cast<const ExifData*>(nullptr));

  const std::string out = os.str();
  ASSERT_GT(out.size(), prefix.size());

  const std::string appended = Trim(out.substr(prefix.size()));
  ASSERT_FALSE(appended.empty());
  ASSERT_TRUE(LooksLikeNumber(appended));

  // Try to parse; if parsing fails, the test should fail (observable contract: it prints a number).
  double parsed = 0.0;
  ASSERT_NO_THROW(parsed = std::stod(appended));
  EXPECT_TRUE(std::isfinite(parsed)) << "Expected a finite numeric output, got: " << appended;
}

}  // namespace