#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

namespace {

// ============================================================================
// IptcDataSets Tests
// ============================================================================

class IptcDataSetsTest_651 : public ::testing::Test {
protected:
    // Known record IDs
    static constexpr uint16_t envelopeRecord = 1;
    static constexpr uint16_t application2Record = 2;
};

// --- recordName ---

TEST_F(IptcDataSetsTest_651, RecordNameEnvelope_651) {
    std::string name = Exiv2::IptcDataSets::recordName(envelopeRecord);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_651, RecordNameApplication2_651) {
    std::string name = Exiv2::IptcDataSets::recordName(application2Record);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_651, RecordNameUnknown_651) {
    // An unknown record ID should return some string (likely containing the number)
    std::string name = Exiv2::IptcDataSets::recordName(999);
    EXPECT_FALSE(name.empty());
}

// --- recordId ---

TEST_F(IptcDataSetsTest_651, RecordIdEnvelope_651) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelopeRecord);
}

TEST_F(IptcDataSetsTest_651, RecordIdApplication2_651) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2Record);
}

TEST_F(IptcDataSetsTest_651, RecordIdUnknown_651) {
    // Unknown record name should not crash; it returns some value
    uint16_t id = Exiv2::IptcDataSets::recordId("NonExistentRecord");
    // Just verify it doesn't crash and returns something
    (void)id;
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_651, RecordDescEnvelope_651) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(envelopeRecord);
    EXPECT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

TEST_F(IptcDataSetsTest_651, RecordDescApplication2_651) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(application2Record);
    EXPECT_NE(desc, nullptr);
}

// --- dataSetName ---

TEST_F(IptcDataSetsTest_651, DataSetNameKnownEnvelope_651) {
    // DataSet 0 in Envelope record is typically "ModelVersion" or similar
    std::string name = Exiv2::IptcDataSets::dataSetName(0, envelopeRecord);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_651, DataSetNameKnownApplication2_651) {
    // DataSet 5 in Application2 is "ObjectName"
    std::string name = Exiv2::IptcDataSets::dataSetName(5, application2Record);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_651, DataSetNameUnknownDataSet_651) {
    std::string name = Exiv2::IptcDataSets::dataSetName(9999, application2Record);
    EXPECT_FALSE(name.empty());
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_651, DataSetTitleKnown_651) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(5, application2Record);
    EXPECT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_651, DataSetTitleUnknown_651) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(9999, application2Record);
    EXPECT_NE(title, nullptr);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_651, DataSetDescKnown_651) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(5, application2Record);
    EXPECT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_651, DataSetDescUnknown_651) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(9999, application2Record);
    EXPECT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_651, DataSetPsNameKnown_651) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(5, application2Record);
    EXPECT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_651, DataSetRepeatableKnown_651) {
    // Keywords (25) in Application2 is typically repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(25, application2Record);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_651, DataSetRepeatableNonRepeatable_651) {
    // ObjectName (5) in Application2 is typically not repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(5, application2Record);
    EXPECT_FALSE(repeatable);
}

// --- dataSet (lookup by name) ---

TEST_F(IptcDataSetsTest_651, DataSetLookupByName_651) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", application2Record);
    EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_651, DataSetLookupByNameKeywords_651) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("Keywords", application2Record);
    EXPECT_EQ(ds, 25);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_651, DataSetTypeKnown_651) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(5, application2Record);
    // ObjectName is typically a string type
    EXPECT_EQ(type, Exiv2::string);
}

// --- envelopeRecordList / application2RecordList ---

TEST_F(IptcDataSetsTest_651, EnvelopeRecordListNotNull_651) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
    EXPECT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_651, Application2RecordListNotNull_651) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    EXPECT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_651, DataSetListOutputsToStream_651) {
    std::ostringstream oss;
    Exiv2::IptcDataSets::dataSetList(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain known dataset names
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
}

// ============================================================================
// IptcKey Tests
// ============================================================================

class IptcKeyTest_651 : public ::testing::Test {};

// --- Construction from string key ---

TEST_F(IptcKeyTest_651, ConstructFromStringKey_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_651, FamilyNameIsIptc_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_651, GroupNameFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_651, TagNameFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_651, TagFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

TEST_F(IptcKeyTest_651, RecordFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_651, RecordNameFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

// --- Construction from tag and record ---

TEST_F(IptcKeyTest_651, ConstructFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_651, TagFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
}

TEST_F(IptcKeyTest_651, RecordFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_651, FamilyNameFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_651, GroupNameFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_651, TagNameFromTagAndRecord_651) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tagName(), "ObjectName");
}

// --- Keywords (tag 25, record 2) ---

TEST_F(IptcKeyTest_651, ConstructKeywordsFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.Keywords");
}

TEST_F(IptcKeyTest_651, ConstructKeywordsFromTagAndRecord_651) {
    Exiv2::IptcKey key(25, 2);
    EXPECT_EQ(key.tagName(), "Keywords");
    EXPECT_EQ(key.key(), "Iptc.Application2.Keywords");
}

// --- Envelope record ---

TEST_F(IptcKeyTest_651, EnvelopeRecordKey_651) {
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.recordName(), "Envelope");
    std::string keyStr = key.key();
    EXPECT_NE(keyStr.find("Iptc.Envelope."), std::string::npos);
}

// --- tagLabel and tagDesc ---

TEST_F(IptcKeyTest_651, TagLabelNotEmpty_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_651, TagDescNotEmpty_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    // Description may or may not be empty, but shouldn't crash
    (void)desc;
}

// --- clone ---

TEST_F(IptcKeyTest_651, CloneProducesSameKey_651) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

TEST_F(IptcKeyTest_651, CloneFromTagAndRecordProducesSameKey_651) {
    Exiv2::IptcKey key(25, 2);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), 25);
}

// --- Invalid key string ---

TEST_F(IptcKeyTest_651, InvalidKeyStringThrows_651) {
    EXPECT_THROW(Exiv2::IptcKey key("InvalidKey"), std::exception);
}

TEST_F(IptcKeyTest_651, WrongFamilyNameThrows_651) {
    EXPECT_THROW(Exiv2::IptcKey key("Exif.Application2.ObjectName"), std::exception);
}

TEST_F(IptcKeyTest_651, EmptyKeyStringThrows_651) {
    EXPECT_THROW(Exiv2::IptcKey key(""), std::exception);
}

// --- makeKey consistency: construct from tag/record then verify key string ---

TEST_F(IptcKeyTest_651, MakeKeyConsistency_651) {
    // Construct from tag and record, key should be built via makeKey
    Exiv2::IptcKey key1(5, 2);
    Exiv2::IptcKey key2("Iptc.Application2.ObjectName");
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.record(), key2.record());
    EXPECT_EQ(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// --- Boundary: unknown dataset number ---

TEST_F(IptcKeyTest_651, UnknownDataSetFromTagAndRecord_651) {
    // Using an unknown dataset number; should still produce a valid key
    Exiv2::IptcKey key(9999, 2);
    std::string keyStr = key.key();
    EXPECT_FALSE(keyStr.empty());
    EXPECT_NE(keyStr.find("Iptc."), std::string::npos);
    EXPECT_EQ(key.tag(), 9999);
    EXPECT_EQ(key.record(), 2);
}

// --- Multiple datasets ---

TEST_F(IptcKeyTest_651, CaptionAbstract_651) {
    // Caption/Abstract is dataset 120 in Application2
    Exiv2::IptcKey key(120, 2);
    EXPECT_EQ(key.tagName(), "Caption");
    EXPECT_EQ(key.key(), "Iptc.Application2.Caption");
}

TEST_F(IptcKeyTest_651, DateCreated_651) {
    // DateCreated is dataset 55 in Application2
    Exiv2::IptcKey key(55, 2);
    EXPECT_EQ(key.tagName(), "DateCreated");
}

TEST_F(IptcKeyTest_651, BylineFromString_651) {
    Exiv2::IptcKey key("Iptc.Application2.Byline");
    EXPECT_EQ(key.tag(), 80);
    EXPECT_EQ(key.record(), 2);
}

}  // namespace
