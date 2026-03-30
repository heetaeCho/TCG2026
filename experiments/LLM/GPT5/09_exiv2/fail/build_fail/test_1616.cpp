// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printSonyMisc1CameraTemperature_1616.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

// A controllable Value test double.
// This is a collaborator passed into SonyMakerNote; overriding it is fine for black-box testing.
class FakeValue final : public Exiv2::Value {
 public:
  FakeValue(size_t count, std::string repr, int64_t i64)
      : Exiv2::Value(Exiv2::unsignedLong), count_(count), repr_(std::move(repr)), i64_(i64) {}

  size_t count() override { return count_; }

  const std::ostream& write(std::ostream& os) override {
    os << repr_;
    return os;
  }

  const int64_t toInt64(size_t /*n*/) override { return i64_; }

 private:
  // Exiv2::Value::clone_() is private in the base, but still virtual and can be overridden.
  const Exiv2::Value* clone_() override { return new FakeValue(*this); }

  size_t count_;
  std::string repr_;
  int64_t i64_;
};

static std::string CallAndGet(Exiv2::Internal::SonyMakerNote& mn,
                              const Exiv2::Value& value,
                              const Exiv2::ExifData* md,
                              std::ostream** returned_stream = nullptr) {
  std::ostringstream oss;
  std::ostream& ret = mn.printSonyMisc1CameraTemperature(oss, value, md);
  if (returned_stream) *returned_stream = &ret;
  return oss.str();
}

static void AddSonyMisc1_0004(Exiv2::ExifData& md, int64_t v, size_t count = 1) {
  // The function under test requires:
  // - key present
  // - pos->count() == 1
  // - pos->toInt64() != 0
  // - pos->toInt64() < 100
  md.add(Exiv2::ExifKey("Exif.SonyMisc1.0x0004"), new FakeValue(count, std::to_string(v), v));
}

}  // namespace

class SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;
};

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, ReturnsSameStreamReference_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, 1);

  std::ostringstream oss;
  std::ostream& ret = mn_.printSonyMisc1CameraTemperature(oss, value, &md);

  EXPECT_EQ(&ret, &oss);
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, NullMetadataPrintsParenthesizedValue_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);

  const std::string out = CallAndGet(mn_, value, /*md=*/nullptr);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_NE(out.find("25"), std::string::npos);
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, ValueCountNotOnePrintsParenthesizedValueEvenIfMetadataPresent_1616) {
  FakeValue value(/*count=*/2, /*repr=*/"25 26", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, 1);

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_NE(out.find("25 26"), std::string::npos);
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, KeyMissingPrintsNA_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;  // no Exif.SonyMisc1.0x0004

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, KeyPresentButCountNotOnePrintsNA_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, /*v=*/1, /*count=*/2);

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, KeyPresentButZeroPrintsNA_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, /*v=*/0, /*count=*/1);

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, KeyPresentButHundredOrMorePrintsNA_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, /*v=*/100, /*count=*/1);

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, ValidGatePrintsValueWithCelsiusSuffix_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"25", /*i64=*/25);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, /*v=*/1, /*count=*/1);  // non-zero and < 100

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_EQ(out, "25 \xC2\xB0" "C");  // "25 °C" in UTF-8
}

TEST_F(SonyMakerNotePrintSonyMisc1CameraTemperatureTest_1616, BoundaryAtNinetyNineStillPrintsCelsius_1616) {
  FakeValue value(/*count=*/1, /*repr=*/"7", /*i64=*/7);
  Exiv2::ExifData md;
  AddSonyMisc1_0004(md, /*v=*/99, /*count=*/1);

  const std::string out = CallAndGet(mn_, value, &md);

  EXPECT_EQ(out, "7 \xC2\xB0" "C");  // "7 °C"
}