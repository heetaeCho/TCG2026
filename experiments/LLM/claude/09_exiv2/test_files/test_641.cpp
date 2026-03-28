#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <string>
#include <stdexcept>

namespace {

// Test fixture for IptcKey tests
class IptcKeyTest_641 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that familyName returns "Iptc"
TEST_F(IptcKeyTest_641, FamilyNameReturnsIptc_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test construction from string key
TEST_F(IptcKeyTest_641, ConstructFromStringKey_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

// Test construction from tag and record
TEST_F(IptcKeyTest_641, ConstructFromTagAndRecord_641) {
    // Tag 5 = ObjectName, Record 2 = Application2
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

// Test that key() returns a properly formed key string
TEST_F(IptcKeyTest_641, KeyStringFormat_641) {
    Exiv2::IptcKey key(5, 2);
    std::string keyStr = key.key();
    // Key should start with "Iptc."
    EXPECT_EQ(keyStr.substr(0, 5), "Iptc.");
}

// Test groupName returns record name
TEST_F(IptcKeyTest_641, GroupNameReturnsRecordName_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string groupName = key.groupName();
    EXPECT_EQ(groupName, "Application2");
}

// Test tagName
TEST_F(IptcKeyTest_641, TagNameReturnsCorrectName_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string tagName = key.tagName();
    EXPECT_EQ(tagName, "ObjectName");
}

// Test record() returns correct record number
TEST_F(IptcKeyTest_641, RecordReturnsCorrectValue_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

// Test tag() returns correct tag number
TEST_F(IptcKeyTest_641, TagReturnsCorrectValue_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

// Test recordName
TEST_F(IptcKeyTest_641, RecordNameReturnsCorrectName_641) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test clone creates a copy
TEST_F(IptcKeyTest_641, CloneCreatesCopy_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->record(), key.record());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
}

// Test familyName is consistent across different instances
TEST_F(IptcKeyTest_641, FamilyNameConsistentAcrossInstances_641) {
    Exiv2::IptcKey key1("Iptc.Application2.ObjectName");
    Exiv2::IptcKey key2("Iptc.Envelope.Destination");
    EXPECT_STREQ(key1.familyName(), key2.familyName());
    EXPECT_STREQ(key1.familyName(), "Iptc");
}

// Test construction with Envelope record
TEST_F(IptcKeyTest_641, EnvelopeRecordConstruction_641) {
    Exiv2::IptcKey key("Iptc.Envelope.Destination");
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_EQ(key.record(), 1);
}

// Test invalid key string throws exception
TEST_F(IptcKeyTest_641, InvalidKeyStringThrows_641) {
    EXPECT_THROW(Exiv2::IptcKey("InvalidKey"), std::exception);
}

// Test invalid key with wrong family name
TEST_F(IptcKeyTest_641, WrongFamilyNameThrows_641) {
    EXPECT_THROW(Exiv2::IptcKey("Exif.Photo.ExposureTime"), std::exception);
}

// Test tagLabel returns non-empty string for known tag
TEST_F(IptcKeyTest_641, TagLabelForKnownTag_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test construction from numeric tag and record then verify key string
TEST_F(IptcKeyTest_641, NumericConstructionProducesValidKey_641) {
    Exiv2::IptcKey key(5, 2);
    std::string keyStr = key.key();
    EXPECT_FALSE(keyStr.empty());
    EXPECT_NE(keyStr.find("Iptc"), std::string::npos);
}

// Test clone independence - modifying original doesn't affect clone
TEST_F(IptcKeyTest_641, CloneIsIndependent_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    // Verify they are separate objects with same values
    EXPECT_EQ(cloned->key(), "Iptc.Application2.ObjectName");
    EXPECT_STREQ(cloned->familyName(), "Iptc");
}

// Test different tags in same record
TEST_F(IptcKeyTest_641, DifferentTagsSameRecord_641) {
    Exiv2::IptcKey key1("Iptc.Application2.ObjectName");
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    EXPECT_EQ(key1.record(), key2.record());
    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test tagDesc for known dataset
TEST_F(IptcKeyTest_641, TagDescForKnownTag_641) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    // Description should exist for a known tag
    // It may or may not be empty depending on the dataset definition
    // Just verify it doesn't crash
    SUCCEED();
}

// Test construction with record 0 (unknown/boundary)
TEST_F(IptcKeyTest_641, RecordZeroBoundary_641) {
    // Record 0 is not typically used but test boundary
    EXPECT_NO_THROW({
        Exiv2::IptcKey key(0, 0);
    });
}

} // namespace
