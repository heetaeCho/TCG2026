#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Record IDs commonly used in IPTC
// IptcDataSets::envelope = 1
// IptcDataSets::application2 = 2

class IptcDataSetsTest_633 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== dataSetPsName tests ====================

TEST_F(IptcDataSetsTest_633, DataSetPsName_KnownEnvelopeDataSet_633) {
    // Envelope record (recordId=1), dataset 0 is typically "Model Version"
    const char* psName = IptcDataSets::dataSetPsName(0, 1);
    ASSERT_NE(psName, nullptr);
    // Should not return "Unknown dataset" for a known dataset
    EXPECT_STRNE(psName, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_KnownApplication2DataSet_633) {
    // Application2 record (recordId=2), dataset 5 is typically "Object Name"
    const char* psName = IptcDataSets::dataSetPsName(5, 2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STRNE(psName, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_UnknownDataSet_633) {
    // Use an invalid/unknown dataset number
    const char* psName = IptcDataSets::dataSetPsName(65535, 1);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_UnknownRecordId_633) {
    // Use an invalid/unknown record ID
    const char* psName = IptcDataSets::dataSetPsName(0, 255);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_BothUnknown_633) {
    const char* psName = IptcDataSets::dataSetPsName(9999, 9999);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Unknown dataset");
}

// ==================== dataSetName tests ====================

TEST_F(IptcDataSetsTest_633, DataSetName_KnownEnvelopeDataSet_633) {
    std::string name = IptcDataSets::dataSetName(0, 1);
    EXPECT_FALSE(name.empty());
    // Known dataset should not have a generic unknown name pattern with hex
}

TEST_F(IptcDataSetsTest_633, DataSetName_KnownApplication2DataSet_633) {
    // Dataset 5 in application2 is "ObjectName"
    std::string name = IptcDataSets::dataSetName(5, 2);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_633, DataSetName_UnknownDataSet_633) {
    std::string name = IptcDataSets::dataSetName(65535, 1);
    EXPECT_FALSE(name.empty());
}

// ==================== dataSetTitle tests ====================

TEST_F(IptcDataSetsTest_633, DataSetTitle_KnownDataSet_633) {
    const char* title = IptcDataSets::dataSetTitle(0, 1);
    ASSERT_NE(title, nullptr);
    EXPECT_STRNE(title, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetTitle_UnknownDataSet_633) {
    const char* title = IptcDataSets::dataSetTitle(65535, 1);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Unknown dataset");
}

// ==================== dataSetDesc tests ====================

TEST_F(IptcDataSetsTest_633, DataSetDesc_KnownDataSet_633) {
    const char* desc = IptcDataSets::dataSetDesc(0, 1);
    ASSERT_NE(desc, nullptr);
    EXPECT_STRNE(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetDesc_UnknownDataSet_633) {
    const char* desc = IptcDataSets::dataSetDesc(65535, 1);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

// ==================== dataSetRepeatable tests ====================

TEST_F(IptcDataSetsTest_633, DataSetRepeatable_KnownNonRepeatable_633) {
    // Dataset 0 (ModelVersion) in envelope record is typically not repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(0, 1);
    EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_633, DataSetRepeatable_KnownRepeatable_633) {
    // Dataset 25 (Keywords) in application2 record is typically repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(25, 2);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_633, DataSetRepeatable_UnknownDataSet_633) {
    // Unknown dataset defaults from unknownDataSet which has repeatable_ = true
    bool repeatable = IptcDataSets::dataSetRepeatable(65535, 1);
    EXPECT_TRUE(repeatable);
}

// ==================== dataSetType tests ====================

TEST_F(IptcDataSetsTest_633, DataSetType_KnownDataSet_633) {
    TypeId type = IptcDataSets::dataSetType(0, 1);
    // ModelVersion is typically unsignedShort
    EXPECT_NE(type, invalidTypeId);
}

TEST_F(IptcDataSetsTest_633, DataSetType_UnknownDataSet_633) {
    TypeId type = IptcDataSets::dataSetType(65535, 1);
    EXPECT_EQ(type, string);
}

// ==================== dataSet (lookup by name) tests ====================

TEST_F(IptcDataSetsTest_633, DataSet_KnownName_EnvelopeRecord_633) {
    uint16_t ds = IptcDataSets::dataSet("ModelVersion", 1);
    EXPECT_EQ(ds, 0);
}

TEST_F(IptcDataSetsTest_633, DataSet_KnownName_Application2Record_633) {
    uint16_t ds = IptcDataSets::dataSet("ObjectName", 2);
    EXPECT_EQ(ds, 5);
}

TEST_F(IptcDataSetsTest_633, DataSet_UnknownName_633) {
    uint16_t ds = IptcDataSets::dataSet("NonExistentDataSet", 1);
    EXPECT_EQ(ds, 65535);
}

TEST_F(IptcDataSetsTest_633, DataSet_Keywords_633) {
    uint16_t ds = IptcDataSets::dataSet("Keywords", 2);
    EXPECT_EQ(ds, 25);
}

// ==================== recordName tests ====================

TEST_F(IptcDataSetsTest_633, RecordName_Envelope_633) {
    std::string name = IptcDataSets::recordName(1);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_633, RecordName_Application2_633) {
    std::string name = IptcDataSets::recordName(2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_633, RecordName_Unknown_633) {
    std::string name = IptcDataSets::recordName(255);
    EXPECT_FALSE(name.empty());
}

// ==================== recordDesc tests ====================

TEST_F(IptcDataSetsTest_633, RecordDesc_Envelope_633) {
    const char* desc = IptcDataSets::recordDesc(1);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_633, RecordDesc_Application2_633) {
    const char* desc = IptcDataSets::recordDesc(2);
    ASSERT_NE(desc, nullptr);
}

// ==================== recordId tests ====================

TEST_F(IptcDataSetsTest_633, RecordId_Envelope_633) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_633, RecordId_Application2_633) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_633, RecordId_Unknown_633) {
    uint16_t id = IptcDataSets::recordId("NonExistentRecord");
    EXPECT_EQ(id, 65535);
}

// ==================== envelopeRecordList tests ====================

TEST_F(IptcDataSetsTest_633, EnvelopeRecordList_NotNull_633) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_633, EnvelopeRecordList_FirstElement_633) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // First element should have number_ 0 (ModelVersion)
    EXPECT_EQ(list[0].number_, 0);
}

// ==================== application2RecordList tests ====================

TEST_F(IptcDataSetsTest_633, Application2RecordList_NotNull_633) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_633, Application2RecordList_FirstElement_633) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    // First element should have number_ 0
    EXPECT_EQ(list[0].number_, 0);
}

// ==================== dataSetList tests ====================

TEST_F(IptcDataSetsTest_633, DataSetList_OutputNotEmpty_633) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_633, DataSetList_ContainsKnownDataSet_633) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // Should contain references to known datasets
    EXPECT_NE(output.find("ModelVersion"), std::string::npos);
}

// ==================== Boundary condition tests ====================

TEST_F(IptcDataSetsTest_633, DataSetPsName_ZeroZero_633) {
    // recordId 0 is not a standard record
    const char* psName = IptcDataSets::dataSetPsName(0, 0);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_633, DataSetName_MaxValues_633) {
    std::string name = IptcDataSets::dataSetName(65535, 65535);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_Application2_ObjectName_633) {
    // Dataset 5 in record 2 is ObjectName, should have a photoshop name
    const char* psName = IptcDataSets::dataSetPsName(5, 2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STRNE(psName, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_633, DataSetPsName_Application2_Keywords_633) {
    const char* psName = IptcDataSets::dataSetPsName(25, 2);
    ASSERT_NE(psName, nullptr);
    EXPECT_STRNE(psName, "Unknown dataset");
}

// ==================== Cross-validation tests ====================

TEST_F(IptcDataSetsTest_633, DataSetRoundTrip_NameToNumber_633) {
    // Look up by name, then verify the name matches back
    uint16_t ds = IptcDataSets::dataSet("ObjectName", 2);
    EXPECT_EQ(ds, 5);
    std::string name = IptcDataSets::dataSetName(ds, 2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_633, RecordIdRoundTrip_633) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
    std::string name = IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_633, RecordIdRoundTrip_Application2_633) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
    std::string name = IptcDataSets::recordName(id);
    EXPECT_EQ(name, "Application2");
}
