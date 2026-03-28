#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// The Converter class is defined in convert.cpp and not directly exposed via a public header.
// We need to use the public API functions that wrap it, or access it through the internal header.
// Based on the codebase, we'll use the conversion functions and test cnvExifGPSCoord behavior
// through the Converter class.

// Forward declaration - Converter is in Exiv2 namespace but in convert.cpp
// We include the necessary headers and use the class directly.
#include "convert.hpp"

namespace {

class ConverterGPSCoordTest_1842 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_.clear();
    xmpData_.clear();
  }

  Exiv2::ExifData exifData_;
  Exiv2::XmpData xmpData_;
};

// Test: Key not found in exifData - should return without modifying xmpData
TEST_F(ConverterGPSCoordTest_1842, KeyNotFound_NoConversion_1842) {
  Exiv2::Converter converter(exifData_, xmpData_);
  
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

// Test: Normal latitude conversion (North)
TEST_F(ConverterGPSCoordTest_1842, NormalLatitudeNorth_1842) {
  // Set GPS Latitude: 40 degrees, 26 minutes, 46 seconds
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  // Set GPS Latitude Ref
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  // Should contain "N" for north
  EXPECT_NE(result.find('N'), std::string::npos);
}

// Test: Normal longitude conversion (West)
TEST_F(ConverterGPSCoordTest_1842, NormalLongitudeWest_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("74/1 0/1 21/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"), rv.get());
  
  exifData_["Exif.GPSInfo.GPSLongitudeRef"] = "W";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLongitude", "Xmp.exif.GPSLongitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLongitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  EXPECT_NE(result.find('W'), std::string::npos);
}

// Test: Normal latitude conversion (South)
TEST_F(ConverterGPSCoordTest_1842, NormalLatitudeSouth_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("33/1 51/1 54/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "S";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  EXPECT_NE(result.find('S'), std::string::npos);
}

// Test: Count is not 3 - should not convert
TEST_F(ConverterGPSCoordTest_1842, CountNotThree_NoConversion_1842) {
  // Add latitude with only 2 components
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

// Test: Missing Ref key - should not convert
TEST_F(ConverterGPSCoordTest_1842, MissingRefKey_NoConversion_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  // Do NOT add GPSLatitudeRef
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

// Test: Zero denominator in one of the rational values - should not convert
TEST_F(ConverterGPSCoordTest_1842, ZeroDenominator_NoConversion_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/0 46/1");  // second component has 0 denominator
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

// Test: Erase mode - source data should be erased after conversion
TEST_F(ConverterGPSCoordTest_1842, EraseMode_SourceErased_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(true);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  // XMP data should be set
  auto xmpIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(xmpIt, xmpData_.end());
  
  // Exif data should be erased
  auto exifIt = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
  EXPECT_EQ(exifIt, exifData_.end());
  
  auto refIt = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
  EXPECT_EQ(refIt, exifData_.end());
}

// Test: No erase mode - source data should remain after conversion
TEST_F(ConverterGPSCoordTest_1842, NoEraseMode_SourceRemains_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(false);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  // XMP data should be set
  auto xmpIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(xmpIt, xmpData_.end());
  
  // Exif data should still exist
  auto exifIt = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"));
  EXPECT_NE(exifIt, exifData_.end());
  
  auto refIt = exifData_.findKey(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef"));
  EXPECT_NE(refIt, exifData_.end());
}

// Test: Overwrite off, target already exists - should not overwrite
TEST_F(ConverterGPSCoordTest_1842, OverwriteOff_ExistingTargetNotOverwritten_1842) {
  // Pre-populate xmp target
  xmpData_["Xmp.exif.GPSLatitude"] = "existing_value";
  
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setOverwrite(false);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  // The value should remain as original since overwrite is off
  EXPECT_EQ(it->toString(), "existing_value");
}

// Test: Zero degrees, minutes, seconds
TEST_F(ConverterGPSCoordTest_1842, ZeroCoordinates_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("0/1 0/1 0/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  // Should contain 0 and N
  EXPECT_NE(result.find('N'), std::string::npos);
  EXPECT_NE(result.find('0'), std::string::npos);
}

// Test: Fractional seconds (high precision rational values)
TEST_F(ConverterGPSCoordTest_1842, FractionalSeconds_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("51/1 30/1 2636/100");  // 51°30'26.36"
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  EXPECT_NE(result.find('N'), std::string::npos);
  // Should contain "51" for degrees
  EXPECT_NE(result.find("51"), std::string::npos);
}

// Test: Longitude East
TEST_F(ConverterGPSCoordTest_1842, LongitudeEast_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("151/1 12/1 30/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLongitudeRef"] = "E";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLongitude", "Xmp.exif.GPSLongitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLongitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  EXPECT_NE(result.find('E'), std::string::npos);
}

// Test: XMP result format contains comma separator
TEST_F(ConverterGPSCoordTest_1842, ResultFormatContainsComma_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  ASSERT_NE(it, xmpData_.end());
  
  std::string result = it->toString();
  // Format is "{degrees},{minutes}[NSEW]"
  EXPECT_NE(result.find(','), std::string::npos);
}

// Test: Erase getter returns correct value
TEST_F(ConverterGPSCoordTest_1842, EraseGetterDefault_1842) {
  Exiv2::Converter converter(exifData_, xmpData_);
  EXPECT_FALSE(converter.erase());
}

// Test: Erase getter after setErase(true)
TEST_F(ConverterGPSCoordTest_1842, EraseGetterAfterSet_1842) {
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.setErase(true);
  EXPECT_TRUE(converter.erase());
}

// Test: Zero denominator in first component
TEST_F(ConverterGPSCoordTest_1842, ZeroDenominatorFirstComponent_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/0 26/1 46/1");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

// Test: Zero denominator in third component
TEST_F(ConverterGPSCoordTest_1842, ZeroDenominatorThirdComponent_1842) {
  Exiv2::URationalValue::UniquePtr rv(new Exiv2::URationalValue);
  rv->read("40/1 26/1 46/0");
  exifData_.add(Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude"), rv.get());
  exifData_["Exif.GPSInfo.GPSLatitudeRef"] = "N";
  
  Exiv2::Converter converter(exifData_, xmpData_);
  converter.cnvExifGPSCoord("Exif.GPSInfo.GPSLatitude", "Xmp.exif.GPSLatitude");
  
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.exif.GPSLatitude"));
  EXPECT_EQ(it, xmpData_.end());
}

}  // namespace
