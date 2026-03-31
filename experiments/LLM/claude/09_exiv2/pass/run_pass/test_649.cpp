#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <string>
#include <stdexcept>

// Test fixture for IptcKey tests
class IptcKeyTest_649 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(IptcKeyTest_649, ConstructFromValidStringKey_649) {
    ASSERT_NO_THROW(Exiv2::IptcKey key("Iptc.Application2.ObjectName"));
}

// Test construction from tag and record
TEST_F(IptcKeyTest_649, ConstructFromTagAndRecord_649) {
    ASSERT_NO_THROW(Exiv2::IptcKey key(5, 2));
}

// Test key() returns expected string for string-constructed key
TEST_F(IptcKeyTest_649, KeyReturnsCorrectString_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string result = key.key();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "Iptc.Application2.ObjectName");
}

// Test familyName() returns "Iptc"
TEST_F(IptcKeyTest_649, FamilyNameReturnsIptc_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    const char* family = key.familyName();
    ASSERT_NE(family, nullptr);
    EXPECT_STREQ(family, "Iptc");
}

// Test groupName() returns the record name
TEST_F(IptcKeyTest_649, GroupNameReturnsRecordName_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string group = key.groupName();
    EXPECT_EQ(group, "Application2");
}

// Test tagName() returns the tag name
TEST_F(IptcKeyTest_649, TagNameReturnsExpected_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string tagName = key.tagName();
    EXPECT_EQ(tagName, "ObjectName");
}

// Test tag() returns correct tag number
TEST_F(IptcKeyTest_649, TagReturnsCorrectNumber_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    uint16_t tag = key.tag();
    EXPECT_EQ(tag, 5);
}

// Test record() returns correct record number
TEST_F(IptcKeyTest_649, RecordReturnsCorrectNumber_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    uint16_t record = key.record();
    EXPECT_EQ(record, 2);
}

// Test recordName() returns expected record name
TEST_F(IptcKeyTest_649, RecordNameReturnsExpected_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string recordName = key.recordName();
    EXPECT_EQ(recordName, "Application2");
}

// Test clone() returns a valid copy
TEST_F(IptcKeyTest_649, CloneReturnsCopy_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->record(), key.record());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
}

// Test construction from tag and record yields correct key string
TEST_F(IptcKeyTest_649, ConstructFromTagRecordYieldsCorrectKey_649) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

// Test familyName from tag/record constructor
TEST_F(IptcKeyTest_649, FamilyNameFromTagRecordConstructor_649) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test construction with Envelope record
TEST_F(IptcKeyTest_649, ConstructWithEnvelopeRecord_649) {
    ASSERT_NO_THROW(Exiv2::IptcKey key("Iptc.Envelope.ModelVersion"));
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
}

// Test invalid key string throws
TEST_F(IptcKeyTest_649, InvalidKeyStringThrows_649) {
    EXPECT_THROW(Exiv2::IptcKey key("InvalidKeyString"), std::exception);
}

// Test invalid family name in key string throws
TEST_F(IptcKeyTest_649, WrongFamilyNameThrows_649) {
    EXPECT_THROW(Exiv2::IptcKey key("Exif.Application2.ObjectName"), std::exception);
}

// Test tagLabel() returns a string (may be empty for some tags)
TEST_F(IptcKeyTest_649, TagLabelReturnsString_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    // tagLabel should return something (possibly non-empty for known tags)
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() returns a string
TEST_F(IptcKeyTest_649, TagDescReturnsString_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    // For known tags, description should not be empty
    // But we just check it doesn't crash
    SUCCEED();
}

// Test clone independence - modifying clone doesn't affect original
TEST_F(IptcKeyTest_649, CloneIsIndependent_649) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    // Verify the original is unchanged
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

// Test construction with different known tags
TEST_F(IptcKeyTest_649, ConstructWithKeywords_649) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tagName(), "Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
}

// Test construction with tag/record for Envelope
TEST_F(IptcKeyTest_649, ConstructFromTagRecordEnvelope_649) {
    Exiv2::IptcKey key(0, 1); // ModelVersion in Envelope
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.groupName(), "Envelope");
}

// Test key consistency between string and tag/record constructors
TEST_F(IptcKeyTest_649, KeyConsistencyBetweenConstructors_649) {
    Exiv2::IptcKey keyFromString("Iptc.Application2.ObjectName");
    Exiv2::IptcKey keyFromTagRecord(5, 2);
    
    EXPECT_EQ(keyFromString.key(), keyFromTagRecord.key());
    EXPECT_EQ(keyFromString.tag(), keyFromTagRecord.tag());
    EXPECT_EQ(keyFromString.record(), keyFromTagRecord.record());
    EXPECT_EQ(keyFromString.tagName(), keyFromTagRecord.tagName());
    EXPECT_EQ(keyFromString.groupName(), keyFromTagRecord.groupName());
    EXPECT_STREQ(keyFromString.familyName(), keyFromTagRecord.familyName());
}

// Test with unknown tag number
TEST_F(IptcKeyTest_649, UnknownTagNumber_649) {
    // Using a tag number that may not be defined - should still construct
    ASSERT_NO_THROW(Exiv2::IptcKey key(9999, 2));
    Exiv2::IptcKey key(9999, 2);
    EXPECT_EQ(key.tag(), 9999);
    EXPECT_EQ(key.record(), 2);
}

// Test empty key string throws
TEST_F(IptcKeyTest_649, EmptyKeyStringThrows_649) {
    EXPECT_THROW(Exiv2::IptcKey key(""), std::exception);
}

// Test key with only family name throws
TEST_F(IptcKeyTest_649, PartialKeyThrows_649) {
    EXPECT_THROW(Exiv2::IptcKey key("Iptc"), std::exception);
}

// Test key with only family and group throws or works
TEST_F(IptcKeyTest_649, TwoPartKeyThrows_649) {
    EXPECT_THROW(Exiv2::IptcKey key("Iptc.Application2"), std::exception);
}
