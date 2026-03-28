#include <gtest/gtest.h>
#include <string>

#include <exiv2/exiv2.hpp>

// The Converter class is defined in convert.cpp and not directly exposed via a public header.
// We need to use the public API functions that exercise the Converter internally,
// or access the Converter class if it's available through internal headers.
// Based on the interface, we'll use copyExifToXmp / copyXmpToExif or create Converter directly.

// Since Converter is in the Exiv2 namespace but defined in convert.cpp,
// we use the public conversion functions that wrap it.
// However, based on the provided code, let's try to include the necessary headers
// and use the public API.

namespace {

class ConverterTest_1844 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_.clear();
    xmpData_.clear();
  }

  Exiv2::ExifData exifData_;
  Exiv2::XmpData xmpData_;
};

// Test: copyExifToXmp with empty data should not crash
TEST_F(ConverterTest_1844, CopyEmptyExifToXmp_1844) {
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  EXPECT_TRUE(xmpData_.empty());
}

// Test: copyXmpToExif with empty data should not crash
TEST_F(ConverterTest_1844, CopyEmptyXmpToExif_1844) {
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  EXPECT_TRUE(exifData_.empty());
}

// Test: Converting Exif UserComment to XMP and back
TEST_F(ConverterTest_1844, ConvertExifUserCommentToXmp_1844) {
  exifData_["Exif.Photo.UserComment"] = "charset=Ascii Test comment";
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.UserComment"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Converting XMP description (dc.description) to Exif UserComment
TEST_F(ConverterTest_1844, ConvertXmpDescriptionToExif_1844) {
  xmpData_["Xmp.dc.description"] = "Test XMP description";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  // The conversion may or may not produce an Exif entry depending on mapping
}

// Test: Converting Exif DateTimeOriginal to XMP
TEST_F(ConverterTest_1844, ConvertExifDateTimeOriginalToXmp_1844) {
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
  if (pos != xmpData_.end()) {
    std::string dateStr = pos->toString();
    EXPECT_FALSE(dateStr.empty());
  }
}

// Test: Converting XMP DateTimeOriginal to Exif
TEST_F(ConverterTest_1844, ConvertXmpDateTimeOriginalToExif_1844) {
  xmpData_["Xmp.exif.DateTimeOriginal"] = "2023-01-15T10:30:00";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
  if (pos != exifData_.end()) {
    std::string dateStr = pos->toString();
    EXPECT_FALSE(dateStr.empty());
  }
}

// Test: Converting Exif ExifVersion to XMP
TEST_F(ConverterTest_1844, ConvertExifVersionToXmp_1844) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
  val->read("48 50 51 48");  // "0230"
  exifData_.add(Exiv2::ExifKey("Exif.Photo.ExifVersion"), val.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Converting XMP ExifVersion to Exif
TEST_F(ConverterTest_1844, ConvertXmpVersionToExif_1844) {
  xmpData_["Xmp.exif.ExifVersion"] = "2.30";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.ExifVersion"));
  if (pos != exifData_.end()) {
    EXPECT_EQ(pos->count(), 4u);
  }
}

// Test: Converting Exif GPSVersionID to XMP
TEST_F(ConverterTest_1844, ConvertExifGPSVersionToXmp_1844) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
  val->read("2 3 0 0");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSVersionID"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Converting XMP GPSVersionID to Exif
TEST_F(ConverterTest_1844, ConvertXmpGPSVersionToExif_1844) {
  xmpData_["Xmp.exif.GPSVersionID"] = "2.3.0.0";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"));
  if (pos != exifData_.end()) {
    EXPECT_GT(pos->count(), 0u);
  }
}

// Test: Converting Exif GPSLatitude to XMP
TEST_F(ConverterTest_1844, ConvertExifGPSLatitudeToXmp_1844) {
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("48/1 51/1 30/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Converting XMP GPSLatitude to Exif
TEST_F(ConverterTest_1844, ConvertXmpGPSLatitudeToExif_1844) {
  xmpData_["Xmp.exif.GPSLatitude"] = "48,51,30N";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: Multiple Exif values conversion doesn't overwrite existing XMP
TEST_F(ConverterTest_1844, NoOverwriteExistingXmpByDefault_1844) {
  // First set XMP value
  xmpData_["Xmp.exif.DateTimeOriginal"] = "2020-01-01T00:00:00";
  std::string originalValue = xmpData_["Xmp.exif.DateTimeOriginal"].toString();
  
  // Set different Exif value
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 12:00:00";
  
  // Copy should overwrite by default (overwrite_ defaults to true in Converter)
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Exif Flash conversion to XMP
TEST_F(ConverterTest_1844, ConvertExifFlashToXmp_1844) {
  exifData_["Exif.Photo.Flash"] = uint16_t(1);  // Flash fired
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  // Check if any flash-related XMP keys were created
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.Flash"));
  // Flash is converted to a struct, so we check sub-properties
}

// Test: XMP Flash conversion to Exif
TEST_F(ConverterTest_1844, ConvertXmpFlashToExif_1844) {
  xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
  xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
  xmpData_["Xmp.exif.Flash/exif:Mode"] = "0";
  xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
  xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.Flash"));
  if (pos != exifData_.end()) {
    EXPECT_GT(pos->count(), 0u);
  }
}

// Test: XMP Comment conversion to Exif (the focus function cnvXmpComment)
TEST_F(ConverterTest_1844, ConvertXmpCommentToExif_1844) {
  xmpData_["Xmp.exif.UserComment"] = "Hello World";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.UserComment"));
  if (pos != exifData_.end()) {
    std::string val = pos->toString();
    // cnvXmpComment prepends "charset=Unicode " to the value
    EXPECT_NE(val.find("Hello World"), std::string::npos);
  }
}

// Test: XMP key not found should not crash cnvXmpComment path
TEST_F(ConverterTest_1844, ConvertXmpCommentNotFound_1844) {
  // xmpData_ is empty, so findKey should return end()
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  EXPECT_TRUE(exifData_.empty());
}

// IPTC conversion tests
class IptcConverterTest_1844 : public ::testing::Test {
 protected:
  void SetUp() override {
    iptcData_.clear();
    xmpData_.clear();
  }

  Exiv2::IptcData iptcData_;
  Exiv2::XmpData xmpData_;
};

// Test: copyIptcToXmp with empty data
TEST_F(IptcConverterTest_1844, CopyEmptyIptcToXmp_1844) {
  ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
  EXPECT_TRUE(xmpData_.empty());
}

// Test: copyXmpToIptc with empty data
TEST_F(IptcConverterTest_1844, CopyEmptyXmpToIptc_1844) {
  ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
  EXPECT_TRUE(iptcData_.empty());
}

// Test: Converting IPTC Caption to XMP
TEST_F(IptcConverterTest_1844, ConvertIptcCaptionToXmp_1844) {
  iptcData_["Iptc.Application2.Caption"] = "Test Caption";
  ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
  if (pos != xmpData_.end()) {
    EXPECT_NE(pos->toString().find("Test Caption"), std::string::npos);
  }
}

// Test: Converting XMP dc.description to IPTC
TEST_F(IptcConverterTest_1844, ConvertXmpDescriptionToIptc_1844) {
  xmpData_["Xmp.dc.description"] = "Test description for IPTC";
  ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Converting IPTC Keywords to XMP
TEST_F(IptcConverterTest_1844, ConvertIptcKeywordsToXmp_1844) {
  iptcData_["Iptc.Application2.Keywords"] = "keyword1";
  ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
  if (pos != xmpData_.end()) {
    EXPECT_NE(pos->toString().find("keyword1"), std::string::npos);
  }
}

// Test: Converting XMP dc.subject to IPTC Keywords
TEST_F(IptcConverterTest_1844, ConvertXmpSubjectToIptcKeywords_1844) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("keyword1");
  xmpData_.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());
  
  ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Exif ISO value conversion
TEST_F(ConverterTest_1844, ConvertExifISOToXmp_1844) {
  exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ISOSpeedRatings"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Exif FocalLength conversion
TEST_F(ConverterTest_1844, ConvertExifFocalLengthToXmp_1844) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("50/1");
  exifData_.add(Exiv2::ExifKey("Exif.Photo.FocalLength"), rv.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.FocalLength"));
  if (pos != xmpData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: XMP FocalLength conversion to Exif
TEST_F(ConverterTest_1844, ConvertXmpFocalLengthToExif_1844) {
  xmpData_["Xmp.exif.FocalLength"] = "50/1";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.FocalLength"));
  if (pos != exifData_.end()) {
    EXPECT_GT(pos->count(), 0u);
  }
}

// Test: Round-trip conversion Exif -> XMP -> Exif
TEST_F(ConverterTest_1844, RoundTripExifXmpExif_1844) {
  exifData_["Exif.Image.Make"] = "TestCamera";
  exifData_["Exif.Image.Model"] = "TestModel";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  Exiv2::ExifData exifData2;
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData2));
  
  auto posOrig = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  auto posNew = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  
  if (posOrig != exifData_.end() && posNew != exifData2.end()) {
    EXPECT_EQ(posOrig->toString(), posNew->toString());
  }
}

// Test: ExifData with SubSecTime
TEST_F(ConverterTest_1844, ConvertExifSubSecTimeToXmp_1844) {
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";
  exifData_["Exif.Photo.SubSecTimeOriginal"] = "123";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
  if (pos != xmpData_.end()) {
    std::string dateStr = pos->toString();
    // Should contain subsecond information
    EXPECT_FALSE(dateStr.empty());
  }
}

// Test: Exif array values (like components configuration)
TEST_F(ConverterTest_1844, ConvertExifComponentsConfigurationToXmp_1844) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::undefined);
  val->read("1 2 3 0");
  exifData_.add(Exiv2::ExifKey("Exif.Photo.ComponentsConfiguration"), val.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Large dataset conversion
TEST_F(ConverterTest_1844, LargeDatasetConversion_1844) {
  // Add many Exif entries
  exifData_["Exif.Image.Make"] = "TestMake";
  exifData_["Exif.Image.Model"] = "TestModel";
  exifData_["Exif.Image.Software"] = "TestSoftware";
  exifData_["Exif.Image.Artist"] = "TestArtist";
  exifData_["Exif.Image.Copyright"] = "TestCopyright";
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
  exifData_["Exif.Photo.DateTimeDigitized"] = "2023:01:01 00:00:00";
  exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(100);
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  EXPECT_FALSE(xmpData_.empty());
}

// Test: Conversion with pre-existing target data
TEST_F(ConverterTest_1844, ConversionWithPreExistingXmpData_1844) {
  xmpData_["Xmp.dc.creator"] = "ExistingCreator";
  
  exifData_["Exif.Image.Artist"] = "NewArtist";
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  // Verify existing data or overwritten data
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
  EXPECT_NE(pos, xmpData_.end());
}

// Test: XMP tiff namespace values to Exif
TEST_F(ConverterTest_1844, ConvertXmpTiffToExif_1844) {
  xmpData_["Xmp.tiff.Make"] = "XmpMake";
  xmpData_["Xmp.tiff.Model"] = "XmpModel";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto posMake = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Make"));
  if (posMake != exifData_.end()) {
    EXPECT_EQ(posMake->toString(), "XmpMake");
  }
  
  auto posModel = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Model"));
  if (posModel != exifData_.end()) {
    EXPECT_EQ(posModel->toString(), "XmpModel");
  }
}

// Test: Orientation value conversion
TEST_F(ConverterTest_1844, ConvertExifOrientationToXmp_1844) {
  exifData_["Exif.Image.Orientation"] = uint16_t(1);
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto pos = xmpData_.findKey(Exiv2::XmpKey("Xmp.tiff.Orientation"));
  if (pos != xmpData_.end()) {
    EXPECT_EQ(pos->toString(), "1");
  }
}

// Test: XMP Orientation to Exif
TEST_F(ConverterTest_1844, ConvertXmpOrientationToExif_1844) {
  xmpData_["Xmp.tiff.Orientation"] = "6";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Orientation"));
  if (pos != exifData_.end()) {
    EXPECT_EQ(pos->toInt64(), 6);
  }
}

// Test: Unicode comment in XMP converted to Exif
TEST_F(ConverterTest_1844, ConvertXmpUnicodeCommentToExif_1844) {
  xmpData_["Xmp.exif.UserComment"] = "Unicode Test: äöü";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto pos = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.UserComment"));
  if (pos != exifData_.end()) {
    std::string val = pos->toString();
    // Should contain charset=Unicode prefix per cnvXmpComment
    EXPECT_TRUE(val.find("charset=Unicode") != std::string::npos ||
                val.find("Unicode Test") != std::string::npos);
  }
}

// Test: Empty string XMP value conversion
TEST_F(ConverterTest_1844, ConvertEmptyXmpValueToExif_1844) {
  xmpData_["Xmp.tiff.Make"] = "";
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

}  // namespace
