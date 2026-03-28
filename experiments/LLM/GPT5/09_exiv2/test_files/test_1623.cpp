// File: test_sonymn_int_printSonyMisc3cModelReleaseYear_1623.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"

// Prefer the umbrella header if available in your build; keep this include last to avoid conflicts.
// If your build already provides Exiv2 types via other includes, you may remove it.
// #include <exiv2/exiv2.hpp>

#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ByteOrder;
using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::TypeId;
using Exiv2::Value;

using Exiv2::Internal::SonyMakerNote;

Value::UniquePtr MakeUnsignedByteValue(std::initializer_list<uint8_t> bytes) {
  auto v = Value::create(Exiv2::unsignedByte);
  std::vector<Exiv2::byte> buf;
  buf.reserve(bytes.size());
  for (auto b : bytes) buf.push_back(static_cast<Exiv2::byte>(b));
  // For unsignedByte, byte order should not matter; still pass a valid value.
  (void)v->read(buf.data(), buf.size(), Exiv2::littleEndian);
  return v;
}

Value::UniquePtr MakeTypeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  (void)v->read(text);
  return v;
}

ExifData MakeExifWithModel(const std::string& model) {
  ExifData exif;
  ExifKey key("Exif.Image.Model");
  auto v = Value::create(Exiv2::asciiString);
  (void)v->read(model);
  exif.add(key, v.get());
  return exif;
}

std::string CallPrint(const Value& value, const ExifData* metadata) {
  SonyMakerNote mn;
  std::ostringstream oss;
  mn.printSonyMisc3cModelReleaseYear(oss, value, metadata);
  return oss.str();
}

}  // namespace

class SonyMakerNoteModelReleaseYearTest_1623 : public ::testing::Test {};

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, ReturnsParenValueWhenMetadataNull_1623) {
  auto v = MakeUnsignedByteValue({1});
  const std::string out = CallPrint(*v, nullptr);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, ReturnsParenValueWhenCountNotOne_1623) {
  auto v = MakeUnsignedByteValue({1, 2});  // count != 1
  ExifData exif = MakeExifWithModel("Some-Other-Model");

  const std::string out = CallPrint(*v, &exif);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, ReturnsParenValueWhenTypeIsNotUnsignedByte_1623) {
  auto v = MakeTypeValue(Exiv2::asciiString, "7");  // typeId != unsignedByte
  ExifData exif = MakeExifWithModel("Some-Other-Model");

  const std::string out = CallPrint(*v, &exif);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, ReturnsNaForKnownModels_1623) {
  // Models known to map to "n/a" in this formatter.
  const char* kModels[] = {"ILCE-1", "ILCE-7M4", "ILCE-7RM5", "ILCE-7SM3", "ILME-FX3"};

  for (const char* model : kModels) {
    SCOPED_TRACE(model);
    ExifData exif = MakeExifWithModel(model);
    auto v = MakeUnsignedByteValue({22});

    const std::string out = CallPrint(*v, &exif);
    EXPECT_EQ(out, "n/a");
  }
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Prints2000WhenValueIsZeroAndModelNotInNaList_1623) {
  ExifData exif = MakeExifWithModel("Not-In-Na-List");
  auto v = MakeUnsignedByteValue({0});

  const std::string out = CallPrint(*v, &exif);
  EXPECT_EQ(out, "2000");
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, Prints20PlusValueWhenWithinRange_1623) {
  ExifData exif = MakeExifWithModel("Not-In-Na-List");
  auto v = MakeUnsignedByteValue({5});

  const std::string out = CallPrint(*v, &exif);
  // Note: This formatter streams "20" << val without zero-padding.
  EXPECT_EQ(out, "205");
}

TEST_F(SonyMakerNoteModelReleaseYearTest_1623, PrintsParenIntWhenGreaterThan99_1623) {
  ExifData exif = MakeExifWithModel("Not-In-Na-List");
  auto v = MakeUnsignedByteValue({100});

  const std::string out = CallPrint(*v, &exif);
  EXPECT_EQ(out, "(100)");
}