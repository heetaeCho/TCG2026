// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Internal::SonyMakerNote::printSony2FpFocusPosition2
// File: sonymn_int_printSony2FpFocusPosition2_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

class SonyMakerNotePrintSony2FpFocusPosition2Test_1615 : public ::testing::Test {};

class StubValue_1615 : public Exiv2::Value {
 public:
  StubValue_1615(size_t count, int64_t v, std::string repr)
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), count_(count), v_(v), repr_(std::move(repr)) {}

  size_t count() const override { return count_; }

  int64_t toInt64(size_t /*n*/ = 0) const override { return v_; }

  std::ostream& write(std::ostream& os) const override {
    os << repr_;
    return os;
  }

 private:
  size_t count_;
  int64_t v_;
  std::string repr_;
};

static std::string Call_1615(const Exiv2::Value& value, const Exiv2::ExifData* exif) {
  std::ostringstream os;
  Exiv2::Internal::SonyMakerNote::printSony2FpFocusPosition2(os, value, exif);
  return os.str();
}

}  // namespace

TEST_F(SonyMakerNotePrintSony2FpFocusPosition2Test_1615, CountNotOne_PrintsParenthesizedValue_1615) {
  StubValue_1615 v(/*count=*/2, /*val=*/42, /*repr=*/"VAL");
  Exiv2::ExifData exif;

  const std::string out = Call_1615(v, &exif);
  EXPECT_EQ("(VAL)", out);
}

TEST_F(SonyMakerNotePrintSony2FpFocusPosition2Test_1615, NullMetadata_PrintsParenthesizedValue_1615) {
  StubValue_1615 v(/*count=*/1, /*val=*/42, /*repr=*/"VAL");

  const std::string out = Call_1615(v, nullptr);
  EXPECT_EQ("(VAL)", out);
}

TEST_F(SonyMakerNotePrintSony2FpFocusPosition2Test_1615, MissingModel_PrintsParenthesizedValue_1615) {
  StubValue_1615 v(/*count=*/1, /*val=*/42, /*repr=*/"VAL");
  Exiv2::ExifData exif;  // intentionally empty -> model lookup expected to fail

  const std::string out = Call_1615(v, &exif);
  EXPECT_EQ("(VAL)", out);
}

TEST_F(SonyMakerNotePrintSony2FpFocusPosition2Test_1615, ModelWithBlockedPrefix_PrintsNa_1615) {
  StubValue_1615 v(/*count=*/1, /*val=*/7, /*repr=*/"VAL");
  Exiv2::ExifData exif;
  exif["Exif.Image.Model"] = "DSC-TEST";  // triggers blocked prefix path

  const std::string out = Call_1615(v, &exif);
  EXPECT_EQ("n/a", out);
}

TEST_F(SonyMakerNotePrintSony2FpFocusPosition2Test_1615, InfinityAndNumericOutput_ArePrinted_1615) {
  Exiv2::ExifData exif;
  exif["Exif.Image.Model"] = "ILCE-7M3";  // allowed model

  {
    StubValue_1615 v(/*count=*/1, /*val=*/255, /*repr=*/"VAL");
    const std::string out = Call_1615(v, &exif);
    EXPECT_EQ("Infinity", out);
  }

  {
    StubValue_1615 v(/*count=*/1, /*val=*/42, /*repr=*/"VAL");
    const std::string out = Call_1615(v, &exif);
    EXPECT_EQ("42", out);
  }
}