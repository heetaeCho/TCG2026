#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_689 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid IptcKey and null Value pointer
TEST_F(IptcdatumTest_689, ConstructWithKeyAndNullValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test construction with a valid IptcKey and a Value
TEST_F(IptcdatumTest_689, ConstructWithKeyAndValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello World");
    Iptcdatum datum(key, &val);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.toString(), "Hello World");
    EXPECT_EQ(datum.count(), 1u);
}

// Test copy constructor
TEST_F(IptcdatumTest_689, CopyConstructor_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test Copy");
    Iptcdatum original(key, &val);
    Iptcdatum copy(original);
    
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.familyName(), original.familyName());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_689, CopyAssignmentOperator_689) {
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("Original");
    Iptcdatum datum1(key1, &val1);
    
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Keyword");
    Iptcdatum datum2(key2, &val2);
    
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), datum1.toString());
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_689, AssignUint16_689) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    
    datum = static_cast<uint16_t>(42);
    EXPECT_EQ(datum.toString(), "42");
}

// Test assignment from string
TEST_F(IptcdatumTest_689, AssignString_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Assigned String");
    EXPECT_EQ(datum.toString(), "Assigned String");
}

// Test assignment from Value
TEST_F(IptcdatumTest_689, AssignValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue val("Value Assignment");
    datum = val;
    EXPECT_EQ(datum.toString(), "Value Assignment");
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_689, SetValueWithPointer_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    StringValue val("Set via pointer");
    datum.setValue(&val);
    EXPECT_EQ(datum.toString(), "Set via pointer");
}

// Test setValue with nullptr
TEST_F(IptcdatumTest_689, SetValueWithNullptr_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);
    
    datum.setValue(nullptr);
    // After setting null, count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with string
TEST_F(IptcdatumTest_689, SetValueWithString_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Initial");
    Iptcdatum datum(key, &val);
    
    int result = datum.setValue("Updated String");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Updated String");
}

// Test key() method
TEST_F(IptcdatumTest_689, KeyMethod_689) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test familyName
TEST_F(IptcdatumTest_689, FamilyName_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName
TEST_F(IptcdatumTest_689, GroupName_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName
TEST_F(IptcdatumTest_689, TagName_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test record() method
TEST_F(IptcdatumTest_689, RecordMethod_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // Application2 record is typically 2
    EXPECT_EQ(datum.record(), 2u);
}

// Test recordName() method
TEST_F(IptcdatumTest_689, RecordName_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag() method
TEST_F(IptcdatumTest_689, TagMethod_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // Caption tag number should be 120
    EXPECT_EQ(datum.tag(), 120u);
}

// Test typeId with no value set
TEST_F(IptcdatumTest_689, TypeIdWithNoValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // When no value, typeId might return a default
    TypeId tid = datum.typeId();
    // Just verify it doesn't crash; value depends on implementation
    (void)tid;
}

// Test typeId with a value set
TEST_F(IptcdatumTest_689, TypeIdWithValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    
    EXPECT_EQ(datum.typeId(), string);
}

// Test typeName
TEST_F(IptcdatumTest_689, TypeName_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    
    EXPECT_NE(datum.typeName(), nullptr);
}

// Test size and count with value
TEST_F(IptcdatumTest_689, SizeAndCountWithValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Hello");
    Iptcdatum datum(key, &val);
    
    EXPECT_GT(datum.size(), 0u);
    EXPECT_GT(datum.count(), 0u);
}

// Test size and count without value
TEST_F(IptcdatumTest_689, SizeAndCountWithoutValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.size(), 0u);
    EXPECT_EQ(datum.count(), 0u);
}

// Test toString with index
TEST_F(IptcdatumTest_689, ToStringWithIndex_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test String");
    Iptcdatum datum(key, &val);
    
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Test String");
}

// Test toInt64
TEST_F(IptcdatumTest_689, ToInt64_689) {
    IptcKey key("Iptc.Application2.Urgency");
    StringValue val("5");
    Iptcdatum datum(key, &val);
    
    // Conversion from string to int may or may not work depending on value type
    // This just tests it doesn't crash
    int64_t result = datum.toInt64(0);
    (void)result;
}

// Test toFloat
TEST_F(IptcdatumTest_689, ToFloat_689) {
    IptcKey key("Iptc.Application2.Urgency");
    StringValue val("3.14");
    Iptcdatum datum(key, &val);
    
    float result = datum.toFloat(0);
    (void)result;
}

// Test toRational
TEST_F(IptcdatumTest_689, ToRational_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("1/2");
    Iptcdatum datum(key, &val);
    
    Rational result = datum.toRational(0);
    (void)result;
}

// Test getValue
TEST_F(IptcdatumTest_689, GetValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test getValue");
    Iptcdatum datum(key, &val);
    
    auto v = datum.getValue();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->toString(), "Test getValue");
}

// Test value() reference
TEST_F(IptcdatumTest_689, ValueReference_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Test value ref");
    Iptcdatum datum(key, &val);
    
    const Value& ref = datum.value();
    EXPECT_EQ(ref.toString(), "Test value ref");
}

// Test write to ostream
TEST_F(IptcdatumTest_689, WriteToOstream_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Write test");
    Iptcdatum datum(key, &val);
    
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(IptcdatumTest_689, CopyToBuffer_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Copy test");
    Iptcdatum datum(key, &val);
    
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    
    std::vector<byte> buf(sz + 10, 0);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(IptcdatumTest_689, TagLabel_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    // Known tag should have a label
    EXPECT_FALSE(label.empty());
}

// Test tagDesc
TEST_F(IptcdatumTest_689, TagDesc_689) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // tagDesc may or may not be empty; just ensure no crash
    std::string desc = datum.tagDesc();
    (void)desc;
}

// Test typeSize
TEST_F(IptcdatumTest_689, TypeSize_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("test");
    Iptcdatum datum(key, &val);
    
    size_t ts = datum.typeSize();
    EXPECT_GT(ts, 0u);
}

// Test Envelope record
TEST_F(IptcdatumTest_689, EnvelopeRecord_689) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.record(), 1u);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test Keywords tag
TEST_F(IptcdatumTest_689, KeywordsTag_689) {
    IptcKey key("Iptc.Application2.Keywords");
    StringValue val("keyword1");
    Iptcdatum datum(key, &val);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Keywords");
    EXPECT_EQ(datum.toString(), "keyword1");
    EXPECT_EQ(datum.tag(), 25u);
}

// Test reassigning value replaces old value
TEST_F(IptcdatumTest_689, ReassignValueReplacesOld_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val1("First");
    Iptcdatum datum(key, &val1);
    EXPECT_EQ(datum.toString(), "First");
    
    StringValue val2("Second");
    datum = val2;
    EXPECT_EQ(datum.toString(), "Second");
}

// Test multiple setValue calls
TEST_F(IptcdatumTest_689, MultipleSetValueCalls_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("A");
    Iptcdatum datum(key, &val);
    
    datum.setValue("B");
    EXPECT_EQ(datum.toString(), "B");
    
    datum.setValue("C");
    EXPECT_EQ(datum.toString(), "C");
}

// Test empty string value
TEST_F(IptcdatumTest_689, EmptyStringValue_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("");
    Iptcdatum datum(key, &val);
    
    EXPECT_EQ(datum.toString(), "");
}

// Test self-assignment
TEST_F(IptcdatumTest_689, SelfAssignment_689) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Self");
    Iptcdatum datum(key, &val);
    
    datum = datum;  // self-assignment
    EXPECT_EQ(datum.toString(), "Self");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test IptcData container operations
TEST_F(IptcdatumTest_689, IptcDataAddAndFind_689) {
    IptcData iptcData;
    
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Container Test");
    
    Iptcdatum datum(key, &val);
    iptcData.add(datum);
    
    EXPECT_FALSE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 1u);
    
    auto it = iptcData.findKey(key);
    ASSERT_NE(it, iptcData.end());
    EXPECT_EQ(it->toString(), "Container Test");
}

// Test IptcData with multiple entries
TEST_F(IptcdatumTest_689, IptcDataMultipleEntries_689) {
    IptcData iptcData;
    
    IptcKey key1("Iptc.Application2.Caption");
    StringValue val1("Caption text");
    iptcData.add(Iptcdatum(key1, &val1));
    
    IptcKey key2("Iptc.Application2.Keywords");
    StringValue val2("Keyword1");
    iptcData.add(Iptcdatum(key2, &val2));
    
    EXPECT_EQ(iptcData.count(), 2u);
}

// Test IptcData erase
TEST_F(IptcdatumTest_689, IptcDataErase_689) {
    IptcData iptcData;
    
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("To be erased");
    iptcData.add(Iptcdatum(key, &val));
    
    EXPECT_EQ(iptcData.count(), 1u);
    
    auto it = iptcData.findKey(key);
    ASSERT_NE(it, iptcData.end());
    iptcData.erase(it);
    
    EXPECT_TRUE(iptcData.empty());
}

// Test IptcData clear
TEST_F(IptcdatumTest_689, IptcDataClear_689) {
    IptcData iptcData;
    
    IptcKey key("Iptc.Application2.Caption");
    StringValue val("Clear me");
    iptcData.add(Iptcdatum(key, &val));
    
    iptcData.clear();
    EXPECT_TRUE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 0u);
}
