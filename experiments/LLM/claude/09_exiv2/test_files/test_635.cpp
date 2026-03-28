#include <gtest/gtest.h>
#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Record IDs commonly used in IPTC
static constexpr uint16_t envelope = 1;
static constexpr uint16_t application2 = 2;

// ============================================================
// Tests for dataSet(const std::string&, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetByKnownName_Envelope_635) {
    // "ModelVersion" is dataset 0 in envelope record
    uint16_t ds = IptcDataSets::dataSet("ModelVersion", envelope);
    EXPECT_EQ(ds, 0);
}

TEST(IptcDataSetsTest_635, DataSetByKnownName_Application2_ObjectName_635) {
    // "ObjectName" is dataset 5 in application2 record
    uint16_t ds = IptcDataSets::dataSet("ObjectName", application2);
    EXPECT_EQ(ds, 5);
}

TEST(IptcDataSetsTest_635, DataSetByKnownName_Application2_Keywords_635) {
    // "Keywords" is dataset 25 in application2 record
    uint16_t ds = IptcDataSets::dataSet("Keywords", application2);
    EXPECT_EQ(ds, 25);
}

TEST(IptcDataSetsTest_635, DataSetByHexString_635) {
    // Unknown name but valid hex should return the hex value
    uint16_t ds = IptcDataSets::dataSet("0x0050", application2);
    EXPECT_EQ(ds, 0x0050);
}

TEST(IptcDataSetsTest_635, DataSetByHexStringZero_635) {
    uint16_t ds = IptcDataSets::dataSet("0x0000", application2);
    EXPECT_EQ(ds, 0x0000);
}

TEST(IptcDataSetsTest_635, DataSetByHexStringMaxFourDigit_635) {
    uint16_t ds = IptcDataSets::dataSet("0xFFFF", application2);
    EXPECT_EQ(ds, 0xFFFF);
}

TEST(IptcDataSetsTest_635, DataSetInvalidNameThrows_635) {
    // A name that is neither a known dataset name nor a valid hex string should throw
    EXPECT_THROW(IptcDataSets::dataSet("NonExistentDataSet", application2), Error);
}

TEST(IptcDataSetsTest_635, DataSetInvalidHexThrows_635) {
    // "0xZZZZ" is not valid hex
    EXPECT_THROW(IptcDataSets::dataSet("0xZZZZ", application2), Error);
}

TEST(IptcDataSetsTest_635, DataSetEmptyStringThrows_635) {
    EXPECT_THROW(IptcDataSets::dataSet("", application2), Error);
}

// ============================================================
// Tests for dataSetName(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetNameKnown_635) {
    std::string name = IptcDataSets::dataSetName(5, application2);
    EXPECT_EQ(name, "ObjectName");
}

TEST(IptcDataSetsTest_635, DataSetNameKnownKeywords_635) {
    std::string name = IptcDataSets::dataSetName(25, application2);
    EXPECT_EQ(name, "Keywords");
}

TEST(IptcDataSetsTest_635, DataSetNameUnknownReturnsHex_635) {
    // Unknown dataset number should return a hex string representation
    std::string name = IptcDataSets::dataSetName(0xFFFF, application2);
    EXPECT_FALSE(name.empty());
    // It should contain "0x" since it's a hex formatted unknown dataset
    EXPECT_NE(name.find("0x"), std::string::npos);
}

TEST(IptcDataSetsTest_635, DataSetNameEnvelopeModelVersion_635) {
    std::string name = IptcDataSets::dataSetName(0, envelope);
    EXPECT_EQ(name, "ModelVersion");
}

// ============================================================
// Tests for dataSetTitle(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetTitleKnown_635) {
    const char* title = IptcDataSets::dataSetTitle(5, application2);
    ASSERT_NE(title, nullptr);
    EXPECT_GT(std::string(title).size(), 0u);
}

TEST(IptcDataSetsTest_635, DataSetTitleUnknown_635) {
    const char* title = IptcDataSets::dataSetTitle(0xFFFF, application2);
    ASSERT_NE(title, nullptr);
}

// ============================================================
// Tests for dataSetDesc(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetDescKnown_635) {
    const char* desc = IptcDataSets::dataSetDesc(5, application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

TEST(IptcDataSetsTest_635, DataSetDescUnknown_635) {
    const char* desc = IptcDataSets::dataSetDesc(0xFFFF, application2);
    ASSERT_NE(desc, nullptr);
}

// ============================================================
// Tests for dataSetPsName(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetPsNameKnown_635) {
    const char* psName = IptcDataSets::dataSetPsName(5, application2);
    ASSERT_NE(psName, nullptr);
}

// ============================================================
// Tests for dataSetRepeatable(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetRepeatableKeywords_635) {
    // Keywords (dataset 25, application2) is typically repeatable
    bool rep = IptcDataSets::dataSetRepeatable(25, application2);
    EXPECT_TRUE(rep);
}

TEST(IptcDataSetsTest_635, DataSetRepeatableObjectName_635) {
    // ObjectName (dataset 5, application2) is typically NOT repeatable
    bool rep = IptcDataSets::dataSetRepeatable(5, application2);
    EXPECT_FALSE(rep);
}

// ============================================================
// Tests for dataSetType(uint16_t, uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetTypeKnown_635) {
    TypeId type = IptcDataSets::dataSetType(5, application2);
    // ObjectName type should be string
    EXPECT_EQ(type, string);
}

TEST(IptcDataSetsTest_635, DataSetTypeModelVersion_635) {
    TypeId type = IptcDataSets::dataSetType(0, envelope);
    // ModelVersion is a short
    EXPECT_EQ(type, unsignedShort);
}

// ============================================================
// Tests for recordName(uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, RecordNameEnvelope_635) {
    std::string name = IptcDataSets::recordName(envelope);
    EXPECT_EQ(name, "Envelope");
}

TEST(IptcDataSetsTest_635, RecordNameApplication2_635) {
    std::string name = IptcDataSets::recordName(application2);
    EXPECT_EQ(name, "Application2");
}

TEST(IptcDataSetsTest_635, RecordNameUnknown_635) {
    std::string name = IptcDataSets::recordName(0xFFFF);
    EXPECT_FALSE(name.empty());
}

// ============================================================
// Tests for recordDesc(uint16_t)
// ============================================================

TEST(IptcDataSetsTest_635, RecordDescEnvelope_635) {
    const char* desc = IptcDataSets::recordDesc(envelope);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

TEST(IptcDataSetsTest_635, RecordDescApplication2_635) {
    const char* desc = IptcDataSets::recordDesc(application2);
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(std::string(desc).size(), 0u);
}

// ============================================================
// Tests for recordId(const std::string&)
// ============================================================

TEST(IptcDataSetsTest_635, RecordIdEnvelope_635) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, envelope);
}

TEST(IptcDataSetsTest_635, RecordIdApplication2_635) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, application2);
}

TEST(IptcDataSetsTest_635, RecordIdInvalidThrows_635) {
    EXPECT_THROW(IptcDataSets::recordId("NonExistentRecord"), Error);
}

// ============================================================
// Tests for envelopeRecordList() and application2RecordList()
// ============================================================

TEST(IptcDataSetsTest_635, EnvelopeRecordListNotNull_635) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
    // First entry should have number_ 0 (ModelVersion)
    EXPECT_EQ(list[0].number_, 0);
}

TEST(IptcDataSetsTest_635, Application2RecordListNotNull_635) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// ============================================================
// Tests for dataSetList(std::ostream&)
// ============================================================

TEST(IptcDataSetsTest_635, DataSetListOutputsData_635) {
    std::ostringstream oss;
    IptcDataSets::dataSetList(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain known dataset names
    EXPECT_NE(output.find("ObjectName"), std::string::npos);
    EXPECT_NE(output.find("Keywords"), std::string::npos);
}

// ============================================================
// Roundtrip: dataSet <-> dataSetName
// ============================================================

TEST(IptcDataSetsTest_635, RoundtripDataSetNameToNumber_635) {
    std::string name = IptcDataSets::dataSetName(25, application2);
    uint16_t number = IptcDataSets::dataSet(name, application2);
    EXPECT_EQ(number, 25);
}

TEST(IptcDataSetsTest_635, RoundtripDataSetNumberToName_635) {
    uint16_t number = IptcDataSets::dataSet("Caption", application2);
    std::string name = IptcDataSets::dataSetName(number, application2);
    EXPECT_EQ(name, "Caption");
}

// ============================================================
// Boundary: Hex values at edges
// ============================================================

TEST(IptcDataSetsTest_635, DataSetHexLowerCase_635) {
    uint16_t ds = IptcDataSets::dataSet("0x00ff", application2);
    EXPECT_EQ(ds, 0x00FF);
}

TEST(IptcDataSetsTest_635, DataSetHexMixedCase_635) {
    uint16_t ds = IptcDataSets::dataSet("0x00Ff", application2);
    EXPECT_EQ(ds, 0x00FF);
}

// ============================================================
// Tests for wrong record but valid dataset name
// ============================================================

TEST(IptcDataSetsTest_635, DataSetNameWrongRecord_635) {
    // "ObjectName" belongs to application2, not envelope
    // Depending on implementation, it may not find it and try hex parse, which fails
    // Or it may still find it. We just verify it doesn't crash.
    try {
        uint16_t ds = IptcDataSets::dataSet("ObjectName", envelope);
        // If it doesn't throw, the returned value is implementation-defined
        (void)ds;
    } catch (const Error&) {
        // It's also acceptable to throw
    }
}
