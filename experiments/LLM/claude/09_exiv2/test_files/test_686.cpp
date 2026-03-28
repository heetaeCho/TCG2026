#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_686 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test construction with IptcKey and null value
TEST_F(IptcdatumTest_686, ConstructWithKeyAndNullValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test construction with IptcKey and a Value
TEST_F(IptcdatumTest_686, ConstructWithKeyAndValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Hello World");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "Hello World");
    EXPECT_EQ(datum.count(), 1u);
}

// Test copy constructor
TEST_F(IptcdatumTest_686, CopyConstructor_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test Copy");
    Iptcdatum original(key, value.get());
    
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.familyName(), original.familyName());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test copy constructor with null value
TEST_F(IptcdatumTest_686, CopyConstructorNullValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum original(key, nullptr);
    
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
}

// Test assignment operator (deep copy)
TEST_F(IptcdatumTest_686, AssignmentOperator_686) {
    IptcKey key1("Iptc.Application2.Caption");
    auto value1 = Value::create(string);
    value1->read("Value1");
    Iptcdatum datum1(key1, value1.get());
    
    IptcKey key2("Iptc.Application2.Keywords");
    auto value2 = Value::create(string);
    value2->read("Value2");
    Iptcdatum datum2(key2, value2.get());
    
    datum1 = datum2;
    
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
    EXPECT_EQ(datum1.tagName(), datum2.tagName());
}

// Test self-assignment
TEST_F(IptcdatumTest_686, SelfAssignment_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("SelfAssign");
    Iptcdatum datum(key, value.get());
    
    datum = datum;
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "SelfAssign");
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_686, AssignUint16_686) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    
    uint16_t val = 42;
    datum = val;
    
    EXPECT_EQ(datum.toString(), "42");
}

// Test assignment from string
TEST_F(IptcdatumTest_686, AssignString_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Assigned String");
    
    EXPECT_EQ(datum.toString(), "Assigned String");
}

// Test assignment from Value
TEST_F(IptcdatumTest_686, AssignValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("Value Object");
    datum = *val;
    
    EXPECT_EQ(datum.toString(), "Value Object");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_686, SetValuePointer_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("Set via pointer");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "Set via pointer");
}

// Test setValue with null pointer
TEST_F(IptcdatumTest_686, SetValueNullPointer_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Initial");
    Iptcdatum datum(key, val.get());
    
    datum.setValue(nullptr);
    // After setting null, the datum should have no value
    // getValue should return nullptr or similar
}

// Test setValue with string
TEST_F(IptcdatumTest_686, SetValueString_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Initial");
    Iptcdatum datum(key, val.get());
    
    int result = datum.setValue("New String Value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "New String Value");
}

// Test key-related accessors
TEST_F(IptcdatumTest_686, KeyAccessors_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(std::string(datum.familyName()), "Iptc");
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.recordName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag and record
TEST_F(IptcdatumTest_686, TagAndRecord_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // Caption tag in Application2 record should return specific values
    uint16_t tag = datum.tag();
    uint16_t record = datum.record();
    
    // Application2 record is 2
    EXPECT_EQ(record, 2u);
    // Caption tag is 120
    EXPECT_EQ(tag, 120u);
}

// Test typeId when value is set
TEST_F(IptcdatumTest_686, TypeIdWithValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Test");
    Iptcdatum datum(key, val.get());
    
    EXPECT_EQ(datum.typeId(), string);
}

// Test count and size with value
TEST_F(IptcdatumTest_686, CountAndSizeWithValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Test");
    Iptcdatum datum(key, val.get());
    
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test write to ostream
TEST_F(IptcdatumTest_686, WriteToStream_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Stream Test");
    Iptcdatum datum(key, val.get());
    
    std::ostringstream os;
    datum.write(os, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test getValue returns valid unique_ptr
TEST_F(IptcdatumTest_686, GetValue_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("GetValue Test");
    Iptcdatum datum(key, val.get());
    
    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "GetValue Test");
}

// Test value() returns reference
TEST_F(IptcdatumTest_686, ValueReference_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Reference Test");
    Iptcdatum datum(key, val.get());
    
    const Value& ref = datum.value();
    EXPECT_EQ(ref.toString(), "Reference Test");
}

// Test deep copy behavior of assignment operator
TEST_F(IptcdatumTest_686, AssignmentDeepCopy_686) {
    IptcKey key1("Iptc.Application2.Caption");
    auto value1 = Value::create(string);
    value1->read("Original");
    Iptcdatum datum1(key1, value1.get());
    
    IptcKey key2("Iptc.Application2.Keywords");
    auto value2 = Value::create(string);
    value2->read("Copy Source");
    Iptcdatum datum2(key2, value2.get());
    
    datum1 = datum2;
    
    // Modify datum2 - datum1 should not be affected (deep copy)
    datum2 = std::string("Modified");
    
    EXPECT_EQ(datum1.toString(), "Copy Source");
    EXPECT_EQ(datum2.toString(), "Modified");
}

// Test deep copy behavior of copy constructor
TEST_F(IptcdatumTest_686, CopyConstructorDeepCopy_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Original Value");
    Iptcdatum original(key, val.get());
    
    Iptcdatum copy(original);
    
    // Modify original - copy should not be affected
    original = std::string("Modified Original");
    
    EXPECT_EQ(copy.toString(), "Original Value");
    EXPECT_EQ(original.toString(), "Modified Original");
}

// Test assignment from null-valued datum
TEST_F(IptcdatumTest_686, AssignmentFromNullValueDatum_686) {
    IptcKey key1("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Has Value");
    Iptcdatum datum1(key1, val.get());
    
    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    
    datum1 = datum2;
    
    EXPECT_EQ(datum1.key(), datum2.key());
}

// Test toString with index
TEST_F(IptcdatumTest_686, ToStringWithIndex_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Indexed");
    Iptcdatum datum(key, val.get());
    
    std::string str = datum.toString(0);
    EXPECT_EQ(str, "Indexed");
}

// Test toInt64
TEST_F(IptcdatumTest_686, ToInt64_686) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t urgency = 5;
    datum = urgency;
    
    int64_t intVal = datum.toInt64(0);
    EXPECT_EQ(intVal, 5);
}

// Test copy to buffer
TEST_F(IptcdatumTest_686, CopyToBuffer_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Buffer");
    Iptcdatum datum(key, val.get());
    
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test different record types
TEST_F(IptcdatumTest_686, EnvelopeRecord_686) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.record(), 1u);
}

// Test typeName when value is set
TEST_F(IptcdatumTest_686, TypeName_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("TypeName");
    Iptcdatum datum(key, val.get());
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
}

// Test multiple assignments
TEST_F(IptcdatumTest_686, MultipleAssignments_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
    
    datum = std::string("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test tagLabel and tagDesc
TEST_F(IptcdatumTest_686, TagLabelAndDesc_686) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    std::string desc = datum.tagDesc();
    
    // These should return non-empty strings for known tags
    EXPECT_FALSE(label.empty());
}

// Test assignment operator preserves key after value change
TEST_F(IptcdatumTest_686, AssignmentPreservesKeyInfo_686) {
    IptcKey key("Iptc.Application2.Caption");
    auto val = Value::create(string);
    val->read("Initial");
    Iptcdatum datum(key, val.get());
    
    IptcKey key2("Iptc.Application2.Keywords");
    auto val2 = Value::create(string);
    val2->read("Keywords Value");
    Iptcdatum datum2(key2, val2.get());
    
    datum = datum2;
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "Keywords Value");
}
