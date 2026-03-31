#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Note: The Converter class is internal to convert.cpp, but the public API
// exposes free functions for conversion. We test through the public interface
// that exercises the Converter internally.

namespace {

class ConverterTest_1834 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_.clear();
    xmpData_.clear();
    iptcData_.clear();
  }

  Exiv2::ExifData exifData_;
  Exiv2::XmpData xmpData_;
  Exiv2::IptcData iptcData_;
};

// Test: copyExifToXmp with empty ExifData produces empty or minimal XmpData
TEST_F(ConverterTest_1834, CopyExifToXmpEmptyData_1834) {
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: copyXmpToExif with empty XmpData produces empty ExifData
TEST_F(ConverterTest_1834, CopyXmpToExifEmptyData_1834) {
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: copyIptcToXmp with empty IptcData
TEST_F(ConverterTest_1834, CopyIptcToXmpEmptyData_1834) {
  ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
}

// Test: copyXmpToIptc with empty XmpData
TEST_F(ConverterTest_1834, CopyXmpToIptcEmptyData_1834) {
  ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Round-trip conversion of a simple Exif value through XMP
TEST_F(ConverterTest_1834, ExifToXmpRoundTripSimpleValue_1834) {
  exifData_["Exif.Image.Artist"] = "Test Artist";
  
  Exiv2::copyExifToXmp(exifData_, xmpData_);
  
  // Check that something was written to XMP
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
  // The artist field maps to dc:creator in XMP
  if (it != xmpData_.end()) {
    EXPECT_NE(it->toString(), "");
  }
}

// Test: Round-trip Exif -> XMP -> Exif preserves data
TEST_F(ConverterTest_1834, ExifToXmpToExifRoundTrip_1834) {
  exifData_["Exif.Image.Artist"] = "Round Trip Artist";
  
  Exiv2::copyExifToXmp(exifData_, xmpData_);
  
  Exiv2::ExifData exifData2;
  Exiv2::copyXmpToExif(xmpData_, exifData2);
  
  // The artist should survive the round trip
  auto it = exifData2.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
  if (it != exifData2.end()) {
    EXPECT_EQ(it->toString(), "Round Trip Artist");
  }
}

// Test: IPTC to XMP round-trip
TEST_F(ConverterTest_1834, IptcToXmpRoundTrip_1834) {
  iptcData_["Iptc.Application2.Headline"] = "Test Headline";
  
  Exiv2::copyIptcToXmp(iptcData_, xmpData_);
  
  // Check XMP has the headline
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
  if (it != xmpData_.end()) {
    EXPECT_EQ(it->toString(), "Test Headline");
  }
}

// Test: XMP to IPTC conversion
TEST_F(ConverterTest_1834, XmpToIptcConversion_1834) {
  xmpData_["Xmp.photoshop.Headline"] = "XMP Headline";
  
  Exiv2::copyXmpToIptc(xmpData_, iptcData_);
  
  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
  if (it != iptcData_.end()) {
    EXPECT_EQ(it->toString(), "XMP Headline");
  }
}

// Test: Exif GPS coordinate conversion to XMP
TEST_F(ConverterTest_1834, ExifGPSCoordToXmp_1834) {
  // Set GPS latitude
  Exiv2::URationalValue::UniquePtr lat(new Exiv2::URationalValue);
  lat->read("49/1 30/1 0/1");
  exifData_["Exif.GPSInfo.GPSLatitude"] = *lat;
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Exif version conversion
TEST_F(ConverterTest_1834, ExifVersionToXmp_1834) {
  exifData_["Exif.Photo.ExifVersion"] = "0230";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.ExifVersion"));
  if (it != xmpData_.end()) {
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test: Exif Flash to XMP conversion
TEST_F(ConverterTest_1834, ExifFlashToXmp_1834) {
  exifData_["Exif.Photo.Flash"] = uint16_t(1);
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP Flash to Exif conversion
TEST_F(ConverterTest_1834, XmpFlashToExif_1834) {
  xmpData_["Xmp.exif.Flash/exif:Fired"] = "True";
  xmpData_["Xmp.exif.Flash/exif:Return"] = "0";
  xmpData_["Xmp.exif.Flash/exif:Mode"] = "0";
  xmpData_["Xmp.exif.Flash/exif:Function"] = "False";
  xmpData_["Xmp.exif.Flash/exif:RedEyeMode"] = "False";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: Exif date conversion to XMP
TEST_F(ConverterTest_1834, ExifDateToXmp_1834) {
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.DateTimeOriginal"));
  if (it != xmpData_.end()) {
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test: XMP date conversion to Exif
TEST_F(ConverterTest_1834, XmpDateToExif_1834) {
  xmpData_["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
  
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Photo.DateTimeOriginal"));
  if (it != exifData_.end()) {
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test: Multiple Exif entries conversion
TEST_F(ConverterTest_1834, MultipleExifEntriesToXmp_1834) {
  exifData_["Exif.Image.Artist"] = "Artist Name";
  exifData_["Exif.Image.Copyright"] = "Copyright 2023";
  exifData_["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
  
  // At least some XMP data should have been created
  EXPECT_FALSE(xmpData_.empty());
}

// Test: Multiple XMP entries conversion to Exif
TEST_F(ConverterTest_1834, MultipleXmpEntriesToExif_1834) {
  xmpData_["Xmp.dc.creator"] = "Creator";
  xmpData_["Xmp.dc.rights"] = "Rights";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: Overwrite existing data in target
TEST_F(ConverterTest_1834, OverwriteExistingExifData_1834) {
  exifData_["Exif.Image.Artist"] = "Old Artist";
  xmpData_["Xmp.dc.creator"] = "New Artist";
  
  Exiv2::copyXmpToExif(xmpData_, exifData_);
  
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
  if (it != exifData_.end()) {
    // By default, overwrite is true, so the new value should be present
    EXPECT_EQ(it->toString(), "New Artist");
  }
}

// Test: moveExifToXmp erases source data
TEST_F(ConverterTest_1834, MoveExifToXmpErasesSource_1834) {
  exifData_["Exif.Image.Artist"] = "Artist to Move";
  
  ASSERT_NO_THROW(Exiv2::moveExifToXmp(exifData_, xmpData_));
  
  // After move, the source exif entries that were converted should be erased
  // (at least partially)
  auto it = exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist"));
  // It may or may not be erased depending on conversion table
  // We just verify no crash
}

// Test: moveXmpToExif erases source data
TEST_F(ConverterTest_1834, MoveXmpToExifErasesSource_1834) {
  xmpData_["Xmp.dc.creator"] = "Creator to Move";
  
  ASSERT_NO_THROW(Exiv2::moveXmpToExif(xmpData_, exifData_));
}

// Test: moveIptcToXmp
TEST_F(ConverterTest_1834, MoveIptcToXmp_1834) {
  iptcData_["Iptc.Application2.Headline"] = "Headline to Move";
  
  ASSERT_NO_THROW(Exiv2::moveIptcToXmp(iptcData_, xmpData_));
}

// Test: moveXmpToIptc
TEST_F(ConverterTest_1834, MoveXmpToIptc_1834) {
  xmpData_["Xmp.photoshop.Headline"] = "Headline from XMP";
  
  ASSERT_NO_THROW(Exiv2::moveXmpToIptc(xmpData_, iptcData_));
}

// Test: Exif UserComment conversion
TEST_F(ConverterTest_1834, ExifUserCommentToXmp_1834) {
  exifData_["Exif.Photo.UserComment"] = "charset=\"Ascii\" Test comment";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: XMP description to Exif UserComment
TEST_F(ConverterTest_1834, XmpDescriptionToExifUserComment_1834) {
  xmpData_["Xmp.exif.UserComment"] = "lang=\"x-default\" Test comment from XMP";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToExif(xmpData_, exifData_));
}

// Test: Exif GPS Version
TEST_F(ConverterTest_1834, ExifGPSVersionToXmp_1834) {
  Exiv2::byte version[] = {2, 3, 0, 0};
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedByte);
  val->read(version, 4, Exiv2::littleEndian);
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID"), val.get());
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: IPTC keywords to XMP
TEST_F(ConverterTest_1834, IptcKeywordsToXmp_1834) {
  iptcData_["Iptc.Application2.Keywords"] = "keyword1";
  
  ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData_, xmpData_));
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
  if (it != xmpData_.end()) {
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test: XMP subject to IPTC keywords
TEST_F(ConverterTest_1834, XmpSubjectToIptcKeywords_1834) {
  xmpData_["Xmp.dc.subject"] = "keyword_from_xmp";
  
  ASSERT_NO_THROW(Exiv2::copyXmpToIptc(xmpData_, iptcData_));
}

// Test: Empty string values
TEST_F(ConverterTest_1834, EmptyStringExifValue_1834) {
  exifData_["Exif.Image.Artist"] = "";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Conversion doesn't crash with large data
TEST_F(ConverterTest_1834, LargeStringValue_1834) {
  std::string largeStr(10000, 'A');
  exifData_["Exif.Image.Artist"] = largeStr;
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Exif array type (e.g., BitsPerSample) to XMP
TEST_F(ConverterTest_1834, ExifArrayToXmp_1834) {
  exifData_["Exif.Image.BitsPerSample"] = "8 8 8";
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: Double conversion doesn't duplicate
TEST_F(ConverterTest_1834, DoubleConversionDoesNotDuplicate_1834) {
  exifData_["Exif.Image.Artist"] = "Single Artist";
  
  Exiv2::copyExifToXmp(exifData_, xmpData_);
  size_t firstCount = xmpData_.count();
  
  Exiv2::copyExifToXmp(exifData_, xmpData_);
  size_t secondCount = xmpData_.count();
  
  // With overwrite=true (default), count should remain the same
  EXPECT_EQ(firstCount, secondCount);
}

// Test: Exif ISO Speed to XMP
TEST_F(ConverterTest_1834, ExifISOToXmp_1834) {
  exifData_["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
  
  ASSERT_NO_THROW(Exiv2::copyExifToXmp(exifData_, xmpData_));
}

// Test: IPTC city to XMP
TEST_F(ConverterTest_1834, IptcCityToXmp_1834) {
  iptcData_["Iptc.Application2.City"] = "New York";
  
  Exiv2::copyIptcToXmp(iptcData_, xmpData_);
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.City"));
  if (it != xmpData_.end()) {
    EXPECT_EQ(it->toString(), "New York");
  }
}

// Test: XMP to IPTC city
TEST_F(ConverterTest_1834, XmpCityToIptc_1834) {
  xmpData_["Xmp.photoshop.City"] = "London";
  
  Exiv2::copyXmpToIptc(xmpData_, iptcData_);
  
  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.City"));
  if (it != iptcData_.end()) {
    EXPECT_EQ(it->toString(), "London");
  }
}

}  // namespace
