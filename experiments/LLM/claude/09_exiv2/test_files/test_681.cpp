#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <string>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_681 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructing an Iptcdatum with a valid IptcKey and no value
TEST_F(IptcdatumTest_681, ConstructWithKeyNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
    EXPECT_EQ(datum.groupName(), "Application2");
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test: toInt64 returns -1 when no value is set
TEST_F(IptcdatumTest_681, ToInt64ReturnsNegativeOneWhenNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, -1);
}

// Test: toInt64 with different index returns -1 when no value
TEST_F(IptcdatumTest_681, ToInt64WithIndexReturnsNegativeOneWhenNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.toInt64(0), -1);
    EXPECT_EQ(datum.toInt64(1), -1);
    EXPECT_EQ(datum.toInt64(100), -1);
}

// Test: Setting a string value and reading it back
TEST_F(IptcdatumTest_681, SetValueString_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Test caption");
    EXPECT_EQ(datum.toString(), "Test caption");
}

// Test: Setting a uint16_t value
TEST_F(IptcdatumTest_681, SetValueUint16_681) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    
    uint16_t val = 42;
    datum = val;
    EXPECT_EQ(datum.toString(), "42");
}

// Test: setValue with string
TEST_F(IptcdatumTest_681, SetValueWithString_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    int result = datum.setValue("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test: Copy constructor
TEST_F(IptcdatumTest_681, CopyConstructor_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Copy me");
    
    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Copy me");
}

// Test: Assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_681, AssignmentOperator_681) {
    IptcKey key1("Iptc.Application2.Caption");
    IptcKey key2("Iptc.Application2.Headline");
    Iptcdatum datum1(key1, nullptr);
    Iptcdatum datum2(key2, nullptr);
    
    datum1 = std::string("Original");
    datum2 = datum1;
    
    EXPECT_EQ(datum2.key(), datum1.key());
    EXPECT_EQ(datum2.toString(), "Original");
}

// Test: record() and recordName()
TEST_F(IptcdatumTest_681, RecordInfo_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.recordName(), "Application2");
    EXPECT_EQ(datum.record(), 2);
}

// Test: tag() returns the correct tag number
TEST_F(IptcdatumTest_681, TagNumber_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    uint16_t tag = datum.tag();
    // Caption/Abstract is tag 120 in IPTC Application2
    EXPECT_EQ(tag, 120);
}

// Test: Setting a Value object directly
TEST_F(IptcdatumTest_681, SetValueObject_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Test Value");
    datum = *value;
    
    EXPECT_EQ(datum.toString(), "Test Value");
    EXPECT_EQ(datum.count(), 1u);
    EXPECT_GT(datum.size(), 0u);
}

// Test: setValue with Value pointer
TEST_F(IptcdatumTest_681, SetValuePointer_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    auto value = Value::create(string);
    value->read("Pointer value");
    datum.setValue(value.get());
    
    EXPECT_EQ(datum.toString(), "Pointer value");
}

// Test: setValue with nullptr
TEST_F(IptcdatumTest_681, SetValueNullPointer_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("Something");
    datum.setValue(nullptr);
    
    // After setting nullptr, toInt64 should return -1
    EXPECT_EQ(datum.toInt64(0), -1);
}

// Test: toInt64 with a numeric value set
TEST_F(IptcdatumTest_681, ToInt64WithNumericValue_681) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    
    datum.setValue("5");
    
    int64_t result = datum.toInt64(0);
    EXPECT_EQ(result, 5);
}

// Test: typeId when no value is set
TEST_F(IptcdatumTest_681, TypeIdNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    // When no value is set, typeId should still return something valid
    TypeId tid = datum.typeId();
    // Not asserting a specific value, just that it doesn't crash
    (void)tid;
}

// Test: getValue returns a valid unique_ptr when value is set
TEST_F(IptcdatumTest_681, GetValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Get this value");
    
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Get this value");
}

// Test: write to ostream
TEST_F(IptcdatumTest_681, WriteToStream_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Stream output");
    
    std::ostringstream os;
    datum.write(os, nullptr);
    
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test: copy to buffer
TEST_F(IptcdatumTest_681, CopyToBuffer_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Buffer data");
    
    size_t sz = datum.size();
    ASSERT_GT(sz, 0u);
    
    std::vector<byte> buf(sz);
    size_t copied = datum.copy(buf.data(), bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test: toFloat returns a value when value is set
TEST_F(IptcdatumTest_681, ToFloat_681) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum.setValue("7");
    
    float result = datum.toFloat(0);
    EXPECT_FLOAT_EQ(result, 7.0f);
}

// Test: tagLabel returns a non-empty string for known tags
TEST_F(IptcdatumTest_681, TagLabel_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: count and size when no value is set
TEST_F(IptcdatumTest_681, CountAndSizeNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.count(), 0u);
    EXPECT_EQ(datum.size(), 0u);
}

// Test: toString with index when no value is set
TEST_F(IptcdatumTest_681, ToStringNoValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    std::string result = datum.toString();
    EXPECT_EQ(result, "");
}

// Test: Envelope record
TEST_F(IptcdatumTest_681, EnvelopeRecord_681) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test: Constructing with a Value pointer
TEST_F(IptcdatumTest_681, ConstructWithValue_681) {
    IptcKey key("Iptc.Application2.Caption");
    auto value = Value::create(string);
    value->read("Initial value");
    
    Iptcdatum datum(key, value.get());
    
    EXPECT_EQ(datum.toString(), "Initial value");
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test: toRational when value is set
TEST_F(IptcdatumTest_681, ToRational_681) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum.setValue("3");
    
    Rational r = datum.toRational(0);
    // 3 as a rational should be 3/1
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 1);
}

// Test: typeName when value is set
TEST_F(IptcdatumTest_681, TypeName_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Some text");
    
    const char* tn = datum.typeName();
    ASSERT_NE(tn, nullptr);
    EXPECT_EQ(std::string(tn), "String");
}

// Test: Multiple assignments overwrite value
TEST_F(IptcdatumTest_681, MultipleAssignments_681) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    
    datum = std::string("First");
    EXPECT_EQ(datum.toString(), "First");
    
    datum = std::string("Second");
    EXPECT_EQ(datum.toString(), "Second");
    
    datum = std::string("Third");
    EXPECT_EQ(datum.toString(), "Third");
}
