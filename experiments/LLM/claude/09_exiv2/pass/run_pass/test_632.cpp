#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Known record IDs from IPTC standard
// Record 1 = Envelope Record
// Record 2 = Application Record 2

class IptcDataSetsTest_632 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== dataSetName tests ====================

TEST_F(IptcDataSetsTest_632, DataSetName_KnownEnvelopeDataSet_632) {
    // DataSet 0 in record 1 is "ModelVersion"
    std::string name = IptcDataSets::dataSetName(0, 1);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_632, DataSetName_KnownApplication2DataSet_632) {
    // DataSet 5 in record 2 is "ObjectName"
    std::string name = IptcDataSets::dataSetName(5, 2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_632, DataSetName_UnknownDataSet_632) {
    // An unknown dataset number in a known record
    std::string name = IptcDataSets::dataSetName(999, 1);
    // Should return something (likely a hex formatted string or "Unknown dataset")
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_632, DataSetName_UnknownRecord_632) {
    std::string name = IptcDataSets::dataSetName(0, 99);
    EXPECT_FALSE(name.empty());
}

// ==================== dataSetTitle tests ====================

TEST_F(IptcDataSetsTest_632, DataSetTitle_KnownDataSet_632) {
    const char* title = IptcDataSets::dataSetTitle(0, 1);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Model Version");
}

TEST_F(IptcDataSetsTest_632, DataSetTitle_UnknownDataSet_632) {
    const char* title = IptcDataSets::dataSetTitle(999, 1);
    ASSERT_NE(title, nullptr);
    // Should return the unknown dataset title
    EXPECT_STREQ(title, "Unknown dataset");
}

// ==================== dataSetDesc tests ====================

TEST_F(IptcDataSetsTest_632, DataSetDesc_KnownEnvelopeDataSet_632) {
    const char* desc = IptcDataSets::dataSetDesc(0, 1);
    ASSERT_NE(desc, nullptr);
    // Should be a meaningful description, not "Unknown dataset"
    EXPECT_STRNE(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_632, DataSetDesc_KnownApplication2DataSet_632) {
    const char* desc = IptcDataSets::dataSetDesc(5, 2);
    ASSERT_NE(desc, nullptr);
    EXPECT_STRNE(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_632, DataSetDesc_UnknownDataSet_632) {
    const char* desc = IptcDataSets::dataSetDesc(999, 1);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_632, DataSetDesc_UnknownRecord_632) {
    const char* desc = IptcDataSets::dataSetDesc(0, 99);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

// ==================== dataSetPsName tests ====================

TEST_F(IptcDataSetsTest_632, DataSetPsName_KnownDataSet_632) {
    const char* psName = IptcDataSets::dataSetPsName(5, 2);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_632, DataSetPsName_UnknownDataSet_632) {
    const char* psName = IptcDataSets::dataSetPsName(999, 2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Unknown dataset");
}

// ==================== dataSetRepeatable tests ====================

TEST_F(IptcDataSetsTest_632, DataSetRepeatable_KnownNonRepeatable_632) {
    // ModelVersion (0, 1) is not repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(0, 1);
    EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_632, DataSetRepeatable_KnownRepeatable_632) {
    // Keywords (25, 2) is repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(25, 2);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_632, DataSetRepeatable_UnknownDataSet_632) {
    // Unknown datasets should default to repeatable (based on unknownDataSet)
    bool repeatable = IptcDataSets::dataSetRepeatable(999, 1);
    EXPECT_TRUE(repeatable);
}

// ==================== dataSet (lookup by name) tests ====================

TEST_F(IptcDataSetsTest_632, DataSet_KnownNameEnvelope_632) {
    uint16_t number = IptcDataSets::dataSet("ModelVersion", 1);
    EXPECT_EQ(number, 0);
}

TEST_F(IptcDataSetsTest_632, DataSet_KnownNameApplication2_632) {
    uint16_t number = IptcDataSets::dataSet("ObjectName", 2);
    EXPECT_EQ(number, 5);
}

TEST_F(IptcDataSetsTest_632, DataSet_KnownKeywords_632) {
    uint16_t number = IptcDataSets::dataSet("Keywords", 2);
    EXPECT_EQ(number, 25);
}

TEST_F(IptcDataSetsTest_632, DataSet_UnknownName_632) {
    uint16_t number = IptcDataSets::dataSet("NonExistentDataSet", 2);
    EXPECT_EQ(number, 0xffff);
}

// ==================== dataSetType tests ====================

TEST_F(IptcDataSetsTest_632, DataSetType_KnownDataSet_632) {
    TypeId type = IptcDataSets::dataSetType(0, 1);
    // ModelVersion should be unsignedShort
    EXPECT_EQ(type, unsignedShort);
}

TEST_F(IptcDataSetsTest_632, DataSetType_StringDataSet_632) {
    // ObjectName (5, 2) should be string type
    TypeId type = IptcDataSets::dataSetType(5, 2);
    EXPECT_EQ(type, string);
}

TEST_F(IptcDataSetsTest_632, DataSetType_UnknownDataSet_632) {
    TypeId type = IptcDataSets::dataSetType(999, 1);
    EXPECT_EQ(type, string);
}

// ==================== recordName tests ====================

TEST_F(IptcDataSetsTest_632, RecordName_EnvelopeRecord_632) {
    std::string name = IptcDataSets::recordName(1);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_632, RecordName_Application2Record_632) {
    std::string name = IptcDataSets::recordName(2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_632, RecordName_UnknownRecord_632) {
    std::string name = IptcDataSets::recordName(99);
    EXPECT_FALSE(name.empty());
}

// ==================== recordDesc tests ====================

TEST_F(IptcDataSetsTest_632, RecordDesc_EnvelopeRecord_632) {
    const char* desc = IptcDataSets::recordDesc(1);
    ASSERT_NE(desc, nullptr);
    EXPECT_STRNE(desc, "");
}

TEST_F(IptcDataSetsTest_632, RecordDesc_Application2Record_632) {
    const char* desc = IptcDataSets::recordDesc(2);
    ASSERT_NE(desc, nullptr);
    EXPECT_STRNE(desc, "");
}

TEST_F(IptcDataSetsTest_632, RecordDesc_UnknownRecord_632) {
    const char* desc = IptcDataSets::recordDesc(99);
    ASSERT_NE(desc, nullptr);
}

// ==================== recordId tests ====================

TEST_F(IptcDataSetsTest_632, RecordId_Envelope_632) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_632, RecordId_Application2_632) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_632, RecordId_Unknown_632) {
    uint16_t id = IptcDataSets::recordId("NonExistentRecord");
    EXPECT_EQ(id, 0xffff);
}

// ==================== envelopeRecordList tests ====================

TEST_F(IptcDataSetsTest_632, EnvelopeRecordList_NotNull_632) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_632, EnvelopeRecordList_FirstEntry_632) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // First entry should be ModelVersion (number 0)
    EXPECT_EQ(list[0].number_, 0);
}

// ==================== application2RecordList tests ====================

TEST_F(IptcDataSetsTest_632, Application2RecordList_NotNull_632) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_632, Application2RecordList_FirstEntry_632) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    // First entry should be RecordVersion (number 0)
    EXPECT_EQ(list[0].number_, 0);
}

// ==================== dataSetList tests ====================

TEST_F(IptcDataSetsTest_632, DataSetList_OutputsData_632) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_632, DataSetList_ContainsKnownDataSetNames_632) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // Should contain some known dataset names
    EXPECT_NE(output.find("ModelVersion"), std::string::npos);
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
}

// ==================== Boundary / Edge Case tests ====================

TEST_F(IptcDataSetsTest_632, DataSetDesc_MaxUint16Number_632) {
    const char* desc = IptcDataSets::dataSetDesc(0xFFFF, 1);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_632, DataSetDesc_MaxUint16Record_632) {
    const char* desc = IptcDataSets::dataSetDesc(0, 0xFFFF);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_632, DataSetName_ZeroZero_632) {
    // Record 0 is not a standard record
    std::string name = IptcDataSets::dataSetName(0, 0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_632, DataSetTitle_ZeroBothParams_632) {
    const char* title = IptcDataSets::dataSetTitle(0, 0);
    ASSERT_NE(title, nullptr);
}

// ==================== Consistency tests ====================

TEST_F(IptcDataSetsTest_632, DataSetRoundTrip_NameToNumberEnvelope_632) {
    // Get name for a known dataset, then look it up by name
    std::string name = IptcDataSets::dataSetName(0, 1);
    uint16_t number = IptcDataSets::dataSet(name, 1);
    EXPECT_EQ(number, 0);
}

TEST_F(IptcDataSetsTest_632, DataSetRoundTrip_NameToNumberApplication2_632) {
    std::string name = IptcDataSets::dataSetName(5, 2);
    uint16_t number = IptcDataSets::dataSet(name, 2);
    EXPECT_EQ(number, 5);
}

TEST_F(IptcDataSetsTest_632, RecordRoundTrip_NameToId_632) {
    std::string name = IptcDataSets::recordName(1);
    uint16_t id = IptcDataSets::recordId(name);
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_632, RecordRoundTrip_Application2_632) {
    std::string name = IptcDataSets::recordName(2);
    uint16_t id = IptcDataSets::recordId(name);
    EXPECT_EQ(id, 2);
}

// ==================== Multiple known dataset tests for Application2 ====================

TEST_F(IptcDataSetsTest_632, DataSetName_Urgency_632) {
    std::string name = IptcDataSets::dataSetName(10, 2);
    EXPECT_EQ(name, "Urgency");
}

TEST_F(IptcDataSetsTest_632, DataSetName_Category_632) {
    std::string name = IptcDataSets::dataSetName(15, 2);
    EXPECT_EQ(name, "Category");
}

TEST_F(IptcDataSetsTest_632, DataSetName_Keywords_632) {
    std::string name = IptcDataSets::dataSetName(25, 2);
    EXPECT_EQ(name, "Keywords");
}

TEST_F(IptcDataSetsTest_632, DataSetName_DateCreated_632) {
    std::string name = IptcDataSets::dataSetName(55, 2);
    EXPECT_EQ(name, "DateCreated");
}

TEST_F(IptcDataSetsTest_632, DataSetName_City_632) {
    std::string name = IptcDataSets::dataSetName(90, 2);
    EXPECT_EQ(name, "City");
}

TEST_F(IptcDataSetsTest_632, DataSetName_Copyright_632) {
    std::string name = IptcDataSets::dataSetName(116, 2);
    EXPECT_EQ(name, "Copyright");
}

TEST_F(IptcDataSetsTest_632, DataSetName_Caption_632) {
    std::string name = IptcDataSets::dataSetName(120, 2);
    EXPECT_EQ(name, "Caption");
}
