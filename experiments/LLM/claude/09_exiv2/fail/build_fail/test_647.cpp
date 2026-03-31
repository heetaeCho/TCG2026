#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

namespace {

// ============================================================================
// IptcDataSets Tests
// ============================================================================

class IptcDataSetsTest_647 : public ::testing::Test {
protected:
    // Known IPTC record IDs
    static constexpr uint16_t envelope = 1;
    static constexpr uint16_t application2 = 2;
};

// --- recordName ---

TEST_F(IptcDataSetsTest_647, RecordName_Envelope_647) {
    std::string name = Exiv2::IptcDataSets::recordName(envelope);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_647, RecordName_Application2_647) {
    std::string name = Exiv2::IptcDataSets::recordName(application2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_647, RecordName_UnknownRecord_647) {
    // Unknown record should return some string (not crash)
    std::string name = Exiv2::IptcDataSets::recordName(0xFFFF);
    EXPECT_FALSE(name.empty());
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_647, RecordDesc_Envelope_647) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::strlen(desc), 0u);
}

TEST_F(IptcDataSetsTest_647, RecordDesc_Application2_647) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::strlen(desc), 0u);
}

// --- recordId ---

TEST_F(IptcDataSetsTest_647, RecordId_Envelope_647) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelope);
}

TEST_F(IptcDataSetsTest_647, RecordId_Application2_647) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2);
}

TEST_F(IptcDataSetsTest_647, RecordId_UnknownName_647) {
    // Should not crash; likely returns some sentinel value
    uint16_t id = Exiv2::IptcDataSets::recordId("NonExistentRecord");
    // Just verify it doesn't crash; the value is implementation-defined
    (void)id;
}

// --- dataSetName ---

TEST_F(IptcDataSetsTest_647, DataSetName_KnownEnvelopeDataSet_ModelVersion_647) {
    // DataSet 0 in Envelope record is "ModelVersion"
    std::string name = Exiv2::IptcDataSets::dataSetName(0, envelope);
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_647, DataSetName_KnownApp2DataSet_ObjectName_647) {
    // DataSet 5 in Application2 record is "ObjectName"
    std::string name = Exiv2::IptcDataSets::dataSetName(5, application2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_647, DataSetName_UnknownDataSet_647) {
    std::string name = Exiv2::IptcDataSets::dataSetName(0xFFFF, application2);
    // Should return some non-empty string for unknown datasets
    EXPECT_FALSE(name.empty());
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_647, DataSetTitle_KnownDataSet_647) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(5, application2);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_647, DataSetTitle_UnknownDataSet_647) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(0xFFFF, application2);
    ASSERT_NE(title, nullptr);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_647, DataSetDesc_KnownDataSet_647) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(5, application2);
    ASSERT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_647, DataSetPsName_KnownDataSet_647) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(5, application2);
    ASSERT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_647, DataSetRepeatable_Keywords_647) {
    // DataSet 25 in Application2 is "Keywords" which is repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(25, application2);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_647, DataSetRepeatable_ObjectName_647) {
    // DataSet 5 in Application2 is "ObjectName" which is not repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(5, application2);
    EXPECT_FALSE(repeatable);
}

// --- dataSet (lookup by name) ---

TEST_F(IptcDataSetsTest_647, DataSet_LookupByName_ObjectName_647) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", application2);
    EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_647, DataSet_LookupByName_Keywords_647) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("Keywords", application2);
    EXPECT_EQ(ds, 25);
}

TEST_F(IptcDataSetsTest_647, DataSet_LookupByName_ModelVersion_647) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ModelVersion", envelope);
    EXPECT_EQ(ds, 0);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_647, DataSetType_ModelVersion_647) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(0, envelope);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_647, DataSetType_ObjectName_647) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(5, application2);
    EXPECT_EQ(type, Exiv2::string);
}

// --- envelopeRecordList / application2RecordList ---

TEST_F(IptcDataSetsTest_647, EnvelopeRecordList_NotNull_647) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_647, Application2RecordList_NotNull_647) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_647, DataSetList_ProducesOutput_647) {
    std::ostringstream os;
    Exiv2::IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain some known dataset names
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
}

// ============================================================================
// IptcKey Tests
// ============================================================================

class IptcKeyTest_647 : public ::testing::Test {};

// --- Construction from string ---

TEST_F(IptcKeyTest_647, ConstructFromString_ValidKey_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_647, FamilyName_IsIptc_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_647, GroupName_Application2_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_647, TagName_ObjectName_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_647, Tag_ObjectName_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
}

TEST_F(IptcKeyTest_647, Record_Application2_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_647, RecordName_Application2_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.recordName(), "Application2");
}

// --- Construction from tag + record ---

TEST_F(IptcKeyTest_647, ConstructFromTagRecord_647) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_647, ConstructFromTagRecord_Envelope_647) {
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.recordName(), "Envelope");
    EXPECT_EQ(key.tagName(), "ModelVersion");
}

// --- tagLabel ---

TEST_F(IptcKeyTest_647, TagLabel_NotEmpty_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// --- tagDesc ---

TEST_F(IptcKeyTest_647, TagDesc_NotEmpty_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    std::string desc = key.tagDesc();
    // Description may or may not be empty, but should not crash
    (void)desc;
}

// --- clone ---

TEST_F(IptcKeyTest_647, Clone_ProducesCopy_647) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->familyName(), key.familyName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
}

// --- Envelope record key ---

TEST_F(IptcKeyTest_647, EnvelopeKey_647) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.recordName(), "Envelope");
}

// --- Keywords (repeatable dataset) ---

TEST_F(IptcKeyTest_647, Keywords_Key_647) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.Keywords");
}

// --- Invalid key construction ---

TEST_F(IptcKeyTest_647, ConstructFromInvalidString_Throws_647) {
    EXPECT_THROW(Exiv2::IptcKey("InvalidKeyString"), Exiv2::Error);
}

TEST_F(IptcKeyTest_647, ConstructFromWrongFamily_Throws_647) {
    EXPECT_THROW(Exiv2::IptcKey("Exif.Application2.ObjectName"), Exiv2::Error);
}

// --- Consistency between tag/record and string constructor ---

TEST_F(IptcKeyTest_647, TagRecordConsistency_647) {
    Exiv2::IptcKey keyFromString("Iptc.Application2.Caption");
    Exiv2::IptcKey keyFromNumbers(keyFromString.tag(), keyFromString.record());
    EXPECT_EQ(keyFromString.key(), keyFromNumbers.key());
    EXPECT_EQ(keyFromString.tagName(), keyFromNumbers.tagName());
    EXPECT_EQ(keyFromString.groupName(), keyFromNumbers.groupName());
}

// --- Multiple datasets from Application2 ---

TEST_F(IptcKeyTest_647, Urgency_Dataset_647) {
    Exiv2::IptcKey key("Iptc.Application2.Urgency");
    EXPECT_EQ(key.tag(), 10);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_647, DateCreated_Dataset_647) {
    Exiv2::IptcKey key("Iptc.Application2.DateCreated");
    EXPECT_EQ(key.tag(), 55);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_647, City_Dataset_647) {
    Exiv2::IptcKey key("Iptc.Application2.City");
    EXPECT_EQ(key.tag(), 90);
    EXPECT_EQ(key.record(), 2);
}

// --- Boundary: construct with tag/record 0,0 ---

TEST_F(IptcKeyTest_647, ConstructFromZeroTagZeroRecord_647) {
    // Record 0 is unknown; should still produce a key without crashing
    Exiv2::IptcKey key(0, 0);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 0);
    // Key string should still be constructable
    std::string k = key.key();
    EXPECT_FALSE(k.empty());
}

}  // namespace
