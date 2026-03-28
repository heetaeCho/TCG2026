// File: test_sonymn_int_printSony2FpAmbientTemperature_1613.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::Value;

// Helper: create a Value (as black-box) by using the public factory + read(string).
static Value::UniquePtr MakeValueFromString(Exiv2::TypeId type, const std::string& text) {
  auto v = Value::create(type);
  // read() is part of the public interface; we don't assert on its return value here.
  (void)v->read(text);
  return v;
}

class SonyMakerNoteTest_1613 : public ::testing::Test {
 protected:
  SonyMakerNote sut_;
};

TEST_F(SonyMakerNoteTest_1613, ReturnsParenWrappedValueWhenMetadataIsNull_1613) {
  auto v = MakeValueFromString(Exiv2::unsignedShort, "25");

  std::ostringstream os;
  sut_.printSony2FpAmbientTemperature(os, *v, /*metadata=*/nullptr);

  // Observable contract from implementation: null metadata => "(" << value << ")"
  EXPECT_EQ(os.str(), "(" + v->toString() + ")");
}

TEST_F(SonyMakerNoteTest_1613, ReturnsParenWrappedValueWhenValueCountIsNotOne_1613) {
  // Intentionally leave unread so count is not guaranteed to be 1 (commonly 0).
  auto v = Value::create(Exiv2::unsignedShort);

  ExifData md;  // metadata exists, but value.count() != 1 should short-circuit first.
  std::ostringstream os;
  sut_.printSony2FpAmbientTemperature(os, *v, &md);

  EXPECT_EQ(os.str(), "(" + v->toString() + ")");
}

TEST_F(SonyMakerNoteTest_1613, PrintsCelsiusWhenMetadataKeyPresentAndEquals255_1613) {
  auto ambient = MakeValueFromString(Exiv2::unsignedShort, "25");

  ExifData md;
  auto gate = MakeValueFromString(Exiv2::unsignedShort, "255");
  md.add(ExifKey("Exif.Sony2Fp.0x0002"), gate.get());

  std::ostringstream os;
  sut_.printSony2FpAmbientTemperature(os, *ambient, &md);

  EXPECT_EQ(os.str(), std::string(ambient->toString()) + " \xC2\xB0" + "C");  // " °C"
}

TEST_F(SonyMakerNoteTest_1613, PrintsNaWhenMetadataMissingGateKey_1613) {
  auto ambient = MakeValueFromString(Exiv2::unsignedShort, "25");

  ExifData md;  // no Exif.Sony2Fp.0x0002
  std::ostringstream os;
  sut_.printSony2FpAmbientTemperature(os, *ambient, &md);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNoteTest_1613, PrintsNaWhenGateKeyNot255OrNotSingleValue_1613) {
  auto ambient = MakeValueFromString(Exiv2::unsignedShort, "25");

  // Case A: gate present but not 255
  {
    ExifData md;
    auto gate = MakeValueFromString(Exiv2::unsignedShort, "254");
    md.add(ExifKey("Exif.Sony2Fp.0x0002"), gate.get());

    std::ostringstream os;
    sut_.printSony2FpAmbientTemperature(os, *ambient, &md);
    EXPECT_EQ(os.str(), "n/a");
  }

  // Case B: gate present, first value 255 but count != 1
  {
    ExifData md;
    auto gate = MakeValueFromString(Exiv2::unsignedShort, "255 1");  // count likely 2
    md.add(ExifKey("Exif.Sony2Fp.0x0002"), gate.get());

    std::ostringstream os;
    sut_.printSony2FpAmbientTemperature(os, *ambient, &md);
    EXPECT_EQ(os.str(), "n/a");
  }
}

}  // namespace