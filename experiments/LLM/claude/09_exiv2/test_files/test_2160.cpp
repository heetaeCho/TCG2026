#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

// Test fixture
class IptcdatumTest_2160 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with key and null value
TEST_F(IptcdatumTest_2160, ConstructWithNullValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test construction with key and a valid value
TEST_F(IptcdatumTest_2160, ConstructWithValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Hello World");
    
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "Hello World");
    EXPECT_EQ(datum.count(), 1u);
    EXPECT_GT(datum.size(), 0u);
}

// Test copy constructor
TEST_F(IptcdatumTest_2160, CopyConstructor_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test Value");
    
    Iptcdatum original(key, value.get());
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.familyName(), original.familyName());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_2160, AssignmentOperatorIptcdatum_2160) {
    IptcKey key1("Iptc.Application2.Caption");
    auto value1 = Value::create(string);
    value1->read("First");
    Iptcdatum datum1(key1, value1.get());
    
    IptcKey key2("Iptc.Application2.Keywords");
    auto value2 = Value::create(string);
    value2->read("Second");
    Iptcdatum datum2(key2, value2.get());
    
    datum1 = datum2;
    EXPECT_EQ(datum1.key(), datum2.key());
    EXPECT_EQ(datum1.toString(), datum2.toString());
}

// Test assignment operator from string
TEST_F(IptcdatumTest_2160, AssignmentOperatorString_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Assigned String");
    EXPECT_EQ(datum.toString(), "Assigned String");
}

// Test assignment operator from uint16_t
TEST_F(IptcdatumTest_2160, AssignmentOperatorUint16_2160) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test assignment operator from Value
TEST_F(IptcdatumTest_2160, AssignmentOperatorValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Value Assigned");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "Value Assigned");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_2160, SetValuePointer_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Set via pointer");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Set via pointer");
}

// Test setValue with nullptr clears value
TEST_F(IptcdatumTest_2160, SetValueNullPointer_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Initial");
    Iptcdatum datum(key, value.get());
    
    datum.setValue(static_cast<const Value*>(nullptr));
    // After setting to nullptr, getValue should return null or size/count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with string
TEST_F(IptcdatumTest_2160, SetValueString_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Initial");
    Iptcdatum datum(key, value.get());
    
    int result = datum.setValue("New String Value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "New String Value");
}

// Test key() method
TEST_F(IptcdatumTest_2160, KeyMethod_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test familyName()
TEST_F(IptcdatumTest_2160, FamilyName_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName()
TEST_F(IptcdatumTest_2160, GroupName_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName()
TEST_F(IptcdatumTest_2160, TagName_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag()
TEST_F(IptcdatumTest_2160, Tag_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Tag for Caption in Application2 should be a valid non-zero tag
    uint16_t tag = datum.tag();
    EXPECT_GT(tag, 0u);
}

// Test record() and recordName()
TEST_F(IptcdatumTest_2160, RecordNameAndRecord_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
    EXPECT_GT(datum.record(), 0u);
}

// Test typeId when no value set
TEST_F(IptcdatumTest_2160, TypeIdNoValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // When no value is set, typeId might return a default
    TypeId tid = datum.typeId();
    // Just ensure it doesn't crash - the type is implementation-defined
    (void)tid;
}

// Test typeId with value
TEST_F(IptcdatumTest_2160, TypeIdWithValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.typeId(), string);
}

// Test typeName with value
TEST_F(IptcdatumTest_2160, TypeNameWithValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test");
    Iptcdatum datum(key, value.get());
    
    EXPECT_NE(datum.typeName(), nullptr);
}

// Test count and size with value
TEST_F(IptcdatumTest_2160, CountAndSizeWithValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Hello");
    Iptcdatum datum(key, value.get());
    
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test count and size without value
TEST_F(IptcdatumTest_2160, CountAndSizeWithoutValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test toString with index
TEST_F(IptcdatumTest_2160, ToStringWithIndex_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Indexed String");
    Iptcdatum datum(key, value.get());
    
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Indexed String");
}

// Test toInt64
TEST_F(IptcdatumTest_2160, ToInt64_2160) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    auto value = Value::create(unsignedShort);
    value->read("100");
    Iptcdatum datum(key, value.get());
    
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, 100);
}

// Test toFloat
TEST_F(IptcdatumTest_2160, ToFloat_2160) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    auto value = Value::create(unsignedShort);
    value->read("50");
    Iptcdatum datum(key, value.get());
    
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 50.0f);
}

// Test getValue
TEST_F(IptcdatumTest_2160, GetValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Get Value Test");
    Iptcdatum datum(key, value.get());
    
    auto retrieved = datum.getValue();
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "Get Value Test");
}

// Test getValue when no value is set
TEST_F(IptcdatumTest_2160, GetValueNoValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto retrieved = datum.getValue();
    EXPECT_EQ(retrieved, nullptr);
}

// Test write to ostream
TEST_F(IptcdatumTest_2160, WriteToStream_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Stream Test");
    Iptcdatum datum(key, value.get());
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(IptcdatumTest_2160, CopyToBuffer_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Buffer Test");
    Iptcdatum datum(key, value.get());
    
    std::vector<byte> buf(datum.size());
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test tagLabel
TEST_F(IptcdatumTest_2160, TagLabel_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // Label should be non-empty for a known tag
    EXPECT_FALSE(label.empty());
}

// Test with Envelope record
TEST_F(IptcdatumTest_2160, EnvelopeRecord_2160) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    auto value = Value::create(unsignedShort);
    value->read("4");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_EQ(datum.toInt64(0), 4);
}

// Test construction with tag/record based IptcKey
TEST_F(IptcdatumTest_2160, ConstructWithTagRecordKey_2160) {
    IptcKey key(120, 2);  // tag 120 (Caption) in record 2 (Application2)
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tag(), 120u);
    EXPECT_EQ(datum.record(), 2u);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test Keywords tag (repeatable field)
TEST_F(IptcdatumTest_2160, KeywordsTag_2160) {
    IptcKey key("Iptc.Application2.Keywords");
    auto value = Value::create(string);
    value->read("keyword1");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "keyword1");
}

// Test self-assignment
TEST_F(IptcdatumTest_2160, SelfAssignment_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Self Assign");
    Iptcdatum datum(key, value.get());
    
    datum = datum;  // self-assignment
    EXPECT_EQ(datum.toString(), "Self Assign");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test empty string value
TEST_F(IptcdatumTest_2160, EmptyStringValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("");
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "");
}

// Test tagDesc
TEST_F(IptcdatumTest_2160, TagDesc_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // tagDesc should return some description string (may or may not be empty depending on dataset)
    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash
    (void)desc;
}

// Test typeSize
TEST_F(IptcdatumTest_2160, TypeSize_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("test");
    Iptcdatum datum(key, value.get());
    
    size_t ts = datum.typeSize();
    EXPECT_GT(ts, 0u);
}

// Test value() reference access
TEST_F(IptcdatumTest_2160, ValueReference_2160) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Reference Test");
    Iptcdatum datum(key, value.get());
    
    const Value& ref = datum.value();
    EXPECT_EQ(ref.toString(), "Reference Test");
    EXPECT_EQ(ref.typeId(), string);
}

// Test value() throws when no value set
TEST_F(IptcdatumTest_2160, ValueReferenceThrowsWhenNoValue_2160) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_THROW(datum.value(), Exiv2::Error);
}

// Test toRational
TEST_F(IptcdatumTest_2160, ToRational_2160) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    auto value = Value::create(unsignedShort);
    value->read("25");
    Iptcdatum datum(key, value.get());
    
    Rational r = datum.toRational(0);
    // The rational representation of 25 should have numerator 25 and denominator 1
    EXPECT_EQ(r.first, 25);
    EXPECT_EQ(r.second, 1);
}
