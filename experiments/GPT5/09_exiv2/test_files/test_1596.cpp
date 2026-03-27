// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printafpointselected_1596.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <utility>

#include "sonymn_int.hpp"

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

// A controllable Value for black-box testing of SonyMakerNote printers.
// We only override the minimal surface used by printAFPointSelected:
// - count(), typeId(), toUint32(), write()
class FakeValue final : public Exiv2::Value {
 public:
  FakeValue(Exiv2::TypeId tid, size_t cnt, uint32_t u32, std::string written = "VAL")
      : Exiv2::Value(tid), cnt_(cnt), u32_(u32), written_(std::move(written)) {
  }

  const size_t count() override {
    return cnt_;
  }

  const uint32_t toUint32(size_t /*n*/) override {
    return u32_;
  }

  const std::ostream& write(std::ostream& os) override {
    os << written_;
    return os;
  }

 private:
  size_t cnt_;
  uint32_t u32_;
  std::string written_;
};

static Exiv2::ExifData MakeExifWithModel(const std::string& model) {
  Exiv2::ExifData exif;
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(v.get() != nullptr);
  // Typical Exiv2 string value parsing accepts a raw string for asciiString.
  v->read(model);
  exif.add(Exiv2::ExifKey("Exif.Image.Model"), v.get());
  return exif;
}

static std::string CallPrint(const Exiv2::Value& value, const Exiv2::ExifData* md) {
  std::ostringstream os;
  Exiv2::Internal::SonyMakerNote::printAFPointSelected(os, value, md);
  return os.str();
}

class SonyMakerNoteTest_1596 : public ::testing::Test {};

}  // namespace

TEST_F(SonyMakerNoteTest_1596, ReturnsParenthesizedWhenMetadataNull_1596) {
  FakeValue v(Exiv2::unsignedByte, 1, 1, "X");
  const std::string out = CallPrint(v, nullptr);
  EXPECT_EQ(out, "(X)");
}

TEST_F(SonyMakerNoteTest_1596, ReturnsParenthesizedWhenCountNotOne_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("SLT-A99");
  FakeValue v(Exiv2::unsignedByte, 2, 1, "Y");  // count != 1 triggers fallback
  const std::string out = CallPrint(v, &exif);
  EXPECT_EQ(out, "(Y)");
}

TEST_F(SonyMakerNoteTest_1596, ReturnsParenthesizedWhenTypeIsNotUnsignedByte_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("SLT-A99");
  FakeValue v(Exiv2::unsignedShort, 1, 1, "Z");  // wrong type triggers fallback
  const std::string out = CallPrint(v, &exif);
  EXPECT_EQ(out, "(Z)");
}

TEST_F(SonyMakerNoteTest_1596, ReturnsParenthesizedWhenModelMissing_1596) {
  Exiv2::ExifData exif;  // no Exif.Image.Model
  FakeValue v(Exiv2::unsignedByte, 1, 1, "M");
  const std::string out = CallPrint(v, &exif);
  EXPECT_EQ(out, "(M)");
}

TEST_F(SonyMakerNoteTest_1596, SLTPrefixUsesSet1Mapping_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("SLT-A77");
  FakeValue v(Exiv2::unsignedByte, 1, 1 /*-> "Center" in Set1*/, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  // Black-box observable expectation: output should include the mapped label.
  EXPECT_NE(out.find("Center"), std::string::npos);
}

TEST_F(SonyMakerNoteTest_1596, HVPrefixUsesSet1Mapping_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("HV-1234");
  FakeValue v(Exiv2::unsignedByte, 1, 19 /*-> "Upper Far Left" in Set1*/, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  EXPECT_NE(out.find("Upper Far Left"), std::string::npos);
}

TEST_F(SonyMakerNoteTest_1596, NEXPrefixUsesSet5Mapping_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("NEX-6");
  FakeValue v(Exiv2::unsignedByte, 1, 1 /*-> "Center Zone" in Set5*/, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  EXPECT_NE(out.find("Center Zone"), std::string::npos);
}

TEST_F(SonyMakerNoteTest_1596, ILCESkipsSet1ConditionalWithoutAFSettingAndFallsBackToSet5_1596) {
  // For ILCE-/ILME-, Set1 branch requires AFAreaModeSetting==4 and "status" true.
  // With only a model present, the observable behavior should follow the later
  // ILCE-/ILME- path that uses Set5.
  Exiv2::ExifData exif = MakeExifWithModel("ILCE-7");
  FakeValue v(Exiv2::unsignedByte, 1, 2 /*-> "Top Zone" in Set5*/, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  EXPECT_NE(out.find("Top Zone"), std::string::npos);
}

TEST_F(SonyMakerNoteTest_1596, UnknownModelReturnsNA_1596) {
  Exiv2::ExifData exif = MakeExifWithModel("DSC-RX100");
  FakeValue v(Exiv2::unsignedByte, 1, 1, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNoteTest_1596, ILCAPrefixWithoutAFSettingReturnsNA_1596) {
  // ILCA- models only match branches that additionally require AFAreaModeSetting status.
  // With only model present, observable behavior should be the final "n/a".
  Exiv2::ExifData exif = MakeExifWithModel("ILCA-68");
  FakeValue v(Exiv2::unsignedByte, 1, 1, "IGNORED");
  const std::string out = CallPrint(v, &exif);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}