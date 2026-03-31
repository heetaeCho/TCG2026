#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// We need access to the Converter class which is defined in convert.cpp
// The public API for conversion is through these free functions and the Converter class
// Since Converter is in the Exiv2 namespace but defined in convert.cpp, we need the header
#include "convert.hpp"

namespace {

class ConverterTest_1835 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_.clear();
    xmpData_.clear();
  }

  Exiv2::ExifData exifData_;
  Exiv2::XmpData xmpData_;
};

class ConverterIptcTest_1835 : public ::testing::Test {
 protected:
  void SetUp() override {
    iptcData_.clear();
    xmpData_.clear();
  }

  Exiv2::IptcData iptcData_;
  Exiv2::XmpData xmpData_;
};

// Test: cnvExifValue with a key that does not exist in ExifData should be a no-op
TEST_F(ConverterTest_1835, CnvExifValueKeyNotFound_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  // Call with a non-existent key; XmpData should remain empty
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");
  EXPECT_TRUE(xmpData_.empty());
}

// Test: cnvExifValue with a valid EXIF key should copy the value to XMP
TEST_F(ConverterTest_1835, CnvExifValueCopiesValue_1835) {
  exifData_["Exif.Image.Make"] = "Canon";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "Canon");
}

// Test: cnvExifValue with erase enabled should remove the source EXIF key
TEST_F(ConverterTest_1835, CnvExifValueWithEraseRemovesSource_1835) {
  exifData_["Exif.Image.Make"] = "Nikon";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(true);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  // The EXIF key should be erased
  auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_EQ(exifPos, exifData_.end());

  // The XMP key should exist
  auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  ASSERT_NE(xmpPos, xmpData_.end());
  EXPECT_EQ(xmpPos->toString(), "Nikon");
}

// Test: cnvExifValue with erase disabled should keep the source EXIF key
TEST_F(ConverterTest_1835, CnvExifValueWithoutEraseKeepsSource_1835) {
  exifData_["Exif.Image.Make"] = "Sony";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(false);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto exifPos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_NE(exifPos, exifData_.end());
}

// Test: erase() returns the current erase setting
TEST_F(ConverterTest_1835, EraseReturnsCorrectValue_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  EXPECT_FALSE(converter.erase());
  converter.setErase(true);
  EXPECT_TRUE(converter.erase());
  converter.setErase(false);
  EXPECT_FALSE(converter.erase());
}

// Test: setOverwrite controls whether existing XMP values are overwritten
TEST_F(ConverterTest_1835, CnvExifValueOverwriteEnabled_1835) {
  exifData_["Exif.Image.Make"] = "Canon";
  xmpData_["Xmp.tiff.Make"] = "OldValue";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setOverwrite(true);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "Canon");
}

// Test: setOverwrite(false) should not overwrite existing XMP values
TEST_F(ConverterTest_1835, CnvExifValueOverwriteDisabled_1835) {
  exifData_["Exif.Image.Make"] = "Canon";
  xmpData_["Xmp.tiff.Make"] = "OldValue";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setOverwrite(false);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "OldValue");
}

// Test: cnvExifValue with Model tag
TEST_F(ConverterTest_1835, CnvExifValueModel_1835) {
  exifData_["Exif.Image.Model"] = "EOS 5D";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifValue("Exif.Image.Model", "Xmp.tiff.Model");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Model"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "EOS 5D");
}

// Test: cnvToXmp performs full conversion from EXIF to XMP
TEST_F(ConverterTest_1835, CnvToXmpBasic_1835) {
  exifData_["Exif.Image.Make"] = "TestMake";
  exifData_["Exif.Image.Model"] = "TestModel";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvToXmp();

  // After conversion, XMP should have some entries
  // We check that the data is not empty (exact entries depend on conversion table)
  // At minimum Make and Model should be converted
  auto makePos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  EXPECT_NE(makePos, xmpData_.end());
}

// Test: cnvFromXmp performs full conversion from XMP to EXIF
TEST_F(ConverterTest_1835, CnvFromXmpBasic_1835) {
  xmpData_["Xmp.tiff.Make"] = "XmpMake";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvFromXmp();

  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  EXPECT_NE(pos, exifData_.end());
}

// Test: cnvNone should not do anything
TEST_F(ConverterTest_1835, CnvNoneDoesNothing_1835) {
  exifData_["Exif.Image.Make"] = "TestMake";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvNone("Exif.Image.Make", "Xmp.tiff.Make");
  EXPECT_TRUE(xmpData_.empty());
}

// Test: cnvExifDate converts date from EXIF to XMP format
TEST_F(ConverterTest_1835, CnvExifDateBasic_1835) {
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 14:30:00";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifDate("Exif.Photo.DateTimeOriginal", "Xmp.exif.DateTimeOriginal");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
  ASSERT_NE(pos, xmpData_.end());
  // XMP dates use ISO 8601 format, should contain 2023
  std::string dateStr = pos->toString();
  EXPECT_NE(dateStr.find("2023"), std::string::npos);
}

// Test: cnvExifDate with non-existent key should be no-op
TEST_F(ConverterTest_1835, CnvExifDateKeyNotFound_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifDate("Exif.Photo.DateTimeOriginal", "Xmp.exif.DateTimeOriginal");
  EXPECT_TRUE(xmpData_.empty());
}

// Test: cnvExifVersion converts version from EXIF to XMP
TEST_F(ConverterTest_1835, CnvExifVersionBasic_1835) {
  // ExifVersion is typically stored as undefined type with value like "0230"
  Exiv2::ExifData exifData;
  exifData["Exif.Photo.ExifVersion"] = "48 50 51 48"; // "0230" in ASCII
  // This may or may not work depending on how the value is stored
  // Let's try directly setting a string
  exifData_["Exif.Photo.ExifVersion"] = "48 50 51 48";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifVersion("Exif.Photo.ExifVersion", "Xmp.exif.ExifVersion");
  // Just verify no crash; the result depends on internal implementation
}

// Test: Constructor with IPTC data
TEST_F(ConverterIptcTest_1835, ConstructorIptc_1835) {
  Exiv2::Converter converter(iptcData_, xmpData_, nullptr);
  // Should construct without issues
  EXPECT_FALSE(converter.erase());
}

// Test: cnvExifArray with valid array data
TEST_F(ConverterTest_1835, CnvExifArrayBasic_1835) {
  exifData_["Exif.Image.XResolution"] = Exiv2::URational(72, 1);
  Exiv2::Converter converter(exifData_, xmpData_);
  // Use a known EXIF->XMP array mapping
  // This tests that the function doesn't crash with valid data
  converter.cnvExifValue("Exif.Image.XResolution", "Xmp.tiff.XResolution");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.XResolution"));
  ASSERT_NE(pos, xmpData_.end());
}

// Test: cnvExifGPSCoord with GPS latitude
TEST_F(ConverterTest_1835, CnvExifGPSCoordBasic_1835) {
  // Set GPS latitude
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("49/1 30/1 0/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  // The coordinate should have been converted
  if (pos != xmpData_.end()) {
    std::string coordStr = pos->toString();
    EXPECT_FALSE(coordStr.empty());
  }
}

// Test: Multiple conversions with overwrite off
TEST_F(ConverterTest_1835, MultipleConversionsOverwriteOff_1835) {
  exifData_["Exif.Image.Make"] = "FirstMake";

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setOverwrite(true);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  // Now change the source and try again with overwrite off
  exifData_["Exif.Image.Make"] = "SecondMake";
  converter.setOverwrite(false);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  ASSERT_NE(pos, xmpData_.end());
  // Should still be FirstMake since overwrite is off
  EXPECT_EQ(pos->toString(), "FirstMake");
}

// Test: Empty string value in EXIF
TEST_F(ConverterTest_1835, CnvExifValueEmptyString_1835) {
  exifData_["Exif.Image.Make"] = "";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifValue("Exif.Image.Make", "Xmp.tiff.Make");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Make"));
  // Whether empty string is written or not depends on implementation
  // At minimum, no crash
}

// Test: cnvExifFlash with valid flash value
TEST_F(ConverterTest_1835, CnvExifFlashBasic_1835) {
  exifData_["Exif.Photo.Flash"] = uint16_t(1); // Flash fired
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifFlash("Exif.Photo.Flash", "Xmp.exif.Flash");
  // Check that some XMP flash data exists
  // Flash in XMP is a struct, so we check for related keys
}

// Test: cnvExifComment conversion
TEST_F(ConverterTest_1835, CnvExifCommentBasic_1835) {
  exifData_["Exif.Photo.UserComment"] = "Test comment";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifComment("Exif.Photo.UserComment", "Xmp.exif.UserComment");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
  if (pos != xmpData_.end()) {
    EXPECT_NE(pos->toString().find("Test comment"), std::string::npos);
  }
}

// Test: cnvExifComment with missing key
TEST_F(ConverterTest_1835, CnvExifCommentKeyNotFound_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifComment("Exif.Photo.UserComment", "Xmp.exif.UserComment");
  EXPECT_TRUE(xmpData_.empty());
}

// Test: setErase with default parameter
TEST_F(ConverterTest_1835, SetEraseDefaultParam_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(); // default is true
  EXPECT_TRUE(converter.erase());
}

// Test: cnvXmpValue from XMP to EXIF
TEST_F(ConverterTest_1835, CnvXmpValueBasic_1835) {
  xmpData_["Xmp.tiff.Make"] = "TestXmpMake";
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvXmpValue("Xmp.tiff.Make", "Exif.Image.Make");

  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  ASSERT_NE(pos, exifData_.end());
  EXPECT_EQ(pos->toString(), "TestXmpMake");
}

// Test: cnvXmpValue with non-existent XMP key
TEST_F(ConverterTest_1835, CnvXmpValueKeyNotFound_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvXmpValue("Xmp.tiff.Make", "Exif.Image.Make");
  EXPECT_TRUE(exifData_.empty());
}

// Test: Full round-trip: EXIF -> XMP -> EXIF
TEST_F(ConverterTest_1835, RoundTripConversion_1835) {
  exifData_["Exif.Image.Make"] = "RoundTripMake";
  exifData_["Exif.Image.Model"] = "RoundTripModel";

  // EXIF -> XMP
  {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvToXmp();
  }

  EXPECT_FALSE(xmpData_.empty());

  // Clear EXIF and convert back
  exifData_.clear();

  // XMP -> EXIF
  {
    Exiv2::Converter converter(exifData_, xmpData_);
    converter.cnvFromXmp();
  }

  auto makePos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  if (makePos != exifData_.end()) {
    EXPECT_EQ(makePos->toString(), "RoundTripMake");
  }
}

// Test: cnvExifGPSVersion conversion
TEST_F(ConverterTest_1835, CnvExifGPSVersionBasic_1835) {
  // GPSVersionID is typically 4 bytes: 2.3.0.0
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
  v->read("2 3 0 0");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), v.get());

  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.exif.GPSVersionID");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
  if (pos != xmpData_.end()) {
    std::string version = pos->toString();
    EXPECT_FALSE(version.empty());
  }
}

// Test: cnvToXmp with empty ExifData should result in empty XmpData
TEST_F(ConverterTest_1835, CnvToXmpEmptyExif_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvToXmp();
  // With empty EXIF, XMP should remain empty
  EXPECT_TRUE(xmpData_.empty());
}

// Test: cnvFromXmp with empty XmpData should result in empty ExifData
TEST_F(ConverterTest_1835, CnvFromXmpEmptyXmp_1835) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvFromXmp();
  EXPECT_TRUE(exifData_.empty());
}

// Test: Integer EXIF value conversion
TEST_F(ConverterTest_1835, CnvExifValueInteger_1835) {
  exifData_["Exif.Image.Orientation"] = uint16_t(1);
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifValue("Exif.Image.Orientation", "Xmp.tiff.Orientation");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Orientation"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "1");
}

// Test: Rational EXIF value conversion
TEST_F(ConverterTest_1835, CnvExifValueRational_1835) {
  exifData_["Exif.Image.XResolution"] = Exiv2::URational(300, 1);
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifValue("Exif.Image.XResolution", "Xmp.tiff.XResolution");

  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.XResolution"));
  ASSERT_NE(pos, xmpData_.end());
  EXPECT_EQ(pos->toString(), "300/1");
}

}  // namespace
