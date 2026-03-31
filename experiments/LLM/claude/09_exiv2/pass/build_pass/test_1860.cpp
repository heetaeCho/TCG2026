#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Test fixture for copyIptcToXmp tests
class CopyIptcToXmpTest_1860 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: Copying empty IPTC data to XMP should result in empty XMP data
TEST_F(CopyIptcToXmpTest_1860, EmptyIptcToXmp_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    // Empty IPTC should not produce XMP entries
    EXPECT_TRUE(xmpData.empty());
}

// Test: Copying IPTC data with a single entry to XMP
TEST_F(CopyIptcToXmpTest_1860, SingleIptcEntryToXmp_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    // Add a caption/abstract (dataset 120, record 2) which maps to dc:description
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    // After conversion, XMP should have at least one entry
    EXPECT_FALSE(xmpData.empty());
}

// Test: Copying with explicit charset parameter
TEST_F(CopyIptcToXmpTest_1860, ExplicitCharset_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, "UTF-8"));
    
    EXPECT_FALSE(xmpData.empty());
}

// Test: Copying with ISO-8859-1 charset
TEST_F(CopyIptcToXmpTest_1860, ISO88591Charset_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "Hello World";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, "ISO-8859-1"));
    
    EXPECT_FALSE(xmpData.empty());
}

// Test: Multiple IPTC entries are converted
TEST_F(CopyIptcToXmpTest_1860, MultipleIptcEntriesToXmp_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "Caption Text";
    iptcData["Iptc.Application2.Byline"] = "Author Name";
    iptcData["Iptc.Application2.ObjectName"] = "Title";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    EXPECT_FALSE(xmpData.empty());
    // Should have multiple XMP entries
    EXPECT_GT(xmpData.count(), 0);
}

// Test: IPTC Keywords are converted to XMP dc:subject
TEST_F(CopyIptcToXmpTest_1860, KeywordsConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Keywords"] = "keyword1";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    EXPECT_FALSE(xmpData.empty());
    
    // Check if dc:subject was created
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Caption maps to dc:description
TEST_F(CopyIptcToXmpTest_1860, CaptionMapsToDescription_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "My Description";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Byline maps to dc:creator
TEST_F(CopyIptcToXmpTest_1860, BylineMapsToCreator_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Byline"] = "Photographer";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData.end());
}

// Test: ObjectName maps to dc:title
TEST_F(CopyIptcToXmpTest_1860, ObjectNameMapsToTitle_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.ObjectName"] = "Photo Title";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Pre-existing XMP data is preserved/overwritten
TEST_F(CopyIptcToXmpTest_1860, PreExistingXmpData_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    // Add pre-existing XMP data
    xmpData["Xmp.dc.description"] = "Existing Description";
    
    iptcData["Iptc.Application2.Caption"] = "New Description";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    // XMP should not be empty
    EXPECT_FALSE(xmpData.empty());
}

// Test: Null charset with empty IPTC data (no crash)
TEST_F(CopyIptcToXmpTest_1860, NullCharsetEmptyIptc_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
}

// Test: Copyright field conversion
TEST_F(CopyIptcToXmpTest_1860, CopyrightConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Copyright"] = "Copyright 2023";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.rights"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Multiple keywords are converted to XMP bag
TEST_F(CopyIptcToXmpTest_1860, MultipleKeywords_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    // Add multiple keywords using the add method
    Exiv2::Iptcdatum kw1(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    kw1.setValue("keyword1");
    iptcData.add(kw1);
    
    Exiv2::Iptcdatum kw2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    kw2.setValue("keyword2");
    iptcData.add(kw2);
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    EXPECT_FALSE(xmpData.empty());
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData.end());
}

// Test: City field conversion to photoshop:City
TEST_F(CopyIptcToXmpTest_1860, CityConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.City"] = "New York";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.City"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Country conversion
TEST_F(CopyIptcToXmpTest_1860, CountryConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.CountryName"] = "United States";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Country"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Verify empty string value is handled
TEST_F(CopyIptcToXmpTest_1860, EmptyStringValue_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
}

// Test: Credit conversion
TEST_F(CopyIptcToXmpTest_1860, CreditConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Credit"] = "Photo Agency";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Credit"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Source conversion
TEST_F(CopyIptcToXmpTest_1860, SourceConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Source"] = "Reuters";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Source"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Urgency field conversion
TEST_F(CopyIptcToXmpTest_1860, UrgencyConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Urgency"] = "5";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Urgency"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Calling copyIptcToXmp twice doesn't crash
TEST_F(CopyIptcToXmpTest_1860, DoubleCopy_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Caption"] = "Test";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    EXPECT_FALSE(xmpData.empty());
}

// Test: XMP data cleared before copy, then copied
TEST_F(CopyIptcToXmpTest_1860, ClearXmpThenCopy_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    xmpData["Xmp.dc.title"] = "Old Title";
    xmpData.clear();
    
    iptcData["Iptc.Application2.ObjectName"] = "New Title";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    EXPECT_FALSE(xmpData.empty());
}

// Test: Headline conversion
TEST_F(CopyIptcToXmpTest_1860, HeadlineConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.Headline"] = "Breaking News";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Headline"));
    EXPECT_NE(it, xmpData.end());
}

// Test: Special instructions conversion
TEST_F(CopyIptcToXmpTest_1860, SpecialInstructionsConversion_1860) {
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    iptcData["Iptc.Application2.SpecialInstructions"] = "Embargo until tomorrow";
    
    ASSERT_NO_THROW(Exiv2::copyIptcToXmp(iptcData, xmpData, nullptr));
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.photoshop.Instructions"));
    EXPECT_NE(it, xmpData.end());
}
