#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>

using namespace Exiv2;

// Test fixture
class IptcDataSetsTest_639 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== envelopeRecordList tests ====================

TEST_F(IptcDataSetsTest_639, EnvelopeRecordListReturnsNonNull_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_639, EnvelopeRecordListHasEntries_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // At least one entry before the terminator
    EXPECT_NE(list[0].number_, 0xffff);
}

// ==================== application2RecordList tests ====================

TEST_F(IptcDataSetsTest_639, Application2RecordListReturnsNonNull_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_639, Application2RecordListHasEntries_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    EXPECT_NE(list[0].number_, 0xffff);
}

// ==================== recordName tests ====================

TEST_F(IptcDataSetsTest_639, RecordNameForEnvelopeRecord_639) {
    // Record 1 is the Envelope record
    std::string name = IptcDataSets::recordName(1);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_639, RecordNameForApplication2Record_639) {
    // Record 2 is the Application2 record
    std::string name = IptcDataSets::recordName(2);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_639, RecordNameForUnknownRecord_639) {
    // Unknown record ID should return something (likely a numeric string or "Unknown")
    std::string name = IptcDataSets::recordName(999);
    EXPECT_FALSE(name.empty());
}

// ==================== recordDesc tests ====================

TEST_F(IptcDataSetsTest_639, RecordDescForEnvelopeRecord_639) {
    const char* desc = IptcDataSets::recordDesc(1);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

TEST_F(IptcDataSetsTest_639, RecordDescForApplication2Record_639) {
    const char* desc = IptcDataSets::recordDesc(2);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

// ==================== recordId tests ====================

TEST_F(IptcDataSetsTest_639, RecordIdForEnvelope_639) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1u);
}

TEST_F(IptcDataSetsTest_639, RecordIdForApplication2_639) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2u);
}

TEST_F(IptcDataSetsTest_639, RecordIdRoundTrip_639) {
    std::string name = IptcDataSets::recordName(1);
    uint16_t id = IptcDataSets::recordId(name);
    EXPECT_EQ(id, 1u);
}

// ==================== dataSetName tests ====================

TEST_F(IptcDataSetsTest_639, DataSetNameForKnownEnvelopeDataSet_639) {
    // DataSet 0 in Envelope record (Record version)
    std::string name = IptcDataSets::dataSetName(0, 1);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_639, DataSetNameForKnownApplication2DataSet_639) {
    // DataSet 5 in Application2 record (Object Name / Title)
    std::string name = IptcDataSets::dataSetName(5, 2);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_639, DataSetNameForUnknownDataSet_639) {
    // Unknown dataset number
    std::string name = IptcDataSets::dataSetName(9999, 1);
    EXPECT_FALSE(name.empty());
}

// ==================== dataSetTitle tests ====================

TEST_F(IptcDataSetsTest_639, DataSetTitleForKnownDataSet_639) {
    const char* title = IptcDataSets::dataSetTitle(0, 1);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetTitleForApplication2DataSet_639) {
    const char* title = IptcDataSets::dataSetTitle(5, 2);
    ASSERT_NE(title, nullptr);
}

// ==================== dataSetDesc tests ====================

TEST_F(IptcDataSetsTest_639, DataSetDescForKnownDataSet_639) {
    const char* desc = IptcDataSets::dataSetDesc(0, 1);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetDescForApplication2DataSet_639) {
    const char* desc = IptcDataSets::dataSetDesc(5, 2);
    ASSERT_NE(desc, nullptr);
}

// ==================== dataSetPsName tests ====================

TEST_F(IptcDataSetsTest_639, DataSetPsNameForKnownDataSet_639) {
    const char* psName = IptcDataSets::dataSetPsName(5, 2);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetPsNameForEnvelopeDataSet_639) {
    const char* psName = IptcDataSets::dataSetPsName(0, 1);
    ASSERT_NE(psName, nullptr);
}

// ==================== dataSetRepeatable tests ====================

TEST_F(IptcDataSetsTest_639, DataSetRepeatableReturnsBool_639) {
    // Just verify it returns without error for known datasets
    bool repeatable = IptcDataSets::dataSetRepeatable(0, 1);
    // Record version is typically not repeatable
    (void)repeatable; // We don't know the exact value but it should not crash
}

TEST_F(IptcDataSetsTest_639, DataSetRepeatableForKeywords_639) {
    // Keywords (dataset 25, record 2) are typically repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(25, 2);
    EXPECT_TRUE(repeatable);
}

// ==================== dataSetType tests ====================

TEST_F(IptcDataSetsTest_639, DataSetTypeForKnownDataSet_639) {
    TypeId type = IptcDataSets::dataSetType(0, 1);
    // Record version typically has a specific type
    (void)type; // Should not crash
}

TEST_F(IptcDataSetsTest_639, DataSetTypeForApplication2DataSet_639) {
    TypeId type = IptcDataSets::dataSetType(5, 2);
    // Object Name is typically a string type
    EXPECT_EQ(type, string);
}

// ==================== dataSet (lookup by name) tests ====================

TEST_F(IptcDataSetsTest_639, DataSetLookupByName_639) {
    // First get the name of a known dataset, then look it up
    std::string name = IptcDataSets::dataSetName(0, 1);
    uint16_t number = IptcDataSets::dataSet(name, 1);
    EXPECT_EQ(number, 0u);
}

TEST_F(IptcDataSetsTest_639, DataSetLookupByNameApplication2_639) {
    std::string name = IptcDataSets::dataSetName(5, 2);
    uint16_t number = IptcDataSets::dataSet(name, 2);
    EXPECT_EQ(number, 5u);
}

TEST_F(IptcDataSetsTest_639, DataSetLookupRoundTripEnvelope_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    if (list[0].number_ != 0xffff) {
        std::string name = IptcDataSets::dataSetName(list[0].number_, 1);
        uint16_t number = IptcDataSets::dataSet(name, 1);
        EXPECT_EQ(number, list[0].number_);
    }
}

TEST_F(IptcDataSetsTest_639, DataSetLookupRoundTripApplication2_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    if (list[0].number_ != 0xffff) {
        std::string name = IptcDataSets::dataSetName(list[0].number_, 2);
        uint16_t number = IptcDataSets::dataSet(name, 2);
        EXPECT_EQ(number, list[0].number_);
    }
}

// ==================== dataSetList tests ====================

TEST_F(IptcDataSetsTest_639, DataSetListOutputsToStream_639) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_639, DataSetListContainsNewlines_639) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST_F(IptcDataSetsTest_639, DataSetListContainsMultipleEntries_639) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // Count newlines - should have many entries
    size_t count = 0;
    for (char c : output) {
        if (c == '\n') count++;
    }
    EXPECT_GT(count, 1u);
}

// ==================== Boundary / Error case tests ====================

TEST_F(IptcDataSetsTest_639, DataSetNameForZeroRecord_639) {
    // Record 0 is not standard; test it doesn't crash
    std::string name = IptcDataSets::dataSetName(0, 0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_639, RecordNameForZeroRecord_639) {
    std::string name = IptcDataSets::recordName(0);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_639, DataSetTitleForUnknownDataSet_639) {
    const char* title = IptcDataSets::dataSetTitle(9999, 9999);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetDescForUnknownDataSet_639) {
    const char* desc = IptcDataSets::dataSetDesc(9999, 9999);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetPsNameForUnknownDataSet_639) {
    const char* psName = IptcDataSets::dataSetPsName(9999, 9999);
    ASSERT_NE(psName, nullptr);
}

TEST_F(IptcDataSetsTest_639, DataSetTypeForUnknownDataSet_639) {
    // Should return some default type
    TypeId type = IptcDataSets::dataSetType(9999, 9999);
    (void)type; // Should not crash
}

TEST_F(IptcDataSetsTest_639, DataSetRepeatableForUnknownDataSet_639) {
    bool repeatable = IptcDataSets::dataSetRepeatable(9999, 9999);
    (void)repeatable; // Should not crash
}

// ==================== Consistency tests ====================

TEST_F(IptcDataSetsTest_639, EnvelopeListTerminatedCorrectly_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    int count = 0;
    while (list[count].number_ != 0xffff) {
        count++;
        // Safety guard to prevent infinite loop in test
        ASSERT_LT(count, 10000);
    }
    EXPECT_GT(count, 0);
}

TEST_F(IptcDataSetsTest_639, Application2ListTerminatedCorrectly_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    int count = 0;
    while (list[count].number_ != 0xffff) {
        count++;
        ASSERT_LT(count, 10000);
    }
    EXPECT_GT(count, 0);
}

TEST_F(IptcDataSetsTest_639, AllEnvelopeDataSetsHaveValidTitle_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    for (int i = 0; list[i].number_ != 0xffff; ++i) {
        ASSERT_NE(list[i].title_, nullptr);
    }
}

TEST_F(IptcDataSetsTest_639, AllApplication2DataSetsHaveValidTitle_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    for (int i = 0; list[i].number_ != 0xffff; ++i) {
        ASSERT_NE(list[i].title_, nullptr);
    }
}

TEST_F(IptcDataSetsTest_639, RecordIdAndRecordNameConsistency_639) {
    // Test round-trip for record id 1 and 2
    for (uint16_t id : {1, 2}) {
        std::string name = IptcDataSets::recordName(id);
        uint16_t retrievedId = IptcDataSets::recordId(name);
        EXPECT_EQ(retrievedId, id) << "Round-trip failed for record id " << id;
    }
}

TEST_F(IptcDataSetsTest_639, DataSetNameAndDataSetConsistencyEnvelope_639) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    for (int i = 0; list[i].number_ != 0xffff; ++i) {
        std::string name = IptcDataSets::dataSetName(list[i].number_, 1);
        uint16_t number = IptcDataSets::dataSet(name, 1);
        EXPECT_EQ(number, list[i].number_) << "Round-trip failed for envelope dataset " << list[i].number_;
    }
}

TEST_F(IptcDataSetsTest_639, DataSetNameAndDataSetConsistencyApplication2_639) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    for (int i = 0; list[i].number_ != 0xffff; ++i) {
        std::string name = IptcDataSets::dataSetName(list[i].number_, 2);
        uint16_t number = IptcDataSets::dataSet(name, 2);
        EXPECT_EQ(number, list[i].number_) << "Round-trip failed for application2 dataset " << list[i].number_;
    }
}
