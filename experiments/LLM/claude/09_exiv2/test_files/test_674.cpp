#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/properties.hpp>
#include <memory>
#include <sstream>
#include <string>

using namespace Exiv2;

class IptcdatumTest_674 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a key and no value (nullptr)
TEST_F(IptcdatumTest_674, ConstructWithKeyAndNullValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test typeId returns invalidTypeId when no value is set
TEST_F(IptcdatumTest_674, TypeIdWithNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test construction with a key and a valid value
TEST_F(IptcdatumTest_674, ConstructWithKeyAndValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Hello World");
    Iptcdatum datum(key, value.get());

    EXPECT_EQ(datum.typeId(), string);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test copy constructor
TEST_F(IptcdatumTest_674, CopyConstructor_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test Copy");
    Iptcdatum original(key, value.get());

    Iptcdatum copy(original);

    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.typeId(), original.typeId());
    EXPECT_EQ(copy.toString(), original.toString());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.record(), original.record());
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_674, AssignmentOperatorIptcdatum_674) {
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
    EXPECT_EQ(datum1.toString(), "Second");
}

// Test assignment operator from uint16_t
TEST_F(IptcdatumTest_674, AssignmentOperatorUint16_674) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);

    uint16_t val = 42;
    datum = val;

    EXPECT_EQ(datum.toInt64(0), 42);
}

// Test assignment operator from string
TEST_F(IptcdatumTest_674, AssignmentOperatorString_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string val = "Test String";
    datum = val;

    EXPECT_EQ(datum.toString(), "Test String");
}

// Test assignment operator from Value
TEST_F(IptcdatumTest_674, AssignmentOperatorValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    auto value = Value::create(string);
    value->read("Value Assign");
    datum = *value;

    EXPECT_EQ(datum.toString(), "Value Assign");
    EXPECT_EQ(datum.typeId(), string);
}

// Test setValue with Value pointer
TEST_F(IptcdatumTest_674, SetValuePointer_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.typeId(), invalidTypeId);

    auto value = Value::create(string);
    value->read("Set via pointer");
    datum.setValue(value.get());

    EXPECT_EQ(datum.typeId(), string);
    EXPECT_EQ(datum.toString(), "Set via pointer");
}

// Test setValue with nullptr resets value
TEST_F(IptcdatumTest_674, SetValueNullptr_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Initial");
    Iptcdatum datum(key, value.get());

    EXPECT_EQ(datum.typeId(), string);

    datum.setValue(nullptr);

    EXPECT_EQ(datum.typeId(), invalidTypeId);
}

// Test setValue with string
TEST_F(IptcdatumTest_674, SetValueString_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    int result = datum.setValue("Hello from string");

    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello from string");
}

// Test key() method
TEST_F(IptcdatumTest_674, KeyMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test recordName() method
TEST_F(IptcdatumTest_674, RecordNameMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test record() method
TEST_F(IptcdatumTest_674, RecordMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Application2 record number is 2
    EXPECT_EQ(datum.record(), 2);
}

// Test familyName() method
TEST_F(IptcdatumTest_674, FamilyNameMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName() method
TEST_F(IptcdatumTest_674, GroupNameMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName() method
TEST_F(IptcdatumTest_674, TagNameMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test tag() method
TEST_F(IptcdatumTest_674, TagMethod_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Caption tag number is 120
    EXPECT_EQ(datum.tag(), 120);
}

// Test count() with no value
TEST_F(IptcdatumTest_674, CountNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.count(), 0u);
}

// Test count() with a value
TEST_F(IptcdatumTest_674, CountWithValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test");
    Iptcdatum datum(key, value.get());

    EXPECT_GT(datum.count(), 0u);
}

// Test size() with no value
TEST_F(IptcdatumTest_674, SizeNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.size(), 0u);
}

// Test size() with a value
TEST_F(IptcdatumTest_674, SizeWithValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Test");
    Iptcdatum datum(key, value.get());

    EXPECT_GT(datum.size(), 0u);
}

// Test toString() with no value
TEST_F(IptcdatumTest_674, ToStringNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.toString(), "");
}

// Test toString(n) with a value
TEST_F(IptcdatumTest_674, ToStringWithIndex_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Hello");
    Iptcdatum datum(key, value.get());

    EXPECT_EQ(datum.toString(0), "Hello");
}

// Test getValue() returns valid unique_ptr when value is set
TEST_F(IptcdatumTest_674, GetValueWithValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("GetValue Test");
    Iptcdatum datum(key, value.get());

    auto retrieved = datum.getValue();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toString(), "GetValue Test");
}

// Test getValue() returns nullptr when no value is set
TEST_F(IptcdatumTest_674, GetValueWithNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    auto retrieved = datum.getValue();
    EXPECT_EQ(retrieved, nullptr);
}

// Test value() throws when no value is set
TEST_F(IptcdatumTest_674, ValueReferenceThrowsWhenNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    EXPECT_THROW(datum.value(), Error);
}

// Test value() returns reference when value is set
TEST_F(IptcdatumTest_674, ValueReferenceWithValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Reference Test");
    Iptcdatum datum(key, value.get());

    EXPECT_NO_THROW({
        const Value& ref = datum.value();
        EXPECT_EQ(ref.toString(), "Reference Test");
    });
}

// Test typeName with no value
TEST_F(IptcdatumTest_674, TypeNameNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // When no value is set, typeName might return nullptr or empty
    const char* tn = datum.typeName();
    // invalidTypeId has a corresponding type name
    // Just check it doesn't crash
    (void)tn;
}

// Test typeName with value set
TEST_F(IptcdatumTest_674, TypeNameWithValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Type Name Test");
    Iptcdatum datum(key, value.get());

    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_STREQ(tn, "String");
}

// Test write to ostream
TEST_F(IptcdatumTest_674, WriteToStream_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Stream Test");
    Iptcdatum datum(key, value.get());

    std::ostringstream os;
    datum.write(os, nullptr);

    EXPECT_FALSE(os.str().empty());
}

// Test copy to buffer
TEST_F(IptcdatumTest_674, CopyToBuffer_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Buffer");
    Iptcdatum datum(key, value.get());

    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);

    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test with Envelope record
TEST_F(IptcdatumTest_674, EnvelopeRecord_674) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);

    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.groupName(), "Envelope");
}

// Test with Keywords tag (known multi-value tag)
TEST_F(IptcdatumTest_674, KeywordsTag_674) {
    IptcKey key("Iptc.Application2.Keywords");
    auto value = Value::create(string);
    value->read("keyword1");
    Iptcdatum datum(key, value.get());

    EXPECT_EQ(datum.tagName(), "Keywords");
    EXPECT_EQ(datum.toString(), "keyword1");
}

// Test tagLabel returns non-empty string for known tags
TEST_F(IptcdatumTest_674, TagLabelKnownTag_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toInt64 with numeric value
TEST_F(IptcdatumTest_674, ToInt64WithNumericValue_674) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("5");

    EXPECT_EQ(datum.toInt64(0), 5);
}

// Test toFloat with numeric value
TEST_F(IptcdatumTest_674, ToFloatWithNumericValue_674) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("3");

    EXPECT_FLOAT_EQ(datum.toFloat(0), 3.0f);
}

// Test self-assignment
TEST_F(IptcdatumTest_674, SelfAssignment_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Self");
    Iptcdatum datum(key, value.get());

    datum = datum;

    EXPECT_EQ(datum.toString(), "Self");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test typeSize with no value
TEST_F(IptcdatumTest_674, TypeSizeNoValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    // Should not crash; typeSize for invalidTypeId
    size_t ts = datum.typeSize();
    (void)ts;
}

// Test with unsignedShort type value
TEST_F(IptcdatumTest_674, UnsignedShortValue_674) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(unsignedShort);
    value->read("12345");
    Iptcdatum datum(key, value.get());

    EXPECT_EQ(datum.typeId(), unsignedShort);
    EXPECT_EQ(datum.toInt64(0), 12345);
}

// Test empty string assignment
TEST_F(IptcdatumTest_674, EmptyStringAssignment_674) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);

    datum = std::string("");

    EXPECT_EQ(datum.toString(), "");
}
