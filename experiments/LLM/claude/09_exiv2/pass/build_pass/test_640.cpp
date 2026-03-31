#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <stdexcept>

// TEST_ID is 640

class IptcKeyTest_640 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(IptcKeyTest_640, ConstructFromStringKey_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

// Test construction from tag and record
TEST_F(IptcKeyTest_640, ConstructFromTagAndRecord_640) {
    Exiv2::IptcKey key(5, 2);  // ObjectName in Application2
    EXPECT_FALSE(key.key().empty());
}

// Test familyName returns "Iptc"
TEST_F(IptcKeyTest_640, FamilyNameIsIptc_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test groupName returns the record name
TEST_F(IptcKeyTest_640, GroupNameReturnsRecordName_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

// Test tagName returns the tag name
TEST_F(IptcKeyTest_640, TagNameReturnsExpected_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

// Test tag returns the correct tag number
TEST_F(IptcKeyTest_640, TagReturnsCorrectNumber_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

// Test record returns the correct record number
TEST_F(IptcKeyTest_640, RecordReturnsCorrectNumber_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

// Test recordName returns the correct record name
TEST_F(IptcKeyTest_640, RecordNameReturnsExpected_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test clone returns a valid copy
TEST_F(IptcKeyTest_640, CloneReturnsCopy_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->record(), key.record());
}

// Test construction from tag/record and verify key composition
TEST_F(IptcKeyTest_640, ConstructFromTagRecordComposesKey_640) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

// Test Envelope record
TEST_F(IptcKeyTest_640, EnvelopeRecord_640) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test construction with invalid key string throws
TEST_F(IptcKeyTest_640, InvalidKeyThrows_640) {
    EXPECT_THROW(Exiv2::IptcKey key("InvalidKey"), std::exception);
}

// Test construction with wrong family name throws
TEST_F(IptcKeyTest_640, WrongFamilyNameThrows_640) {
    EXPECT_THROW(Exiv2::IptcKey key("Exif.Application2.ObjectName"), std::exception);
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcKeyTest_640, TagLabelNonEmpty_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_FALSE(key.tagLabel().empty());
}

// Test tagDesc returns a string (may or may not be empty)
TEST_F(IptcKeyTest_640, TagDescReturnsString_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    // tagDesc may be empty but should not throw
    std::string desc = key.tagDesc();
    (void)desc;  // Just verifying it doesn't throw
}

// Test different Application2 tags
TEST_F(IptcKeyTest_640, Application2Keywords_640) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "Keywords");
}

// Test construction from numeric tag and record for Envelope
TEST_F(IptcKeyTest_640, ConstructEnvelopeFromTagRecord_640) {
    Exiv2::IptcKey key(0, 1);  // ModelVersion in Envelope
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.recordName(), "Envelope");
}

// Test that cloned key is independent
TEST_F(IptcKeyTest_640, ClonedKeyIsIndependent_640) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    // Both should have the same values
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->familyName(), std::string(key.familyName()));
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

// Test copy construction behavior through clone for Application2.Caption
TEST_F(IptcKeyTest_640, CaptionAbstractKey_640) {
    Exiv2::IptcKey key(120, 2);  // Caption/Abstract
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tag(), 120);
    EXPECT_FALSE(key.key().empty());
}

// Test with an unknown tag number
TEST_F(IptcKeyTest_640, UnknownTagNumber_640) {
    // Using a tag number that may not be defined - should still construct
    Exiv2::IptcKey key(9999, 2);
    EXPECT_EQ(key.tag(), 9999);
    EXPECT_EQ(key.record(), 2);
    EXPECT_FALSE(key.key().empty());
}
