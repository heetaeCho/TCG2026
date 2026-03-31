#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteLensIdTest_476 : public ::testing::Test {
 protected:
  void SetUp() override {}

  // Helper to create a Value with a single unsigned byte
  std::unique_ptr<Value> makeUByteValue(uint8_t val) {
    auto v = Value::create(unsignedByte);
    byte b = val;
    v->read(&b, 1, littleEndian);
    return v;
  }

  // Helper to set up ExifData with lens metadata fields for the Nikon3 group
  void setupLensMetadata(ExifData& exifData, const std::string& group,
                         uint8_t lensIdNumber, uint8_t lensFStops,
                         uint8_t minFocalLength, uint8_t maxFocalLength,
                         uint8_t maxApertureAtMinFocal,
                         uint8_t maxApertureAtMaxFocal, uint8_t mcuVersion,
                         uint8_t lensType) {
    std::string prefix = std::string("Exif.") + group + ".";

    {
      ExifKey key(prefix + "LensIDNumber");
      auto val = Value::create(unsignedByte);
      byte b = lensIdNumber;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "LensFStops");
      auto val = Value::create(unsignedByte);
      byte b = lensFStops;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "MinFocalLength");
      auto val = Value::create(unsignedByte);
      byte b = minFocalLength;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "MaxFocalLength");
      auto val = Value::create(unsignedByte);
      byte b = maxFocalLength;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "MaxApertureAtMinFocal");
      auto val = Value::create(unsignedByte);
      byte b = maxApertureAtMinFocal;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "MaxApertureAtMaxFocal");
      auto val = Value::create(unsignedByte);
      byte b = maxApertureAtMaxFocal;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key(prefix + "MCUVersion");
      auto val = Value::create(unsignedByte);
      byte b = mcuVersion;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
    {
      ExifKey key("Exif.Nikon3.LensType");
      auto val = Value::create(unsignedByte);
      byte b = lensType;
      val->read(&b, 1, littleEndian);
      exifData.add(key, val.get());
    }
  }
};

// Test: No metadata provided, known lens ID (first entry: lid=0x01)
TEST_F(Nikon3MakerNoteLensIdTest_476, NoMetadata_KnownLensId_476) {
  std::ostringstream os;
  auto value = makeUByteValue(0x01);  // AF Nikkor 50mm f/1.8
  Nikon3MakerNote::printLensId(os, *value, nullptr, "Nikon3");
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF Nikkor 50mm f/1.8"), std::string::npos);
}

// Test: No metadata provided, unknown lens ID
TEST_F(Nikon3MakerNoteLensIdTest_476, NoMetadata_UnknownLensId_476) {
  std::ostringstream os;
  auto value = makeUByteValue(0xFD);  // Not a known first-match lid
  Nikon3MakerNote::printLensId(os, *value, nullptr, "Nikon3");
  std::string result = os.str();
  // Should output the raw value in parentheses since no match
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: With metadata, known lens - AF Nikkor 50mm f/1.8
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFNikkor50mm_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // First entry: lid=0x01, stps=0x58, focs=0x50, focl=0x50,
  // aps=0x14, apl=0x14, lfw=0x02, ltype=0x00
  setupLensMetadata(exifData, group, 0x01, 0x58, 0x50, 0x50, 0x14, 0x14, 0x02,
                    0x00);

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF Nikkor 50mm f/1.8"), std::string::npos);
}

// Test: With metadata, known lens - AF Nikkor 50mm f/1.4
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFNikkor50mmF14_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // lid=0x05, stps=0x54, focs=0x50, focl=0x50,
  // aps=0x0C, apl=0x0C, lfw=0x04, ltype=0x00
  setupLensMetadata(exifData, group, 0x05, 0x54, 0x50, 0x50, 0x0C, 0x0C, 0x04,
                    0x00);

  auto value = makeUByteValue(0x05);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF Nikkor 50mm f/1.4"), std::string::npos);
}

// Test: With metadata, no matching lens (all zeros except some fields)
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_NoMatch_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Use values that don't match any lens entry
  setupLensMetadata(exifData, group, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                    0xFF);

  auto value = makeUByteValue(0xFF);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Should fall through to the default "(" value ")" output
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: With metadata but missing LensIDNumber key
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_MissingKey_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Only add LensType, skip all other required fields
  {
    ExifKey key("Exif.Nikon3.LensType");
    auto val = Value::create(unsignedByte);
    byte b = 0x00;
    val->read(&b, 1, littleEndian);
    exifData.add(key, val.get());
  }

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Missing required keys should result in fallback output
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: With metadata, Sigma lens (Sigma 50mm F1.4 DG HSM | A)
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_SigmaLens_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Sigma 50mm F1.4 DG HSM | A:
  // lid=0x88, stps=0x54, focs=0x50, focl=0x50,
  // aps=0x0C, apl=0x0C, lfw=0x4B, ltype=0x06
  setupLensMetadata(exifData, group, 0x88, 0x54, 0x50, 0x50, 0x0C, 0x0C, 0x4B,
                    0x06);

  auto value = makeUByteValue(0x88);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Sigma"), std::string::npos);
  EXPECT_NE(result.find("50mm F1.4 DG HSM"), std::string::npos);
}

// Test: With metadata, Tamron lens (SP AF 90mm F/2.8 Di Macro 1:1)
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_TamronLens_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Tamron SP AF 90mm F/2.8 Di Macro:
  // lid=0xF8, stps=0x54, focs=0x64, focl=0x64,
  // aps=0x24, apl=0x24, lfw=0xDF, ltype=0x06
  setupLensMetadata(exifData, group, 0xF8, 0x54, 0x64, 0x64, 0x24, 0x24, 0xDF,
                    0x06);

  auto value = makeUByteValue(0xF8);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Tamron"), std::string::npos);
  EXPECT_NE(result.find("SP AF 90mm"), std::string::npos);
}

// Test: With metadata, AF-S Nikkor 50mm f/1.4G
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFS_Nikkor50mmF14G_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd2";

  // AF-S Nikkor 50mm f/1.4G:
  // lid=0xA0, stps=0x54, focs=0x50, focl=0x50,
  // aps=0x0C, apl=0x0C, lfw=0xA2, ltype=0x06
  setupLensMetadata(exifData, group, 0xA0, 0x54, 0x50, 0x50, 0x0C, 0x0C, 0xA2,
                    0x06);

  auto value = makeUByteValue(0xA0);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF-S Nikkor 50mm f/1.4G"), std::string::npos);
}

// Test: With metadata, AF-S Nikkor 50mm f/1.8G
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFS_Nikkor50mmF18G_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd2";

  // AF-S Nikkor 50mm f/1.8G:
  // lid=0xB0, stps=0x4C, focs=0x50, focl=0x50,
  // aps=0x14, apl=0x14, lfw=0xB2, ltype=0x06
  setupLensMetadata(exifData, group, 0xB0, 0x4C, 0x50, 0x50, 0x14, 0x14, 0xB2,
                    0x06);

  auto value = makeUByteValue(0xB0);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF-S Nikkor 50mm f/1.8G"), std::string::npos);
}

// Test: With metadata, AF Zoom-Nikkor 35-70mm f/3.3-4.5
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFZoom3570_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // lid=0x02, stps=0x42, focs=0x44, focl=0x5C,
  // aps=0x2A, apl=0x34, lfw=0x02, ltype=0x00
  setupLensMetadata(exifData, group, 0x02, 0x42, 0x44, 0x5C, 0x2A, 0x34, 0x02,
                    0x00);

  auto value = makeUByteValue(0x02);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF Zoom-Nikkor 35-70mm f/3.3-4.5"), std::string::npos);
}

// Test: With metadata but wrong type (not unsignedByte) for one of the lens fields
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_WrongTypeForField_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Add LensIDNumber as unsignedShort instead of unsignedByte
  {
    std::string prefix = std::string("Exif.") + group + ".";
    ExifKey key(prefix + "LensIDNumber");
    auto val = Value::create(unsignedShort);
    val->read("1");
    exifData.add(key, val.get());
  }

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Should fallback due to wrong type
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: With empty metadata (no keys at all)
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_EmptyExifData_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Should fallback since metadata keys are missing
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: With metadata, Nikkor 45mm f/2.8 P (non-AF lens)
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_Nikkor45mmP_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // lid=0x72, stps=0x48, focs=0x4C, focl=0x4C,
  // aps=0x24, apl=0x24, lfw=0x77, ltype=0x00
  setupLensMetadata(exifData, group, 0x72, 0x48, 0x4C, 0x4C, 0x24, 0x24, 0x77,
                    0x00);

  auto value = makeUByteValue(0x72);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("Nikkor 45mm f/2.8 P"), std::string::npos);
}

// Test: No metadata, lid=0x00 which is the "No CPU" manual lens entry
TEST_F(Nikon3MakerNoteLensIdTest_476, NoMetadata_ManualLensNoCPU_476) {
  std::ostringstream os;
  auto value = makeUByteValue(0x00);
  Nikon3MakerNote::printLensId(os, *value, nullptr, "Nikon3");
  std::string result = os.str();
  // lid=0x00 matches "Manual Lens" "No CPU" as first match
  // The result should contain something (either the lens name or parenthesized value)
  EXPECT_FALSE(result.empty());
}

// Test: With metadata, TC-16A teleconverter
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_TC16A_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // TC-16A: lid=0x01, stps=0x00, focs=0x00, focl=0x00,
  // aps=0x00, apl=0x00, lfw=0x02, ltype=0x00
  setupLensMetadata(exifData, group, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
                    0x00);

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("TC-16A"), std::string::npos);
}

// Test: With metadata, AF Nikkor 50mm f/1.8D
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_AFNikkor50mmF18D_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // AF Nikkor 50mm f/1.8D:
  // lid=0x76, stps=0x58, focs=0x50, focl=0x50,
  // aps=0x14, apl=0x14, lfw=0x7A, ltype=0x02
  setupLensMetadata(exifData, group, 0x76, 0x58, 0x50, 0x50, 0x14, 0x14, 0x7A,
                    0x02);

  auto value = makeUByteValue(0x76);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  EXPECT_NE(result.find("Nikon"), std::string::npos);
  EXPECT_NE(result.find("AF Nikkor 50mm f/1.8D"), std::string::npos);
}

// Test: Stream returns reference to itself
TEST_F(Nikon3MakerNoteLensIdTest_476, StreamReturnsSelf_476) {
  std::ostringstream os;
  auto value = makeUByteValue(0x01);
  auto& result = Nikon3MakerNote::printLensId(os, *value, nullptr, "Nikon3");
  EXPECT_EQ(&result, &os);
}

// Test: With metadata, Sigma lens matching by lid but relaxed stps matching
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_SigmaRelaxedStps_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";

  // Sigma 35mm F1.4 DG HSM:
  // lid=0x91, stps=0x54, focs=0x44, focl=0x44,
  // aps=0x0C, apl=0x0C, lfw=0x4B, ltype=0x06
  // Sigma lenses have relaxed stps matching in the code
  setupLensMetadata(exifData, group, 0x91, 0x00, 0x44, 0x44, 0x0C, 0x0C, 0x4B,
                    0x06);

  auto value = makeUByteValue(0x91);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Sigma lenses ignore stps mismatch, so should still match
  EXPECT_NE(result.find("Sigma"), std::string::npos);
  EXPECT_NE(result.find("35mm F1.4 DG HSM"), std::string::npos);
}

// Test: With metadata missing LensType key
TEST_F(Nikon3MakerNoteLensIdTest_476, WithMetadata_MissingLensType_476) {
  std::ostringstream os;
  ExifData exifData;
  std::string group = "NikonLd1";
  std::string prefix = std::string("Exif.") + group + ".";

  // Add all 7 required keys but skip LensType
  const uint8_t values[] = {0x01, 0x58, 0x50, 0x50, 0x14, 0x14, 0x02};
  const char* tags[] = {"LensIDNumber",        "LensFStops",
                        "MinFocalLength",      "MaxFocalLength",
                        "MaxApertureAtMinFocal", "MaxApertureAtMaxFocal",
                        "MCUVersion"};

  for (int i = 0; i < 7; i++) {
    ExifKey key(prefix + tags[i]);
    auto val = Value::create(unsignedByte);
    byte b = values[i];
    val->read(&b, 1, littleEndian);
    exifData.add(key, val.get());
  }

  auto value = makeUByteValue(0x01);
  Nikon3MakerNote::printLensId(os, *value, &exifData, group);
  std::string result = os.str();
  // Missing LensType should cause fallback
  EXPECT_NE(result.find("("), std::string::npos);
}
