#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <stdexcept>

// TEST_ID is 2158

class IptcKeyTest_2158 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a valid string key
TEST_F(IptcKeyTest_2158, ConstructFromValidStringKey_2158) {
    EXPECT_NO_THROW(Exiv2::IptcKey key("Iptc.Application2.ObjectName"));
}

// Test construction from tag and record
TEST_F(IptcKeyTest_2158, ConstructFromTagAndRecord_2158) {
    EXPECT_NO_THROW(Exiv2::IptcKey key(5, 2));
}

// Test key() returns the expected string for a string-constructed key
TEST_F(IptcKeyTest_2158, KeyReturnsCorrectString_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string result = key.key();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "Iptc.Application2.ObjectName");
}

// Test familyName() returns "Iptc"
TEST_F(IptcKeyTest_2158, FamilyNameReturnsIptc_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test groupName() returns the record name
TEST_F(IptcKeyTest_2158, GroupNameReturnsRecordName_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

// Test tagName() returns the tag name
TEST_F(IptcKeyTest_2158, TagNameReturnsCorrectName_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

// Test tag() returns correct tag number
TEST_F(IptcKeyTest_2158, TagReturnsCorrectNumber_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

// Test record() returns correct record number
TEST_F(IptcKeyTest_2158, RecordReturnsCorrectNumber_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

// Test recordName() returns correct record name
TEST_F(IptcKeyTest_2158, RecordNameReturnsCorrectName_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test construction from tag and record, then verify key components
TEST_F(IptcKeyTest_2158, ConstructFromTagRecordVerifyKey_2158) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
    EXPECT_EQ(key.groupName(), "Application2");
    EXPECT_EQ(key.tagName(), "ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

// Test clone() produces an equivalent copy
TEST_F(IptcKeyTest_2158, CloneProducesEquivalentCopy_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

// Test invalid key string throws exception
TEST_F(IptcKeyTest_2158, InvalidKeyStringThrows_2158) {
    EXPECT_THROW(Exiv2::IptcKey key("InvalidKey"), std::exception);
}

// Test key string with wrong family name throws
TEST_F(IptcKeyTest_2158, WrongFamilyNameThrows_2158) {
    EXPECT_THROW(Exiv2::IptcKey key("Exif.Application2.ObjectName"), std::exception);
}

// Test empty key string throws
TEST_F(IptcKeyTest_2158, EmptyKeyStringThrows_2158) {
    EXPECT_THROW(Exiv2::IptcKey key(""), std::exception);
}

// Test tagLabel() returns a non-empty label for known tag
TEST_F(IptcKeyTest_2158, TagLabelReturnsNonEmpty_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() returns a description for known tag
TEST_F(IptcKeyTest_2158, TagDescReturnsDescription_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    // tagDesc may or may not be empty, but should not throw
    EXPECT_NO_THROW(key.tagDesc());
}

// Test Envelope record (record 1)
TEST_F(IptcKeyTest_2158, EnvelopeRecordKey_2158) {
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_EQ(key.recordName(), "Envelope");
}

// Test construction with Envelope record from string
TEST_F(IptcKeyTest_2158, EnvelopeRecordFromString_2158) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test different Application2 tags
TEST_F(IptcKeyTest_2158, Application2Keywords_2158) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "Keywords");
}

// Test Application2 Caption (tag 120)
TEST_F(IptcKeyTest_2158, Application2Caption_2158) {
    Exiv2::IptcKey key(120, 2);
    EXPECT_EQ(key.tag(), 120);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "Caption");
    EXPECT_EQ(key.key(), "Iptc.Application2.Caption");
}

// Test that key constructed from tag/record and from string produce same results
TEST_F(IptcKeyTest_2158, TagRecordAndStringConstructionEquivalent_2158) {
    Exiv2::IptcKey keyFromString("Iptc.Application2.Keywords");
    Exiv2::IptcKey keyFromTagRecord(25, 2);

    EXPECT_EQ(keyFromString.key(), keyFromTagRecord.key());
    EXPECT_EQ(keyFromString.tag(), keyFromTagRecord.tag());
    EXPECT_EQ(keyFromString.record(), keyFromTagRecord.record());
    EXPECT_EQ(keyFromString.tagName(), keyFromTagRecord.tagName());
    EXPECT_EQ(keyFromString.groupName(), keyFromTagRecord.groupName());
    EXPECT_EQ(keyFromString.recordName(), keyFromTagRecord.recordName());
}

// Test write through ostream operator
TEST_F(IptcKeyTest_2158, WriteToOstream_2158) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::ostringstream oss;
    oss << key;
    EXPECT_FALSE(oss.str().empty());
    EXPECT_EQ(oss.str(), "Iptc.Application2.ObjectName");
}

// Test unknown tag number for given record
TEST_F(IptcKeyTest_2158, UnknownTagNumber_2158) {
    // Tag 9999 in record 2 is unlikely to be defined
    EXPECT_NO_THROW(Exiv2::IptcKey key(9999, 2));
    Exiv2::IptcKey key(9999, 2);
    EXPECT_EQ(key.tag(), 9999);
    EXPECT_EQ(key.record(), 2);
}
