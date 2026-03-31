#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Known record IDs from IPTC standard
static constexpr uint16_t envelope = 1;
static constexpr uint16_t application2 = 2;

// Known dataset numbers for envelope record
static constexpr uint16_t envelopeModelVersion = 0;
static constexpr uint16_t envelopeDestination = 5;
static constexpr uint16_t envelopeCharacterSet = 90;

// Known dataset numbers for application2 record
static constexpr uint16_t app2RecordVersion = 0;
static constexpr uint16_t app2ObjectName = 5;
static constexpr uint16_t app2Keywords = 25;
static constexpr uint16_t app2Caption = 120;
static constexpr uint16_t app2City = 90;
static constexpr uint16_t app2Copyright = 116;

// ==================== dataSetName tests ====================

TEST(IptcDataSetsTest_630, DataSetName_KnownEnvelopeDataSet_630) {
    std::string name = IptcDataSets::dataSetName(envelopeModelVersion, envelope);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "ModelVersion");
}

TEST(IptcDataSetsTest_630, DataSetName_KnownApplication2DataSet_630) {
    std::string name = IptcDataSets::dataSetName(app2ObjectName, application2);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "ObjectName");
}

TEST(IptcDataSetsTest_630, DataSetName_Keywords_630) {
    std::string name = IptcDataSets::dataSetName(app2Keywords, application2);
    EXPECT_EQ(name, "Keywords");
}

TEST(IptcDataSetsTest_630, DataSetName_Caption_630) {
    std::string name = IptcDataSets::dataSetName(app2Caption, application2);
    EXPECT_EQ(name, "Caption");
}

TEST(IptcDataSetsTest_630, DataSetName_UnknownDataSet_ReturnsHexString_630) {
    // Use a dataset number that is unlikely to exist
    std::string name = IptcDataSets::dataSetName(0xFFFF, application2);
    EXPECT_EQ(name, "0xffff");
}

TEST(IptcDataSetsTest_630, DataSetName_UnknownRecordId_ReturnsHexString_630) {
    // Use a record ID that doesn't exist
    std::string name = IptcDataSets::dataSetName(0, 255);
    EXPECT_EQ(name, "0x0000");
}

TEST(IptcDataSetsTest_630, DataSetName_UnknownDataSetSmallNumber_630) {
    std::string name = IptcDataSets::dataSetName(0x0001, 255);
    EXPECT_EQ(name, "0x0001");
}

// ==================== dataSetTitle tests ====================

TEST(IptcDataSetsTest_630, DataSetTitle_KnownDataSet_630) {
    const char* title = IptcDataSets::dataSetTitle(app2ObjectName, application2);
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(strlen(title) > 0);
}

TEST(IptcDataSetsTest_630, DataSetTitle_UnknownDataSet_630) {
    const char* title = IptcDataSets::dataSetTitle(0xFFFF, application2);
    ASSERT_NE(title, nullptr);
}

// ==================== dataSetDesc tests ====================

TEST(IptcDataSetsTest_630, DataSetDesc_KnownDataSet_630) {
    const char* desc = IptcDataSets::dataSetDesc(app2ObjectName, application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(strlen(desc) > 0);
}

TEST(IptcDataSetsTest_630, DataSetDesc_UnknownDataSet_630) {
    const char* desc = IptcDataSets::dataSetDesc(0xFFFF, application2);
    ASSERT_NE(desc, nullptr);
}

// ==================== dataSetPsName tests ====================

TEST(IptcDataSetsTest_630, DataSetPsName_KnownDataSet_630) {
    const char* psName = IptcDataSets::dataSetPsName(app2ObjectName, application2);
    ASSERT_NE(psName, nullptr);
}

TEST(IptcDataSetsTest_630, DataSetPsName_UnknownDataSet_630) {
    const char* psName = IptcDataSets::dataSetPsName(0xFFFF, application2);
    ASSERT_NE(psName, nullptr);
}

// ==================== dataSetRepeatable tests ====================

TEST(IptcDataSetsTest_630, DataSetRepeatable_Keywords_IsRepeatable_630) {
    // Keywords are typically repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(app2Keywords, application2);
    EXPECT_TRUE(repeatable);
}

TEST(IptcDataSetsTest_630, DataSetRepeatable_RecordVersion_NotRepeatable_630) {
    bool repeatable = IptcDataSets::dataSetRepeatable(app2RecordVersion, application2);
    EXPECT_FALSE(repeatable);
}

// ==================== dataSet (lookup by name) tests ====================

TEST(IptcDataSetsTest_630, DataSet_LookupByName_Known_630) {
    uint16_t ds = IptcDataSets::dataSet("ObjectName", application2);
    EXPECT_EQ(ds, app2ObjectName);
}

TEST(IptcDataSetsTest_630, DataSet_LookupByName_Keywords_630) {
    uint16_t ds = IptcDataSets::dataSet("Keywords", application2);
    EXPECT_EQ(ds, app2Keywords);
}

TEST(IptcDataSetsTest_630, DataSet_LookupByName_Caption_630) {
    uint16_t ds = IptcDataSets::dataSet("Caption", application2);
    EXPECT_EQ(ds, app2Caption);
}

TEST(IptcDataSetsTest_630, DataSet_LookupByName_ModelVersion_Envelope_630) {
    uint16_t ds = IptcDataSets::dataSet("ModelVersion", envelope);
    EXPECT_EQ(ds, envelopeModelVersion);
}

TEST(IptcDataSetsTest_630, DataSet_LookupByName_Hex_630) {
    // Looking up using a hex string for an unknown dataset
    uint16_t ds = IptcDataSets::dataSet("0xffff", application2);
    EXPECT_EQ(ds, 0xFFFF);
}

// ==================== dataSetType tests ====================

TEST(IptcDataSetsTest_630, DataSetType_KnownDataSet_630) {
    TypeId type = IptcDataSets::dataSetType(app2Keywords, application2);
    EXPECT_EQ(type, string);
}

TEST(IptcDataSetsTest_630, DataSetType_RecordVersion_630) {
    TypeId type = IptcDataSets::dataSetType(app2RecordVersion, application2);
    EXPECT_EQ(type, unsignedShort);
}

// ==================== recordName tests ====================

TEST(IptcDataSetsTest_630, RecordName_Envelope_630) {
    std::string name = IptcDataSets::recordName(envelope);
    EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_630, RecordName_Application2_630) {
    std::string name = IptcDataSets::recordName(application2);
    EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_630, RecordName_Unknown_630) {
    std::string name = IptcDataSets::recordName(255);
    // Unknown record should still return something
    EXPECT_FALSE(name.empty());
}

// ==================== recordDesc tests ====================

TEST(IptcDataSetsTest_630, RecordDesc_Envelope_630) {
    const char* desc = IptcDataSets::recordDesc(envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(strlen(desc) > 0);
}

TEST(IptcDataSetsTest_630, RecordDesc_Application2_630) {
    const char* desc = IptcDataSets::recordDesc(application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(strlen(desc) > 0);
}

// ==================== recordId tests ====================

TEST(IptcDataSetsTest_630, RecordId_Envelope_630) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelope);
}

TEST(IptcDataSetsTest_630, RecordId_Application2_630) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2);
}

// ==================== envelopeRecordList tests ====================

TEST(IptcDataSetsTest_630, EnvelopeRecordList_NotNull_630) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_630, EnvelopeRecordList_FirstEntryValid_630) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // First entry should have a valid title
    EXPECT_NE(list[0].title_, nullptr);
}

// ==================== application2RecordList tests ====================

TEST(IptcDataSetsTest_630, Application2RecordList_NotNull_630) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_630, Application2RecordList_FirstEntryValid_630) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    EXPECT_NE(list[0].title_, nullptr);
}

// ==================== dataSetList tests ====================

TEST(IptcDataSetsTest_630, DataSetList_ProducesOutput_630) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST(IptcDataSetsTest_630, DataSetList_ContainsKnownDataSet_630) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // The output should contain known dataset names
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
    EXPECT_NE(output.find("Keywords"), std::string::npos);
}

// ==================== Roundtrip tests ====================

TEST(IptcDataSetsTest_630, RoundTrip_NameToNumberAndBack_630) {
    // Get dataset number from name, then get name from number
    uint16_t ds = IptcDataSets::dataSet("Keywords", application2);
    std::string name = IptcDataSets::dataSetName(ds, application2);
    EXPECT_EQ(name, "Keywords");
}

TEST(IptcDataSetsTest_630, RoundTrip_RecordNameToIdAndBack_630) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    std::string name = IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_630, RoundTrip_Application2_630) {
    uint16_t id = IptcDataSets::recordId("Application2");
    std::string name = IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Application2");
}

// ==================== Boundary/edge cases ====================

TEST(IptcDataSetsTest_630, DataSetName_ZeroRecordId_630) {
    // Record ID 0 is not a standard record
    std::string name = IptcDataSets::dataSetName(0, 0);
    // Should return hex format since record 0 likely doesn't exist
    EXPECT_FALSE(name.empty());
}

TEST(IptcDataSetsTest_630, DataSetName_MaxUint16_630) {
    std::string name = IptcDataSets::dataSetName(0xFFFF, 0xFFFF);
    EXPECT_EQ(name, "0xffff");
}

TEST(IptcDataSetsTest_630, DataSetTitle_MaxValues_630) {
    const char* title = IptcDataSets::dataSetTitle(0xFFFF, 0xFFFF);
    ASSERT_NE(title, nullptr);
}

TEST(IptcDataSetsTest_630, Copyright_DataSet_630) {
    std::string name = IptcDataSets::dataSetName(app2Copyright, application2);
    EXPECT_FALSE(name.empty());
    // Should not be a hex fallback
    EXPECT_NE(name.substr(0, 2), "0x");
}

TEST(IptcDataSetsTest_630, City_DataSet_630) {
    std::string name = IptcDataSets::dataSetName(app2City, application2);
    EXPECT_EQ(name, "City");
}

TEST(IptcDataSetsTest_630, EnvelopeCharacterSet_630) {
    std::string name = IptcDataSets::dataSetName(envelopeCharacterSet, envelope);
    EXPECT_EQ(name, "CharacterSet");
}

TEST(IptcDataSetsTest_630, EnvelopeDestination_630) {
    std::string name = IptcDataSets::dataSetName(envelopeDestination, envelope);
    EXPECT_EQ(name, "Destination");
}
