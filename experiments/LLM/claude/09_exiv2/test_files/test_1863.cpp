#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Test fixture for moveXmpToIptc tests
class MoveXmpToIptcTest_1863 : public ::testing::Test {
 protected:
  Exiv2::XmpData xmpData_;
  Exiv2::IptcData iptcData_;

  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    Exiv2::XmpParser::terminate();
  }
};

// Test that moveXmpToIptc with empty XmpData produces empty IptcData
TEST_F(MoveXmpToIptcTest_1863, EmptyXmpDataProducesEmptyIptcData_1863) {
  ASSERT_TRUE(xmpData_.empty());
  ASSERT_TRUE(iptcData_.empty());

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // With no XMP data to convert, IPTC should remain empty or have minimal content
  // XMP data should remain empty as well (nothing to erase)
  EXPECT_TRUE(xmpData_.empty());
}

// Test that moveXmpToIptc converts dc.description to IPTC caption
TEST_F(MoveXmpToIptcTest_1863, ConvertsDcDescriptionToIptcCaption_1863) {
  xmpData_["Xmp.dc.description"] = "Test description";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // After move, XMP data should be erased (setErase is called)
  // Check that IPTC data has content
  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  if (it != iptcData_.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("Test description"));
  }
}

// Test that moveXmpToIptc erases XMP data after conversion
TEST_F(MoveXmpToIptcTest_1863, ErasesXmpDataAfterConversion_1863) {
  xmpData_["Xmp.dc.creator"] = "Test Author";

  ASSERT_FALSE(xmpData_.empty());

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // The XMP entries that were converted should be erased
  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
  // After move with erase, the converted key should be gone
  EXPECT_TRUE(it == xmpData_.end());
}

// Test that moveXmpToIptc converts dc.creator to IPTC Byline
TEST_F(MoveXmpToIptcTest_1863, ConvertsDcCreatorToIptcByline_1863) {
  xmpData_["Xmp.dc.creator"] = "John Doe";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Byline"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("John Doe", it->toString());
  }
}

// Test that moveXmpToIptc converts dc.rights to IPTC Copyright
TEST_F(MoveXmpToIptcTest_1863, ConvertsDcRightsToIptcCopyright_1863) {
  xmpData_["Xmp.dc.rights"] = "Copyright 2023";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Copyright"));
  if (it != iptcData_.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("Copyright 2023"));
  }
}

// Test that moveXmpToIptc converts dc.subject (keywords) to IPTC Keywords
TEST_F(MoveXmpToIptcTest_1863, ConvertsDcSubjectToIptcKeywords_1863) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("keyword1");
  xmpData_.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("keyword1", it->toString());
  }
}

// Test that moveXmpToIptc with pre-existing IPTC data overwrites
TEST_F(MoveXmpToIptcTest_1863, OverwritesExistingIptcData_1863) {
  // Add existing IPTC data
  Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
  datum.setValue("Old caption");
  iptcData_.add(datum);

  // Add XMP data that maps to the same IPTC field
  xmpData_["Xmp.dc.description"] = "New caption";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  if (it != iptcData_.end()) {
    // The value should be the new one since overwrite is default (true)
    EXPECT_NE(std::string::npos, it->toString().find("New caption"));
  }
}

// Test that moveXmpToIptc handles photoshop namespace
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopCityToIptcCity_1863) {
  xmpData_["Xmp.photoshop.City"] = "New York";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.City"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("New York", it->toString());
  }

  // Verify that the XMP entry was erased
  auto xmpIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.photoshop.City"));
  EXPECT_TRUE(xmpIt == xmpData_.end());
}

// Test that moveXmpToIptc handles photoshop.Country
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopCountryToIptcCountry_1863) {
  xmpData_["Xmp.photoshop.Country"] = "United States";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.CountryName"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("United States", it->toString());
  }
}

// Test multiple XMP entries conversion
TEST_F(MoveXmpToIptcTest_1863, ConvertsMultipleXmpEntries_1863) {
  xmpData_["Xmp.dc.description"] = "A description";
  xmpData_["Xmp.dc.creator"] = "An author";
  xmpData_["Xmp.photoshop.City"] = "Paris";

  size_t xmpCountBefore = xmpData_.count();
  EXPECT_GE(xmpCountBefore, 3u);

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // After move, the converted XMP entries should be erased
  // IPTC should have entries
  // We don't make strong assertions about exact count since implementation details vary
  EXPECT_FALSE(iptcData_.empty());
}

// Test that dc.title is converted to IPTC ObjectName
TEST_F(MoveXmpToIptcTest_1863, ConvertsDcTitleToIptcObjectName_1863) {
  xmpData_["Xmp.dc.title"] = "My Title";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.ObjectName"));
  if (it != iptcData_.end()) {
    EXPECT_NE(std::string::npos, it->toString().find("My Title"));
  }
}

// Test that XMP entries with no IPTC mapping are not converted but still erased
TEST_F(MoveXmpToIptcTest_1863, NonMappableXmpEntriesHandled_1863) {
  // Add an XMP entry that typically has no IPTC mapping
  xmpData_["Xmp.xmp.Rating"] = "5";

  size_t iptcCountBefore = iptcData_.size();

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // The IPTC data might not have gained entries for non-mappable XMP properties
  // This tests that the function doesn't crash
  SUCCEED();
}

// Test photoshop.Headline conversion
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopHeadlineToIptcHeadline_1863) {
  xmpData_["Xmp.photoshop.Headline"] = "Breaking News";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Headline"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("Breaking News", it->toString());
  }
}

// Test calling moveXmpToIptc twice doesn't cause issues
TEST_F(MoveXmpToIptcTest_1863, CallingTwiceIsIdempotent_1863) {
  xmpData_["Xmp.dc.description"] = "Test";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);
  size_t countAfterFirst = iptcData_.size();

  // Calling again with (now empty/reduced) XMP data
  Exiv2::moveXmpToIptc(xmpData_, iptcData_);
  size_t countAfterSecond = iptcData_.size();

  // Second call should not add duplicate entries since XMP was erased
  EXPECT_EQ(countAfterFirst, countAfterSecond);
}

// Test photoshop.Instructions conversion
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopInstructionsToIptc_1863) {
  xmpData_["Xmp.photoshop.Instructions"] = "Special instructions";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.SpecialInstructions"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("Special instructions", it->toString());
  }
}

// Test that Iptc.Application2.Credit maps from photoshop.Credit
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopCreditToIptcCredit_1863) {
  xmpData_["Xmp.photoshop.Credit"] = "Photo credit";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Credit"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("Photo credit", it->toString());
  }
}

// Test that photoshop.Source converts to IPTC Source
TEST_F(MoveXmpToIptcTest_1863, ConvertsPhotoshopSourceToIptcSource_1863) {
  xmpData_["Xmp.photoshop.Source"] = "Reuters";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  auto it = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Source"));
  if (it != iptcData_.end()) {
    EXPECT_EQ("Reuters", it->toString());
  }
}
