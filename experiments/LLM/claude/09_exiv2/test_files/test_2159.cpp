#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <cstdint>

namespace {

// Test fixture for IptcKey tests
class IptcKeyTest_2159 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction from tag and record
// ============================================================

TEST_F(IptcKeyTest_2159, ConstructFromTagAndRecord_BasicValues_2159) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_2159, ConstructFromTagAndRecord_ZeroValues_2159) {
    Exiv2::IptcKey key(0, 0);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 0);
}

TEST_F(IptcKeyTest_2159, ConstructFromTagAndRecord_MaxValues_2159) {
    Exiv2::IptcKey key(65535, 65535);
    EXPECT_EQ(key.tag(), 65535);
    EXPECT_EQ(key.record(), 65535);
}

TEST_F(IptcKeyTest_2159, FamilyName_ReturnsIptc_2159) {
    Exiv2::IptcKey key(5, 2);
    std::string familyName = key.familyName();
    EXPECT_EQ(familyName, "Iptc");
}

TEST_F(IptcKeyTest_2159, KeyFormat_FromTagAndRecord_2159) {
    // Record 2 is "Application2", tag 5 is "ObjectName" in standard IPTC
    Exiv2::IptcKey key(5, 2);
    std::string keyStr = key.key();
    EXPECT_FALSE(keyStr.empty());
    // Key should start with "Iptc."
    EXPECT_EQ(keyStr.substr(0, 5), "Iptc.");
}

TEST_F(IptcKeyTest_2159, GroupName_FromTagAndRecord_2159) {
    Exiv2::IptcKey key(5, 2);
    std::string groupName = key.groupName();
    EXPECT_FALSE(groupName.empty());
}

TEST_F(IptcKeyTest_2159, TagName_FromTagAndRecord_2159) {
    Exiv2::IptcKey key(5, 2);
    std::string tagName = key.tagName();
    EXPECT_FALSE(tagName.empty());
}

TEST_F(IptcKeyTest_2159, RecordName_FromTagAndRecord_2159) {
    Exiv2::IptcKey key(5, 2);
    std::string recordName = key.recordName();
    EXPECT_FALSE(recordName.empty());
}

// ============================================================
// Construction from string key
// ============================================================

TEST_F(IptcKeyTest_2159, ConstructFromString_ValidKey_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
    EXPECT_EQ(key.familyName(), std::string("Iptc"));
}

TEST_F(IptcKeyTest_2159, ConstructFromString_TagAndRecordCorrect_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    // ObjectName is tag 5, Application2 is record 2
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_2159, ConstructFromString_GroupName_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_2159, ConstructFromString_TagName_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_2159, ConstructFromString_RecordName_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

TEST_F(IptcKeyTest_2159, ConstructFromString_InvalidKey_Throws_2159) {
    EXPECT_THROW(Exiv2::IptcKey("InvalidKey"), Exiv2::Error);
}

TEST_F(IptcKeyTest_2159, ConstructFromString_WrongFamily_Throws_2159) {
    EXPECT_THROW(Exiv2::IptcKey("Exif.Application2.ObjectName"), Exiv2::Error);
}

TEST_F(IptcKeyTest_2159, ConstructFromString_EmptyString_Throws_2159) {
    EXPECT_THROW(Exiv2::IptcKey(""), Exiv2::Error);
}

// ============================================================
// Clone
// ============================================================

TEST_F(IptcKeyTest_2159, Clone_ReturnsValidCopy_2159) {
    Exiv2::IptcKey key(5, 2);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
}

TEST_F(IptcKeyTest_2159, Clone_FromStringKey_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), "Iptc.Application2.ObjectName");
}

// ============================================================
// Tag label and description
// ============================================================

TEST_F(IptcKeyTest_2159, TagLabel_KnownTag_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    // Known tags should have a non-empty label
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_2159, TagDesc_KnownTag_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    // tagDesc may or may not be empty, but it should not throw
    std::string desc = key.tagDesc();
    // Just verify it doesn't crash; desc might be empty for some tags
}

// ============================================================
// Various known IPTC keys
// ============================================================

TEST_F(IptcKeyTest_2159, ConstructFromString_Keywords_2159) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.Keywords");
}

TEST_F(IptcKeyTest_2159, ConstructFromString_Urgency_2159) {
    Exiv2::IptcKey key("Iptc.Application2.Urgency");
    EXPECT_EQ(key.tag(), 10);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_2159, ConstructFromString_Byline_2159) {
    Exiv2::IptcKey key("Iptc.Application2.Byline");
    EXPECT_EQ(key.tag(), 80);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_2159, ConstructFromString_Caption_2159) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    EXPECT_EQ(key.tag(), 120);
    EXPECT_EQ(key.record(), 2);
}

// ============================================================
// Envelope record (record 1)
// ============================================================

TEST_F(IptcKeyTest_2159, ConstructFromTagAndRecord_EnvelopeRecord_2159) {
    // Record 1 is the Envelope record
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tag(), 0);
    std::string keyStr = key.key();
    EXPECT_FALSE(keyStr.empty());
    EXPECT_EQ(keyStr.substr(0, 5), "Iptc.");
}

TEST_F(IptcKeyTest_2159, ConstructFromString_EnvelopeRecord_2159) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.groupName(), "Envelope");
}

// ============================================================
// Consistency between constructors
// ============================================================

TEST_F(IptcKeyTest_2159, Consistency_TagRecordVsString_2159) {
    Exiv2::IptcKey fromTag(5, 2);
    Exiv2::IptcKey fromStr("Iptc.Application2.ObjectName");
    
    EXPECT_EQ(fromTag.key(), fromStr.key());
    EXPECT_EQ(fromTag.tag(), fromStr.tag());
    EXPECT_EQ(fromTag.record(), fromStr.record());
    EXPECT_EQ(fromTag.familyName(), fromStr.familyName());
    EXPECT_EQ(fromTag.groupName(), fromStr.groupName());
    EXPECT_EQ(fromTag.tagName(), fromStr.tagName());
    EXPECT_EQ(fromTag.recordName(), fromStr.recordName());
}

// ============================================================
// Unknown tags
// ============================================================

TEST_F(IptcKeyTest_2159, UnknownTag_DoesNotThrow_2159) {
    // Using a tag number that is likely not defined in standard IPTC
    Exiv2::IptcKey key(9999, 2);
    // Should still work, just with generic/unknown names
    EXPECT_EQ(key.tag(), 9999);
    EXPECT_EQ(key.record(), 2);
    EXPECT_FALSE(key.key().empty());
}

// ============================================================
// Write method (inherited from Key)
// ============================================================

TEST_F(IptcKeyTest_2159, WriteToStream_2159) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::ostringstream os;
    os << key;
    EXPECT_EQ(os.str(), key.key());
}

}  // namespace
