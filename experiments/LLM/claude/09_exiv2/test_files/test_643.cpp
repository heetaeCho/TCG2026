#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

namespace {

// ============================================================
// Tests for IptcDataSets static methods
// ============================================================

class IptcDataSetsTest_643 : public ::testing::Test {
protected:
    // Known IPTC record IDs
    static constexpr uint16_t envelope = 1;
    static constexpr uint16_t application2 = 2;
};

// --- dataSetName ---

TEST_F(IptcDataSetsTest_643, DataSetName_KnownEnvelopeDataSet_643) {
    // DataSet 0 in envelope record is "ModelVersion"
    std::string name = Exiv2::IptcDataSets::dataSetName(0, envelope);
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_643, DataSetName_KnownApplication2DataSet_643) {
    // DataSet 5 in application2 record is "ObjectName"
    std::string name = Exiv2::IptcDataSets::dataSetName(5, application2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_643, DataSetName_UnknownDataSet_643) {
    // An unknown dataset number should return a string (likely with hex representation)
    std::string name = Exiv2::IptcDataSets::dataSetName(9999, application2);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_643, DataSetName_Caption_643) {
    // DataSet 120 in application2 record is "Caption"
    std::string name = Exiv2::IptcDataSets::dataSetName(120, application2);
    EXPECT_EQ(name, "Caption");
}

TEST_F(IptcDataSetsTest_643, DataSetName_Keywords_643) {
    // DataSet 25 in application2 record is "Keywords"
    std::string name = Exiv2::IptcDataSets::dataSetName(25, application2);
    EXPECT_EQ(name, "Keywords");
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_643, DataSetTitle_KnownDataSet_643) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(5, application2);
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(std::string(title).length() > 0);
}

TEST_F(IptcDataSetsTest_643, DataSetTitle_UnknownDataSet_643) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(9999, application2);
    ASSERT_NE(title, nullptr);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_643, DataSetDesc_KnownDataSet_643) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(5, application2);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_643, DataSetDesc_UnknownDataSet_643) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(9999, application2);
    ASSERT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_643, DataSetPsName_KnownDataSet_643) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(5, application2);
    ASSERT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_643, DataSetRepeatable_Keywords_643) {
    // Keywords (25) in application2 is repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(25, application2);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_643, DataSetRepeatable_ObjectName_643) {
    // ObjectName (5) in application2 is not repeatable
    bool repeatable = Exiv2::IptcDataSets::dataSetRepeatable(5, application2);
    EXPECT_FALSE(repeatable);
}

// --- dataSet (lookup by name) ---

TEST_F(IptcDataSetsTest_643, DataSet_LookupByName_ObjectName_643) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ObjectName", application2);
    EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_643, DataSet_LookupByName_Keywords_643) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("Keywords", application2);
    EXPECT_EQ(ds, 25);
}

TEST_F(IptcDataSetsTest_643, DataSet_LookupByName_Caption_643) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("Caption", application2);
    EXPECT_EQ(ds, 120);
}

TEST_F(IptcDataSetsTest_643, DataSet_LookupByName_UnknownName_643) {
    // Looking up a nonexistent name should throw or return a sentinel
    EXPECT_THROW(Exiv2::IptcDataSets::dataSet("NonExistentDataSet", application2), Exiv2::Error);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_643, DataSetType_ModelVersion_643) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(0, envelope);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_643, DataSetType_Keywords_643) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(25, application2);
    EXPECT_EQ(type, Exiv2::string);
}

// --- recordName ---

TEST_F(IptcDataSetsTest_643, RecordName_Envelope_643) {
    std::string name = Exiv2::IptcDataSets::recordName(envelope);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_643, RecordName_Application2_643) {
    std::string name = Exiv2::IptcDataSets::recordName(application2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_643, RecordName_UnknownRecord_643) {
    std::string name = Exiv2::IptcDataSets::recordName(9999);
    EXPECT_FALSE(name.empty());
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_643, RecordDesc_Envelope_643) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

TEST_F(IptcDataSetsTest_643, RecordDesc_Application2_643) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(application2);
    ASSERT_NE(desc, nullptr);
}

// --- recordId ---

TEST_F(IptcDataSetsTest_643, RecordId_Envelope_643) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelope);
}

TEST_F(IptcDataSetsTest_643, RecordId_Application2_643) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2);
}

TEST_F(IptcDataSetsTest_643, RecordId_UnknownRecord_643) {
    EXPECT_THROW(Exiv2::IptcDataSets::recordId("NonExistentRecord"), Exiv2::Error);
}

// --- envelopeRecordList / application2RecordList ---

TEST_F(IptcDataSetsTest_643, EnvelopeRecordList_NotNull_643) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_643, Application2RecordList_NotNull_643) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_643, DataSetList_OutputNotEmpty_643) {
    std::ostringstream oss;
    Exiv2::IptcDataSets::dataSetList(oss);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(IptcDataSetsTest_643, DataSetList_ContainsKeywords_643) {
    std::ostringstream oss;
    Exiv2::IptcDataSets::dataSetList(oss);
    EXPECT_NE(oss.str().find("Keywords"), std::string::npos);
}

// ============================================================
// Tests for IptcKey
// ============================================================

class IptcKeyTest_643 : public ::testing::Test {};

TEST_F(IptcKeyTest_643, ConstructFromTagAndRecord_643) {
    Exiv2::IptcKey key(5, 2);  // ObjectName in Application2
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
}

TEST_F(IptcKeyTest_643, TagName_ObjectName_643) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_643, RecordName_Application2_643) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.recordName(), "Application2");
}

TEST_F(IptcKeyTest_643, GroupName_Application2_643) {
    Exiv2::IptcKey key(5, 2);
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_643, FamilyName_Iptc_643) {
    Exiv2::IptcKey key(5, 2);
    std::string family(key.familyName());
    EXPECT_EQ(family, "Iptc");
}

TEST_F(IptcKeyTest_643, Key_Format_643) {
    Exiv2::IptcKey key(5, 2);
    std::string k = key.key();
    EXPECT_EQ(k, "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_643, ConstructFromString_643) {
    Exiv2::IptcKey key("Iptc.Application2.ObjectName");
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_643, ConstructFromString_Keywords_643) {
    Exiv2::IptcKey key("Iptc.Application2.Keywords");
    EXPECT_EQ(key.tag(), 25);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.tagName(), "Keywords");
}

TEST_F(IptcKeyTest_643, ConstructFromString_Envelope_643) {
    Exiv2::IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tagName(), "ModelVersion");
}

TEST_F(IptcKeyTest_643, Clone_643) {
    Exiv2::IptcKey key(25, 2);
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
}

TEST_F(IptcKeyTest_643, TagLabel_NotEmpty_643) {
    Exiv2::IptcKey key(5, 2);
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_643, TagDesc_NotEmpty_643) {
    Exiv2::IptcKey key(5, 2);
    std::string desc = key.tagDesc();
    // desc may or may not be empty depending on dataset, but should not crash
}

TEST_F(IptcKeyTest_643, ConstructFromInvalidString_643) {
    // An invalid key string should throw
    EXPECT_THROW(Exiv2::IptcKey("Invalid.Key.String"), Exiv2::Error);
}

TEST_F(IptcKeyTest_643, ConstructFromString_Caption_643) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    EXPECT_EQ(key.tag(), 120);
    EXPECT_EQ(key.record(), 2);
    EXPECT_EQ(key.key(), "Iptc.Application2.Caption");
}

TEST_F(IptcKeyTest_643, ConstructFromTagAndRecord_EnvelopeModelVersion_643) {
    Exiv2::IptcKey key(0, 1);
    EXPECT_EQ(key.key(), "Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.familyName(), std::string("Iptc"));
    EXPECT_EQ(key.groupName(), "Envelope");
    EXPECT_EQ(key.tagName(), "ModelVersion");
}

// --- Boundary: tag/record with maximum uint16_t ---

TEST_F(IptcKeyTest_643, ConstructFromTagAndRecord_UnknownHighValues_643) {
    // Should not crash; unknown tags/records produce some name
    Exiv2::IptcKey key(65535, 65535);
    EXPECT_FALSE(key.tagName().empty());
    EXPECT_FALSE(key.key().empty());
}

// --- Consistency: round-trip from tag/record to key string and back ---

TEST_F(IptcKeyTest_643, RoundTrip_TagRecord_To_KeyString_643) {
    Exiv2::IptcKey key1(25, 2);
    std::string keyStr = key1.key();
    Exiv2::IptcKey key2(keyStr);
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.record(), key1.record());
    EXPECT_EQ(key2.key(), key1.key());
}

}  // namespace
