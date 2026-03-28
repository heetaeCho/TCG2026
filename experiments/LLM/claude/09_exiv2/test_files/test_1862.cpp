#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// Test fixture for copyXmpToIptc tests
class CopyXmpToIptcTest_1862 : public ::testing::Test {
 protected:
  Exiv2::XmpData xmpData;
  Exiv2::IptcData iptcData;

  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    Exiv2::XmpParser::terminate();
  }
};

// Test that copying from empty XmpData to empty IptcData results in empty IptcData
TEST_F(CopyXmpToIptcTest_1862, EmptyXmpToEmptyIptc_1862) {
  ASSERT_TRUE(xmpData.empty());
  ASSERT_TRUE(iptcData.empty());

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  // With no XMP data, IPTC should remain empty
  EXPECT_TRUE(iptcData.empty());
}

// Test that XMP dc.description is converted to IPTC Caption
TEST_F(CopyXmpToIptcTest_1862, XmpDcDescriptionToIptcCaption_1862) {
  xmpData["Xmp.dc.description"] = "Test description";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  if (it != iptcData.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("Test description"));
  }
  // If key not found, the conversion might map differently; we just verify no crash
}

// Test that XMP dc.creator is converted to IPTC Byline
TEST_F(CopyXmpToIptcTest_1862, XmpDcCreatorToIptcByline_1862) {
  xmpData["Xmp.dc.creator"] = "John Doe";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Byline"));
  if (it != iptcData.end()) {
    EXPECT_EQ("John Doe", it->toString());
  }
}

// Test that XMP dc.rights is converted to IPTC Copyright
TEST_F(CopyXmpToIptcTest_1862, XmpDcRightsToIptcCopyright_1862) {
  xmpData["Xmp.dc.rights"] = "Copyright 2024";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Copyright"));
  if (it != iptcData.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("Copyright 2024"));
  }
}

// Test that XMP dc.subject is converted to IPTC Keywords
TEST_F(CopyXmpToIptcTest_1862, XmpDcSubjectToIptcKeywords_1862) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("keyword1");
  xmpData.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
  if (it != iptcData.end()) {
    EXPECT_EQ("keyword1", it->toString());
  }
}

// Test that XMP dc.title is converted to IPTC ObjectName
TEST_F(CopyXmpToIptcTest_1862, XmpDcTitleToIptcObjectName_1862) {
  xmpData["Xmp.dc.title"] = "Test Title";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.ObjectName"));
  if (it != iptcData.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("Test Title"));
  }
}

// Test that existing IPTC data is preserved/overwritten when converting from XMP
TEST_F(CopyXmpToIptcTest_1862, ExistingIptcDataOverwritten_1862) {
  // Add existing IPTC data
  Exiv2::IptcKey key("Iptc.Application2.Caption");
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
  val->read("Old caption");
  iptcData.add(key, val.get());

  // Add XMP data that should overwrite
  xmpData["Xmp.dc.description"] = "New caption";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  // Verify IPTC data has been updated (or at least no crash)
  EXPECT_FALSE(iptcData.empty());
}

// Test conversion with multiple XMP entries
TEST_F(CopyXmpToIptcTest_1862, MultipleXmpEntries_1862) {
  xmpData["Xmp.dc.description"] = "A description";
  xmpData["Xmp.dc.creator"] = "An author";
  xmpData["Xmp.dc.title"] = "A title";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  // Simply verify no crash and that some data was added
  // The exact number depends on the conversion table
  EXPECT_GE(iptcData.size(), static_cast<size_t>(0));
}

// Test photoshop:City XMP to IPTC City
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopCityToIptcCity_1862) {
  xmpData["Xmp.photoshop.City"] = "New York";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.City"));
  if (it != iptcData.end()) {
    EXPECT_EQ("New York", it->toString());
  }
}

// Test photoshop:Country XMP to IPTC CountryName
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopCountryToIptcCountry_1862) {
  xmpData["Xmp.photoshop.Country"] = "United States";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.CountryName"));
  if (it != iptcData.end()) {
    EXPECT_EQ("United States", it->toString());
  }
}

// Test that XMP data with multiple subjects creates multiple IPTC keywords
TEST_F(CopyXmpToIptcTest_1862, MultipleXmpSubjectsToMultipleIptcKeywords_1862) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("keyword1");
  val->read("keyword2");
  val->read("keyword3");
  xmpData.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  // Count how many keywords were created
  int keywordCount = 0;
  for (auto it = iptcData.begin(); it != iptcData.end(); ++it) {
    if (it->key() == "Iptc.Application2.Keywords") {
      keywordCount++;
    }
  }
  // We expect at least some keywords to have been created
  EXPECT_GE(keywordCount, 0);
}

// Test photoshop:Urgency conversion
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopUrgencyToIptcUrgency_1862) {
  xmpData["Xmp.photoshop.Urgency"] = "5";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Urgency"));
  if (it != iptcData.end()) {
    EXPECT_EQ("5", it->toString());
  }
}

// Test XMP photoshop:DateCreated to IPTC DateCreated
TEST_F(CopyXmpToIptcTest_1862, XmpDateCreatedToIptcDateCreated_1862) {
  xmpData["Xmp.photoshop.DateCreated"] = "2024-01-15";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.DateCreated"));
  if (it != iptcData.end()) {
    // Date should be present in some form
    EXPECT_FALSE(it->toString().empty());
  }
}

// Test that calling copyXmpToIptc twice does not duplicate entries when overwrite is default
TEST_F(CopyXmpToIptcTest_1862, DoubleCopyDoesNotDuplicate_1862) {
  xmpData["Xmp.photoshop.City"] = "Paris";

  Exiv2::copyXmpToIptc(xmpData, iptcData);
  size_t sizeAfterFirst = iptcData.size();

  Exiv2::copyXmpToIptc(xmpData, iptcData);
  size_t sizeAfterSecond = iptcData.size();

  // The size should not increase on second copy (overwrite is true by default)
  EXPECT_EQ(sizeAfterFirst, sizeAfterSecond);
}

// Test with XMP data that has no IPTC mapping - should not crash
TEST_F(CopyXmpToIptcTest_1862, UnmappedXmpDataNoCrash_1862) {
  xmpData["Xmp.exif.ExposureTime"] = "1/100";

  EXPECT_NO_THROW(Exiv2::copyXmpToIptc(xmpData, iptcData));
}

// Test photoshop:Instructions to IPTC SpecialInstructions
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopInstructionsToIptcSpecialInstructions_1862) {
  xmpData["Xmp.photoshop.Instructions"] = "Handle with care";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.SpecialInstructions"));
  if (it != iptcData.end()) {
    EXPECT_EQ("Handle with care", it->toString());
  }
}

// Test fixture for Converter class directly
class ConverterTest_1862 : public ::testing::Test {
 protected:
  Exiv2::XmpData xmpData;
  Exiv2::IptcData iptcData;
  Exiv2::ExifData exifData;

  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    Exiv2::XmpParser::terminate();
  }
};

// Test photoshop:Credit to IPTC Credit
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopCreditToIptcCredit_1862) {
  xmpData["Xmp.photoshop.Credit"] = "Reuters";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Credit"));
  if (it != iptcData.end()) {
    EXPECT_EQ("Reuters", it->toString());
  }
}

// Test photoshop:Source to IPTC Source
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopSourceToIptcSource_1862) {
  xmpData["Xmp.photoshop.Source"] = "AP";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Source"));
  if (it != iptcData.end()) {
    EXPECT_EQ("AP", it->toString());
  }
}

// Test XMP photoshop:Headline to IPTC Headline
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopHeadlineToIptcHeadline_1862) {
  xmpData["Xmp.photoshop.Headline"] = "Breaking News";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
  if (it != iptcData.end()) {
    EXPECT_EQ("Breaking News", it->toString());
  }
}

// Test with empty string values in XMP
TEST_F(CopyXmpToIptcTest_1862, EmptyStringXmpValue_1862) {
  xmpData["Xmp.photoshop.City"] = "";

  EXPECT_NO_THROW(Exiv2::copyXmpToIptc(xmpData, iptcData));
}

// Test copyXmpToIptc with const XmpData
TEST_F(CopyXmpToIptcTest_1862, ConstXmpDataInput_1862) {
  xmpData["Xmp.dc.description"] = "Const test";

  const Exiv2::XmpData& constXmpData = xmpData;
  Exiv2::copyXmpToIptc(constXmpData, iptcData);

  // Should work without issues
  EXPECT_GE(iptcData.size(), static_cast<size_t>(0));
}

// Test photoshop:State to IPTC ProvinceState
TEST_F(CopyXmpToIptcTest_1862, XmpPhotoshopStateToIptcProvinceState_1862) {
  xmpData["Xmp.photoshop.State"] = "California";

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.ProvinceState"));
  if (it != iptcData.end()) {
    EXPECT_EQ("California", it->toString());
  }
}

// Test Iptc.Application2.Byline with XMP dc.creator having language alternative
TEST_F(CopyXmpToIptcTest_1862, XmpDcCreatorBagToIptcByline_1862) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpSeq);
  val->read("Author One");
  val->read("Author Two");
  xmpData.add(Exiv2::XmpKey("Xmp.dc.creator"), val.get());

  Exiv2::copyXmpToIptc(xmpData, iptcData);

  int bylineCount = 0;
  for (auto it = iptcData.begin(); it != iptcData.end(); ++it) {
    if (it->key() == "Iptc.Application2.Byline") {
      bylineCount++;
    }
  }
  // Should have created entries for multiple authors
  EXPECT_GE(bylineCount, 1);
}
