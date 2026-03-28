#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_676 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with a valid IptcKey and null value
TEST_F(IptcdatumTest_676, ConstructWithKeyAndNullValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test construction with a valid IptcKey and check family name
TEST_F(IptcdatumTest_676, FamilyNameIsIptc_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_STREQ(datum.familyName(), "Iptc");
}

// Test groupName returns the record name
TEST_F(IptcdatumTest_676, GroupNameReturnsRecordName_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.groupName(), "Application2");
}

// Test tagName returns the correct tag name
TEST_F(IptcdatumTest_676, TagNameReturnsCorrectTag_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.tagName(), "Caption");
}

// Test recordName returns the record name
TEST_F(IptcdatumTest_676, RecordNameReturnsApplication2_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.recordName(), "Application2");
}

// Test tag() returns a valid tag number
TEST_F(IptcdatumTest_676, TagReturnsValidNumber_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Caption is tag 120 in Application2
    EXPECT_EQ(datum.tag(), 120);
}

// Test record() returns the correct record number
TEST_F(IptcdatumTest_676, RecordReturnsCorrectNumber_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    // Application2 is record 2
    EXPECT_EQ(datum.record(), 2);
}

// Test copy constructor
TEST_F(IptcdatumTest_676, CopyConstructor_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test caption");

    Iptcdatum copy(datum);
    EXPECT_EQ(copy.key(), datum.key());
    EXPECT_EQ(copy.toString(), "Test caption");
}

// Test assignment operator from another Iptcdatum
TEST_F(IptcdatumTest_676, AssignmentOperatorFromIptcdatum_676) {
    IptcKey key1("Iptc.Application2.Caption");
    Iptcdatum datum1(key1, nullptr);
    datum1 = std::string("Original");

    IptcKey key2("Iptc.Application2.Keywords");
    Iptcdatum datum2(key2, nullptr);
    datum2 = datum1;

    EXPECT_EQ(datum2.toString(), "Original");
}

// Test assignment from string
TEST_F(IptcdatumTest_676, AssignStringValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello World");
    EXPECT_EQ(datum.toString(), "Hello World");
}

// Test assignment from uint16_t
TEST_F(IptcdatumTest_676, AssignUint16Value_676) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    uint16_t val = 5;
    datum = val;
    EXPECT_EQ(datum.toString(), "5");
}

// Test setValue with string
TEST_F(IptcdatumTest_676, SetValueString_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    int result = datum.setValue("Test value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Test value");
}

// Test setValue with Value pointer (nullptr)
TEST_F(IptcdatumTest_676, SetValueNullptr_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Something");
    datum.setValue(nullptr);
    // After setting nullptr value, count should be 0
    EXPECT_EQ(datum.count(), 0u);
}

// Test setValue with actual Value
TEST_F(IptcdatumTest_676, SetValueWithValueObject_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue sv("Test");
    datum = sv;
    EXPECT_EQ(datum.toString(), "Test");
}

// Test count with no value set
TEST_F(IptcdatumTest_676, CountWithNoValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.count(), 0u);
}

// Test count with a value set
TEST_F(IptcdatumTest_676, CountWithValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Some text");
    EXPECT_GT(datum.count(), 0u);
}

// Test size with no value
TEST_F(IptcdatumTest_676, SizeWithNoValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.size(), 0u);
}

// Test size with a value
TEST_F(IptcdatumTest_676, SizeWithValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test typeSize returns the size of the type
TEST_F(IptcdatumTest_676, TypeSizeConsistentWithTypeId_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    TypeId tid = datum.typeId();
    size_t expectedSize = TypeInfo::typeSize(tid);
    EXPECT_EQ(datum.typeSize(), expectedSize);
}

// Test typeName returns non-null string
TEST_F(IptcdatumTest_676, TypeNameNotNull_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    const char* tn = datum.typeName();
    EXPECT_NE(tn, nullptr);
}

// Test typeId with string value
TEST_F(IptcdatumTest_676, TypeIdWithStringValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Test");
    TypeId tid = datum.typeId();
    EXPECT_EQ(tid, string);
}

// Test toString with index
TEST_F(IptcdatumTest_676, ToStringWithIndex_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Hello");
    std::string result = datum.toString(0);
    EXPECT_EQ(result, "Hello");
}

// Test write to ostream
TEST_F(IptcdatumTest_676, WriteToOstream_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Stream test");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test getValue returns a valid unique_ptr when value is set
TEST_F(IptcdatumTest_676, GetValueReturnsValidPtr_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Value test");
    auto val = datum.getValue();
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "Value test");
}

// Test getValue returns nullptr when no value is set
TEST_F(IptcdatumTest_676, GetValueReturnsNullWhenNoValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    auto val = datum.getValue();
    // When no value is set, getValue should return nullptr
    EXPECT_EQ(val, nullptr);
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(IptcdatumTest_676, TagLabelNotEmpty_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test toInt64 with a numeric string value
TEST_F(IptcdatumTest_676, ToInt64WithNumericValue_676) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("42");
    int64_t val = datum.toInt64(0);
    EXPECT_EQ(val, 42);
}

// Test toFloat with a numeric string value
TEST_F(IptcdatumTest_676, ToFloatWithNumericValue_676) {
    IptcKey key("Iptc.Application2.Urgency");
    Iptcdatum datum(key, nullptr);
    datum = std::string("3");
    float val = datum.toFloat(0);
    EXPECT_FLOAT_EQ(val, 3.0f);
}

// Test with Envelope record
TEST_F(IptcdatumTest_676, EnvelopeRecord_676) {
    IptcKey key("Iptc.Envelope.CharacterSet");
    Iptcdatum datum(key, nullptr);
    EXPECT_EQ(datum.record(), 1);
    EXPECT_EQ(datum.recordName(), "Envelope");
    EXPECT_EQ(datum.familyName(), std::string("Iptc"));
}

// Test key format
TEST_F(IptcdatumTest_676, KeyFormat_676) {
    IptcKey key("Iptc.Application2.Keywords");
    Iptcdatum datum(key, nullptr);
    std::string k = datum.key();
    EXPECT_EQ(k, "Iptc.Application2.Keywords");
}

// Test copy to buffer
TEST_F(IptcdatumTest_676, CopyToBuffer_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Buf");
    byte buf[256] = {0};
    size_t copied = datum.copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test assignment from Value object
TEST_F(IptcdatumTest_676, AssignFromValueObject_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    StringValue sv("From Value");
    datum.setValue(nullptr);
    datum = sv;
    EXPECT_EQ(datum.toString(), "From Value");
}

// Test empty string assignment
TEST_F(IptcdatumTest_676, EmptyStringAssignment_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("");
    EXPECT_EQ(datum.toString(), "");
}

// Test self-assignment
TEST_F(IptcdatumTest_676, SelfAssignment_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum = std::string("Self");
    datum = datum;
    EXPECT_EQ(datum.toString(), "Self");
}

// Test multiple setValue calls
TEST_F(IptcdatumTest_676, MultipleSetValue_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
    datum.setValue("Third");
    EXPECT_EQ(datum.toString(), "Third");
}

// Test construction with a Value pointer
TEST_F(IptcdatumTest_676, ConstructWithValuePointer_676) {
    IptcKey key("Iptc.Application2.Caption");
    StringValue sv("Initial");
    Iptcdatum datum(key, &sv);
    EXPECT_EQ(datum.toString(), "Initial");
}

// Test tagDesc returns a string (may or may not be empty)
TEST_F(IptcdatumTest_676, TagDescReturnsString_676) {
    IptcKey key("Iptc.Application2.Caption");
    Iptcdatum datum(key, nullptr);
    std::string desc = datum.tagDesc();
    // Just verify it doesn't crash; description may or may not be empty
    EXPECT_NO_THROW(datum.tagDesc());
}
