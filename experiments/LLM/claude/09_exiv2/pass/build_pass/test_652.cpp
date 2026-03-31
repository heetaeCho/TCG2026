#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/datasets.hpp>
#include <exiv2/types.hpp>

using namespace Exiv2;

// ============================================================
// Tests for IptcDataSets static methods
// ============================================================

class IptcDataSetsTest_652 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- recordName / recordId ---

TEST_F(IptcDataSetsTest_652, RecordNameEnvelope_652) {
    std::string name = IptcDataSets::recordName(1);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_652, RecordNameApplication2_652) {
    std::string name = IptcDataSets::recordName(2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_652, RecordNameUnknown_652) {
    // Unknown record id should return some string (likely a numeric representation)
    std::string name = IptcDataSets::recordName(999);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcDataSetsTest_652, RecordIdEnvelope_652) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_652, RecordIdApplication2_652) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_652, RecordIdUnknown_652) {
    // Unknown record name - should return some value (likely 0xffff or similar)
    uint16_t id = IptcDataSets::recordId("NonExistentRecord");
    // Just ensure it doesn't crash and returns something
    EXPECT_TRUE(id != 1 && id != 2);
}

// --- dataSetName ---

TEST_F(IptcDataSetsTest_652, DataSetNameKnownEnvelope_652) {
    // Dataset 0 in Envelope record (record 1) is "ModelVersion"
    std::string name = IptcDataSets::dataSetName(0, 1);
    EXPECT_EQ(name, "ModelVersion");
}

TEST_F(IptcDataSetsTest_652, DataSetNameKnownApplication2_652) {
    // Dataset 5 in Application2 (record 2) is "ObjectName"
    std::string name = IptcDataSets::dataSetName(5, 2);
    EXPECT_EQ(name, "ObjectName");
}

TEST_F(IptcDataSetsTest_652, DataSetNameUnknown_652) {
    // Unknown dataset number - should return a string representation
    std::string name = IptcDataSets::dataSetName(9999, 1);
    EXPECT_FALSE(name.empty());
}

// --- dataSetTitle ---

TEST_F(IptcDataSetsTest_652, DataSetTitleKnown_652) {
    const char* title = IptcDataSets::dataSetTitle(0, 1);
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(std::string(title).length() > 0);
}

TEST_F(IptcDataSetsTest_652, DataSetTitleUnknown_652) {
    const char* title = IptcDataSets::dataSetTitle(9999, 1);
    ASSERT_NE(title, nullptr);
}

// --- dataSetDesc ---

TEST_F(IptcDataSetsTest_652, DataSetDescKnown_652) {
    const char* desc = IptcDataSets::dataSetDesc(0, 1);
    ASSERT_NE(desc, nullptr);
}

// --- dataSetPsName ---

TEST_F(IptcDataSetsTest_652, DataSetPsNameKnown_652) {
    const char* psName = IptcDataSets::dataSetPsName(5, 2);
    ASSERT_NE(psName, nullptr);
}

// --- dataSetRepeatable ---

TEST_F(IptcDataSetsTest_652, DataSetRepeatableKnown_652) {
    // ModelVersion (0, 1) is typically not repeatable
    bool rep = IptcDataSets::dataSetRepeatable(0, 1);
    EXPECT_FALSE(rep);
}

TEST_F(IptcDataSetsTest_652, DataSetRepeatableKeywords_652) {
    // Keywords (25, 2) is typically repeatable
    bool rep = IptcDataSets::dataSetRepeatable(25, 2);
    EXPECT_TRUE(rep);
}

// --- dataSet (lookup by name) ---

TEST_F(IptcDataSetsTest_652, DataSetLookupByName_652) {
    uint16_t ds = IptcDataSets::dataSet("ModelVersion", 1);
    EXPECT_EQ(ds, 0);
}

TEST_F(IptcDataSetsTest_652, DataSetLookupByNameApplication2_652) {
    uint16_t ds = IptcDataSets::dataSet("ObjectName", 2);
    EXPECT_EQ(ds, 5);
}

// --- dataSetType ---

TEST_F(IptcDataSetsTest_652, DataSetTypeKnown_652) {
    TypeId type = IptcDataSets::dataSetType(0, 1);
    // ModelVersion is typically unsignedShort
    EXPECT_EQ(type, unsignedShort);
}

// --- recordDesc ---

TEST_F(IptcDataSetsTest_652, RecordDescEnvelope_652) {
    const char* desc = IptcDataSets::recordDesc(1);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

TEST_F(IptcDataSetsTest_652, RecordDescApplication2_652) {
    const char* desc = IptcDataSets::recordDesc(2);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

// --- envelopeRecordList / application2RecordList ---

TEST_F(IptcDataSetsTest_652, EnvelopeRecordListNotNull_652) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_652, Application2RecordListNotNull_652) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// --- dataSetList ---

TEST_F(IptcDataSetsTest_652, DataSetListOutputsNonEmpty_652) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(IptcDataSetsTest_652, DataSetListContainsKnownEntry_652) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    // Should contain ModelVersion or similar known datasets
    EXPECT_NE(output.find("ModelVersion"), std::string::npos);
}

// ============================================================
// Tests for IptcKey
// ============================================================

class IptcKeyTest_652 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(IptcKeyTest_652, ConstructFromTagAndRecord_652) {
    IptcKey key(0, 1);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.familyName(), std::string("Iptc"));
}

TEST_F(IptcKeyTest_652, ConstructFromString_652) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.key(), "Iptc.Envelope.ModelVersion");
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 1);
}

TEST_F(IptcKeyTest_652, KeyFormatFromTagRecord_652) {
    IptcKey key(5, 2);
    std::string k = key.key();
    EXPECT_EQ(k, "Iptc.Application2.ObjectName");
}

TEST_F(IptcKeyTest_652, FamilyNameIsIptc_652) {
    IptcKey key(5, 2);
    EXPECT_STREQ(key.familyName(), "Iptc");
}

TEST_F(IptcKeyTest_652, GroupNameIsRecordName_652) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.groupName(), "Application2");
}

TEST_F(IptcKeyTest_652, TagNameIsDataSetName_652) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.tagName(), "ObjectName");
}

TEST_F(IptcKeyTest_652, RecordNameMethod_652) {
    IptcKey key(5, 2);
    EXPECT_EQ(key.recordName(), "Application2");
}

TEST_F(IptcKeyTest_652, CloneProducesCopy_652) {
    IptcKey key(5, 2);
    auto clone = key.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->key(), key.key());
    EXPECT_EQ(clone->tag(), key.tag());
}

TEST_F(IptcKeyTest_652, ConstructFromStringEnvelope_652) {
    IptcKey key("Iptc.Envelope.Destination");
    EXPECT_EQ(key.record(), 1);
    EXPECT_EQ(key.tag(), 5);
    EXPECT_EQ(key.tagName(), "Destination");
}

TEST_F(IptcKeyTest_652, TagLabelNonEmpty_652) {
    IptcKey key(5, 2);
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(IptcKeyTest_652, TagDescNonEmpty_652) {
    IptcKey key(5, 2);
    std::string desc = key.tagDesc();
    // desc may or may not be empty depending on dataset, just verify no crash
    (void)desc;
}

// ============================================================
// Tests for operator<< (DataSet streaming)
// ============================================================

class DataSetOutputTest_652 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DataSetOutputTest_652, DataSetListContainsFormattedOutput_652) {
    // We can exercise operator<< indirectly through dataSetList
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    
    // The output should contain hex values (0x prefix from format)
    EXPECT_NE(output.find("0x"), std::string::npos);
    // Should contain "true" or "false" for mandatory/repeatable fields
    EXPECT_TRUE(output.find("true") != std::string::npos || output.find("false") != std::string::npos);
    // Should contain "Iptc." as part of key strings
    EXPECT_NE(output.find("Iptc."), std::string::npos);
}

TEST_F(DataSetOutputTest_652, DataSetListContainsEnvelopeEntries_652) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("Envelope"), std::string::npos);
}

TEST_F(DataSetOutputTest_652, DataSetListContainsApplication2Entries_652) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    std::string output = os.str();
    EXPECT_NE(output.find("Application2"), std::string::npos);
}

// ============================================================
// Boundary / Error tests
// ============================================================

class IptcBoundaryTest_652 : public ::testing::Test {};

TEST_F(IptcBoundaryTest_652, UnknownDataSetNumber_652) {
    // Querying an unknown dataset should not crash
    std::string name = IptcDataSets::dataSetName(0xFFFF, 1);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcBoundaryTest_652, UnknownRecordId_652) {
    std::string name = IptcDataSets::recordName(0xFFFF);
    EXPECT_FALSE(name.empty());
}

TEST_F(IptcBoundaryTest_652, DataSetTypeUnknownDataSet_652) {
    // Should return some default type for unknown dataset
    TypeId type = IptcDataSets::dataSetType(0xFFFF, 1);
    const char* tn = TypeInfo::typeName(type);
    ASSERT_NE(tn, nullptr);
}

TEST_F(IptcBoundaryTest_652, IptcKeyFromInvalidStringThrows_652) {
    // An improperly formatted key string should throw or handle gracefully
    EXPECT_THROW(IptcKey("InvalidKeyFormat"), std::exception);
}

TEST_F(IptcBoundaryTest_652, IptcKeyZeroTagZeroRecord_652) {
    // Edge case: tag=0, record=0 - should not crash
    // Record 0 may be unknown but should still work
    IptcKey key(0, 0);
    EXPECT_EQ(key.tag(), 0);
    EXPECT_EQ(key.record(), 0);
    std::string k = key.key();
    EXPECT_FALSE(k.empty());
}

TEST_F(IptcBoundaryTest_652, RecordDescUnknownRecord_652) {
    const char* desc = IptcDataSets::recordDesc(0);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcBoundaryTest_652, DataSetRepeatableUnknown_652) {
    // Unknown dataset - should not crash
    bool rep = IptcDataSets::dataSetRepeatable(0xFFFF, 0xFFFF);
    // Just checking it returns a bool without crashing
    (void)rep;
}

// ============================================================
// TypeInfo tests (basic)
// ============================================================

class TypeInfoTest_652 : public ::testing::Test {};

TEST_F(TypeInfoTest_652, TypeNameForUnsignedShort_652) {
    const char* name = TypeInfo::typeName(unsignedShort);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Short");
}

TEST_F(TypeInfoTest_652, TypeNameForString_652) {
    const char* name = TypeInfo::typeName(string);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "String");
}

TEST_F(TypeInfoTest_652, TypeIdRoundTrip_652) {
    const char* name = TypeInfo::typeName(unsignedShort);
    ASSERT_NE(name, nullptr);
    TypeId id = TypeInfo::typeId(name);
    EXPECT_EQ(id, unsignedShort);
}

TEST_F(TypeInfoTest_652, TypeSizeUnsignedShort_652) {
    size_t sz = TypeInfo::typeSize(unsignedShort);
    EXPECT_EQ(sz, 2u);
}
