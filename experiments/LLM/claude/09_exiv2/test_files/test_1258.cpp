#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>

// Test fixture for XmpProperties tests
class XmpPropertiesTest_1258 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {
    // Clean up any registered namespaces
    Exiv2::XmpProperties::unregisterNs();
  }
};

// ==================== printProperty tests ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyWithUnknownKeyUsesDefaultPrintValue_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("TestValue");
  Exiv2::XmpProperties::printProperty(os, "Xmp.dc.unknown_key_xyz", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("TestValue"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyWithKnownKeyOrientation_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("1");
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.Orientation", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // Orientation=1 should print "top, left"
  EXPECT_NE(result.find("top"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyWithKnownKeyColorSpace_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("1");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.ColorSpace", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // ColorSpace=1 is sRGB
  EXPECT_NE(result.find("sRGB"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyWithEmptyValue_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  // Don't read any data, count should be 0
  // With count == 0, it should use default printValue
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.Orientation", *value);
  // Should not crash and should produce some output (possibly empty string)
  // The important thing is it doesn't crash
  SUCCEED();
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyWhiteBalance_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.WhiteBalance", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // WhiteBalance=0 should be "Auto"
  EXPECT_NE(result.find("Auto"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyResolutionUnit_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("2");
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.ResolutionUnit", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // ResolutionUnit=2 is "inch"
  EXPECT_NE(result.find("inch"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyContrast_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.Contrast", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Normal"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertySharpness_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.Sharpness", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Normal"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyXResolution_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("72");
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.XResolution", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("72"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyYResolution_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("300");
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.YResolution", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("300"), std::string::npos);
}

// ==================== Namespace registration tests ====================

TEST_F(XmpPropertiesTest_1258, RegisterAndLookupNamespace_1258) {
  Exiv2::XmpProperties::registerNs("http://test.example.com/ns/1.0/", "testns");
  std::string result = Exiv2::XmpProperties::prefix("http://test.example.com/ns/1.0/");
  EXPECT_EQ(result, "testns");
}

TEST_F(XmpPropertiesTest_1258, RegisterAndGetNs_1258) {
  Exiv2::XmpProperties::registerNs("http://test2.example.com/ns/1.0/", "testns2");
  std::string result = Exiv2::XmpProperties::ns("testns2");
  EXPECT_EQ(result, "http://test2.example.com/ns/1.0/");
}

TEST_F(XmpPropertiesTest_1258, UnregisterSpecificNamespace_1258) {
  Exiv2::XmpProperties::registerNs("http://test3.example.com/ns/1.0/", "testns3");
  std::string prefixResult = Exiv2::XmpProperties::prefix("http://test3.example.com/ns/1.0/");
  EXPECT_EQ(prefixResult, "testns3");
  Exiv2::XmpProperties::unregisterNs("http://test3.example.com/ns/1.0/");
  // After unregistering, prefix should return empty
  std::string result = Exiv2::XmpProperties::prefix("http://test3.example.com/ns/1.0/");
  EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, UnregisterAllCustomNamespaces_1258) {
  Exiv2::XmpProperties::registerNs("http://test4.example.com/ns/1.0/", "testns4");
  Exiv2::XmpProperties::registerNs("http://test5.example.com/ns/1.0/", "testns5");
  Exiv2::XmpProperties::unregisterNs();
  std::string r1 = Exiv2::XmpProperties::prefix("http://test4.example.com/ns/1.0/");
  std::string r2 = Exiv2::XmpProperties::prefix("http://test5.example.com/ns/1.0/");
  EXPECT_TRUE(r1.empty());
  EXPECT_TRUE(r2.empty());
}

// ==================== Built-in namespace tests ====================

TEST_F(XmpPropertiesTest_1258, PrefixForDcNamespace_1258) {
  std::string result = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
  EXPECT_EQ(result, "dc");
}

TEST_F(XmpPropertiesTest_1258, NsForDcPrefix_1258) {
  std::string result = Exiv2::XmpProperties::ns("dc");
  EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1258, NsForExifPrefix_1258) {
  std::string result = Exiv2::XmpProperties::ns("exif");
  EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, NsForTiffPrefix_1258) {
  std::string result = Exiv2::XmpProperties::ns("tiff");
  EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, NsForXmpPrefix_1258) {
  std::string result = Exiv2::XmpProperties::ns("xmp");
  EXPECT_FALSE(result.empty());
}

// ==================== Unknown prefix/ns tests ====================

TEST_F(XmpPropertiesTest_1258, PrefixForUnknownNamespace_1258) {
  std::string result = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/ns/");
  EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, NsForUnknownPrefix_1258) {
  std::string result = Exiv2::XmpProperties::ns("nonexistent_prefix_xyz");
  EXPECT_TRUE(result.empty());
}

// ==================== propertyType tests ====================

TEST_F(XmpPropertiesTest_1258, PropertyTypeForKnownKey_1258) {
  Exiv2::XmpKey key("Xmp.dc.title");
  Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
  EXPECT_NE(type, Exiv2::invalidTypeId);
}

TEST_F(XmpPropertiesTest_1258, PropertyTypeForDcDescription_1258) {
  Exiv2::XmpKey key("Xmp.dc.description");
  Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
  EXPECT_NE(type, Exiv2::invalidTypeId);
}

// ==================== propertyInfo tests ====================

TEST_F(XmpPropertiesTest_1258, PropertyInfoForKnownKey_1258) {
  Exiv2::XmpKey key("Xmp.dc.title");
  auto info = Exiv2::XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1258, PropertyInfoForUnknownKey_1258) {
  Exiv2::XmpKey key("Xmp.dc.nonexistent_property_xyz");
  auto info = Exiv2::XmpProperties::propertyInfo(key);
  EXPECT_EQ(info, nullptr);
}

// ==================== propertyTitle and propertyDesc tests ====================

TEST_F(XmpPropertiesTest_1258, PropertyTitleForKnownKey_1258) {
  Exiv2::XmpKey key("Xmp.dc.title");
  const char* title = Exiv2::XmpProperties::propertyTitle(key);
  EXPECT_NE(title, nullptr);
  EXPECT_GT(strlen(title), 0u);
}

TEST_F(XmpPropertiesTest_1258, PropertyDescForKnownKey_1258) {
  Exiv2::XmpKey key("Xmp.dc.title");
  const char* desc = Exiv2::XmpProperties::propertyDesc(key);
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1258, PropertyTitleForUnknownProperty_1258) {
  Exiv2::XmpKey key("Xmp.dc.nonexistent_property_xyz");
  const char* title = Exiv2::XmpProperties::propertyTitle(key);
  EXPECT_EQ(title, nullptr);
}

TEST_F(XmpPropertiesTest_1258, PropertyDescForUnknownProperty_1258) {
  Exiv2::XmpKey key("Xmp.dc.nonexistent_property_xyz");
  const char* desc = Exiv2::XmpProperties::propertyDesc(key);
  EXPECT_EQ(desc, nullptr);
}

// ==================== propertyList tests ====================

TEST_F(XmpPropertiesTest_1258, PropertyListForDc_1258) {
  auto list = Exiv2::XmpProperties::propertyList("dc");
  EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1258, PropertyListForExif_1258) {
  auto list = Exiv2::XmpProperties::propertyList("exif");
  EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1258, PropertyListForTiff_1258) {
  auto list = Exiv2::XmpProperties::propertyList("tiff");
  EXPECT_NE(list, nullptr);
}

// ==================== nsInfo tests ====================

TEST_F(XmpPropertiesTest_1258, NsInfoForDc_1258) {
  auto info = Exiv2::XmpProperties::nsInfo("dc");
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1258, NsInfoForExif_1258) {
  auto info = Exiv2::XmpProperties::nsInfo("exif");
  EXPECT_NE(info, nullptr);
}

// ==================== nsDesc tests ====================

TEST_F(XmpPropertiesTest_1258, NsDescForDc_1258) {
  const char* desc = Exiv2::XmpProperties::nsDesc("dc");
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1258, NsDescForExif_1258) {
  const char* desc = Exiv2::XmpProperties::nsDesc("exif");
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

// ==================== registeredNamespaces tests ====================

TEST_F(XmpPropertiesTest_1258, RegisteredNamespacesContainsBuiltIns_1258) {
  Exiv2::Dictionary nsDict;
  Exiv2::XmpProperties::registeredNamespaces(nsDict);
  // Should contain at least dc
  EXPECT_FALSE(nsDict.empty());
}

TEST_F(XmpPropertiesTest_1258, RegisteredNamespacesContainsCustomAfterRegister_1258) {
  Exiv2::XmpProperties::registerNs("http://custom.example.com/ns/1.0/", "customns");
  Exiv2::Dictionary nsDict;
  Exiv2::XmpProperties::registeredNamespaces(nsDict);
  bool found = false;
  for (const auto& entry : nsDict) {
    if (entry.first == "http://custom.example.com/ns/1.0/" || entry.second == "customns") {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// ==================== printProperties tests ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertiesForDc_1258) {
  std::ostringstream os;
  Exiv2::XmpProperties::printProperties(os, "dc");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, PrintPropertiesForExif_1258) {
  std::ostringstream os;
  Exiv2::XmpProperties::printProperties(os, "exif");
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== lookupNsRegistry tests ====================

TEST_F(XmpPropertiesTest_1258, LookupNsRegistryForRegisteredPrefix_1258) {
  Exiv2::XmpProperties::registerNs("http://lookup.example.com/ns/1.0/", "lookupns");
  Exiv2::XmpNsInfo::Prefix prefix("lookupns");
  auto info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1258, LookupNsRegistryForUnregisteredPrefix_1258) {
  Exiv2::XmpNsInfo::Prefix prefix("nonexistent_prefix_xyz");
  auto info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
  EXPECT_EQ(info, nullptr);
}

// ==================== Exposure mode (known key with special print function) ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyExposureMode_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.ExposureMode", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // ExposureMode=0 should be "Auto"
  EXPECT_NE(result.find("Auto"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyExposureProgram_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("2");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.ExposureProgram", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyMeteringMode_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("5");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.MeteringMode", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // MeteringMode=5 should be "Multi-segment" or "Pattern"
}

TEST_F(XmpPropertiesTest_1258, PrintPropertySaturation_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.Saturation", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Normal"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertySceneCaptureType_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.SceneCaptureType", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // SceneCaptureType=0 should be "Standard"
  EXPECT_NE(result.find("Standard"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyCustomRendered_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.CustomRendered", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // CustomRendered=0 should be "Normal"
  EXPECT_NE(result.find("Normal"), std::string::npos);
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyGPSAltitudeRef_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.GPSAltitudeRef", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== printProperty return value test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyReturnsOstream_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("test_return_value");
  std::ostream& returned = Exiv2::XmpProperties::printProperty(os, "Xmp.dc.subject", *value);
  EXPECT_EQ(&returned, &os);
}

// ==================== YCbCrPositioning test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyYCbCrPositioning_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("1");
  Exiv2::XmpProperties::printProperty(os, "Xmp.tiff.YCbCrPositioning", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // YCbCrPositioning=1 is "Centered"
  EXPECT_NE(result.find("Centered"), std::string::npos);
}

// ==================== SubjectDistanceRange test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertySubjectDistanceRange_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.SubjectDistanceRange", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== LightSource test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyLightSource_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.LightSource", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== ExifVersion test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyExifVersion_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("2.30");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.ExifVersion", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== Date printing test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyCreateDate_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("2023-01-15T10:30:00");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.CreateDate", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1258, PrintPropertyDateTimeOriginal_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("2023-06-20T14:00:00");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.DateTimeOriginal", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ==================== GainControl test ====================

TEST_F(XmpPropertiesTest_1258, PrintPropertyGainControl_1258) {
  std::ostringstream os;
  auto value = Exiv2::Value::create(Exiv2::xmpText);
  value->read("0");
  Exiv2::XmpProperties::printProperty(os, "Xmp.exif.GainControl", *value);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // GainControl=0 is "None"
  EXPECT_NE(result.find("None"), std::string::npos);
}
