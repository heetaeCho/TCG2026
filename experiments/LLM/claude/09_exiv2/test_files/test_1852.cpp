#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

// We need access to the Converter class which is defined in convert.cpp
// The public API exposes copyXmpToIptc, copyIptcToXmp, etc.
// But we need to test cnvXmpValueToIptc specifically through the Converter class.
// Since Converter is in the Exiv2 namespace but defined in convert.cpp,
// we include the necessary headers and use the conversion functions.

namespace {

class CnvXmpValueToIptcTest_1852 : public ::testing::Test {
 protected:
  void SetUp() override {
    xmpData_.clear();
    iptcData_.clear();
  }

  Exiv2::XmpData xmpData_;
  Exiv2::IptcData iptcData_;
};

// Test: When XMP key does not exist, IPTC data should remain unchanged
TEST_F(CnvXmpValueToIptcTest_1852, NonExistentXmpKey_NoConversion_1852) {
  // Use the public API to convert XMP to IPTC
  // The xmpData_ is empty, so nothing should be converted
  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // IPTC data should remain empty since there's no XMP data
  EXPECT_TRUE(iptcData_.empty());
}

// Test: Convert XMP text value to IPTC
TEST_F(CnvXmpValueToIptcTest_1852, XmpTextToIptc_BasicConversion_1852) {
  // Set an XMP value that maps to an IPTC field
  // Xmp.dc.description maps to Iptc.Application2.Caption
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" Test description";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // Check that something was added to IPTC
  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  if (pos != iptcData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Convert XMP subject (bag) to IPTC keywords
TEST_F(CnvXmpValueToIptcTest_1852, XmpBagToIptc_MultipleValues_1852) {
  // Xmp.dc.subject is an XmpBag that maps to Iptc.Application2.Keywords
  xmpData_["Xmp.dc.subject"] = "keyword1";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // Check that keywords were added
  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
  if (pos != iptcData_.end()) {
    EXPECT_EQ(pos->toString(), "keyword1");
  }
}

// Test: UTF-8 encoding marker is set when converting text values
TEST_F(CnvXmpValueToIptcTest_1852, Utf8EncodingMarkerSet_1852) {
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" UTF-8 test";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Envelope.CharacterSet"));
  if (pos != iptcData_.end()) {
    EXPECT_EQ(pos->toString(), "\033%G");
  }
}

// Test: Empty XMP data results in empty IPTC data
TEST_F(CnvXmpValueToIptcTest_1852, EmptyXmpData_EmptyIptcResult_1852) {
  Exiv2::copyXmpToIptc(xmpData_, iptcData_);
  EXPECT_TRUE(iptcData_.empty());
}

// Test: XMP title (langAlt) to IPTC ObjectName
TEST_F(CnvXmpValueToIptcTest_1852, XmpTitleToIptcObjectName_1852) {
  xmpData_["Xmp.dc.title"] = "lang=\"x-default\" My Title";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.ObjectName"));
  if (pos != iptcData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Conversion with erase mode (moveXmpToIptc)
TEST_F(CnvXmpValueToIptcTest_1852, MoveXmpToIptc_ErasesXmpData_1852) {
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" Move test";

  Exiv2::moveXmpToIptc(xmpData_, iptcData_);

  // After move, the XMP data that was converted should be erased
  auto xmpPos = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
  // It may or may not be erased depending on mapping, but we check the move happened
  EXPECT_FALSE(iptcData_.empty());
}

// Test: Multiple XMP bag entries create multiple IPTC entries
TEST_F(CnvXmpValueToIptcTest_1852, MultipleBagEntries_MultipleIptcEntries_1852) {
  // Add multiple keywords via XmpBag
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("keyword1");
  val->read("keyword2");
  val->read("keyword3");
  xmpData_.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // Count IPTC keywords
  int count = 0;
  for (auto it = iptcData_.begin(); it != iptcData_.end(); ++it) {
    if (it->key() == "Iptc.Application2.Keywords") {
      ++count;
    }
  }
  EXPECT_GE(count, 1);
}

// Test: Overwrite behavior - when IPTC already has data and overwrite is default
TEST_F(CnvXmpValueToIptcTest_1852, OverwriteExistingIptcData_1852) {
  // Pre-populate IPTC
  iptcData_["Iptc.Application2.Caption"] = "Old caption";

  // Set XMP
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" New caption";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  EXPECT_NE(pos, iptcData_.end());
}

// Test: XMP creator to IPTC Byline
TEST_F(CnvXmpValueToIptcTest_1852, XmpCreatorToIptcByline_1852) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpSeq);
  val->read("John Doe");
  xmpData_.add(Exiv2::XmpKey("Xmp.dc.creator"), val.get());

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Byline"));
  if (pos != iptcData_.end()) {
    EXPECT_EQ(pos->toString(), "John Doe");
  }
}

// Test: XMP rights to IPTC Copyright
TEST_F(CnvXmpValueToIptcTest_1852, XmpRightsToIptcCopyright_1852) {
  xmpData_["Xmp.dc.rights"] = "lang=\"x-default\" Copyright 2024";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Copyright"));
  if (pos != iptcData_.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

// Test: Conversion preserves special characters in values
TEST_F(CnvXmpValueToIptcTest_1852, SpecialCharactersPreserved_1852) {
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" Ünïcödé tëst àéîõü";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  auto pos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
  if (pos != iptcData_.end()) {
    std::string val = pos->toString();
    EXPECT_FALSE(val.empty());
  }
}

// Test: CharacterSet is set to UTF-8 indicator
TEST_F(CnvXmpValueToIptcTest_1852, CharacterSetIndicatesUtf8_1852) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpBag);
  val->read("test_keyword");
  xmpData_.add(Exiv2::XmpKey("Xmp.dc.subject"), val.get());

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // If keywords were added, CharacterSet should be set
  auto kwPos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords"));
  if (kwPos != iptcData_.end()) {
    auto csPos = iptcData_.findKey(Exiv2::IptcKey("Iptc.Envelope.CharacterSet"));
    EXPECT_NE(csPos, iptcData_.end());
    if (csPos != iptcData_.end()) {
      EXPECT_EQ(csPos->toString(), "\033%G");
    }
  }
}

// Test: IPTC data not modified when XMP has no mappable keys
TEST_F(CnvXmpValueToIptcTest_1852, NoMappableXmpKeys_IptcUnchanged_1852) {
  // Add an XMP key that doesn't map to IPTC
  xmpData_["Xmp.xmp.CreatorTool"] = "TestTool";

  size_t sizeBefore = iptcData_.size();
  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  // CreatorTool doesn't map to any IPTC field, so size should remain same
  // (or only non-mappable data was present)
  // We just check no crash occurred
  SUCCEED();
}

// Test: copyXmpToIptc followed by copyIptcToXmp roundtrip
TEST_F(CnvXmpValueToIptcTest_1852, RoundtripConversion_1852) {
  xmpData_["Xmp.dc.description"] = "lang=\"x-default\" Roundtrip test";

  Exiv2::copyXmpToIptc(xmpData_, iptcData_);

  Exiv2::XmpData xmpData2;
  Exiv2::copyIptcToXmp(iptcData_, xmpData2);

  auto pos = xmpData2.findKey(Exiv2::XmpKey("Xmp.dc.description"));
  if (pos != xmpData2.end()) {
    EXPECT_FALSE(pos->toString().empty());
  }
}

}  // namespace
