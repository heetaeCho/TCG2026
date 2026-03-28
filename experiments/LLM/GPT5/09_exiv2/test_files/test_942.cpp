// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "canonmn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::TypeId;
using Exiv2::Value;

using Exiv2::Internal::CanonMakerNote;

class CanonMakerNotePrintFocalLengthTest_942 : public ::testing::Test {
protected:
  static std::string StreamValue(const Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    EXPECT_NE(v.get(), nullptr);
    // Value parsing is handled by Exiv2; tests rely only on public API.
    const int rc = v->read(text);
    EXPECT_EQ(0, rc);
    return v;
  }

  static void AddLensToExif(ExifData& exif, const Value& lensValue) {
    const ExifKey key("Exif.CanonCs.Lens");
    exif.add(key, &lensValue);
  }

  static std::string CallPrintFocalLength(const Value& v, const ExifData* md) {
    CanonMakerNote mn;  // Works whether printFocalLength is static or non-static.
    std::ostringstream os;
    mn.printFocalLength(os, v, md);
    return os.str();
  }
};

TEST_F(CanonMakerNotePrintFocalLengthTest_942, NullMetadata_FallsBackToStreamingValue_942) {
  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");  // count() >= 4
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, nullptr);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, CountLessThan4_FallsBackToStreamingValue_942) {
  ExifData exif;
  auto v = MakeValue(TypeId::unsignedShort, "0 100 0");  // count() == 3 (<4)
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, NonUnsignedShortType_FallsBackToStreamingValue_942) {
  ExifData exif;
  auto v = MakeValue(TypeId::asciiString, "hello");  // wrong type
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, MetadataMissingLensKey_FallsBackToStreamingValue_942) {
  ExifData exif;
  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, LensValueWrongType_FallsBackToStreamingValue_942) {
  ExifData exif;

  auto lens = MakeValue(TypeId::asciiString, "not-a-ushort");  // wrong type for lens
  AddLensToExif(exif, *lens);

  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, LensValueCountLessThan3_FallsBackToStreamingValue_942) {
  ExifData exif;

  auto lens = MakeValue(TypeId::unsignedShort, "1 2");  // count() == 2 (<3)
  AddLensToExif(exif, *lens);

  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, LensFuZero_FallsBackToStreamingValue_942) {
  ExifData exif;

  // fu is taken from lens value index 2; set it to 0 to trigger fallback.
  auto lens = MakeValue(TypeId::unsignedShort, "0 0 0");
  AddLensToExif(exif, *lens);

  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");
  const std::string expected = StreamValue(*v);

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ(expected, actual);
}

TEST_F(CanonMakerNotePrintFocalLengthTest_942, ValidMetadataAndValues_FormatsAsMillimetersWithOneDecimal_942) {
  ExifData exif;

  // fu = lens[2] (as float). Use 2 so 100 / 2 = 50.0.
  auto lens = MakeValue(TypeId::unsignedShort, "0 0 2");
  AddLensToExif(exif, *lens);

  // value.toFloat(1) is used; set index 1 to 100.
  auto v = MakeValue(TypeId::unsignedShort, "0 100 0 0");

  const std::string actual = CallPrintFocalLength(*v, &exif);

  EXPECT_EQ("50.0 mm", actual);
}

}  // namespace