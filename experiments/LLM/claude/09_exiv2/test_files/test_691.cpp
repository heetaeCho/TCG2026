#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_691 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a known IPTC key
TEST_F(IptcdatumTest_691, ConstructWithValidKey_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test that tag() returns the correct dataset number
TEST_F(IptcdatumTest_691, TagReturnsCorrectDataset_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    // Caption is dataset 120 in Application Record 2
    EXPECT_EQ(datum.tag(), 120);
}

// Test record() returns the correct record ID
TEST_F(IptcdatumTest_691, RecordReturnsCorrectRecordId_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.record(), 2);
}

// Test recordName() returns correct record name
TEST_F(IptcdatumTest_691, RecordNameReturnsApplication2_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tagName() returns the correct tag name
TEST_F(IptcdatumTest_691, TagNameReturnsCaption_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test setValue with a string value
TEST_F(IptcdatumTest_691, SetValueString_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test count after setValue
TEST_F(IptcdatumTest_691, CountAfterSetValue_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Test Caption");
    EXPECT_GT(datum.count(), 0u);
}

// Test size after setValue
TEST_F(IptcdatumTest_691, SizeAfterSetValue_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Test Caption");
    EXPECT_GT(datum.size(), 0u);
}

// Test assignment operator with string
TEST_F(IptcdatumTest_691, AssignmentOperatorString_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum = std::string("Assigned Value");
    EXPECT_EQ(datum.toString(), "Assigned Value");
}

// Test copy constructor
TEST_F(IptcdatumTest_691, CopyConstructor_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Copy Test");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Copy Test");
    EXPECT_EQ(copy.tag(), datum.tag());
    EXPECT_EQ(copy.record(), datum.record());
}

// Test assignment operator (copy)
TEST_F(IptcdatumTest_691, CopyAssignment_691) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1);
    datum1.setValue("First");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2);
    datum2.setValue("Second");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum2.toString(), "First");
}

// Test setValue with Value pointer (nullptr resets)
TEST_F(IptcdatumTest_691, SetValueWithNullptr_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Initial");
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting null, count and size should be 0
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue with a Value object
TEST_F(IptcdatumTest_691, SetValueWithValueObject_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    auto value = Value::create(string);
    value->read("Value Object Test");
    datum.setValue(value.get());
    EXPECT_EQ(datum.toString(), "Value Object Test");
}

// Test assignment operator with Value reference
TEST_F(IptcdatumTest_691, AssignmentOperatorValueRef_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    auto value = Value::create(string);
    value->read("Value Ref Test");
    datum = *value;
    EXPECT_EQ(datum.toString(), "Value Ref Test");
}

// Test getValue returns a valid unique_ptr
TEST_F(IptcdatumTest_691, GetValueReturnsValidPtr_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("GetValue Test");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "GetValue Test");
}

// Test value() reference
TEST_F(IptcdatumTest_691, ValueReferenceAccess_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Value Ref");
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "Value Ref");
}

// Test typeId after setValue
TEST_F(IptcdatumTest_691, TypeIdAfterSetValue_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Type Test");
    // Caption should be of type string
    EXPECT_EQ(datum.typeId(), string);
}

// Test typeName
TEST_F(IptcdatumTest_691, TypeNameIsNotNull_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("TypeName Test");
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
}

// Test with Envelope record
TEST_F(IptcdatumTest_691, EnvelopeRecordDatum_691) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Envelope");
}

// Test write to ostream
TEST_F(IptcdatumTest_691, WriteToStream_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Stream Test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("Stream Test"), std::string::npos);
}

// Test with Keywords (repeatable dataset)
TEST_F(IptcdatumTest_691, KeywordsDataset_691) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key);
    datum.setValue("keyword1");
    EXPECT_EQ(datum.toString(), "keyword1");
    EXPECT_EQ(datum.tagName(), "Keywords");
}

// Test assignment operator with uint16_t
TEST_F(IptcdatumTest_691, AssignmentOperatorUint16_691) {
    // Urgency is a numeric dataset
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key);
    datum = std::string("5");
    EXPECT_EQ(datum.toString(), "5");
}

// Test copy to buffer
TEST_F(IptcdatumTest_691, CopyToBuffer_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("Buffer Test");
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test toString with index
TEST_F(IptcdatumTest_691, ToStringWithIndex_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("IndexTest");
    std::string s = datum.toString(0);
    EXPECT_EQ(s, "IndexTest");
}

// Test tagLabel returns non-empty for known dataset
TEST_F(IptcdatumTest_691, TagLabelNonEmpty_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test empty value before setValue
TEST_F(IptcdatumTest_691, EmptyValueBeforeSetValue_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test setValue called multiple times overwrites
TEST_F(IptcdatumTest_691, SetValueOverwrites_691) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key);
    datum.setValue("First Value");
    EXPECT_EQ(datum.toString(), "First Value");
    datum.setValue("Second Value");
    EXPECT_EQ(datum.toString(), "Second Value");
}

// Test IptcDataSets utility functions
class IptcDataSetsTest_691 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_691, DataSetNameForCaption_691) {
    std::string name = IptcDataSets::dataSetName(120, 2);
    EXPECT_EQ(name, "Caption");
}

TEST_F(IptcDataSetsTest_691, DataSetTitleForCaption_691) {
    const char* title = IptcDataSets::dataSetTitle(120, 2);
    ASSERT_NE(title, nullptr);
}

TEST_F(IptcDataSetsTest_691, DataSetDescForCaption_691) {
    const char* desc = IptcDataSets::dataSetDesc(120, 2);
    ASSERT_NE(desc, nullptr);
}

TEST_F(IptcDataSetsTest_691, DataSetRepeatableKeywords_691) {
    // Keywords (dataset 25, record 2) should be repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(25, 2);
    EXPECT_TRUE(repeatable);
}

TEST_F(IptcDataSetsTest_691, DataSetRepeatableCaption_691) {
    // Caption (dataset 120, record 2) is typically not repeatable
    bool repeatable = IptcDataSets::dataSetRepeatable(120, 2);
    EXPECT_FALSE(repeatable);
}

TEST_F(IptcDataSetsTest_691, DataSetLookupByName_691) {
    uint16_t ds = IptcDataSets::dataSet("Caption", 2);
    EXPECT_EQ(ds, 120);
}

TEST_F(IptcDataSetsTest_691, RecordNameForRecord2_691) {
    std::string name = IptcDataSets::recordName(2);
    EXPECT_EQ(name, "Application2");
}

TEST_F(IptcDataSetsTest_691, RecordNameForRecord1_691) {
    std::string name = IptcDataSets::recordName(1);
    EXPECT_EQ(name, "Envelope");
}

TEST_F(IptcDataSetsTest_691, RecordIdFromName_691) {
    uint16_t id = IptcDataSets::recordId("Application2");
    EXPECT_EQ(id, 2);
}

TEST_F(IptcDataSetsTest_691, RecordIdFromEnvelopeName_691) {
    uint16_t id = IptcDataSets::recordId("Envelope");
    EXPECT_EQ(id, 1);
}

TEST_F(IptcDataSetsTest_691, DataSetType_691) {
    TypeId type = IptcDataSets::dataSetType(120, 2);
    EXPECT_EQ(type, string);
}

TEST_F(IptcDataSetsTest_691, DataSetListToStream_691) {
    std::ostringstream os;
    IptcDataSets::dataSetList(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(IptcDataSetsTest_691, EnvelopeRecordListNotNull_691) {
    const DataSet* list = IptcDataSets::envelopeRecordList();
    ASSERT_NE(list, nullptr);
}

TEST_F(IptcDataSetsTest_691, Application2RecordListNotNull_691) {
    const DataSet* list = IptcDataSets::application2RecordList();
    ASSERT_NE(list, nullptr);
}

// Test with an unknown dataset number
TEST_F(IptcDataSetsTest_691, UnknownDataSetName_691) {
    // Using an unlikely dataset number
    std::string name = IptcDataSets::dataSetName(9999, 2);
    // Should return some default/unknown name
    EXPECT_FALSE(name.empty());
}

// Test PsName for known dataset
TEST_F(IptcDataSetsTest_691, DataSetPsNameForCaption_691) {
    const char* psName = IptcDataSets::dataSetPsName(120, 2);
    ASSERT_NE(psName, nullptr);
}

// Test RecordDesc
TEST_F(IptcDataSetsTest_691, RecordDescForRecord2_691) {
    const char* desc = IptcDataSets::recordDesc(2);
    ASSERT_NE(desc, nullptr);
}
