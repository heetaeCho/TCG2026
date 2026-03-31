#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_675 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid IptcKey and null value
TEST_F(IptcdatumTest_675, ConstructWithKeyAndNullValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test copy constructor
TEST_F(IptcdatumTest_675, CopyConstructor_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test caption");
    
    Iptcdatum copy(datum);
    
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), datum.toString());
    EXPECT_EQ(copy.familyName(), datum.familyName());
    EXPECT_EQ(copy.groupName(), datum.groupName());
    EXPECT_EQ(copy.tagName(), datum.tagName());
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_675, AssignmentOperatorIptcdatum_675) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("Caption 1");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = std::string("Keyword 1");

    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum2.toString(), "Caption 1");
}

// Test assignment operator from string
TEST_F(IptcdatumTest_675, AssignmentOperatorString_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    
    EXPECT_EQ(datum.toString(), "Hello World");
    EXPECT_GT(datum.count(), 0u);
    EXPECT_GT(datum.size(), 0u);
}

// Test assignment operator from uint16_t
TEST_F(IptcdatumTest_675, AssignmentOperatorUint16_675) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 42;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test setValue with string
TEST_F(IptcdatumTest_675, SetValueString_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Test value");
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test value");
}

// Test key() returns correct key string
TEST_F(IptcdatumTest_675, KeyReturnsCorrectString_675) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test recordName()
TEST_F(IptcdatumTest_675, RecordName_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test record() returns correct record number
TEST_F(IptcdatumTest_675, Record_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // Application2 record is record 2
    EXPECT_EQ(datum.record(), 2u);
}

// Test familyName()
TEST_F(IptcdatumTest_675, FamilyName_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName()
TEST_F(IptcdatumTest_675, GroupName_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName()
TEST_F(IptcdatumTest_675, TagName_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag() returns correct tag number
TEST_F(IptcdatumTest_675, Tag_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // Caption tag in Application2 record
    EXPECT_EQ(datum.tag(), 120u);
}

// Test typeName() returns non-null for datum with value
TEST_F(IptcdatumTest_675, TypeName_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test typeId() for a datum with a string value
TEST_F(IptcdatumTest_675, TypeId_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    
    TypeId tid = datum.typeId();
    // Should be a valid type id
    EXPECT_NE(tid, invalidTypeId);
}

// Test typeSize()
TEST_F(IptcdatumTest_675, TypeSize_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    
    size_t ts = datum.typeSize();
    EXPECT_GT(ts, 0u);
}

// Test count() with string value
TEST_F(IptcdatumTest_675, CountWithStringValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    
    EXPECT_GT(datum.count(), 0u);
}

// Test size() with string value
TEST_F(IptcdatumTest_675, SizeWithStringValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    
    EXPECT_GT(datum.size(), 0u);
}

// Test toString()
TEST_F(IptcdatumTest_675, ToString_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("My Caption");
    
    EXPECT_EQ(datum.toString(), "My Caption");
}

// Test toString(n)
TEST_F(IptcdatumTest_675, ToStringWithIndex_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("My Caption");
    
    std::string result = datum.toString(0);
    EXPECT_FALSE(result.empty());
}

// Test toInt64()
TEST_F(IptcdatumTest_675, ToInt64_675) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 100;
    datum = val;
    
    EXPECT_EQ(datum.toInt64(0), 100);
}

// Test toFloat()
TEST_F(IptcdatumTest_675, ToFloat_675) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 50;
    datum = val;
    
    EXPECT_FLOAT_EQ(datum.toFloat(0), 50.0f);
}

// Test getValue()
TEST_F(IptcdatumTest_675, GetValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test value");
    
    auto value = datum.getValue();
    EXPECT_NE(value, nullptr);
    EXPECT_EQ(value->toString(), "Test value");
}

// Test value() reference
TEST_F(IptcdatumTest_675, ValueReference_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test value");
    
    const Value& val = datum.value();
    EXPECT_EQ(val.toString(), "Test value");
}

// Test write to ostream
TEST_F(IptcdatumTest_675, WriteToOstream_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Caption text");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(IptcdatumTest_675, CopyToBuffer_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    
    size_t sz = datum.size();
    std::vector<byte> buf(sz + 10, 0);
    size_t copied = datum.copy(buf.data(), bigEndian);
    
    EXPECT_GT(copied, 0u);
}

// Test assignment with Value object
TEST_F(IptcdatumTest_675, AssignmentOperatorValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue strValue("Assigned from Value");
    datum = strValue;
    
    EXPECT_EQ(datum.toString(), "Assigned from Value");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_675, SetValueWithPointer_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto val = Value::create(string);
    val->read("Pointer value");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "Pointer value");
}

// Test setValue with nullptr
TEST_F(IptcdatumTest_675, SetValueWithNullptr_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Some value");
    
    datum.setValue(nullptr);
    // After setting to nullptr, count and size should be 0
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test tagLabel()
TEST_F(IptcdatumTest_675, TagLabel_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // Caption should have a descriptive label
    EXPECT_FALSE(label.empty());
}

// Test tagDesc()
TEST_F(IptcdatumTest_675, TagDesc_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string desc = datum.tagDesc();
    // May or may not be empty depending on the tag, but should not crash
}

// Test Envelope record
TEST_F(IptcdatumTest_675, EnvelopeRecord_675) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.record(), 1u);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test construction with a value pointer
TEST_F(IptcdatumTest_675, ConstructWithValue_675) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("TestKeyword");
    Iptcdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "TestKeyword");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
}

// Test empty string value
TEST_F(IptcdatumTest_675, EmptyStringValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    
    EXPECT_EQ(datum.toString(), "");
    EXPECT_EQ(datum.size(), 0u);
}

// Test that typeName returns the correct type name matching TypeInfo
TEST_F(IptcdatumTest_675, TypeNameConsistentWithTypeId_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    
    TypeId tid = datum.typeId();
    const char* tn = datum.typeName();
    const char* expected = TypeInfo::typeName(tid);
    
    if (tn && expected) {
        EXPECT_STREQ(tn, expected);
    }
}

// Test self-assignment
TEST_F(IptcdatumTest_675, SelfAssignment_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Self assign test");
    
    datum = datum;
    
    EXPECT_EQ(datum.toString(), "Self assign test");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test multiple setValue calls
TEST_F(IptcdatumTest_675, MultipleSetValue_675) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
    
    datum.setValue("Third");
    EXPECT_EQ(datum.toString(), "Third");
}
