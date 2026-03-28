#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Known record IDs from IPTC standard
static constexpr uint16_t envelopeRecord = 1;
static constexpr uint16_t application2Record = 2;

// Known dataset numbers for envelope record
static constexpr uint16_t envelopeModelVersion = 0;
static constexpr uint16_t envelopeDestination = 5;
static constexpr uint16_t envelopeFileFormat = 20;
static constexpr uint16_t envelopeCharacterSet = 90;

// Known dataset numbers for application2 record
static constexpr uint16_t app2RecordVersion = 0;
static constexpr uint16_t app2ObjectName = 5;
static constexpr uint16_t app2Keywords = 25;
static constexpr uint16_t app2Caption = 120;
static constexpr uint16_t app2Byline = 80;
static constexpr uint16_t app2City = 90;
static constexpr uint16_t app2Country = 101;

class IptcDataSetsTest_634 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for dataSetRepeatable
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_Keywords_ReturnsTrue_634) {
    // Keywords (25) in Application2 record is repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2Keywords, application2Record);
    EXPECT_TRUE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_RecordVersion_ReturnsFalse_634) {
    // RecordVersion (0) in Application2 record is not repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2RecordVersion, application2Record);
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_ObjectName_ReturnsFalse_634) {
    // ObjectName (5) in Application2 is not repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2ObjectName, application2Record);
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_Byline_ReturnsTrue_634) {
    // Byline (80) in Application2 is repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2Byline, application2Record);
    EXPECT_TRUE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_UnknownDataSet_ReturnsFalse_634) {
    // Unknown dataset should return unknownDataSet.repeatable_ which is false
    bool result = IptcDataSets::dataSetRepeatable(9999, application2Record);
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_Destination_ReturnsTrue_634) {
    // Destination (5) in envelope record is repeatable
    bool result = IptcDataSets::dataSetRepeatable(envelopeDestination, envelopeRecord);
    EXPECT_TRUE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_EnvelopeModelVersion_ReturnsFalse_634) {
    bool result = IptcDataSets::dataSetRepeatable(envelopeModelVersion, envelopeRecord);
    EXPECT_FALSE(result);
}

// ============================================================
// Tests for dataSetName
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetName_Keywords_634) {
    std::string name = IptcDataSets::dataSetName(app2Keywords, application2Record);
    EXPECT_EQ(name, "Keywords");
}

TEST_F(IptcDataSetsTest_634, DataSetName_Caption_634) {
    std::string name = IptcDataSets::dataSetName(app2Caption, application2Record);
    EXPECT_EQ(name, "Caption");
}

TEST_F(IptcDataSetsTest_634, DataSetName_ObjectName_634) {
    std::string name = IptcDataSets::dataSetName(app2ObjectName, application2Record);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_634, DataSetName_UnknownDataSet_634) {
    // Unknown dataset number should return something like "0x????" hex representation
    std::string name = IptcDataSets::dataSetName(9999, application2Record);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_634, DataSetName_RecordVersion_Envelope_634) {
    std::string name = IptcDataSets::dataSetName(envelopeModelVersion, envelopeRecord);
    EXPECT_EQ(name, "ModelVersion");
}

// ============================================================
// Tests for dataSetTitle
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetTitle_Keywords_634) {
    const char* title = IptcDataSets::dataSetTitle(app2Keywords, application2Record);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Keywords");
}

TEST_F(IptcDataSetsTest_634, DataSetTitle_UnknownDataSet_634) {
    const char* title = IptcDataSets::dataSetTitle(9999, application2Record);
    ASSERT_NE(title, nullptr);
}

// ============================================================
// Tests for dataSetDesc
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetDesc_Keywords_634) {
    const char* desc = IptcDataSets::dataSetDesc(app2Keywords, application2Record);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

TEST_F(IptcDataSetsTest_634, DataSetDesc_UnknownDataSet_634) {
    const char* desc = IptcDataSets::dataSetDesc(9999, application2Record);
    ASSERT_NE(desc, nullptr);
}

// ============================================================
// Tests for dataSetPsName
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetPsName_Keywords_634) {
    const char* psName = IptcDataSets::dataSetPsName(app2Keywords, application2Record);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_634, DataSetPsName_UnknownDataSet_634) {
    const char* psName = IptcDataSets::dataSetPsName(9999, application2Record);
    ASSERT_NE(psName, nullptr);
}

// ============================================================
// Tests for dataSet (lookup by name)
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSet_Keywords_634) {
    uint16_t ds = IptcDataSets::dataSet("Keywords", application2Record);
    EXPECT_EQ(ds, app2Keywords);
}

TEST_F(IptcDataSetsTest_634, DataSet_Caption_634) {
    uint16_t ds = IptcDataSets::dataSet("Caption", application2Record);
    EXPECT_EQ(ds, app2Caption);
}

TEST_F(IptcDataSetsTest_634, DataSet_ObjectName_634) {
    uint16_t ds = IptcDataSets::dataSet("ObjectName", application2Record);
    EXPECT_EQ(ds, app2ObjectName);
}

TEST_F(IptcDataSetsTest_634, DataSet_UnknownName_634) {
    // Looking up a non-existent name should return something (likely 0xffff)
    uint16_t ds = IptcDataSets::dataSet("NonExistentDataSet", application2Record);
    EXPECT_EQ(ds, 0xffff);
}

// ============================================================
// Tests for dataSetType
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetType_Keywords_IsString_634) {
    TypeId type = IptcDataSets::dataSetType(app2Keywords, application2Record);
    EXPECT_EQ(type, string);
}

TEST_F(IptcDataSetsTest_634, DataSetType_RecordVersion_634) {
    TypeId type = IptcDataSets::dataSetType(app2RecordVersion, application2Record);
    EXPECT_EQ(type, unsignedShort);
}

TEST_F(IptcDataSetsTest_634, DataSetType_UnknownDataSet_634) {
    TypeId type = IptcDataSets::dataSetType(9999, application2Record);
    EXPECT_EQ(type, string);
}

// ============================================================
// Tests for recordName
// ============================================================

TEST_F(IptcDataSetsTest_634, RecordName_Envelope_634) {
    std::string name = IptcDataSets::recordName(envelopeRecord);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_634, RecordName_Application2_634) {
    std::string name = IptcDataSets::recordName(application2Record);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_634, RecordName_Unknown_634) {
    std::string name = IptcDataSets::recordName(99);
    EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for recordDesc
// ============================================================

TEST_F(IptcDataSetsTest_634, RecordDesc_Envelope_634) {
    const char* desc = IptcDataSets::recordDesc(envelopeRecord);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

TEST_F(IptcDataSetsTest_634, RecordDesc_Application2_634) {
    const char* desc = IptcDataSets::recordDesc(application2Record);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

// ============================================================
// Tests for recordId
// ============================================================

TEST_F(IptcDataSetsTest_634, RecordId_Envelope_634) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelopeRecord);
}

TEST_F(IptcDataSetsTest_634, RecordId_Application2_634) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2Record);
}

TEST_F(IptcDataSetsTest_634, RecordId_UnknownRecord_634) {
    uint16_t id = IptcDataSets::recordId("NonExistentRecord");
    EXPECT_EQ(id, IptcDataSets::invalidRecord);
}

// ============================================================
// Tests for envelopeRecordList / application2RecordList
// ============================================================

TEST_F(IptcDataSetsTest_634, EnvelopeRecordList_NotNull_634) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_634, Application2RecordList_NotNull_634) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_634, EnvelopeRecordList_ContainsModelVersion_634) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // First entry should be ModelVersion (number 0)
    EXPECT_EQ(list[0].number_, envelopeModelVersion);
}

TEST_F(IptcDataSetsTest_634, Application2RecordList_ContainsRecordVersion_634) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list[0].number_, app2RecordVersion);
}

// ============================================================
// Tests for dataSetList
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetList_OutputsNonEmpty_634) {
    std::ostringstream oss;
    IptcDataSets::dataSetList(oss);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(IptcDataSetsTest_634, DataSetList_ContainsKeywords_634) {
    std::ostringstream oss;
    IptcDataSets::dataSetList(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("Keywords"), std::string::npos);
}

TEST_F(IptcDataSetsTest_634, DataSetList_ContainsCaption_634) {
    std::ostringstream oss;
    IptcDataSets::dataSetList(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("Caption"), std::string::npos);
}

// ============================================================
// Boundary/Edge tests
// ============================================================

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_InvalidRecord_634) {
    // Using invalid record ID with a valid-looking dataset number
    bool result = IptcDataSets::dataSetRepeatable(0, 255);
    // Should fall back to unknownDataSet behavior
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetName_ZeroNumber_ZeroRecord_634) {
    // Edge case: record 0 is not a standard record
    std::string name = IptcDataSets::dataSetName(0, 0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_MaxUint16_MaxUint16_634) {
    // Maximum possible values
    bool result = IptcDataSets::dataSetRepeatable(0xFFFF, 0xFFFF);
    // Should return unknownDataSet.repeatable_ which is false
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetType_MaxValues_634) {
    TypeId type = IptcDataSets::dataSetType(0xFFFF, 0xFFFF);
    // Unknown dataset type is string
    EXPECT_EQ(type, string);
}

TEST_F(IptcDataSetsTest_634, DataSet_EmptyString_634) {
    // Looking up empty string should not crash
    uint16_t ds = IptcDataSets::dataSet("", application2Record);
    EXPECT_EQ(ds, 0xffff);
}

// ============================================================
// Consistency tests
// ============================================================

TEST_F(IptcDataSetsTest_634, RoundTrip_NameToDataSet_And_Back_634) {
    // Get name for a known dataset, then look it up back
    std::string name = IptcDataSets::dataSetName(app2Keywords, application2Record);
    uint16_t ds = IptcDataSets::dataSet(name, application2Record);
    EXPECT_EQ(ds, app2Keywords);
}

TEST_F(IptcDataSetsTest_634, RoundTrip_RecordNameToId_And_Back_634) {
    std::string name = IptcDataSets::recordName(application2Record);
    uint16_t id = IptcDataSets::recordId(name);
    EXPECT_EQ(id, application2Record);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_City_ReturnsFalse_634) {
    // City (90) in Application2 is not repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2City, application2Record);
    EXPECT_FALSE(result);
}

TEST_F(IptcDataSetsTest_634, DataSetRepeatable_Caption_ReturnsFalse_634) {
    // Caption (120) is not repeatable
    bool result = IptcDataSets::dataSetRepeatable(app2Caption, application2Record);
    EXPECT_FALSE(result);
}
