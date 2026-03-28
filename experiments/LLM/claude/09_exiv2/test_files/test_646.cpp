#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <string>

// Test fixture for IptcKey tests
class IptcKeyTest_646 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from tag and record, and verify tag() returns correct value
TEST_F(IptcKeyTest_646, ConstructFromTagAndRecord_TagReturnsCorrectValue_646) {
    Exiv2::IptcKey key(25, 2);
    EXPECT_EQ(key.tag(), 25);
}

// Test construction from tag and record, and verify record() returns correct value
TEST_F(IptcKeyTest_646, ConstructFromTagAndRecord_RecordReturnsCorrectValue_646) {
    Exiv2::IptcKey key(25, 2);
    EXPECT_EQ(key.record(), 2);
}

// Test construction from string key
TEST_F(IptcKeyTest_646, ConstructFromString_ValidKey_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.familyName(), std::string("Iptc"));
    EXPECT_EQ(key.groupName(), std::string("Application2"));
    EXPECT_EQ(key.tagName(), std::string("Keywords"));
}

// Test that key() returns a properly formed key string
TEST_F(IptcKeyTest_646, KeyReturnsProperlyFormedString_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    std::string result = key.key();
    EXPECT_EQ(result, "Iptc.Application2.Keywords");
}

// Test familyName returns "Iptc"
TEST_F(IptcKeyTest_646, FamilyNameReturnsIptc_646) {
    Exiv2::IptcKey key(25, 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test tag and record with zero values (boundary)
TEST_F(IptcKeyTest_646, ZeroTagAndRecord_646) {
    Exiv2::IptcKey key(0, 0);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 0);
}

// Test with maximum uint16_t values (boundary)
TEST_F(IptcKeyTest_646, MaxUint16TagAndRecord_646) {
    // Record values that are valid in IPTC might be limited, 
    // but we test boundary of the uint16_t type
    // This may throw if invalid record, so we test known valid ones
    Exiv2::IptcKey key(65535, 2);
    EXPECT_EQ(key.tag(), 65535);
}

// Test clone creates a copy with same tag
TEST_F(IptcKeyTest_646, CloneReturnsCopyWithSameTag_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->key(), key.key());
}

// Test clone creates a copy with same record
TEST_F(IptcKeyTest_646, CloneReturnsCopyWithSameRecord_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->record(), key.record());
}

// Test recordName returns expected value for Application2
TEST_F(IptcKeyTest_646, RecordNameForApplication2_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test construction with Envelope record
TEST_F(IptcKeyTest_646, ConstructWithEnvelopeRecord_646) {
    Exiv2::IptcKey key("Iptc.Envelope.Destination");
    EXPECT_EQ(key.familyName(), std::string("Iptc"));
    EXPECT_EQ(key.groupName(), std::string("Envelope"));
}

// Test tag construction with record 1 (Envelope)
TEST_F(IptcKeyTest_646, ConstructFromTagWithEnvelopeRecord_646) {
    Exiv2::IptcKey key(5, 1);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.recordName(), "Envelope");
}

// Test tag construction with record 2 (Application2)
TEST_F(IptcKeyTest_646, ConstructFromTagWithApplication2Record_646) {
    Exiv2::IptcKey key(25, 2);
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.recordName(), "Application2");
}

// Test that tagLabel returns a non-empty string for known tags
TEST_F(IptcKeyTest_646, TagLabelForKnownTag_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test key() reconstructed from tag and record matches expected format
TEST_F(IptcKeyTest_646, KeyFromTagAndRecordFormat_646) {
    Exiv2::IptcKey key(25, 2);
    std::string k = key.key();
    // Key should start with "Iptc."
    EXPECT_EQ(k.substr(0, 5), "Iptc.");
}

// Test that constructing from invalid key string throws
TEST_F(IptcKeyTest_646, ConstructFromInvalidKeyThrows_646) {
    EXPECT_THROW(Exiv2::IptcKey key("Invalid.Key.Format"), std::exception);
}

// Test that constructing from empty string throws
TEST_F(IptcKeyTest_646, ConstructFromEmptyStringThrows_646) {
    EXPECT_THROW(Exiv2::IptcKey key(""), std::exception);
}

// Test copy via clone preserves all attributes
TEST_F(IptcKeyTest_646, ClonePreservesAllAttributes_646) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->record(), key.record());
}

// Test tagDesc for a known tag returns something (may be empty for unknown)
TEST_F(IptcKeyTest_646, TagDescForKnownTag_646) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    // Just verify it doesn't crash; description may or may not be empty
    std::string desc = key.tagDesc();
    // No assertion on content since it depends on implementation
    SUCCEED();
}

// Test multiple different known IPTC tags
TEST_F(IptcKeyTest_646, DifferentKnownTags_646) {
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::IptcKey key2("Iptc.Application2.Byline");

    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_EQ(key1.record(), key2.record());
}
