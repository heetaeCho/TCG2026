#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/properties.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

// Helper to create a valid IptcKey
static IptcKey makeKey(uint16_t tag = 0x0005, uint16_t record = 2) {
    // Use a well-known IPTC key string
    return IptcKey("Iptc.Application2.ObjectName");
}

class IptcdatumTest_680 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: Default construction with key and null value pointer
TEST_F(IptcdatumTest_680, ConstructWithNullValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    // When no value is set, toString should return empty string
    EXPECT_EQ(datum.toString(), "");
    EXPECT_EQ(datum.toString(0), "");
}

// Test: key() returns the correct key string
TEST_F(IptcdatumTest_680, KeyReturnsCorrectString_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.ObjectName");
}

// Test: familyName() returns "Iptc"
TEST_F(IptcdatumTest_680, FamilyNameReturnsIptc_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test: groupName() returns the record name
TEST_F(IptcdatumTest_680, GroupNameReturnsRecordName_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test: tagName() returns the tag name
TEST_F(IptcdatumTest_680, TagNameReturnsCorrectName_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.tagName(), "ObjectName");
}

// Test: recordName() returns the record name
TEST_F(IptcdatumTest_680, RecordNameReturnsCorrectName_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test: record() returns the correct record number
TEST_F(IptcdatumTest_680, RecordReturnsCorrectNumber_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 2);
}

// Test: tag() returns the correct tag number
TEST_F(IptcdatumTest_680, TagReturnsCorrectNumber_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.tag(), 5);
}

// Test: setValue with string sets the value correctly
TEST_F(IptcdatumTest_680, SetValueFromString_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    int result = datum.setValue("TestObjectName");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "TestObjectName");
}

// Test: operator= with string value
TEST_F(IptcdatumTest_680, AssignStringValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test: count() with no value set
TEST_F(IptcdatumTest_680, CountWithNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test: size() with no value set
TEST_F(IptcdatumTest_680, SizeWithNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test: count() after setting a value
TEST_F(IptcdatumTest_680, CountAfterSetValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("TestValue");
    EXPECT_GT(datum.count(), 0u);
}

// Test: size() after setting a value
TEST_F(IptcdatumTest_680, SizeAfterSetValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("TestValue");
    EXPECT_GT(datum.size(), 0u);
}

// Test: Copy constructor
TEST_F(IptcdatumTest_680, CopyConstructor_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);
    datum.setValue("CopyTest");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.toString(), "CopyTest");
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.tag(), datum.tag());
    EXPECT_EQ(copy.record(), datum.record());
}

// Test: Copy assignment operator
TEST_F(IptcdatumTest_680, CopyAssignment_680) {
    IptcKey key1("Iptc.Application2.ObjectName");
    Iptcdatum datum1(key1, nullptr);
    datum1.setValue("Original");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2.setValue("Other");

    datum2 = datum1;
    EXPECT_EQ(datum2.toString(), "Original");
    EXPECT_EQ(datum2.key(), datum1.key());
}

// Test: toString(n) with index 0 after setting value
TEST_F(IptcdatumTest_680, ToStringWithIndex_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("IndexedValue");
    EXPECT_EQ(datum.toString(0), "IndexedValue");
}

// Test: toString(n) with no value returns empty string
TEST_F(IptcdatumTest_680, ToStringWithIndexNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(0), "");
    EXPECT_EQ(datum.toString(1), "");
}

// Test: getValue() with no value set
TEST_F(IptcdatumTest_680, GetValueWithNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    auto val = datum.getValue();
    EXPECT_EQ(val.get(), nullptr);
}

// Test: getValue() with value set
TEST_F(IptcdatumTest_680, GetValueWithValueSet_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("SomeValue");
    auto val = datum.getValue();
    EXPECT_NE(val.get(), nullptr);
}

// Test: setValue with Value pointer (nullptr)
TEST_F(IptcdatumTest_680, SetValueWithNullPointer_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("InitialValue");
    EXPECT_NE(datum.toString(), "");

    datum.setValue(static_cast<const Value*>(nullptr));
    EXPECT_EQ(datum.toString(), "");
}

// Test: Assign with Value object
TEST_F(IptcdatumTest_680, AssignValueObject_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    auto value = Value::create(string);
    value->read("ValueObjectTest");
    datum = *value;

    EXPECT_EQ(datum.toString(), "ValueObjectTest");
}

// Test: write to ostream
TEST_F(IptcdatumTest_680, WriteToOstream_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("WriteTest");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: typeId with no value
TEST_F(IptcdatumTest_680, TypeIdNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    // Without a value, typeId behavior is implementation-defined but should not crash
    TypeId tid = datum.typeId();
    (void)tid; // Just ensure it doesn't crash
}

// Test: typeId after setting string value
TEST_F(IptcdatumTest_680, TypeIdAfterSetStringValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("TypeTest");
    TypeId tid = datum.typeId();
    EXPECT_NE(tid, invalidTypeId);
}

// Test: tagLabel returns non-empty for known tags
TEST_F(IptcdatumTest_680, TagLabelForKnownTag_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: Construction with a Value pointer
TEST_F(IptcdatumTest_680, ConstructWithValuePointer_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    auto value = Value::create(string);
    value->read("ConstructedValue");

    Iptcdatum datum(key, value.get());
    EXPECT_EQ(datum.toString(), "ConstructedValue");
}

// Test: Assign uint16_t value
TEST_F(IptcdatumTest_680, AssignUint16Value_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum = static_cast<uint16_t>(42);
    // The datum should have a value now
    EXPECT_NE(datum.toString(), "");
}

// Test: toInt64 with no value
TEST_F(IptcdatumTest_680, ToInt64NoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    // Should handle gracefully
    int64_t val = datum.toInt64(0);
    (void)val; // Just ensure no crash
}

// Test: toFloat with no value
TEST_F(IptcdatumTest_680, ToFloatNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    float val = datum.toFloat(0);
    (void)val; // Just ensure no crash
}

// Test: toRational with no value
TEST_F(IptcdatumTest_680, ToRationalNoValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    Rational val = datum.toRational(0);
    (void)val; // Just ensure no crash
}

// Test: Different IPTC keys - Envelope record
TEST_F(IptcdatumTest_680, EnvelopeRecordKey_680) {
    IptcKey key("Iptc.Envelope.ModelVersion");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.groupName(), "Envelope");
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test: Keywords tag
TEST_F(IptcdatumTest_680, KeywordsTag_680) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);

    datum.setValue("keyword1");
    EXPECT_EQ(datum.toString(), "keyword1");
    EXPECT_EQ(datum.tagName(), "Keywords");
}

// Test: copy to buffer after setting value
TEST_F(IptcdatumTest_680, CopyToBuffer_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("BufferTest");
    size_t sz = datum.size();
    EXPECT_GT(sz, 0u);

    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test: Empty string value
TEST_F(IptcdatumTest_680, EmptyStringValue_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("");
    EXPECT_EQ(datum.toString(), "");
}

// Test: Multiple setValue calls overwrite
TEST_F(IptcdatumTest_680, MultipleSetValueOverwrites_680) {
    IptcKey key("Iptc.Application2.ObjectName");
    Iptcdatum datum(key, nullptr);

    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");

    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}
