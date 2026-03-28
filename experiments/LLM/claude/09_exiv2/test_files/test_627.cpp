#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/datasets.hpp"

using namespace Exiv2;

// Test fixture
class IptcDataSetsTest_627 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ========== envelopeRecordList tests ==========

TEST_F(IptcDataSetsTest_627, EnvelopeRecordListIsNotNull_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_627, EnvelopeRecordListFirstEntryIsModelVersion_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    EXPECT_EQ(list[0].number_, IptcDataSets::ModelVersion);
    EXPECT_STREQ(list[0].name_, "ModelVersion");
}

// ========== application2RecordList tests ==========

TEST_F(IptcDataSetsTest_627, Application2RecordListIsNotNull_627) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// ========== dataSetName tests ==========

TEST_F(IptcDataSetsTest_627, DataSetNameModelVersion_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_627, DataSetNameDestination_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::Destination, IptcDataSets::envelope);
    EXPECT_EQ(name, "Destination");
}

TEST_F(IptcDataSetsTest_627, DataSetNameFileFormat_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::FileFormat, IptcDataSets::envelope);
    EXPECT_EQ(name, "FileFormat");
}

TEST_F(IptcDataSetsTest_627, DataSetNameFileVersion_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::FileVersion, IptcDataSets::envelope);
    EXPECT_EQ(name, "FileVersion");
}

TEST_F(IptcDataSetsTest_627, DataSetNameServiceId_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ServiceId, IptcDataSets::envelope);
    EXPECT_EQ(name, "ServiceId");
}

TEST_F(IptcDataSetsTest_627, DataSetNameEnvelopeNumber_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::EnvelopeNumber, IptcDataSets::envelope);
    EXPECT_EQ(name, "EnvelopeNumber");
}

TEST_F(IptcDataSetsTest_627, DataSetNameDateSent_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::DateSent, IptcDataSets::envelope);
    EXPECT_EQ(name, "DateSent");
}

TEST_F(IptcDataSetsTest_627, DataSetNameTimeSent_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::TimeSent, IptcDataSets::envelope);
    EXPECT_EQ(name, "TimeSent");
}

TEST_F(IptcDataSetsTest_627, DataSetNameCharacterSet_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::CharacterSet, IptcDataSets::envelope);
    EXPECT_EQ(name, "CharacterSet");
}

TEST_F(IptcDataSetsTest_627, DataSetNameUNO_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::UNO, IptcDataSets::envelope);
    EXPECT_EQ(name, "UNO");
}

TEST_F(IptcDataSetsTest_627, DataSetNameARMId_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ARMId, IptcDataSets::envelope);
    EXPECT_EQ(name, "ARMId");
}

TEST_F(IptcDataSetsTest_627, DataSetNameARMVersion_627) {
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ARMVersion, IptcDataSets::envelope);
    EXPECT_EQ(name, "ARMVersion");
}

TEST_F(IptcDataSetsTest_627, DataSetNameInvalidDataSet_627) {
    // Testing with an unknown dataset number
    std::string name = IptcDataSets::dataSetName(9999, IptcDataSets::envelope);
    EXPECT_FALSE(name.empty());
}

// ========== dataSetTitle tests ==========

TEST_F(IptcDataSetsTest_627, DataSetTitleModelVersion_627) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Model Version");
}

TEST_F(IptcDataSetsTest_627, DataSetTitleDestination_627) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::Destination, IptcDataSets::envelope);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Destination");
}

TEST_F(IptcDataSetsTest_627, DataSetTitleDateSent_627) {
    const char* title = IptcDataSets::dataSetTitle(IptcDataSets::DateSent, IptcDataSets::envelope);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Date Sent");
}

// ========== dataSetDesc tests ==========

TEST_F(IptcDataSetsTest_627, DataSetDescModelVersion_627) {
    const char* desc = IptcDataSets::dataSetDesc(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

TEST_F(IptcDataSetsTest_627, DataSetDescEnvelopePriority_627) {
    const char* desc = IptcDataSets::dataSetDesc(IptcDataSets::EnvelopePriority, IptcDataSets::envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

// ========== dataSetPsName tests ==========

TEST_F(IptcDataSetsTest_627, DataSetPsNameModelVersion_627) {
    const char* psName = IptcDataSets::dataSetPsName(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    ASSERT_NE(psName, nullptr);
}

// ========== dataSetRepeatable tests ==========

TEST_F(IptcDataSetsTest_627, DataSetRepeatableDestinationIsTrue_627) {
    bool repeatable = IptcDataSets::dataSetRepeatable(IptcDataSets::Destination, IptcDataSets::envelope);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_627, DataSetRepeatableModelVersionIsFalse_627) {
    bool repeatable = IptcDataSets::dataSetRepeatable(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_627, DataSetRepeatableProductIdIsTrue_627) {
    bool repeatable = IptcDataSets::dataSetRepeatable(IptcDataSets::ProductId, IptcDataSets::envelope);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_627, DataSetRepeatableEnvelopePriorityIsFalse_627) {
    bool repeatable = IptcDataSets::dataSetRepeatable(IptcDataSets::EnvelopePriority, IptcDataSets::envelope);
    EXPECT_FALSE(repeatable);
}

// ========== dataSetType tests ==========

TEST_F(IptcDataSetsTest_627, DataSetTypeModelVersionIsUnsignedShort_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeDestinationIsString_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::Destination, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::string);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeDateSentIsDate_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::DateSent, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::date);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeTimeSentIsTime_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::TimeSent, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::time);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeServiceIdIsString_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::ServiceId, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::string);
}

// ========== dataSet (lookup by name) tests ==========

TEST_F(IptcDataSetsTest_627, DataSetLookupModelVersion_627) {
    uint16_t number = IptcDataSets::dataSet("ModelVersion", IptcDataSets::envelope);
    EXPECT_EQ(number, IptcDataSets::ModelVersion);
}

TEST_F(IptcDataSetsTest_627, DataSetLookupDestination_627) {
    uint16_t number = IptcDataSets::dataSet("Destination", IptcDataSets::envelope);
    EXPECT_EQ(number, IptcDataSets::Destination);
}

TEST_F(IptcDataSetsTest_627, DataSetLookupDateSent_627) {
    uint16_t number = IptcDataSets::dataSet("DateSent", IptcDataSets::envelope);
    EXPECT_EQ(number, IptcDataSets::DateSent);
}

TEST_F(IptcDataSetsTest_627, DataSetLookupEnvelopeNumber_627) {
    uint16_t number = IptcDataSets::dataSet("EnvelopeNumber", IptcDataSets::envelope);
    EXPECT_EQ(number, IptcDataSets::EnvelopeNumber);
}

TEST_F(IptcDataSetsTest_627, DataSetLookupInvalidName_627) {
    // Looking up an invalid name should either throw or return a sentinel value
    EXPECT_ANY_THROW(IptcDataSets::dataSet("NonExistentDataSet", IptcDataSets::envelope));
}

// ========== recordName tests ==========

TEST_F(IptcDataSetsTest_627, RecordNameEnvelope_627) {
    std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_627, RecordNameApplication2_627) {
    std::string name = IptcDataSets::recordName(IptcDataSets::application2);
    EXPECT_FALSE(name.empty());
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_627, RecordNameInvalidRecord_627) {
    std::string name = IptcDataSets::recordName(9999);
    EXPECT_FALSE(name.empty());
}

// ========== recordDesc tests ==========

TEST_F(IptcDataSetsTest_627, RecordDescEnvelope_627) {
    const char* desc = IptcDataSets::recordDesc(IptcDataSets::envelope);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_627, RecordDescApplication2_627) {
    const char* desc = IptcDataSets::recordDesc(IptcDataSets::application2);
    ASSERT_NE(desc, nullptr);
}

// ========== recordId tests ==========

TEST_F(IptcDataSetsTest_627, RecordIdEnvelope_627) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST_F(IptcDataSetsTest_627, RecordIdApplication2_627) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, IptcDataSets::application2);
}

TEST_F(IptcDataSetsTest_627, RecordIdInvalidName_627) {
    EXPECT_ANY_THROW(IptcDataSets::recordId("NonExistentRecord"));
}

// ========== dataSetList tests ==========

TEST_F(IptcDataSetsTest_627, DataSetListProducesOutput_627) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_627, DataSetListContainsModelVersion_627) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("ModelVersion"), std::string::npos);
}

TEST_F(IptcDataSetsTest_627, DataSetListContainsDestination_627) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("Destination"), std::string::npos);
}

TEST_F(IptcDataSetsTest_627, DataSetListContainsDateSent_627) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("DateSent"), std::string::npos);
}

// ========== Cross-check consistency tests ==========

TEST_F(IptcDataSetsTest_627, DataSetNameAndLookupAreConsistent_627) {
    // Getting name from number then looking up by name should return the same number
    std::string name = IptcDataSets::dataSetName(IptcDataSets::ModelVersion, IptcDataSets::envelope);
    uint16_t number = IptcDataSets::dataSet(name, IptcDataSets::envelope);
    EXPECT_EQ(number, IptcDataSets::ModelVersion);
}

TEST_F(IptcDataSetsTest_627, RecordNameAndRecordIdAreConsistent_627) {
    std::string name = IptcDataSets::recordName(IptcDataSets::envelope);
    uint16_t id = IptcDataSets::recordId(name);
    EXPECT_EQ(id, IptcDataSets::envelope);
}

TEST_F(IptcDataSetsTest_627, EnvelopeRecordListEntriesMatchStaticLookups_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    // First entry should match ModelVersion lookups
    std::string name = IptcDataSets::dataSetName(list[0].number_, IptcDataSets::envelope);
    EXPECT_EQ(name, std::string(list[0].name_));
}

// ========== Boundary/edge tests for envelope record entries ==========

TEST_F(IptcDataSetsTest_627, EnvelopeRecordListLastValidEntryIsARMVersion_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    // The 14th entry (index 13) should be ARMVersion based on global data
    EXPECT_EQ(list[13].number_, IptcDataSets::ARMVersion);
    EXPECT_STREQ(list[13].name_, "ARMVersion");
}

TEST_F(IptcDataSetsTest_627, EnvelopeRecordListTerminatedBySentinel_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    // The 15th entry (index 14) should be the sentinel with number 65535
    EXPECT_EQ(list[14].number_, 0xFFFF);
}

TEST_F(IptcDataSetsTest_627, AllEnvelopeEntriesHaveEnvelopeRecordId_627) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    for (int i = 0; i < 14; ++i) {
        EXPECT_EQ(list[i].recordId_, IptcDataSets::envelope)
            << "Entry " << i << " (" << list[i].name_ << ") has wrong recordId";
    }
}

// ========== Multiple envelope dataset type checks ==========

TEST_F(IptcDataSetsTest_627, DataSetTypeFileFormatIsUnsignedShort_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::FileFormat, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeARMIdIsUnsignedShort_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::ARMId, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::unsignedShort);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeEnvelopeNumberIsString_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::EnvelopeNumber, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::string);
}

TEST_F(IptcDataSetsTest_627, DataSetTypeCharacterSetIsString_627) {
    TypeId type = IptcDataSets::dataSetType(IptcDataSets::CharacterSet, IptcDataSets::envelope);
    EXPECT_EQ(type, Exiv2::string);
}

// ========== Tests with application2 record ==========

TEST_F(IptcDataSetsTest_627, Application2RecordListFirstEntryValid_627) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
    // The first entry should have a valid name
    ASSERT_NE(list[0].name_, nullptr);
    EXPECT_TRUE(std::string(list[0].name_).length() > 0);
}

TEST_F(IptcDataSetsTest_627, RecordNameForApplication2_627) {
    std::string name = IptcDataSets::recordName(IptcDataSets::application2);
    EXPECT_EQ(name, "Application2");
}

// ========== dataSetName with invalid number and record ==========

TEST_F(IptcDataSetsTest_627, DataSetNameUnknownNumberEnvelope_627) {
    // Using an unknown dataset number
    std::string name = IptcDataSets::dataSetName(12345, IptcDataSets::envelope);
    // Should return some name (possibly with the number in hex)
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_627, DataSetTitleForInvalidDataSet_627) {
    const char* title = IptcDataSets::dataSetTitle(9999, IptcDataSets::envelope);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_627, DataSetDescForInvalidDataSet_627) {
    const char* desc = IptcDataSets::dataSetDesc(9999, IptcDataSets::envelope);
    ASSERT_NE(desc, nullptr);
}
