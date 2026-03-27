// ============================================================================
// TEST_ID: 1597
// File: test_sonymn_int_printafpointsused_1597.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Internal header under test
#include "sonymn_int.hpp"

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::byte;

class SonyMakerNotePrintAFPointsUsedTest_1597 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeUnsignedByteValue(const std::vector<byte>& bytes) {
    auto v = Exiv2::Value::create(Exiv2::unsignedByte);
    EXPECT_NE(v.get(), nullptr);

    // Prefer buffer-based read so we can precisely control bits.
    // ByteOrder is observable only via API; we do not assume internal representation beyond
    // providing a valid byte buffer.
    const int rc = v->read(bytes.data(), bytes.size(), Exiv2::littleEndian);
    (void)rc;  // Some implementations may return 0/len; we don't rely on it.
    return v;
  }

  static Exiv2::Value::UniquePtr MakeAsciiStringValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    const int rc = v->read(s);
    (void)rc;
    return v;
  }

  static void SetExifModel(Exiv2::ExifData& exif, const std::string& model) {
    // Common Exiv2 key for model.
    exif["Exif.Image.Model"] = model;
  }

  static std::string CallPrint(const Exiv2::Value& value, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::SonyMakerNote mn;
    mn.printAFPointsUsed(os, value, md);
    return os.str();
  }
};

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, ReturnsParenthesizedValueWhenMetadataNull_1597) {
  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, nullptr);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  EXPECT_NE(out.find(v->toString()), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, ReturnsParenthesizedValueWhenTypeIsNotUnsignedByte_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "NEX-5N");

  auto v = MakeAsciiStringValue("abc");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  EXPECT_NE(out.find(v->toString()), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, ReturnsParenthesizedValueWhenModelNotAvailableInMetadata_1597) {
  // Provide metadata pointer, but do not set Exif.Image.Model.
  Exiv2::ExifData exif;

  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
  EXPECT_NE(out.find(v->toString()), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, PrintsSet1LabelsWhenModelDoesNotStartWithILCAOrDSC_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "NEX-5N");  // Does not start with "ILCA-" or "DSC-"

  // Set bit 0 -> expected to include the label at index 0 in set1 ("Center").
  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  // We only assert observable text includes known labels from provided TagDetails.
  EXPECT_NE(out.find("Center"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, PrintsMultipleSet1LabelsWhenMultipleBitsSet_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "SLT-A99V");  // Not ILCA-/DSC- -> set1

  // Set bits 0 and 1 -> should include "Center" and "Top" (set1 indices 0 and 1).
  auto v = MakeUnsignedByteValue({0x03});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  EXPECT_NE(out.find("Center"), std::string::npos);
  EXPECT_NE(out.find("Top"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, PrintsSet2LabelsForILCA68_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "ILCA-68");  // Special-cased -> set2

  // Set bit 0 -> expected to include set2 index 0 label ("A5").
  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  EXPECT_NE(out.find("A5"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, PrintsSet2AutoLabelForBit128Boundary_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "ILCA-77M2");  // Special-cased -> set2

  // Boundary: set bit 128 (0-based). That is byte index 16, bit 0.
  std::vector<byte> bytes(17, 0x00);
  bytes[16] = 0x01;

  auto v = MakeUnsignedByteValue(bytes);
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  EXPECT_NE(out.find("Auto"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, ReturnsNAForILCAModelsOtherThan68Or77M2_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "ILCA-7RM3");  // Starts with ILCA- but not 68/77M2 -> "n/a"

  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFPointsUsedTest_1597, ReturnsNAForDSCModels_1597) {
  Exiv2::ExifData exif;
  SetExifModel(exif, "DSC-RX100");  // Starts with DSC- -> "n/a"

  auto v = MakeUnsignedByteValue({0x01});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = CallPrint(*v, &exif);

  EXPECT_NE(out.find("n/a"), std::string::npos);
}

}  // namespace