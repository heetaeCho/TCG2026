#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

namespace {

// Known record IDs from the codebase
// envelope = 1, application2 = 2, invalidRecord = 0

class IptcDataSetsTest_637 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== recordDesc tests ====================

TEST_F(IptcDataSetsTest_637, RecordDescEnvelope_637) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(1);  // envelope
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "IIM envelope record");
}

TEST_F(IptcDataSetsTest_637, RecordDescApplication2_637) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(2);  // application2
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "IIM application record 2");
}

TEST_F(IptcDataSetsTest_637, RecordDescInvalidRecordId_637) {
    // For an unknown record ID, should return unknownDataSet.desc_
    const char* desc = Exiv2::IptcDataSets::recordDesc(0);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_637, RecordDescUnknownHighId_637) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(999);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_637, RecordDescMaxUint16_637) {
    const char* desc = Exiv2::IptcDataSets::recordDesc(0xFFFF);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

// ==================== recordName tests ====================

TEST_F(IptcDataSetsTest_637, RecordNameEnvelope_637) {
    std::string name = Exiv2::IptcDataSets::recordName(1);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_637, RecordNameApplication2_637) {
    std::string name = Exiv2::IptcDataSets::recordName(2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_637, RecordNameInvalidRecord_637) {
    std::string name = Exiv2::IptcDataSets::recordName(0);
    // Unknown record should return something (likely a numeric string or "(invalid)")
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_637, RecordNameUnknownId_637) {
    std::string name = Exiv2::IptcDataSets::recordName(50);
    EXPECT_FALSE(name.empty());
}

// ==================== recordId tests ====================

TEST_F(IptcDataSetsTest_637, RecordIdEnvelope_637) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_637, RecordIdApplication2_637) {
    uint16_t id = Exiv2::IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_637, RecordIdUnknownName_637) {
    uint16_t id = Exiv2::IptcDataSets::recordId("NonExistentRecord");
    // Should return invalidRecord = 0 or some sentinel
    EXPECT_EQ(id, 0);
}

// ==================== envelopeRecordList / application2RecordList tests ====================

TEST_F(IptcDataSetsTest_637, EnvelopeRecordListNotNull_637) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_637, Application2RecordListNotNull_637) {
    const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// ==================== dataSetName tests ====================

TEST_F(IptcDataSetsTest_637, DataSetNameKnownEnvelope_637) {
    // Dataset 0 in envelope record (recordId=1) is typically "ModelVersion"
    std::string name = Exiv2::IptcDataSets::dataSetName(0, 1);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_637, DataSetNameUnknownDataset_637) {
    std::string name = Exiv2::IptcDataSets::dataSetName(65535, 1);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_637, DataSetNameKnownApp2_637) {
    // Dataset 5 in application2 (recordId=2) is typically "ObjectName"
    std::string name = Exiv2::IptcDataSets::dataSetName(5, 2);
    EXPECT_FALSE(name.empty());
}

// ==================== dataSetTitle tests ====================

TEST_F(IptcDataSetsTest_637, DataSetTitleKnown_637) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(0, 1);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_637, DataSetTitleUnknown_637) {
    const char* title = Exiv2::IptcDataSets::dataSetTitle(65535, 999);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Unknown dataset");
}

// ==================== dataSetDesc tests ====================

TEST_F(IptcDataSetsTest_637, DataSetDescKnown_637) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(0, 1);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_637, DataSetDescUnknown_637) {
    const char* desc = Exiv2::IptcDataSets::dataSetDesc(65535, 999);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

// ==================== dataSetPsName tests ====================

TEST_F(IptcDataSetsTest_637, DataSetPsNameKnown_637) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(0, 1);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_637, DataSetPsNameUnknown_637) {
    const char* psName = Exiv2::IptcDataSets::dataSetPsName(65535, 999);
    ASSERT_NE(psName, nullptr);
    EXPECT_STREQ(psName, "Unknown dataset");
}

// ==================== dataSetRepeatable tests ====================

TEST_F(IptcDataSetsTest_637, DataSetRepeatableKnown_637) {
    // Just check it doesn't crash and returns a bool for a known dataset
    bool rep = Exiv2::IptcDataSets::dataSetRepeatable(0, 1);
    // ModelVersion is typically not repeatable
    (void)rep;  // Just ensure it returns without error
}

TEST_F(IptcDataSetsTest_637, DataSetRepeatableUnknown_637) {
    // unknownDataSet has repeatable_ = true
    bool rep = Exiv2::IptcDataSets::dataSetRepeatable(65535, 999);
    EXPECT_TRUE(rep);
}

// ==================== dataSetType tests ====================

TEST_F(IptcDataSetsTest_637, DataSetTypeKnown_637) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(0, 1);
    // ModelVersion is typically unsignedShort
    (void)type;
}

TEST_F(IptcDataSetsTest_637, DataSetTypeUnknown_637) {
    Exiv2::TypeId type = Exiv2::IptcDataSets::dataSetType(65535, 999);
    EXPECT_EQ(type, Exiv2::string);
}

// ==================== dataSet (lookup by name) tests ====================

TEST_F(IptcDataSetsTest_637, DataSetLookupByNameEnvelope_637) {
    // Look up "ModelVersion" in envelope record
    uint16_t ds = Exiv2::IptcDataSets::dataSet("ModelVersion", 1);
    EXPECT_EQ(ds, 0);
}

TEST_F(IptcDataSetsTest_637, DataSetLookupByNameUnknown_637) {
    uint16_t ds = Exiv2::IptcDataSets::dataSet("TotallyFakeDataset", 1);
    EXPECT_EQ(ds, 0xFFFF);
}

// ==================== dataSetList tests ====================

TEST_F(IptcDataSetsTest_637, DataSetListProducesOutput_637) {
    std::ostringstream os;
    Exiv2::IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_637, DataSetListContainsEnvelopeInfo_637) {
    std::ostringstream os;
    Exiv2::IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // Should contain some envelope-related content
    EXPECT_NE(output.find("Envelope"), std::string::npos);
}

TEST_F(IptcDataSetsTest_637, DataSetListContainsApplication2Info_637) {
    std::ostringstream os;
    Exiv2::IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("Application2"), std::string::npos);
}

// ==================== Boundary / edge case tests ====================

TEST_F(IptcDataSetsTest_637, RecordDescBoundaryRecordId3_637) {
    // Record ID 3 is not envelope or application2
    const char* desc = Exiv2::IptcDataSets::recordDesc(3);
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Unknown dataset");
}

TEST_F(IptcDataSetsTest_637, DataSetNameInvalidRecordId_637) {
    std::string name = Exiv2::IptcDataSets::dataSetName(0, 0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_637, RecordNameAndRecordIdRoundTrip_637) {
    // Round-trip: recordName -> recordId -> recordName
    std::string name1 = Exiv2::IptcDataSets::recordName(1);
    uint16_t id = Exiv2::IptcDataSets::recordId(name1);
    EXPECT_EQ(id, 1);
    std::string name2 = Exiv2::IptcDataSets::recordName(id);
    EXPECT_EQ(name1, name2);
}

TEST_F(IptcDataSetsTest_637, RecordNameAndRecordIdRoundTripApp2_637) {
    std::string name1 = Exiv2::IptcDataSets::recordName(2);
    uint16_t id = Exiv2::IptcDataSets::recordId(name1);
    EXPECT_EQ(id, 2);
    std::string name2 = Exiv2::IptcDataSets::recordName(id);
    EXPECT_EQ(name1, name2);
}

}  // namespace
