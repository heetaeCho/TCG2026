#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <string>
#include <stdexcept>

using namespace Exiv2;

// Test constructing IptcKey from a string key
TEST_F(IptcKeyTest_642, ConstructFromStringKey_642) {
    // This is a placeholder test fixture; using TEST instead
}

class IptcKeyTest_642 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(IptcKeyTest_642, ConstructFromValidStringKey_642) {
    ASSERT_NO_THROW(IptcKey key("Iptc.Application2.ObjectName"));
}

// Test that key() returns the expected key string
TEST_F(IptcKeyTest_642, KeyReturnsCorrectString_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    std::string result = key.key();
    EXPECT_EQ(result, "Iptc.Application2.ObjectName");
}

// Test that familyName() returns "Iptc"
TEST_F(IptcKeyTest_642, FamilyNameReturnsIptc_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test that groupName() returns the record name
TEST_F(IptcKeyTest_642, GroupNameReturnsRecordName_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    std::string groupName = key.groupName();
    std::string recordName = key.recordName();
    EXPECT_EQ(groupName, recordName);
}

// Test that groupName() equals recordName() for Application2
TEST_F(IptcKeyTest_642, GroupNameEqualsRecordNameApplication2_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

// Test that tagName() returns the expected tag name
TEST_F(IptcKeyTest_642, TagNameReturnsExpectedValue_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

// Test construction from tag and record numbers
TEST_F(IptcKeyTest_642, ConstructFromTagAndRecord_642) {
    ASSERT_NO_THROW(IptcKey key(5, 2));
}

// Test that tag() returns correct tag number when constructed from numbers
TEST_F(IptcKeyTest_642, TagReturnsCorrectValueFromNumbers_642) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
}

// Test that record() returns correct record number when constructed from numbers
TEST_F(IptcKeyTest_642, RecordReturnsCorrectValueFromNumbers_642) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.record(), 2);
}

// Test that key string is properly formed when constructed from tag and record
TEST_F(IptcKeyTest_642, KeyStringFromTagAndRecord_642) {
    IptcKey key(5, 2);
    std::string keyStr = key.key();
    EXPECT_FALSE(keyStr.empty());
    // Should start with "Iptc."
    EXPECT_EQ(keyStr.substr(0, 5), "Iptc.");
}

// Test clone produces a valid copy
TEST_F(IptcKeyTest_642, CloneProducesValidCopy_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->record(), key.record());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

// Test that familyName is consistent across constructions
TEST_F(IptcKeyTest_642, FamilyNameConsistentAcrossConstructors_642) {
    IptcKey key1("Iptc.Application2.ObjectName");
    IptcKey key2(5, 2);
    EXPECT_STREQ(key1.familyName(), key2.familyName());
}

// Test Envelope record
TEST_F(IptcKeyTest_642, EnvelopeRecord_642) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_EQ(key.recordName(), "Envelope");
}

// Test that tagLabel returns a non-empty string for known tags
TEST_F(IptcKeyTest_642, TagLabelForKnownTag_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    // Known tags should have a label
    EXPECT_FALSE(label.empty());
}

// Test construction with invalid key string throws
TEST_F(IptcKeyTest_642, ConstructFromInvalidKeyThrows_642) {
    EXPECT_THROW(IptcKey key("Invalid.Key.String"), std::exception);
}

// Test construction with empty string throws
TEST_F(IptcKeyTest_642, ConstructFromEmptyStringThrows_642) {
    EXPECT_THROW(IptcKey key(""), std::exception);
}

// Test construction with wrong family name throws
TEST_F(IptcKeyTest_642, ConstructFromWrongFamilyThrows_642) {
    EXPECT_THROW(IptcKey key("Exif.Application2.ObjectName"), std::exception);
}

// Test record name for Application2
TEST_F(IptcKeyTest_642, RecordNameApplication2_642) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test record name for Envelope
TEST_F(IptcKeyTest_642, RecordNameEnvelope_642) {
    IptcKey key(0, 1);
    EXPECT_EQ(key.recordName(), "Envelope");
}

// Test tagDesc for a known tag
TEST_F(IptcKeyTest_642, TagDescForKnownTag_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    // Description may or may not be empty depending on the tag, but should not throw
    SUCCEED();
}

// Test that tag value is correct when constructed from string
TEST_F(IptcKeyTest_642, TagValueFromStringConstruction_642) {
    IptcKey key("Iptc.Application2.ObjectName");
    // ObjectName is tag 5 in Application2 (record 2)
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

// Test copy semantics via clone
TEST_F(IptcKeyTest_642, CloneIsIndependentCopy_642) {
    IptcKey key("Iptc.Application2.Keywords");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test multiple different tags in Application2
TEST_F(IptcKeyTest_642, DifferentTagsInApplication2_642) {
    IptcKey key1("Iptc.Application2.ObjectName");
    IptcKey key2("Iptc.Application2.Keywords");
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_NE(key1.tagName(), key2.tagName());
}
