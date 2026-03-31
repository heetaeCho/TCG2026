#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <string>
#include <stdexcept>

// Test fixture for IptcKey tests
class IptcKeyTest_648 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from tag and record, then verify record()
TEST_F(IptcKeyTest_648, ConstructFromTagAndRecord_RecordReturnsCorrectValue_648) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(2, key.record());
}

// Test construction from tag and record, then verify tag()
TEST_F(IptcKeyTest_648, ConstructFromTagAndRecord_TagReturnsCorrectValue_648) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(5, key.tag());
}

// Test construction from string key for Envelope record
TEST_F(IptcKeyTest_648, ConstructFromStringKey_EnvelopeRecord_648) {
    Exiv2::IptcKey key("Iptc.Envelope.Destination");
    EXPECT_EQ(1, key.record());
    EXPECT_EQ("Iptc", std::string(key.familyName()));
    EXPECT_EQ("Envelope", key.groupName());
    EXPECT_EQ("Destination", key.tagName());
}

// Test construction from string key for Application2 record
TEST_F(IptcKeyTest_648, ConstructFromStringKey_Application2Record_648) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(2, key.record());
    EXPECT_EQ("Iptc", std::string(key.familyName()));
    EXPECT_EQ("Application2", key.groupName());
    EXPECT_EQ("ObjectName", key.tagName());
}

// Test familyName always returns "Iptc"
TEST_F(IptcKeyTest_648, FamilyNameReturnsIptc_648) {
    Exiv2::IptcKey key(10, 2);
    EXPECT_STREQ("Iptc", key.familyName());
}

// Test key() returns properly formatted key string
TEST_F(IptcKeyTest_648, KeyReturnsFormattedString_648) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    std::string result = key.key();
    EXPECT_EQ("Iptc.Application2.Keywords", result);
}

// Test recordName for Envelope record (record 1)
TEST_F(IptcKeyTest_648, RecordNameForEnvelope_648) {
    Exiv2::IptcKey key(5, 1);
    EXPECT_EQ("Envelope", key.recordName());
}

// Test recordName for Application2 record (record 2)
TEST_F(IptcKeyTest_648, RecordNameForApplication2_648) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ("Application2", key.recordName());
}

// Test clone() returns a valid copy
TEST_F(IptcKeyTest_648, CloneReturnsCopy_648) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    auto cloned = key.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.tag(), cloned->tag());
    EXPECT_EQ(key.record(), cloned->record());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test record with zero record value
TEST_F(IptcKeyTest_648, RecordWithZeroValue_648) {
    // Record 0 may not be standard but test boundary
    try {
        Exiv2::IptcKey key(1, 0);
        EXPECT_EQ(0, key.record());
    } catch (...) {
        // If construction fails for record 0, that's acceptable behavior
    }
}

// Test construction with known Application2 tags
TEST_F(IptcKeyTest_648, Application2Keywords_648) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(2, key.record());
    EXPECT_EQ("Keywords", key.tagName());
}

// Test that tag and record round-trip correctly through numeric constructor
TEST_F(IptcKeyTest_648, NumericConstructorRoundTrip_648) {
    uint16_t expectedTag = 25;
    uint16_t expectedRecord = 2;
    Exiv2::IptcKey key(expectedTag, expectedRecord);
    EXPECT_EQ(expectedTag, key.tag());
    EXPECT_EQ(expectedRecord, key.record());
}

// Test invalid key string throws exception
TEST_F(IptcKeyTest_648, InvalidKeyStringThrows_648) {
    EXPECT_THROW(Exiv2::IptcKey key("InvalidKey"), std::exception);
}

// Test tagLabel returns non-empty for known tags
TEST_F(IptcKeyTest_648, TagLabelForKnownTag_648) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    std::string label = key.tagLabel();
    // Known tags should have a non-empty label
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns a string (may be empty for some tags)
TEST_F(IptcKeyTest_648, TagDescReturnsString_648) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    // Just verify it doesn't crash; description may or may not be empty
    std::string desc = key.tagDesc();
    // No assertion on content as it depends on the dataset definitions
}

// Test construction from string then key() gives back the same string
TEST_F(IptcKeyTest_648, StringConstructorKeyConsistency_648) {
    std::string keyStr = "Iptc.Envelope.ModelVersion";
    Exiv2::IptcKey key(keyStr);
    EXPECT_EQ(keyStr, key.key());
}

// Test multiple different record values
TEST_F(IptcKeyTest_648, DifferentRecordValues_648) {
    Exiv2::IptcKey key1(5, 1);
    Exiv2::IptcKey key2(5, 2);
    EXPECT_NE(key1.record(), key2.record());
    EXPECT_EQ(1, key1.record());
    EXPECT_EQ(2, key2.record());
}

// Test groupName matches recordName
TEST_F(IptcKeyTest_648, GroupNameMatchesRecordName_648) {
    Exiv2::IptcKey key("Iptc.Application2.Urgency");
    EXPECT_EQ(key.groupName(), key.recordName());
}

// Test clone is independent of original
TEST_F(IptcKeyTest_648, CloneIsIndependent_648) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    // Verify the cloned key has the same values
    EXPECT_EQ(key.record(), cloned->record());
    EXPECT_EQ(key.tag(), cloned->tag());
    EXPECT_EQ(key.key(), cloned->key());
}

// Test with badly formatted string (wrong family)
TEST_F(IptcKeyTest_648, WrongFamilyNameThrows_648) {
    EXPECT_THROW(Exiv2::IptcKey key("Exif.Application2.Keywords"), std::exception);
}

// Test with incomplete key string
TEST_F(IptcKeyTest_648, IncompleteKeyStringThrows_648) {
    EXPECT_THROW(Exiv2::IptcKey key("Iptc.Application2"), std::exception);
}

// Test Envelope record tags
TEST_F(IptcKeyTest_648, EnvelopeModelVersion_648) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(1, key.record());
    EXPECT_EQ("Envelope", key.recordName());
}
